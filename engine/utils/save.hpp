#pragma once
#include <stdio.h>

template <typename T>
void save(T* data, const char* path)
{
    FILE* f = fopen(path, "w+");
    fwrite(data, sizeof(T), 1, f);
    fclose(f);
}

template <typename T>
void load(T* data, const char* path)
{
    FILE* f = fopen(path, "r");
    fread(data, sizeof(T), 1, f);
    fclose(f);
}
