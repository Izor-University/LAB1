#ifndef COMPLEX_H
#define COMPLEX_H

#include <stddef.h>

typedef struct Complex Complex;

size_t   Complex_SizeOf(void);
void     Complex_Copy(void* dest, const void* src);


Complex* Complex_Create(double real, double imag);
Complex* Complex_Zero(void);



Complex* Complex_Add(const Complex* a, const Complex* b);
Complex* Complex_Subtract(const Complex* a, const Complex* b);
Complex* Complex_Multiply(const Complex* a, const Complex* b);


void Complex_Print(const Complex* elem);
int  Complex_Equal(const Complex* a, const Complex* b);

#endif