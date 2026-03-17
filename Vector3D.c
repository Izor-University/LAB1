#include "Vector3D.h"
#include <stdio.h>
#include <stdlib.h>


struct Vector3D {
    void* x;
    void* y;
    void* z;
    TypeInfo* typeInfo;
};

size_t Vector3D_SizeOf(void) {
    return sizeof(struct Vector3D);
}

void Vector3D_Create(Vector3D* vec, void* x, void* y, void* z, TypeInfo* typeInfo) {
    if (!vec || !x || !y || !z || !typeInfo) return;
    vec->typeInfo = typeInfo;
    vec->x = x;
    vec->y = y;
    vec->z = z;
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

Vector3D* Vector3D_Clone(const Vector3D* src) {
    if (!src) return NULL;
    TypeInfo* ti = src->typeInfo;

    Vector3D* vec = malloc(Vector3D_SizeOf());
    void* xb = malloc(ti->element_size);
    void* yb = malloc(ti->element_size);
    void* zb = malloc(ti->element_size);
    if (!vec || !xb || !yb || !zb) {
        free(vec); free(xb); free(yb); free(zb);
        return NULL;
    }

    ti->copy(xb, src->x);
    ti->copy(yb, src->y);
    ti->copy(zb, src->z);
    Vector3D_Create(vec, xb, yb, zb, ti);
    return vec;
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

void Vector3D_Add(Vector3D* result, const Vector3D* v1, const Vector3D* v2) {
    if (!result || !v1 || !v2) return;
    if (v1->typeInfo != v2->typeInfo) {
        fprintf(stderr, "Error: type mismatch in Vector3D_Add\n");
        return;
    }

    TypeInfo* ti = v1->typeInfo;

    ti->add(result->x, v1->x, v2->x);
    ti->add(result->y, v1->y, v2->y);
    ti->add(result->z, v1->z, v2->z);
    result->typeInfo = ti;
}

void Vector3D_DotProduct(void* result, const Vector3D* v1, const Vector3D* v2) {
    if (!result || !v1 || !v2) return;
    if (v1->typeInfo != v2->typeInfo) {
        fprintf(stderr, "Error: type mismatch in Vector3D_DotProduct\n");
        return;
    }

    TypeInfo* ti = v1->typeInfo;

    void* px = malloc(ti->element_size);
    void* py = malloc(ti->element_size);
    void* pz = malloc(ti->element_size);
    void* tmp = malloc(ti->element_size);

    ti->multiply(px, v1->x, v2->x);
    ti->multiply(py, v1->y, v2->y);
    ti->multiply(pz, v1->z, v2->z);
    ti->add(tmp, px, py);
    ti->add(result, tmp, pz);

    free(px);
    free(py);
    free(pz);
    free(tmp);
}

void Vector3D_CrossProduct(Vector3D* result, const Vector3D* v1, const Vector3D* v2) {
    if (!result || !v1 || !v2) return;
    if (v1->typeInfo != v2->typeInfo) {
        fprintf(stderr, "Error: type mismatch in Vector3D_CrossProduct\n");
        return;
    }
    TypeInfo* ti = v1->typeInfo;

    /* rx = y1*z2 - z1*y2 */
    void* p1x = malloc(ti->element_size);
    void* p2x = malloc(ti->element_size);
    ti->multiply(p1x, v1->y, v2->z);
    ti->multiply(p2x, v1->z, v2->y);
    ti->subtract(result->x, p1x, p2x);
    free(p1x); free(p2x);

    /* ry = z1*x2 - x1*z2 */
    void* p1y = malloc(ti->element_size);
    void* p2y = malloc(ti->element_size);
    ti->multiply(p1y, v1->z, v2->x);
    ti->multiply(p2y, v1->x, v2->z);
    ti->subtract(result->y, p1y, p2y);
    free(p1y); free(p2y);

    /* rz = x1*y2 - y1*x2 */
    void* p1z = malloc(ti->element_size);
    void* p2z = malloc(ti->element_size);
    ti->multiply(p1z, v1->x, v2->y);
    ti->multiply(p2z, v1->y, v2->x);
    ti->subtract(result->z, p1z, p2z);
    free(p1z); free(p2z);

    result->typeInfo = ti;
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

    printf(" X = "); vec->typeInfo->print(vec->x);
    printf(" Y = "); vec->typeInfo->print(vec->y);
    printf(" Z = "); vec->typeInfo->print(vec->z);
}
