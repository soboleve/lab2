#ifndef TESTS_H
#define TESTS_H

#include <gtest/gtest.h>
#include <string>
#include <fstream>

using namespace std;

extern "C"
{
#include <../editor/text/text.h>
#include <../editor/text/_text.h>
#include "../editor/common.h"
}

text load_text(const char *filename)
{
    text text = create_text();

    load(text, filename);

    return text;
}

const char *inputFile = "input.txt";

/* Макрос для перехвата вывода */
#define getOutput(func) \
    testing::internal::CaptureStdout(); \
    { func } \
    output = testing::internal::GetCapturedStdout()

/* Макрос для получения сожержимого файла */
#define getContent(file) \
    string content; \
    string line; \
    ifstream out(file); \
    while (getline(out, line)) \
        content += line + "\n"; \
    out.close()

/* Группа тестов save */

TEST(save_tests, save_no_write_attribute)
{
   text txt = load_text(inputFile);

   string output;

   getOutput(save(txt, "/var"););

   ASSERT_EQ(output, "The file /var cannot be created\n");
}

TEST(save_tests, save_empty_file)
{
    const char *file = "empty.txt";

    /* Запись в файл строки 123 */
    text txt = create_text();
    append_line(txt, "123");
    save(txt, file);

    /* Запись в файл пустого содержимого */
    remove_all(txt);
    save(txt, file);

    getContent(file);

    remove("empty.txt");

    ASSERT_EQ(content, "");
}

TEST(save_tests, save_data)
{
    const char *file = "save.txt";

    const char *excepted_content = "hello\nworld!\n";

    text txt = create_text();
    append_line(txt, excepted_content);
    save(txt, file);

    getContent(file);
    remove(file);
    ASSERT_EQ(content, excepted_content);
}

/* Группа тестов show */

TEST(show_tests, show_data)
{
    text txt = load_text(inputFile);

    string output;

    getOutput(show(txt););
    ASSERT_EQ(output, "qwert\n123\nwasd1\nabc\n|\n");
}

TEST(show_tests, show_empty_data)
{
    text txt = create_text();

    string output;

    getOutput(show(txt););
    ASSERT_EQ(output, "");
}

/* Группа тестов mwcursor */

TEST(mwcursor_tests, mwcursor_test)
{
    text txt = load_text(inputFile);

    string output;

    mwcursor(txt, 1, 1);
    getOutput(show(txt););
    ASSERT_EQ(output, "|qwert\n123\nwasd1\nabc\n\n");

    mwcursor(txt, 3, 3);
    getOutput(show(txt););
    ASSERT_EQ(output, "qwert\n123\nwa|sd1\nabc\n\n");

    mwcursor(txt, 5, 1);
    getOutput(show(txt););
    ASSERT_EQ(output, "qwert\n123\nwasd1\nabc\n|\n");
}

TEST(mwcursor_tests, mwcursor_out)
{
    text txt = load_text(inputFile);

    string output;

    const string init_data = "qwert\n123\nwasd1\nabc\n|\n"; //курсор до перемещения

    mwcursor(txt, 0, 0);
    getOutput(show(txt););
    ASSERT_EQ(output, init_data);

    mwcursor(txt, 100, 100);
    getOutput(show(txt););
    ASSERT_EQ(output, init_data);
}

TEST(mwcursor_tests, mwcursor_empty_file)
{
    text txt = create_text();

    string output;

    mwcursor(txt, 1, 1);
    getOutput(show(txt););
    ASSERT_EQ(output, "");
}

/* Группа тестов showlineswithdigits */

TEST(showlineswithdigits_tests, showlineswithdigits_test)
{
    text txt = load_text(inputFile);

    string output;

    getOutput(showlineswithdigits(txt););
    ASSERT_EQ(output, "123\nwasd1\n");
}

TEST(showlineswithdigits_tests, showlineswithdigits_empty_file)
{
    text txt = create_text();

    string output;

    getOutput(showlineswithdigits(txt););
    ASSERT_EQ(output, "");
}

/* Группа тестов ch */

TEST(ch_tests, ch_test)
{
    text txt = load_text(inputFile);

    string output;

    mwcursor(txt, 1, 2);
    const char *init_line = "q|wert\n123\nwasd1\nabc\n\n";
    const char *excpected_line = "wert|q\n123\nwasd1\nabc\n\n";
    getOutput(change(txt); show(txt););
    ASSERT_EQ(output, excpected_line);
    getOutput(change(txt); show(txt););
    ASSERT_EQ(output, init_line);

    mwcursor(txt, 3, 1);
    const char *init_line2 = "qwert\n123\n|wasd1\nabc\n\n";
    const char *excpected_line2 = "qwert\n123\nwasd1|\nabc\n\n";
    getOutput(change(txt); show(txt););
    ASSERT_EQ(output, excpected_line2);
    getOutput(change(txt); show(txt););
    ASSERT_EQ(output, init_line2);

    mwcursor(txt, 5, 1);
    const char *init_line3 = "qwert\n123\nwasd1\nabc\n|\n";
    const char *excpected_line3 = "qwert\n123\nwasd1\nabc\n|\n";
    getOutput(change(txt); show(txt););
    ASSERT_EQ(output, excpected_line3);
    getOutput(change(txt); show(txt););
    ASSERT_EQ(output, init_line3);
}

TEST(ch_tests, ch_test_empty_file)
{
    text txt = create_text();

    string output;

    getOutput(change(txt); show(txt););

    ASSERT_EQ(output, "");
}

/* Группа тестов c1n */

TEST(c1n_tests, c1n_test)
{
    text txt = load_text(inputFile);

    const char* excpected_line1 = "123\nwasd1\nabc\n\nqwert|\n";
    const char* excpected_line2 = "wasd1\nabc\n\nqwert\n123|\n";

    string output;

    getOutput(c1n(txt);show(txt););
    ASSERT_EQ(output, excpected_line1);

    getOutput(c1n(txt);show(txt););
    ASSERT_EQ(output, excpected_line2);
}

TEST(c1n_tests, c1n_empty_file)
{
    text txt = create_text();

    string output;

    getOutput(c1n(txt); show(txt););

    ASSERT_EQ(output, "");
}

#endif // TESTS_H
