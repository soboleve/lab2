
#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "text.h"
#include "string.h"
#include "ctype.h"

static void show_line_with_digits(int index, char *contents, int cursor, void *data);

void showlineswithdigits(text txt)
{
    process_forward(txt, show_line_with_digits, NULL);
}

static void show_line_with_digits(int index, char *contents, int cursor, void *data)
{
    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);

    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(data);

    if (!strpbrk(contents, "0123456789"))
        return;

    if (cursor != -1)
        printf("%.*s|%s", cursor - 1, contents, contents + cursor - 1);
    else
        printf("%s", contents);
}
