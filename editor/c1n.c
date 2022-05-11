#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "text.h"
#include <string.h>
#include "_text.h"

void c1n(text txt)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0)
    {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    char buff[MAXLINE];
    strcpy(buff, txt->begin->contents);

    append_line(txt, buff);

    node *next = txt->begin->next;

    txt->begin = next;
}
