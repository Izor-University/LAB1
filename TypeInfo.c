//
// Created by OPS on 17.02.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "TypeInfo.h"


static void* double_create_zero() {
    double* zero = malloc(sizeof(double));
    *zero = 0.0;
    return zero;
}

void double_copy(void* dest, const void* src) {
    double* dest_double = (double*)dest;
    double* src_double = (double*)src;

    *dest_double = *src_double;
}

static void* double_add(const void* a, const void* b) {
    double* a_double = (double*)a;
    double* b_double = (double*)b;
    double* result = (double*)malloc(sizeof(double));

    *result = *a_double + *b_double;
    return result;
}

static void* double_sub(const void* a, const void* b) {
    double* a_double = (double*)a;
    double* b_double = (double*)b;
    double* result = (double*)malloc(sizeof(double));

    *result = *a_double - *b_double;
    return result;
}

static void* double_mul(const void* a, const void* b) {
    double* a_double = (double*)a;
    double* b_double = (double*)b;
    double* result = (double*)malloc(sizeof(double));

    *result = *a_double * *b_double;
    return result;
}

void double_print(const void* element) {
    double* element_double = (double*)element;
    printf("%lf\n", *element_double);
}




static TypeInfo* ofDouble = NULL;

void* GetGetDoubleTypeInfo() {
    if (ofDouble==NULL) {
        ofDouble=malloc(sizeof(ofDouble));
        ofDouble->element_size=sizeof(double);
    }
}
