#include <stdio.h>
#include "text.h"
#include "common.h"
#include "assert.h"

static void write_line_to_file(int index, char *contents, int cursor, void *data);

void save(text txt, const char *filename)
{
    FILE *file;

    if ((file = fopen(filename, "w")) == NULL)
    {
        printf("The file %s cannot be created\n", filename);
        return;
    }
    process_forward(txt, write_line_to_file, file);

    fclose(file);
}

static void write_line_to_file(int index, char *contents, int cursor, void *data)
{
    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(cursor);

    /* Запись строки в файл*/
    fputs(contents, (FILE*)data);
}
