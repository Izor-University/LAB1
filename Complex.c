#include "Complex.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Complex {
    double real;
    double imag;
};

size_t Complex_SizeOf() {
    return sizeof(struct Complex);
}

void Complex_Copy(void* dest, const void* src) {
    Complex* d = (Complex*)dest;
    const Complex* s = (const Complex*)src;
    d->real = s->real;
    d->imag = s->imag;
}

void Complex_Create(Complex* dest, double real, double imag) {
    if (!dest) return;
    dest->real = real;
    dest->imag = imag;
}

void Complex_Zero(Complex* dest) {
    if (!dest) return;
    dest->real = 0.0;
    dest->imag = 0.0;
}

void Complex_Add(Complex* result, const Complex* arg1, const Complex* arg2) {
    if (!result || !arg1 || !arg2) {
        fprintf(stderr, "Error: NULL in Complex_Add\n");
        return;
    }
    result->real = arg1->real + arg2->real;
    result->imag = arg1->imag + arg2->imag;
}

void Complex_Subtract(Complex* result, const Complex* arg1, const Complex* arg2) {
    if (!result || !arg1 || !arg2) {
        fprintf(stderr, "Error: NULL in Complex_Subtract\n");
        return;
    }
    result->real = arg1->real - arg2->real;
    result->imag = arg1->imag - arg2->imag;
}

void Complex_Multiply(Complex* result, const Complex* arg1, const Complex* arg2) {
    if (!result || !arg1 || !arg2) {
        fprintf(stderr, "Error: NULL in Complex_Multiply\n");
        return;
    }
    double real = arg1->real * arg2->real - arg1->imag * arg2->imag;
    double imag = arg1->real * arg2->imag + arg1->imag * arg2->real;
    result->real = real;
    result->imag = imag;
}

void Complex_Print(const Complex* elem) {
    if (!elem) {
        printf("NULL");
        return;
    }
    if (fabs(elem->imag) < 1e-9)
        printf("%.3f", elem->real);
    else if (elem->imag >= 0)
        printf("%.3f+%.3fi", elem->real, elem->imag);
    else
        printf("%.3f%.3fi", elem->real, elem->imag);
}

int Complex_Equal(const Complex* arg1, const Complex* arg2) {
    if (!arg1 && !arg2) return 1;
    if (!arg1 || !arg2) return 0;
    return fabs(arg1->real - arg2->real) < 1e-9 &&
           fabs(arg1->imag - arg2->imag) < 1e-9;
}