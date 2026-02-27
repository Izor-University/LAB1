#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stddef.h>

typedef struct TypeInfo {
    size_t element_size;
    void*  (*create_zero)();
    void   (*copy)(void* dest, const void* src);
    void   (*destroy)(void* element);
    void*  (*add)(const void* arg1, const void* arg2);
    void*  (*subtract)(const void* arg1, const void* arg2);
    void*  (*multiply)(const void* arg1, const void* arg2);
    void   (*print)(const void* element);
    int    (*compare)(const void* arg1, const void* arg2);
} TypeInfo;

TypeInfo* ofDouble();
TypeInfo* ofComplex();

void TypeInfo_FreeAll();

#endif
