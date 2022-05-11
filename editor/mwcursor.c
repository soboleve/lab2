#include "text/_text.h"

void mwcursor(text txt, int toIndex, int toPos)
{
     /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0)
    {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    node *p = txt->begin;

    int index = 1;

    while (p != txt->end && index++ != toIndex)
    {
        p = p->next;

        if (p == txt->end && index != toIndex)
            return;
    }

    txt->cursor->line = p;
    txt->cursor->position = toPos;
}
