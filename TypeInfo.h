#ifndef UNTITLED_TYPEINFO_H
#define UNTITLED_TYPEINFO_H
#include <stdio.h>  
typedef struct TypeInfo {
    size_t element_size;
    void* (*create_zero)();
    void (*copy)(void* dest, const void* src);
    void (*destroy)(void* element);
    void* (*add)(const void* a, const void* b);
    void* (*subtract)(const void* a, const void* b);
    void* (*multiply)(const void* a, const void* b);
    void (*print)(const void* element);
    int (*compare)(const void* a, const void* b);
} TypeInfo;

void* ofDouble();
void* ofComplex();
#endif //UNTITLED_TYPEINFO_H
