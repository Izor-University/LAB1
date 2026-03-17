#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stddef.h>

typedef struct TypeInfo {
    size_t element_size;
    void (*copy)(void* dest, const void* src);
    void (*destroy)(void* element);
    void (*add)(void* result, const void* arg1, const void* arg2);
    void (*subtract)(void* result, const void* arg1, const void* arg2);
    void (*multiply)(void* result, const void* arg1, const void* arg2);
    void (*print)(const void* element);
    int (*compare)(const void* arg1, const void* arg2);
} TypeInfo;

TypeInfo* ofDouble();
TypeInfo* ofComplex();

void TypeInfo_FreeAll();

#endif
