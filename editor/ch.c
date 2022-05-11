#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "text/text.h"
#include "text/_text.h"
#include <string.h>

void change(text txt)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0)
    {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    char buff[MAXLINE] = "";

    strncpy(buff, txt->cursor->line->contents, strlen(txt->cursor->line->contents) - 1);

    int pos = txt->cursor->position - 1;

    sprintf(txt->cursor->line->contents, "%.*s%.*s\n", 
    (int)strlen(buff) - pos , buff + pos, pos, buff);

    txt->cursor->position = strlen(buff) - pos + 1;
}