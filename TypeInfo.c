#include "TypeInfo.h"
#include "Complex.h"
#include <stdio.h>
#include <stdlib.h>


static TypeInfo* double_type = NULL;
static TypeInfo* complex_type = NULL;

//Double

static void double_copy(void* dest, const void* src) {
    *(double*)dest = *(const double*)src;
}

static void double_add(void* result, const void* arg1, const void* arg2) {
    *(double*)result = *(const double*)arg1 + *(const double*)arg2;
}

static void double_sub(void* result, const void* arg1, const void* arg2) {
    *(double*)result = *(const double*)arg1 - *(const double*)arg2;
}

static void double_mul(void* result, const void* arg1, const void* arg2) {
    *(double*)result = *(const double*)arg1 * *(const double*)arg2;
}

static void double_print(const void* elem) {
    printf("%.3f\n", *(const double*)elem);
}

static int double_compare(const void* arg1, const void* arg2) {
    double diff = *(const double*)arg1 - *(const double*)arg2;

    if (diff < -1e-9) return -1;// arg1 < arg2
    if (diff > 1e-9) return 1;// arg1 > arg2

    return 0;
}

//Complex

static void complex_copy(void* dest, const void* src) {
    Complex_Copy(dest, src);
}

static void complex_add(void* result, const void* arg1, const void* arg2) {
    Complex_Add((Complex*)result, (const Complex*)arg1, (const Complex*)arg2);
}

static void complex_sub(void* result, const void* arg1, const void* arg2) {
    Complex_Subtract((Complex*)result, (const Complex*)arg1, (const Complex*)arg2);
}

static void complex_mul(void* result, const void* arg1, const void* arg2) {
    Complex_Multiply((Complex*)result, (const Complex*)arg1, (const Complex*)arg2);
}

static void complex_print(const void* elem) {
    Complex_Print((const Complex*)elem);
    printf("\n");
}

static int complex_compare(const void* arg1, const void* arg2) {
    return Complex_Equal((const Complex*)arg1, (const Complex*)arg2) ? 0 : 1;
}

//Functions
TypeInfo* ofDouble() {
    if (double_type == NULL) {
        double_type = (TypeInfo*)malloc(sizeof(TypeInfo));
        double_type->element_size = sizeof(double);
        double_type->copy = double_copy;
        double_type->destroy = NULL;
        double_type->add = double_add;
        double_type->subtract = double_sub;
        double_type->multiply = double_mul;
        double_type->print = double_print;
        double_type->compare = double_compare;
    }
    return double_type;
}

TypeInfo* ofComplex() {
    if (complex_type == NULL) {
        complex_type = (TypeInfo*)malloc(sizeof(TypeInfo));
        complex_type->element_size = Complex_SizeOf();
        complex_type->copy = complex_copy;
        complex_type->destroy = NULL;
        complex_type->add = complex_add;
        complex_type->subtract = complex_sub;
        complex_type->multiply = complex_mul;
        complex_type->print = complex_print;
        complex_type->compare = complex_compare;
    }
    return complex_type;
}

void TypeInfo_FreeAll() {
    free(double_type); double_type = NULL;
    free(complex_type); complex_type = NULL;
}
