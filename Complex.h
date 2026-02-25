#ifndef COMPLEX_H
#define COMPLEX_H

#include <stddef.h>

typedef struct Complex Complex;

size_t   Complex_SizeOf();
void     Complex_Copy(void* dest, const void* src);

Complex* Complex_Create(double real, double imag);
Complex* Complex_Zero();

Complex* Complex_Add(const Complex* arg1, const Complex* arg2);
Complex* Complex_Subtract(const Complex* arg1, const Complex* arg2);
Complex* Complex_Multiply(const Complex* arg1, const Complex* arg2);

void Complex_Print(const Complex* elem);
int  Complex_Equal(const Complex* arg1, const Complex* arg2);

#endif
