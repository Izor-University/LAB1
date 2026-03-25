// main.c
#include "Vector3D.h"
#include "TypeInfo.h"
#include "Complex.h"
#include "Matrix3x3.h"
#include <stdio.h>
#include <stdlib.h>

// ========== Prototypes ==========

void print_menu(void);
Vector3D* create_double_vector(void);
Vector3D* create_complex_vector(void);
Vector3D* create_vector_same_type(Vector3D* v1);
void handle_add(Vector3D* v1);
void handle_dot(Vector3D* v1);
void handle_cross(Vector3D* v1);
void handle_rotate(Vector3D* v1);

// ========== Main ==========

int main(void) {
    Vector3D* v1 = NULL;

    printf("3D Vector Implementation\n");
    printf("Laboratory Work 1, Variant 10\n");

    while (1) {
        print_menu();
        int choice = -1;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }
        switch (choice) {
        case 1:
            if (v1) Vector3D_Destroy(v1);
            v1 = create_double_vector();
            if (v1) {
                printf("v1 =\n");
                Vector3D_Print(v1);
            }
            break;

        case 2:
            if (v1) Vector3D_Destroy(v1);
            v1 = create_complex_vector();
            if (v1) {
                printf("v1 =\n");
                Vector3D_Print(v1);
            }
            break;

        case 3:
            if (!v1) { printf("No vector. Create one first.\n"); break; }
            handle_add(v1);
            break;

        case 4:
            if (!v1) { printf("No vector. Create one first.\n"); break; }
            handle_dot(v1);
            break;

        case 5:
            if (!v1) { printf("No vector. Create one first.\n"); break; }
            handle_cross(v1);
            break;

        case 6:
            if (!v1) { printf("No vector. Create one first.\n"); break; }
            handle_rotate(v1);
            break;

        case 7:
            if (!v1) { printf("No vector.\n"); break; }
            printf("v1 =\n");
            Vector3D_Print(v1);
            break;

        case 0:
            if (v1) Vector3D_Destroy(v1);
            TypeInfo_FreeAll();
            printf("Exit.\n");
            return 0;

        default:
            printf("Invalid choice.\n");
            break;
        }
    }
}

// ========== Menu ==========

