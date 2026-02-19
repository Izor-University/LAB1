#include "Complex.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void Complex_Destroy(Complex* elem) {
    free(elem);
}

Complex* Complex_Add(const Complex* arg1, const Complex* arg2) {
    if (arg1 == NULL || arg2 == NULL) {
        fprintf(stderr, "Error: NULL pointer in Complex_arg1dd\n");
        return NULL;
    }
    return Complex_Create(arg1->real + arg2->real, arg1->imag + arg2->imag);
}

Complex* Complex_Subtract(const Complex* arg1, const Complex* arg2) {
    if (arg1 == NULL || arg2 == NULL) {
        fprintf(stderr, "Error: NULL pointer in Complex_Subtract\n");
        return NULL;
    }
    return Complex_Create(arg1->real - arg2->real, arg1->imag - arg2->imag);
}

Complex* Complex_Multiply(const Complex* arg1, const Complex* arg2) {
    if (arg1 == NULL || arg2 == NULL) {
        fprintf(stderr, "Error: NULL pointer in Complex_Multiply\n");
        return NULL;
    }

    // (arg1 + bi)(elem + di) = (ac - bd) + (ad + bc)i
    double real = arg1->real * arg2->real - arg1->imag * arg2->imag;
    double imag = arg1->real * arg2->imag + arg1->imag * arg2->real;

    return Complex_Create(real, imag);
}

Complex* Complex_Conjugate(const Complex* elem) {
    if (elem == NULL) {
        fprintf(stderr, "Error: NULL pointer in Complex_Conjugate\n");
        return NULL;
    }
    return Complex_Create(elem->real, -elem->imag);
}

void Complex_Print(const Complex* elem) {
    if (elem == NULL) {
        printf("NULL");
        return;
    }

    if (fabs(elem->imag) < 1e-9) {
        printf("%.3f", elem->real);
    } else if (elem->imag >= 0) {
        printf("%.3f+%.3fi", elem->real, elem->imag);
    } else {
        printf("%.3f%.3fi", elem->real, elem->imag);
    }
}

int Complex_Equal(const Complex* arg1, const Complex* arg2) {
    if (arg1 == NULL && arg2 == NULL) return 1;
    if (arg1 == NULL || arg2 == NULL) return 0;

    return fabs(arg1->real - arg2->real) < 1e-9 &&
           fabs(arg1->imag - arg2->imag) < 1e-9;
}
