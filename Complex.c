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
    Complex*       d = (Complex*)dest;

    const Complex* s = (const Complex*)src;

    d->real = s->real;
    d->imag = s->imag;
}

Complex* Complex_Create(double real, double imag) {
    Complex* elem = (Complex*)malloc(sizeof(Complex));

    if (elem == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Complex\n");
        return NULL;
    }

    elem->real = real;
    elem->imag = imag;

    return elem;
}

Complex* Complex_Zero() {
    return Complex_Create(0.0, 0.0);
}

Complex* Complex_Add(const Complex* arg1, const Complex* arg2) {
    if (!arg1 || !arg2) {
        fprintf(stderr, "Error: NULL in Complex_Add\n");
        return NULL;
    }

    return Complex_Create(arg1->real + arg2->real, arg1->imag + arg2->imag);
}

Complex* Complex_Subtract(const Complex* arg1, const Complex* arg2) {
    if (!arg1 || !arg2) {
        fprintf(stderr, "Error: NULL in Complex_Subtract\n");
        return NULL;
    }

    return Complex_Create(arg1->real - arg2->real, arg1->imag - arg2->imag);
}

Complex* Complex_Multiply(const Complex* arg1, const Complex* arg2) {
    if (!arg1 || !arg2) {
        fprintf(stderr, "Error: NULL in Complex_Multiply\n");
        return NULL;
    }

    double real = arg1->real * arg2->real - arg1->imag * arg2->imag;
    double imag = arg1->real * arg2->imag + arg1->imag * arg2->real;

    return Complex_Create(real, imag);
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
