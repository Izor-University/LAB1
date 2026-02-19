//
// Created by OPS on 17.02.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "TypeInfo.h"
#include "Complex.h"

static TypeInfo* double_type = NULL;
static TypeInfo* complex_type = NULL;

//Double operations
static void* double_create_zero() {
    double* zero = malloc(sizeof(double));
    *zero = 0.0;
    return zero;
}

static void double_copy(void* dest, const void* src) {
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

static void double_print(const void* element) {
    double* element_double = (double*)element;
    printf("%lf\n", *element_double);
}

static int double_compare(const void* arg1, const void* arg2){
	double* arg1_double = (double*)arg1;
	double* arg2_double = (double*)arg2;
	
	double diff = *arg1_double - *arg2_double;
	if (diff < -1e-9) return -1; // arg1 < arg2
	if (diff > 1e-9) return 1; // arg1 > arg2
	return 0; // arg1 = arg2
}

//Complex operations

static void* complex_create_zero() {
    return Complex_Zero();  // Уже возвращает указатель
}

static void complex_copy(void* dest, const void* src) {
    Complex* dest_c = (Complex*)dest;
    const Complex* src_c = (const Complex*)src;
    dest_c->real = src_c->real;
    dest_c->imag = src_c->imag;
}

static void complex_destroy(void* element) {
    Complex_Destroy((Complex*)element);
}

static void* complex_add(const void* a, const void* b) {
    return Complex_Add((const Complex*)a, (const Complex*)b);
}

static void* complex_subtract(const void* a, const void* b) {
    return Complex_Subtract((const Complex*)a, (const Complex*)b);
}

static void* complex_multiply(const void* a, const void* b) {
    return Complex_Multiply((const Complex*)a, (const Complex*)b);
}

static void complex_print(const void* element) {
    Complex_Print((const Complex*)element);
}

static int complex_compare(const void* a, const void* b) {
    return Complex_Equal((const Complex*)a, (const Complex*)b) ? 0 : 1;
}



void* ofDouble() {
    if (double_type == NULL) {
        double_type=malloc(sizeof(TypeInfo));
        double_type->element_size = sizeof(double);
        double_type->create_zero = double_create_zero;
	    double_type->destroy = NULL;
	    double_type->copy = double_copy;
	    double_type->add = double_add;
	    double_type->subtract = double_sub;
	    double_type->multiply = double_mul;
	    double_type->print = double_print;
	    double_type->compare = double_compare;
    }
    return double_type;
}

void* ofComplex() {
    if (complex_type == NULL) {
        complex_type=malloc(sizeof(TypeInfo));
        complex_type->element_size = sizeof(Complex);
        complex_type->create_zero = complex_create_zero;
        complex_type->destroy = complex_destroy;
        complex_type->copy = complex_copy;
        complex_type->add = complex_add;
        complex_type->subtract = complex_subtract;
        complex_type->multiply = complex_multiply;
        complex_type->print = complex_print;
        complex_type->compare = complex_compare;
    }
    return complex_type;
}
