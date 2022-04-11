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

#ifdef __cplusplus
extern "C" {
#endif

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
char* file_read(char* filename)
{
    FILE* file;
    int ch;
    if ((file = fopen(filename,"r")) == NULL)
        return NULL;
    if (fseek(file, 0L, SEEK_END))
        return NULL;
    long size = ftell(file);
    if (fseek(file, 0L, SEEK_SET))
        return NULL;
    char* content = (char*) malloc((size + 1) * sizeof(char));
    if (content == NULL)
        return NULL;
    int i = 0;
    while ((ch = getc(file)) != EOF)
    {
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
int file_write(char* filename,char* content,int length)
{
    FILE* file;
    if ((file = fopen(filename,"w")) == NULL)
        return -1;
    for (int i = 0; i < length; i++)
    {
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
int file_size(char* filename, long* out)
{
    FILE* file;
    if ((file = fopen(filename,"r")) == NULL)
    {
        return -1;
    }
    if (fseek(file, 0L, SEEK_END))
        return -1;
    *out = ftell(file);
    if (fclose(file))
        return -1;
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // __C_UTILS_H__