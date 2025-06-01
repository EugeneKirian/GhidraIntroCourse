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

struct struct_default_alignement
{
    char c;
    long l;
    unsigned char b[2];
    unsigned char z[3];
    double zz;
};

#pragma pack(push, 1)
struct packed_struct_1_alignement
{
    char c;
    long l;
    unsigned char b[2];
    unsigned char z[3];
    double zz;
};
#pragma pack(pop)

#pragma pack(push, 2)
struct packed_struct_2_alignement
{
    char c;
    long l;
    unsigned char b[2];
    unsigned char z[3];
    double zz;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct packed_struct_4_alignement
{
    char c;
    long l;
    unsigned char b[2];
    unsigned char z[3];
    double zz;
};
#pragma pack(pop)

#pragma pack(push, 8)
struct packed_struct_8_alignement
{
    char c;
    long l;
    unsigned char b[2];
    unsigned char z[3];
    double zz;
};
#pragma pack(pop)

#pragma pack(push, 16)
struct packed_struct_16_alignement
{
    char c;
    long l;
    unsigned char b[2];
    unsigned char z[3];
    double zz;
};
#pragma pack(pop)

void structure_sizes_example()
{
    printf("Struct struct_default_alignement size: %d\n",
        sizeof(struct struct_default_alignement));

    printf("Struct packed_struct_1_alignement size: %d\n",
        sizeof(struct packed_struct_1_alignement));

    printf("Struct packed_struct_2_alignement size: %d\n",
        sizeof(struct packed_struct_2_alignement));

    printf("Struct packed_struct_4_alignement size: %d\n",
        sizeof(struct packed_struct_4_alignement));

    printf("Struct packed_struct_8_alignement size: %d\n",
        sizeof(struct packed_struct_8_alignement));

    printf("Struct packed_struct_16_alignement size: %d\n",
        sizeof(struct packed_struct_16_alignement));
}

void simple_structure_example()
{
    SYSTEMTIME time;
    ZeroMemory(&time, sizeof(SYSTEMTIME));

    GetLocalTime(&time);

    printf("Current Time: %d-%02d-%02d %02d:%02d:%02d\n",
        time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
}

void simple_structure_copy_example()
{
    SYSTEMTIME time, copy;
    ZeroMemory(&time, sizeof(SYSTEMTIME));

    GetLocalTime(&time);

    copy = time;

    printf("Copy Time: %d-%02d-%02d %02d:%02d:%02d\n",
        copy.wYear, copy.wMonth, copy.wDay, copy.wHour, copy.wMinute, copy.wSecond);
}

void structure_array_example()
{
	int index = 0;
    int length = 0;
	float free_space_percentage;
	char drive[MAX_PATH];
    char drives[MAX_PATH];

    const int count = GetLogicalDriveStringsA(MAX_PATH, drives);

    if (count == 0)
    {
        printf("Unable to get available disk volumes.\n");

        return;
    }

    ZeroMemory(drive, MAX_PATH * sizeof(char));

    while (TRUE)
    {
        drive[length] = drives[index];

        length = drives[index] == '\0' ? 0 : (length + 1);

        if (length == 0)
        {
            DWORD total_clusters = 0, free_clusters = 0;
            DWORD sectors_in_cluster = 0, bytes_in_sector = 0;

            GetDiskFreeSpaceA(drive, &sectors_in_cluster, &bytes_in_sector,
                &free_clusters, &total_clusters);

            free_space_percentage = total_clusters == 0
                ? 100.0f
                : (100.0f * (float)free_clusters / (float)total_clusters);
            
            printf("Drive: %s Free Space: %f%%\n", drive, free_space_percentage);
        }

        if (drives[index] == '\0' && drives[index + 1] == '\0') { break; }

        index++;
    }
}

#define MAX_STRUCTURE_COUNT 32

struct file_system_entity
{
    HANDLE handle;
    char path[MAX_PATH];
    unsigned char is_directory;
};

int file_structures_count = 0;
struct file_system_entity entities[MAX_STRUCTURE_COUNT];

void get_system_drive_path(char* result)
{
    char system[MAX_PATH] = { 0 };
    
	if (result == NULL) { return; }

    GetSystemDirectoryA(system, MAX_PATH);

    _splitpath(system, result, NULL, NULL, NULL);
}

void get_system_drive_search_pattern(char* drive)
{
    if (drive == NULL) { return; }

	strcat(drive, "\\*");
}

void file_system_structure_example()
{
	int i, iteration = 0;
	char drive[MAX_PATH] = { 0 };
	HANDLE handle = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAA ffd;

    printf("Struct file_system_entity size: %d\n", sizeof(struct file_system_entity));

    get_system_drive_path(drive);

    if (drive[0] == '\0')
    {
        printf("Unable to get system drive name.\n");

        return;
    }

    get_system_drive_search_pattern(drive);

    ZeroMemory(&ffd, sizeof(ffd));

    handle = FindFirstFileA(drive, &ffd);

    if (handle == INVALID_HANDLE_VALUE)
    {
        printf("Unable to start file discovery for %s\n", drive);

        return;
    }

    do
    {
        strcat(entities[iteration].path, ffd.cFileName);
        
        entities[iteration].is_directory = (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        iteration++;
    } while (iteration < MAX_STRUCTURE_COUNT && FindNextFileA(handle, &ffd) != 0);

    FindClose(handle);

    file_structures_count = iteration;

    for (i = 0; i < iteration; i++)
    {
        printf("%s\t\t%s\n", entities[i].is_directory ? "<DIR>" : "<FILE>", entities[i].path);
    }
}

struct addition_structure
{
    int integer;
    float single;
};

void modify_structure_through_pointer(struct addition_structure* input)
{
    input->integer++;
    input->single++;
}

void structure_pointer_example()
{
	int i;
    struct addition_structure value;

    value.integer = 0;
    value.single = 0.0f;

    printf("Original structure values %d %f\n", value.integer, value.single);

    for (i = 0; i < 10; i++)
    {
        modify_structure_through_pointer(&value);

        printf("Modified structure values %d %f\n", value.integer, value.single);
    }
}

void structure_pointer_math_example()
{
	int i;
	const struct file_system_entity* pointer = entities;

    printf("Struct Pointer Math\n");

    for (i = 0; i < file_structures_count; i++)
    {
        printf("%s\n", pointer->path);

        pointer++;
    }

    printf("\n");
}

void modify_structure_through_value(struct addition_structure input)
{
    input.integer++;
    input.single++;
}

void structure_value_example()
{
	int i;
    struct addition_structure value;

    value.integer = 0;
    value.single = 0.0f;

    printf("Original structure values %d %f\n", value.integer, value.single);

    for (i = 0; i < 10; i++)
    {
        modify_structure_through_value(value);

        printf("Modified structure values %d %f\n", value.integer, value.single);
    }
}

int main(int argc, char** argv)
{
    structure_sizes_example();
    simple_structure_example();
    simple_structure_copy_example();
    structure_array_example();
    file_system_structure_example();
    structure_pointer_example();
    structure_pointer_math_example();
    structure_value_example();
    
    return 0;
}