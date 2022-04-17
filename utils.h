/*
 * Copyright (c) 2022 XXIV
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __C_UTILS_H__
#define __C_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char **names;
#ifdef _DIRENT_HAVE_D_TYPE
    unsigned char *types;
#endif
    int size;
} dir_read_t;

/**
 * Read a file
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* content = file_read("note.txt");
 *   printf("%s", content);
 *   free(content);
 *   return 0;
 * }
 * * *
 *
 * @param filename file name to read
 * @return dynamic string holds file content
 */
char *file_read(char *filename) {
    FILE *file;
    int ch;
    if ((file = fopen(filename, "r")) == NULL)
        return NULL;
    if (fseek(file, 0L, SEEK_END))
        return NULL;
    long size = ftell(file);
    if (fseek(file, 0L, SEEK_SET))
        return NULL;
    char *content = (char *) malloc((size + 1) * sizeof(char));
    if (content == NULL)
        return NULL;
    int i = 0;
    while ((ch = getc(file)) != EOF) {
        content[i] = (char) ch;
        i++;
    }
    if (fclose(file))
        return NULL;
    return content;
}

/**
 * Write a file
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include <string.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   char* content = "This is my note";
 *   file_write("note.txt", content, strlen(content));
 *   return 0;
 * }
 * * *
 *
 * @param filename file name to write
 * @param content content
 * @param length length of the content
 * @return 0 on success and non zero value on failure
 */
int file_write(char *filename, char *content, int length) {
    FILE *file;
    if ((file = fopen(filename, "w")) == NULL)
        return -1;
    for (int i = 0; i < length; i++) {
        fprintf(file, "%c", content[i]);
    }
    if (fclose(file))
        return -1;
    return 0;
}

/**
 * File size
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 *
 * int main()
 * {
 *   long size;
 *   file_size("note.txt", &size);
 *   printf("note.txt size: %ld", size);
 *   return 0;
 * }
 * * *
 *
 * @param filename file name
 * @param out a long type variable to store the size
 * @return 0 on success and non zero value on failure
 */
int file_size(char *filename, long *out) {
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL) {
        return -1;
    }
    if (fseek(file, 0L, SEEK_END))
        return -1;
    *out = ftell(file);
    if (fclose(file))
        return -1;
    return 0;
}

/**
 * Read directory
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 * 
 * int main() 
 * {
 *   dir_read_t dir;
 *   dir_read(&dir,".");
 *   for (int i = 0; i < dir.size; i++)
 *   {
 *     printf("%s: %u\n", dir.names[i], dir.types[i]);
 *   }
 *   dir_read_clean(&dir);
 *   return 0;
 * }
 * * *
 *
 * @param dir_read pointer to dir_read_t
 * @param dirname directory name
 * @return 0 on success and non zero value on failure
 */
int dir_read(dir_read_t *dir_read, char *dirname) {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(dirname)) == NULL) {
        return -1;
    }
    char **names = (char **) malloc(sizeof(char *));
    if (names == NULL) {
        return -1;
    }
#ifdef _DIRENT_HAVE_D_TYPE
    unsigned char *types = (unsigned char *) malloc(sizeof(unsigned char));
    if (types == NULL) {
        return -1;
    }
#endif
    int i = 0;
    int size = 1;
    while ((ent = readdir(dir)) != NULL) {
        names = (char **) realloc(names, size * sizeof(char *));
        if (names == NULL) {
            return -1;
        }
        names[i] = (char *) malloc((strlen(ent->d_name) + 1) * sizeof(char));
        if (names[i] == NULL) {
            return -1;
        }
        strncpy(names[i], ent->d_name, strlen(ent->d_name));
#ifdef _DIRENT_HAVE_D_TYPE
        types = (unsigned char*) realloc(types,size * sizeof(unsigned char));
            if (types == NULL)
            {
                return -1;
            }
          types[i] = ent->d_type;
#endif
        size++;
        i++;
    }
    dir_read->names = names;
#ifdef _DIRENT_HAVE_D_TYPE
    dir_read->types = types;
#endif
    dir_read->size = i;
    if (closedir(dir))
        return -1;
    return 0;
}

/**
 * function to free the memory after using dir_read
 *
 * @param dir_read pointer to dir_read
 */
void dir_read_clean(dir_read_t *dir_read) {
    if (dir_read != NULL) {
        if (dir_read->names != NULL) {
            for (int i = 0; i < dir_read->size; i++)
            {
                if (dir_read->names[i] != NULL)
                {
                    free(dir_read->names[i]);
                }
            }
            free(dir_read->names);
        }
#ifdef _DIRENT_HAVE_D_TYPE
        if (dir_read->types != NULL) {
            free(dir_read->types);
        }
#endif
    }
}

/**
 * String format like "sprintf" but it
 * returns the formatted string and it's
 * dynamically allocated
 *
 * Example:
 * * *
 * #include <stdio.h>
 * #include "utils.h"
 * 
 * int main() 
 * {
 *   char* str = string_format("Hello %s", "World");
 *   printf("%s\n", str);
 *   free(str);
 *   return 0;
 * }
 * * *
 *
 * @param format formatted string
 * @return dynamic string
 */
char* string_format(char *format, ...)
{
  va_list arg;
  int len;
  va_start (arg, format);
  
  len = vsnprintf(0, 0, format, arg);
  char* str = (char*) malloc((len + 1) * sizeof(char));
  if (str == NULL)
  {
    return NULL;
  }
  va_start (arg, format);
  vsnprintf(str, (len + 1), format, arg);
  va_end (arg);
  return str;
}

#ifdef __cplusplus
}
#endif

#endif // __C_UTILS_H__