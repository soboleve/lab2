/**
 * common.h -- прототипы функций реализации команд редактора
 * 
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef COMMON_H
#define COMMON_H

#include "text/text.h"

/* Декларирует неиспользуемый аргумент,
 * корректно подавляя предупреждение вида "unused parameter" */
#define UNUSED(x) (void)(x)

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt);

/**
 * Загружает содержимое указанного файла
 */
void load(text txt, const char *filename);

/**
 * Сохраняет содержимое в указанный файл, перезаписывая его
 */
void save(text txt, const char *filename);

/**
 * Перемещает курсор в указанную позицию.
 */
void mwcursor(text txt, int toIndex, int toPos);

/**
 * Выводит строки, содержащие цифры
 */
void showlineswithdigits(text txt);

/**
 * Обмен содержимого текущей строки до и после курсора
 */
void change(text txt);

/**
 * Перемещает первую строку в конец текста
 */
void c1n(text txt);

#endif