void print_menu(void) {
    printf("\n");
    printf("1. Create double vector\n");
    printf("2. Create complex vector\n");
    printf("3. Add (v1 + v2)\n");
    printf("4. Dot (v1 . v2)\n");
    printf("5. Cross (v1 x v2)\n");
    printf("6. Rotate (double only)\n");
    printf("7. Print v1\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

// ========== Create ==========

Vector3D* create_double_vector(void) {
    double x, y, z;
    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) { while (getchar() != '\n'); return NULL; }
    printf("Enter y: ");
    if (scanf("%lf", &y) != 1) { while (getchar() != '\n'); return NULL; }
    printf("Enter z: ");
    if (scanf("%lf", &z) != 1) { while (getchar() != '\n'); return NULL; }

    TypeInfo* ti = ofDouble();

    double* xb = malloc(ti->element_size);
    double* yb = malloc(ti->element_size);
    double* zb = malloc(ti->element_size);
    if (!xb || !yb || !zb) {
        free(xb); free(yb); free(zb);
        return NULL;
    }
    *xb = x; *yb = y; *zb = z;

    Vector3D* vec = malloc(Vector3D_SizeOf());
    if (!vec) {
        free(xb); free(yb); free(zb);
        return NULL;
    }

    Vector3D_Create(vec, xb, yb, zb, ti);
    return vec;
}

Vector3D* create_complex_vector(void) {
    double x_re, x_im, y_re, y_im, z_re, z_im;
    printf("Enter x (real imag): ");
    if (scanf("%lf %lf", &x_re, &x_im) != 2) { while (getchar() != '\n'); return NULL; }
    printf("Enter y (real imag): ");
    if (scanf("%lf %lf", &y_re, &y_im) != 2) { while (getchar() != '\n'); return NULL; }
    printf("Enter z (real imag): ");
    if (scanf("%lf %lf", &z_re, &z_im) != 2) { while (getchar() != '\n'); return NULL; }

    TypeInfo* ti = ofComplex();

    Complex* xb = malloc(Complex_SizeOf());
    Complex* yb = malloc(Complex_SizeOf());
    Complex* zb = malloc(Complex_SizeOf());

    if (!xb || !yb || !zb) {
        free(xb); free(yb); free(zb);
        printf("Error: allocation failed.\n");
        return NULL;
    }

    Complex_Create(xb, x_re, x_im);
    Complex_Create(yb, y_re, y_im);
    Complex_Create(zb, z_re, z_im);

    Vector3D* vec = malloc(Vector3D_SizeOf());
    if (!vec) {
        free(xb); free(yb); free(zb);
        printf("Error: allocation failed.\n");
        return NULL;
    }

    Vector3D_Create(vec, xb, yb, zb, ti);
    return vec;
}

Vector3D* create_vector_same_type(Vector3D* v1) {
    if (Vector3D_GetTypeInfo(v1) == ofDouble())
        return create_double_vector();
    else
        return create_complex_vector();
}

// ========== Operations ==========

void handle_add(Vector3D* v1) {
    printf("Enter second vector:\n");
    Vector3D* v2 = create_vector_same_type(v1);
    if (!v2) { printf("Failed to create vector.\n"); return; }

    TypeInfo* ti = Vector3D_GetTypeInfo(v1);

    Vector3D* result = malloc(Vector3D_SizeOf());
    void* rx = malloc(ti->element_size);
    void* ry = malloc(ti->element_size);
    void* rz = malloc(ti->element_size);

    if (!result || !rx || !ry || !rz) {
        free(result); free(rx); free(ry); free(rz);
        Vector3D_Destroy(v2);
        return;
    }

    Vector3D_Create(result, rx, ry, rz, ti);
    Vector3D_Add(result, v1, v2);

    printf("v1 =\n"); Vector3D_Print(v1);
    printf("v2 =\n"); Vector3D_Print(v2);
    printf("v1 + v2 =\n"); Vector3D_Print(result);

    Vector3D_Destroy(result);
    Vector3D_Destroy(v2);
}

void handle_dot(Vector3D* v1) {
    printf("Enter second vector:\n");
    Vector3D* v2 = create_vector_same_type(v1);
    if (!v2) { printf("Failed to create vector.\n"); return; }

    TypeInfo* ti = Vector3D_GetTypeInfo(v1);
    void* result = malloc(ti->element_size);
    if (!result) { Vector3D_Destroy(v2); return; }

    Vector3D_DotProduct(result, v1, v2);

    printf("v1 =\n"); Vector3D_Print(v1);
    printf("v2 =\n"); Vector3D_Print(v2);
    printf("v1 . v2 = ");

    ti->print(result);

    free(result);
    Vector3D_Destroy(v2);
}

void handle_cross(Vector3D* v1) {
    printf("Enter second vector:\n");
    Vector3D* v2 = create_vector_same_type(v1);
    if (!v2) { printf("Failed to create vector.\n"); return; }

    TypeInfo* ti = Vector3D_GetTypeInfo(v1);

    Vector3D* result = malloc(Vector3D_SizeOf());
    void* rx = malloc(ti->element_size);
    void* ry = malloc(ti->element_size);
    void* rz = malloc(ti->element_size);

    if (!result || !rx || !ry || !rz) {
        free(result); free(rx); free(ry); free(rz);
        Vector3D_Destroy(v2);
        return;
    }

    Vector3D_Create(result, rx, ry, rz, ti);
    Vector3D_CrossProduct(result, v1, v2);

    printf("v1 =\n"); Vector3D_Print(v1);
    printf("v2 =\n"); Vector3D_Print(v2);
    printf("v1 x v2 =\n"); Vector3D_Print(result);

    Vector3D_Destroy(result);
    Vector3D_Destroy(v2);
}

void handle_rotate(Vector3D* v1) {
    if (Vector3D_GetTypeInfo(v1) != ofDouble()) {
        printf("Rotation is only supported for double vectors.\n");
        return;
    }

    char axis;
    double angle;
    printf("Enter axis (x, y, z): ");
    if (scanf(" %c", &axis) != 1) { while (getchar() != '\n'); return; }
    printf("Enter angle (in radians): ");
    if (scanf("%lf", &angle) != 1) { while (getchar() != '\n'); return; }

    TypeInfo* ti = Vector3D_GetTypeInfo(v1);

    Vector3D* result = malloc(Vector3D_SizeOf());
    void* rx = malloc(ti->element_size);
    void* ry = malloc(ti->element_size);
    void* rz = malloc(ti->element_size);
    if (!result || !rx || !ry || !rz) {
        free(result); free(rx); free(ry); free(rz);
        printf("Allocation failed.\n");
        return;
    }
    Vector3D_Create(result, rx, ry, rz, ti);

    Matrix3x3* rot_matrix = malloc(Matrix3x3_SizeOf());
    void* mat_data[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            mat_data[i][j] = malloc(ti->element_size);
            if (ti == ofDouble()) { 
                *(double*)mat_data[i][j] = 0.0; 
            }
        }
    }
    Matrix3x3_Create(rot_matrix, mat_data, ti);

    Matrix3x3_MakeRotation(rot_matrix, axis, angle);
    Matrix3x3_MultiplyVector(result, rot_matrix, v1);

    printf("v1 rotated around '%c' by %.3f rad =\n", axis, angle);
    Vector3D_Print(result);

    Matrix3x3_Destroy(rot_matrix);
    Vector3D_Destroy(result);
}