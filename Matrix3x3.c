#include "Matrix3x3.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Matrix3x3 {
    void* data[3][3];
    TypeInfo* typeInfo;
};

size_t Matrix3x3_SizeOf(void) {
    return sizeof(struct Matrix3x3);
}

void Matrix3x3_Create(Matrix3x3* mat, void* data[3][3], TypeInfo* typeInfo) {
    if (!mat || !data || !typeInfo) return;
    mat->typeInfo = typeInfo;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            mat->data[i][j] = data[i][j];
        }
    }
}

void Matrix3x3_Destroy(Matrix3x3* mat) {
    if (!mat) return;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (mat->typeInfo->destroy) {
                mat->typeInfo->destroy(mat->data[i][j]);
            }
            free(mat->data[i][j]);
        }
    }
    free(mat);
}

void Matrix3x3_MakeRotation(Matrix3x3* mat, char axis, double angle) {
    if (!mat) return;
    if (mat->typeInfo != ofDouble()) {
        fprintf(stderr, "Error: Rotation matrix initialization supports only double type.\n");
        return;
    }

    double c = cos(angle);
    double s = sin(angle);
    double temp[3][3] = {0}; // Инициализируем нулями

    if (axis == 'x' || axis == 'X') {
        temp[0][0] = 1.0;
        temp[1][1] = c;  temp[1][2] = -s;
        temp[2][1] = s;  temp[2][2] = c;
    } else if (axis == 'y' || axis == 'Y') {
        temp[0][0] = c;  temp[0][2] = s;
        temp[1][1] = 1.0;
        temp[2][0] = -s; temp[2][2] = c;
    } else if (axis == 'z' || axis == 'Z') {
        temp[0][0] = c;  temp[0][1] = -s;
        temp[1][0] = s;  temp[1][1] = c;
        temp[2][2] = 1.0;
    } else {
        fprintf(stderr, "Error: Invalid rotation axis '%c'.\n", axis);
        return;
    }

    // Копируем полиморфно
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            mat->typeInfo->copy(mat->data[i][j], &temp[i][j]);
        }
    }
}

void Matrix3x3_MultiplyVector(Vector3D* result, const Matrix3x3* mat, const Vector3D* vec) {
    if (!result || !mat || !vec) return;
    if (mat->typeInfo != Vector3D_GetTypeInfo(vec)) {
        fprintf(stderr, "Error: Type mismatch between matrix and vector.\n");
        return;
    }

    TypeInfo* ti = mat->typeInfo;
    
    void* vec_data[3] = { Vector3D_GetX(vec), Vector3D_GetY(vec), Vector3D_GetZ(vec) };
    void* res_data[3] = { Vector3D_GetX(result), Vector3D_GetY(result), Vector3D_GetZ(result) };

    void* term = malloc(ti->element_size);
    void* sum = malloc(ti->element_size);

    for (int i = 0; i < 3; ++i) {
        // Код стал гораздо чище без арифметики индексов (i * 3 + j)
        ti->multiply(sum, mat->data[i][0], vec_data[0]);
        
        ti->multiply(term, mat->data[i][1], vec_data[1]);
        ti->add(sum, sum, term);
        
        ti->multiply(term, mat->data[i][2], vec_data[2]);
        ti->add(sum, sum, term);
        
        ti->copy(res_data[i], sum);
    }

    free(term);
    free(sum);
}