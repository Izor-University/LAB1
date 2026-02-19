#ifndef UNTITLED_VECTOR3D_H
#define UNTITLED_VECTOR3D_H

#include "TypeInfo.h"

typedef struct Vector3D {
    void* x;
    void* y;
    void* z;
    TypeInfo* TypeInfo;
} Vector3D;

Vector3D* Vector3D_Create(void* x, void* y, void* z, TypeInfo* TypeInfo);
void Vector3D_Destroy(Vector3D* vec);


void* Vector3D_GetX(const Vector3D* vec);
void* Vector3D_GetY(const Vector3D* vec);
void* Vector3D_GetZ(const Vector3D* vec);
void Vector3D_SetX(Vector3D* vec, const void* x);
void Vector3D_SetY(Vector3D* vec, const void* y);
void Vector3D_SetZ(Vector3D* vec, const void* z);


Vector3D* Vector3D_Add(const Vector3D* v1, const Vector3D* v2);
void* Vector3D_DotProduct(const Vector3D* v1, const Vector3D* v2);
Vector3D* Vector3D_CrossProduct(const Vector3D* v1, const Vector3D* v2);


void Vector3D_Print(const Vector3D* vec);
Vector3D* Vector3D_Clone(const Vector3D* vec);

#endif //UNTITLED_VECTOR3D_H