#include "props.h"
#include <ctest.h>
#include <stdio.h>
#define N 1000

figure circle[N];

void create_circle(figure* circle, size_t n, int p1, int p2, double p3)
{
    circle[n].x = p1;
    circle[n].y = p2;
    circle[n].r = p3;
    circle[n].name[0] = 'c';
    circle[n].name[1] = 'i';
    circle[n].name[2] = 'r';
    circle[n].name[3] = 'c';
    circle[n].name[4] = 'l';
    circle[n].name[5] = 'e';
    circle[n].name[6] = '\0';
}

CTEST(perimeter, test_1)
{
    create_circle(circle, 1, 1, 2, 1.5);
    double expect = 3 * M_PI;
    double result = perimeter(circle, 1);
    ASSERT_DBL_NEAR_TOL(expect, result, 1);
}

CTEST(area, test_1)
{
    create_circle(circle, 1, 1, 2, 2);
    double expect = 4 * M_PI;
    double result = area(circle, 1);
    ASSERT_DBL_NEAR_TOL(expect, result, 1);
}

CTEST(crossing, crossed_figures)
{
    create_circle(circle, 1, 1, 2, 2);
    create_circle(circle, 2, 2, 2, 2);
    int expect = 1;
    int result = crossing(circle, 1, 2);
    ASSERT_EQUAL(expect, result);
}

CTEST(crossing, not_crossed_figures)
{
    create_circle(circle, 1, 1, 2, 2);
    create_circle(circle, 2, 7, 8, 2);
    int expect = 0;
    int result = crossing(circle, 1, 2);
    ASSERT_EQUAL(expect, result);
}

CTEST(parse_coord, correct_x)
{
    char* line = "circle (1 2, 3)\n";
    size_t expect = 0;
    size_t i = 8;
    size_t result = parse_coord(&i, &circle[0].x, line);
    ASSERT_EQUAL(expect, result);
}

CTEST(parse_coord, incorrect_x)
{
    char* line = "circle (a 2, 3)\n";
    size_t expect = 1;
    size_t i = 8;
    size_t result = parse_coord(&i, &circle[0].x, line);
    ASSERT_EQUAL(expect, result);
}

CTEST(parse_coord, correct_y)
{
    char* line = "circle (1 2, 3)\n";
    size_t expect = 0;
    size_t i = 10;
    size_t result = parse_coord(&i, &circle[0].x, line);
    ASSERT_EQUAL(expect, result);
}

CTEST(parse_coord, incorrect_y)
{
    char* line = "circle (1 b, 3)\n";
    size_t expect = 1;
    size_t i = 10;
    size_t result = parse_coord(&i, &circle[0].x, line);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, correct_string)
{
    char* line = "circle (1 2, 3)\n";
    size_t expect = 1;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, correct_string_2)
{
    char* line = "circle (      1       2     ,       3)\n";
    size_t expect = 1;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, correct_string_3)
{
    char* line = "CiRCLE(      1       2     ,       3)\n";
    size_t expect = 1;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, correct_string_4)
{
    char* line = "circle(1 2, 0.1)\n";
    size_t expect = 1;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string)
{
    char* line = "circle (1, 3)\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string_2)
{
    char* line = "circle (1 n, 3)\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string_3)
{
    char* line = "circle (1, d)\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string_4)
{
    char* line = "circle ()\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string_5)
{
    char* line = "circle 1 2, 3\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string_6)
{
    char* line = "1 2, 3)\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string_7)
{
    char* line = "circle (1 2, 3\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string_8)
{
    char* line = "circle\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}

CTEST(scan_string, invalid_string_9)
{
    char* line = "circlr (1 2, 3)\n";
    size_t expect = 0;
    size_t result = scan_string(line, 0, circle);
    ASSERT_EQUAL(expect, result);
}
