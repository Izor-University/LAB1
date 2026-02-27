#include "Vector3D.h"
#include <stdio.h>
#include <stdlib.h>


struct Vector3D {
    void*     x;
    void*     y;
    void*     z;
    TypeInfo* typeInfo;
};

Vector3D* Vector3D_Create(void* x, void* y, void* z, TypeInfo* typeInfo) {
    if (!x || !y || !z || !typeInfo) return NULL;
    Vector3D* vec = (Vector3D*)malloc(sizeof(Vector3D));
    if (!vec) return NULL;
    vec->typeInfo = typeInfo;
    vec->x = malloc(typeInfo->element_size);
    vec->y = malloc(typeInfo->element_size);
    vec->z = malloc(typeInfo->element_size);
    if (!vec->x || !vec->y || !vec->z) {
        fprintf(stderr, "Error: Memory allocation failed for vector components\n");
        free(vec->x); free(vec->y); free(vec->z); free(vec);
        return NULL;
    }
    typeInfo->copy(vec->x, x);
    typeInfo->copy(vec->y, y);
    typeInfo->copy(vec->z, z);
    return vec;
}

void Vector3D_Destroy(Vector3D* vec) {
    if (!vec) return;
    if (vec->typeInfo->destroy) {
        vec->typeInfo->destroy(vec->x);
        vec->typeInfo->destroy(vec->y);
        vec->typeInfo->destroy(vec->z);
    }
    free(vec->x); free(vec->y); free(vec->z);
    free(vec);
}

Vector3D* Vector3D_Clone(const Vector3D* vec) {
    if (!vec) return NULL;
    return Vector3D_Create(vec->x, vec->y, vec->z, vec->typeInfo);
}


//Getters
void* Vector3D_GetX(const Vector3D* vec) {
    return vec->x;
}
void* Vector3D_GetY(const Vector3D* vec) {
    return vec->y;
}
void* Vector3D_GetZ(const Vector3D* vec) {
    return vec->z;
}

TypeInfo* Vector3D_GetTypeInfo(const Vector3D* vec) {
    return vec->typeInfo;
}

//Setters

void Vector3D_SetX(Vector3D* vec, const void* x) {
    if (vec) vec->typeInfo->copy(vec->x, x);
}
void Vector3D_SetY(Vector3D* vec, const void* y) {
    if (vec) vec->typeInfo->copy(vec->y, y);
}
void Vector3D_SetZ(Vector3D* vec, const void* z) {
    if (vec) vec->typeInfo->copy(vec->z, z);
}

//Operations

Vector3D* Vector3D_Add(const Vector3D* v1, const Vector3D* v2) {
    if (!v1 || !v2) return NULL;
    if (v1->typeInfo != v2->typeInfo) {
        fprintf(stderr, "Error: type mismatch in Vector3D_Add\n");
        return NULL;
    }

    TypeInfo* ti = v1->typeInfo;

    void* rx = ti->add(v1->x, v2->x);
    void* ry = ti->add(v1->y, v2->y);
    void* rz = ti->add(v1->z, v2->z);

    Vector3D* res = Vector3D_Create(rx, ry, rz, ti);

    free(rx);
    free(ry);
    free(rz);

    return res;
}

void* Vector3D_DotProduct(const Vector3D* v1, const Vector3D* v2) {
    if (!v1 || !v2) return NULL;
    if (v1->typeInfo != v2->typeInfo) {
        fprintf(stderr, "Error: type mismatch in Vector3D_DotProduct\n");
        return NULL;
    }

    TypeInfo* ti = v1->typeInfo;

    void* px = ti->multiply(v1->x, v2->x);
    void* py = ti->multiply(v1->y, v2->y);
    void* pz = ti->multiply(v1->z, v2->z);
    void* tmp = ti->add(px, py);
    void* res = ti->add(tmp, pz);

    free(px);
    free(py);
    free(pz);
    free(tmp);
    return res;
}

Vector3D* Vector3D_CrossProduct(const Vector3D* v1, const Vector3D* v2) {
    if (!v1 || !v2) return NULL;
    if (v1->typeInfo != v2->typeInfo) {
        fprintf(stderr, "Error: type mismatch in Vector3D_CrossProduct\n");
        return NULL;
    }
    TypeInfo* ti = v1->typeInfo;

    /* rx = y1*z2 - z1*y2 */
    void* p1x = ti->multiply(v1->y, v2->z);
    void* p2x = ti->multiply(v1->z, v2->y);
    void* rx  = ti->subtract(p1x, p2x);

    /* ry = z1*x2 - x1*z2 */
    void* p1y = ti->multiply(v1->z, v2->x);
    void* p2y = ti->multiply(v1->x, v2->z);
    void* ry  = ti->subtract(p1y, p2y);

    /* rz = x1*y2 - y1*x2 */
    void* p1z = ti->multiply(v1->x, v2->y);
    void* p2z = ti->multiply(v1->y, v2->x);
    void* rz  = ti->subtract(p1z, p2z);

    Vector3D* res = Vector3D_Create(rx, ry, rz, ti);

    free(p1x); free(p2x); free(rx);
    free(p1y); free(p2y); free(ry);
    free(p1z); free(p2z); free(rz);


    return res;
}

//Utils

void Vector3D_Print(const Vector3D* vec) {
    if (!vec) {
        printf("NULL vector\n");
        return;
    }
    if (!vec->typeInfo->print) {
        printf("(no print)\n");
        return;
    }

    printf("  X = "); vec->typeInfo->print(vec->x);
    printf("  Y = "); vec->typeInfo->print(vec->y);
    printf("  Z = "); vec->typeInfo->print(vec->z);
}
