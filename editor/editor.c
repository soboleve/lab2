/**
 * editor.c -- строковый текстовый редактор
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text/text.h"
#include "common.h"

#define MAXLINE 255

int main()
{
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;

    /* Создаем объект для представления текста */
    text txt = create_text();

    /* Цикл обработки команд */
    while (1)
    {
        printf("ed > ");

        /* Получаем команду */

        fgets(cmdline, MAXLINE, stdin);

        /* Извлекаем имя команды */
        if ((cmd = strtok(cmdline, " \n")) == NULL)
        {
            continue;
        }

        /* Распознаем поддерживаемую команду */

        /* Завершаем работу редактора */
        if (strcmp(cmd, "quit") == 0)
        {
            fprintf(stderr, "Bye!\n");
            break;
        }

        /* Загружаем содержимое файла, заданного параметром */
        if (strcmp(cmd, "load") == 0)
        {
            if ((arg = strtok(NULL, " \n")) == NULL)
            {
                fprintf(stderr, "Usage: load filename\n");
            }
            else
            {
                load(txt, arg);
            }
            continue;
        }

        /* Выводим текст */
        if (strcmp(cmd, "show") == 0)
        {
            show(txt);
            continue;
        }

        /* Сохраняем текст */
        if (strcmp(cmd, "save") == 0)
        {
            if ((arg = strtok(NULL, " \n")) == NULL)
            {
                fprintf(stderr, "Usage: save filename\n");
            }
            else
            {
                save(txt, arg);
            }
            continue;
        }

        /* Перемещаем кусор на строку l и позицию m*/
        if (strcmp(cmd, "mwcursor") == 0)
        {
            char *index = strtok(NULL, " \n"), *pos = strtok(NULL, " \n");
            if (index && pos)
                mwcursor(txt, atoi(index), atoi(pos));
            else
                printf("Usage: cursor pos\n");
            continue;
        }

        /* Выводим строки, содержащие цифры */
        if (strcmp(cmd, "showlineswithdigits") == 0)
        {
            showlineswithdigits(txt);
            continue;
        }

        /* Обмен содержимого текущей строки до и после курсора */
        if (strcmp(cmd, "ch") == 0)
        {
            change(txt);
            continue;
        }

        /* Перемещение первой строки в конец файла */
        if (strcmp(cmd, "c1n") == 0)
        {
            c1n(txt);
            continue;
        }

        /* Если команда не известна */
        fprintf(stderr, "Unknown command: %s\n", cmd);
    }

    return 0;
}
