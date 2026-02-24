#include "Complex.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Complex {
    double real;
    double imag;
};

size_t Complex_SizeOf(void) {
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

Complex* Complex_Zero(void) {
    return Complex_Create(0.0, 0.0);
}

Complex* Complex_Add(const Complex* a, const Complex* b) {
    if (!a || !b) {
        fprintf(stderr, "Error: NULL in Complex_Add\n");
        return NULL;
    }

    return Complex_Create(a->real + b->real, a->imag + b->imag);
}

Complex* Complex_Subtract(const Complex* a, const Complex* b) {
    if (!a || !b) {
        fprintf(stderr, "Error: NULL in Complex_Subtract\n");
        return NULL;
    }

    return Complex_Create(a->real - b->real, a->imag - b->imag);
}

Complex* Complex_Multiply(const Complex* a, const Complex* b) {
    if (!a || !b) {
        fprintf(stderr, "Error: NULL in Complex_Multiply\n");
        return NULL;
    }

    double real = a->real * b->real - a->imag * b->imag;
    double imag = a->real * b->imag + a->imag * b->real;

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

int Complex_Equal(const Complex* a, const Complex* b) {
    if (!a && !b) return 1;
    if (!a || !b) return 0;

    return fabs(a->real - b->real) < 1e-9 &&
           fabs(a->imag - b->imag) < 1e-9;
}
