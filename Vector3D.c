//
// Created by OPS on 17.02.2026.
//

#include "Vector3D.h"
#include <stdlib.h>
#include <stdio.h>

Vector3D* Vector3D_Create(void* x, void* y, void* z, TypeInfo* TypeInfo) {
    Vector3D* vec;
    vec = (Vector3D*)malloc(sizeof(Vector3D));

    vec->TypeInfo = TypeInfo;

    vec->x = malloc(sizeof(TypeInfo->element_size));
    vec->y = malloc(sizeof(TypeInfo->element_size));
    vec->z = malloc(sizeof(TypeInfo->element_size));

    if (vec->x == NULL || vec->y == NULL || vec->z == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for vector components\n");
        free(vec->x);
        free(vec->y);
        free(vec->z);
        free(vec);
        return NULL;
    }

    TypeInfo->copy(vec->x, x);
    TypeInfo->copy(vec->y, y);
    TypeInfo->copy(vec->z, z);

    return vec;
}

void Vector3D_Destroy(Vector3D* vec) {
    if (vec == NULL) return;
    if (vec->TypeInfo->destroy != NULL) {
        vec->TypeInfo->destroy(vec->x);
        vec->TypeInfo->destroy(vec->y);
        vec->TypeInfo->destroy(vec->z);
    }

    free(vec->x);
    free(vec->y);
    free(vec->z);

    free(vec);
}

//Getters

void* Vector3D_GetX(const Vector3D* vec) {
    if (vec == NULL) return NULL;
    return vec->x;
}

void* Vector3D_GetY(const Vector3D* vec) {
    if (vec == NULL) return NULL;
    return vec->y;
}

void* Vector3D_GetZ(const Vector3D* vec) {
    if (vec == NULL) return NULL;
    return vec->z;
}

//Setters

void Vector3D_SetX(Vector3D* vec, const void* x) {
    if (vec == NULL) return;
    vec->TypeInfo->copy(vec->x, x);
}

void Vector3D_SetY(Vector3D* vec, const void* y) {
    if (vec == NULL) return;
    vec->TypeInfo->copy(vec->y, y);
}

void Vector3D_SetZ(Vector3D* vec, const void* z) {
    if (vec == NULL) return;
    vec->TypeInfo->copy(vec->z, z);
}

//Operations

Vector3D* Vector3D_Add(const Vector3D* v1, const Vector3D* v2) {
    if (v1 == NULL || v2 == NULL) return NULL;
    if (v1->TypeInfo != v2->TypeInfo) {
        fprintf(stderr, "Error: Vectors have different types in Vector3D_Add\n");
        return NULL;
    }

    TypeInfo* new = v1->TypeInfo;

    void* new_x = new->add(v1->x, v2->x);
    void* new_y = new->add(v1->y, v2->y);
    void* new_z = new->add(v1->z, v2->z);

    Vector3D* result = Vector3D_Create(new_x, new_y, new_z, new);

    free(new_x); free(new_y); free(new_z);

    return result;
}

void* Vector3D_DotProduct(const Vector3D* v1, const Vector3D* v2) {
    if (v1 == NULL || v2 == NULL) return NULL;
    if (v1->TypeInfo != v2->TypeInfo) {
        fprintf(stderr, "Error: Vectors have different types in Vector3D_DotProduct\n");
        return NULL;
    }
    TypeInfo* new = v1->TypeInfo;
    void* prod_x = new->multiply(v1->x, v2->x);
    void* prod_y = new->multiply(v1->y, v2->y);
    void* prod_z = new->multiply(v1->z, v2->z);

    void* temp = new->add(prod_x, prod_y);

    void* result = new->add(temp, prod_z);

    free(prod_x); free(prod_y); free(prod_z); free(temp);

    return result;
}
Vector3D* Vector3D_CrossProduct(const Vector3D* v1, const Vector3D* v2) {
    if (v1 == NULL || v2 == NULL) return NULL;

    TypeInfo* new = v1->TypeInfo;

    // CrossProduct: v1 × v2
    // result.x = v1.y * v2.z - v1.z * v2.y
    // result.y = v1.z * v2.x - v1.x * v2.z
    // result.z = v1.x * v2.y - v1.y * v2.x

    // Component X
    void* prod1_x = new->multiply(v1->y, v2->z);
    void* prod2_x = new->multiply(v1->z, v2->y);
    void* new_x = new->subtract(prod1_x, prod2_x);
    
    // Component Y
    void* prod1_y = new->multiply(v1->z, v2->x);
    void* prod2_y = new->multiply(v1->x, v2->z);
    void* new_y = new->subtract(prod1_y, prod2_y);
    
    // Component Z
    void* prod1_z = new->multiply(v1->x, v2->y);
    void* prod2_z = new->multiply(v1->y, v2->x);
    void* new_z = new->subtract(prod1_z, prod2_z);

    Vector3D* result = Vector3D_Create(new_x, new_y, new_z, new);

    free(new_x);
    free(new_y);
    free(new_z);
    free(prod1_x);
    free(prod1_y);
    free(prod1_z);
    free(prod2_x);
    free(prod2_y);
    free(prod2_z);
    free(new);

    return result;
}

//Utils

void Vector3D_Print(const Vector3D* vec) {
    if (vec == NULL) {
        printf("NULL vector\n");
        return;
    }

    if (vec->TypeInfo->print == NULL) {
        printf("(print function not available)");
        return;
    }

    printf("X = ");
    vec->TypeInfo->print(vec->x);
    printf("Y = ");
    vec->TypeInfo->print(vec->y);
    printf("Z = ");
    vec->TypeInfo->print(vec->z);
}
Vector3D* Vector3D_Clone(const Vector3D* vec) {
    if (vec == NULL) return NULL;
    return Vector3D_Create(vec->x, vec->y, vec->z, vec->TypeInfo);
}
