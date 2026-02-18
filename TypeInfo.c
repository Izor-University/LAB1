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

static void double_print(const void* element) {
    double* element_double = (double*)element;
    printf("%lf\n", *element_double);
}

static int double_compare(const void* arg1, const void* arg2){
	double* arg1_double = (double*)arg1;
	double* arg2_double = (double*)arg2;
	
	double diff = *arg1_double - *arg2_double;
	if (diff < -1e-9) return -1; // arg1 > arg2
	if (diff > 1e-9) return 1; // arg1 < arg2
	return 0; // arg1 = arg2
}



static TypeInfo* ofDouble = NULL;

void* GetDoubleTypeInfo() {
    if (ofDouble==NULL) {
        ofDouble=malloc(sizeof(ofDouble));
        ofDouble->element_size=sizeof(double);
        ofDouble->create_zero=double_create_zero();
	ofDouble->destroy = NULL;
	ofDouble->copy = double_copy(void* dest, const void* src);
	ofDouble->add = double_add(const void* arg1, const coid* arg2);
	ofDouble->substract = double_sub(const void* arg1, const void* arg2);
	ofDouble->multiply = doubel_mul(const void* arg1, const void* arg2);
	ofDouble->print = double_print(const void* element);
	ofDouble->compare = double_compare(const void* arg1, const void* arg2);
    }
}
