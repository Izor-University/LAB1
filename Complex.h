#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct Complex {
	double real;
	double imag;
} Complex;

// Создание и уничтожение
Complex* Complex_Create(double real, double imag);
Complex* Complex_Zero();
void Complex_Destroy(Complex* elem);

// Арифметические операции (возвращают новые объекты)
Complex* Complex_Add(const Complex* arg1, const Complex* arg2);
Complex* Complex_Subtract(const Complex* arg1, const Complex* arg2);
Complex* Complex_Multiply(const Complex* arg1, const Complex* arg2);
Complex* Complex_Conjugate(const Complex* elem);


// Утилиты
void Complex_Print(const Complex* elem);
int Complex_Equal(const Complex* arg1, const Complex* arg2);

#endif
