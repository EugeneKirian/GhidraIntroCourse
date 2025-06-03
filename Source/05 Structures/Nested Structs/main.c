/*
Copyright (c) 2025 Eugene Kirian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

struct large_structure
{
    SYSTEMTIME UTC;
    SYSTEMTIME Local;
};

void print_large_structure(struct large_structure value)
{
    printf("UTC: %d-%d-%d %d:%d:%d\n",
        value.UTC.wYear, value.UTC.wMonth, value.UTC.wDay,
        value.UTC.wHour, value.UTC.wMinute, value.UTC.wSecond);
    printf("Local: %d-%d-%d %d:%d:%d\n",
        value.Local.wYear, value.Local.wMonth, value.Local.wDay,
        value.Local.wHour, value.Local.wMinute, value.Local.wSecond);
}

void large_structure_value_example()
{
    struct large_structure value;

    GetSystemTime(&value.UTC);
    GetLocalTime(&value.Local);

    print_large_structure(value);
}

int main(int argc, char** argv)
{
    large_structure_value_example();

    return 0;
}