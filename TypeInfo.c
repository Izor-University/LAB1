#include "TypeInfo.h"
#include "Complex.h"
#include <stdio.h>
#include <stdlib.h>


static TypeInfo* double_type  = NULL;
static TypeInfo* complex_type = NULL;

//Double

static void* double_create_zero(void) {
    double* z = (double*)malloc(sizeof(double));

    *z = 0.0;

    return z;
}

static void double_copy(void* dest, const void* src) {
    *(double*)dest = *(const double*)src;
}

static void* double_add(const void* a, const void* b) {
    double* r = (double*)malloc(sizeof(double));

    *r = *(const double*)a + *(const double*)b;

    return r;
}

static void* double_sub(const void* a, const void* b) {
    double* r = (double*)malloc(sizeof(double));

    *r = *(const double*)a - *(const double*)b;\

    return r;
}

static void* double_mul(const void* a, const void* b) {
    double* r = (double*)malloc(sizeof(double));

    *r = *(const double*)a * *(const double*)b;

    return r;
}

static void double_print(const void* e) {
    printf("%.3f\n", *(const double*)e);
}

static int double_compare(const void* a, const void* b) {
    double d = *(const double*)a - *(const double*)b;

    if (d < -1e-9) return -1;
    if (d >  1e-9) return  1;

    return 0;
}

//Complex

static void* complex_create_zero(void) {
    return Complex_Zero();
}

static void complex_copy(void* dest, const void* src) {
    Complex_Copy(dest, src);
}

static void* complex_add(const void* a, const void* b) {
    return Complex_Add((const Complex*)a, (const Complex*)b);
}

static void* complex_sub(const void* a, const void* b) {
    return Complex_Subtract((const Complex*)a, (const Complex*)b);
}

static void* complex_mul(const void* a, const void* b) {
    return Complex_Multiply((const Complex*)a, (const Complex*)b);
}

static void complex_print(const void* e) {
    Complex_Print((const Complex*)e);
    printf("\n");
}

static int complex_compare(const void* a, const void* b) {
    return Complex_Equal((const Complex*)a, (const Complex*)b) ? 0 : 1;
}


//Functions
TypeInfo* ofDouble(void) {
    if (double_type == NULL) {
        double_type = (TypeInfo*)malloc(sizeof(TypeInfo));
        double_type->element_size = sizeof(double);
        double_type->create_zero  = double_create_zero;
        double_type->copy         = double_copy;
        double_type->destroy      = NULL;
        double_type->add          = double_add;
        double_type->subtract     = double_sub;
        double_type->multiply     = double_mul;
        double_type->print        = double_print;
        double_type->compare      = double_compare;
    }
    return double_type;
}

TypeInfo* ofComplex(void) {
    if (complex_type == NULL) {
        complex_type = (TypeInfo*)malloc(sizeof(TypeInfo));
        complex_type->element_size = Complex_SizeOf();
        complex_type->create_zero  = complex_create_zero;
        complex_type->copy         = complex_copy;
        complex_type->destroy      = NULL;
        complex_type->add          = complex_add;
        complex_type->subtract     = complex_sub;
        complex_type->multiply     = complex_mul;
        complex_type->print        = complex_print;
        complex_type->compare      = complex_compare;
    }
    return complex_type;
}

void TypeInfo_FreeAll(void) {
    free(double_type);  double_type  = NULL;
    free(complex_type); complex_type = NULL;
}
