#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "TypeInfo.h"
#include "Vector3D.h"
#include <stddef.h>

typedef struct Matrix3x3 Matrix3x3;

size_t Matrix3x3_SizeOf(void);

// Теперь принимаем двумерный массив 3x3
void Matrix3x3_Create(Matrix3x3* mat, void* data[3][3], TypeInfo* typeInfo);
void Matrix3x3_Destroy(Matrix3x3* mat);

void Matrix3x3_MakeRotation(Matrix3x3* mat, char axis, double angle);
void Matrix3x3_MultiplyVector(Vector3D* result, const Matrix3x3* mat, const Vector3D* vec);

#endif