#ifndef COMPLEX_H
#define COMPLEX_H

#include <stddef.h>

typedef struct Complex Complex;

size_t Complex_SizeOf();
void Complex_Copy(void* dest, const void* src);

void Complex_Create(Complex* dest, double real, double imag);
void Complex_Zero(Complex* dest);

void Complex_Add(Complex* result, const Complex* arg1, const Complex* arg2);
void Complex_Subtract(Complex* result, const Complex* arg1, const Complex* arg2);
void Complex_Multiply(Complex* result, const Complex* arg1, const Complex* arg2);

void Complex_Print(const Complex* elem);
int Complex_Equal(const Complex* arg1, const Complex* arg2);

#endif