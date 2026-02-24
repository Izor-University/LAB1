#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stddef.h>

typedef struct TypeInfo {
    size_t element_size;
    void*  (*create_zero)(void);
    void   (*copy)(void* dest, const void* src);
    void   (*destroy)(void* element);       // NULL, если нет специального освобождения
    void*  (*add)(const void* a, const void* b);
    void*  (*subtract)(const void* a, const void* b);
    void*  (*multiply)(const void* a, const void* b);
    void   (*print)(const void* element);
    int    (*compare)(const void* a, const void* b);
} TypeInfo;

TypeInfo* ofDouble(void);
TypeInfo* ofComplex(void);

void TypeInfo_FreeAll(void);

#endif /* TYPEINFO_H */
