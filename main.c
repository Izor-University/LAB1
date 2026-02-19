//
// Created by OPS on 17.02.2026.
//

#include "Vector3D.h"
#include "TypeInfo.h"
#include "Complex.h"
#include <stdio.h>
#include <stdlib.h>

// ========== Prototypes ==========

void print_menu();
Vector3D* create_double_vector();
Vector3D* create_complex_vector();
Vector3D* create_vector_same_type(Vector3D* v1);
void handle_add(Vector3D* v1);
void handle_dot(Vector3D* v1);
void handle_cross(Vector3D* v1);

// ========== Main ==========

int main() {
    Vector3D* v1 = NULL;
    int choice;

    printf("3D Vector Implementation\n");
    printf("Laboratory Work 1, Variant 10\n");

    while (1) {
        print_menu();

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
                if (!v1) { printf("No vector.\n"); break; }
                printf("v1 =\n");
                Vector3D_Print(v1);
                break;

            case 0:
                if (v1) Vector3D_Destroy(v1);
                printf("Exit.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}

// ========== Menu ==========

void print_menu() {
    printf("\n");
    printf("1. Create double vector\n");
    printf("2. Create complex vector\n");
    printf("3. Add (v1 + v2)\n");
    printf("4. Dot product (v1 . v2)\n");
    printf("5. Cross product (v1 x v2)\n");
    printf("6. Print v1\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

// ========== Create ==========

Vector3D* create_double_vector() {
    double x, y, z;

    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) { while (getchar() != '\n'); return NULL; }

    printf("Enter y: ");
    if (scanf("%lf", &y) != 1) { while (getchar() != '\n'); return NULL; }

    printf("Enter z: ");
    if (scanf("%lf", &z) != 1) { while (getchar() != '\n'); return NULL; }

    return Vector3D_Create(&x, &y, &z, (TypeInfo*)ofDouble());
}

Vector3D* create_complex_vector() {
    double x_re, x_im, y_re, y_im, z_re, z_im;

    printf("Enter x (real imag): ");
    if (scanf("%lf %lf", &x_re, &x_im) != 2) { while (getchar() != '\n'); return NULL; }

    printf("Enter y (real imag): ");
    if (scanf("%lf %lf", &y_re, &y_im) != 2) { while (getchar() != '\n'); return NULL; }

    printf("Enter z (real imag): ");
    if (scanf("%lf %lf", &z_re, &z_im) != 2) { while (getchar() != '\n'); return NULL; }

    Complex* x = Complex_Create(x_re, x_im);
    Complex* y = Complex_Create(y_re, y_im);
    Complex* z = Complex_Create(z_re, z_im);

    if (!x || !y || !z) {
        Complex_Destroy(x);
        Complex_Destroy(y);
        Complex_Destroy(z);
        printf("Error: allocation failed.\n");
        return NULL;
    }

    Vector3D* vec = Vector3D_Create(x, y, z, (TypeInfo*)ofComplex());

    Complex_Destroy(x);
    Complex_Destroy(y);
    Complex_Destroy(z);

    return vec;
}

// Создает второй вектор того же типа, что и v1
Vector3D* create_vector_same_type(Vector3D* v1) {
    if (v1->TypeInfo == (TypeInfo*)ofDouble()) {
        return create_double_vector();
    } else {
        return create_complex_vector();
    }
}

// ========== Operations ==========

void handle_add(Vector3D* v1) {
    printf("Enter second vector:\n");
    Vector3D* v2 = create_vector_same_type(v1);
    if (!v2) { printf("Failed to create vector.\n"); return; }

    Vector3D* result = Vector3D_Add(v1, v2);

    if (result) {
        printf("v1 =\n");
        Vector3D_Print(v1);
        printf("v2 =\n");
        Vector3D_Print(v2);
        printf("v1 + v2 =\n");
        Vector3D_Print(result);
        Vector3D_Destroy(result);
    }

    Vector3D_Destroy(v2);
}

void handle_dot(Vector3D* v1) {
    printf("Enter second vector:\n");
    Vector3D* v2 = create_vector_same_type(v1);
    if (!v2) { printf("Failed to create vector.\n"); return; }

    void* result = Vector3D_DotProduct(v1, v2);

    if (result) {
        printf("v1 =\n");
        Vector3D_Print(v1);
        printf("v2 =\n");
        Vector3D_Print(v2);
        printf("v1 . v2 = ");

        if (v1->TypeInfo == (TypeInfo*)ofDouble()) {
            printf("%lf\n", *(double*)result);
            free(result);
        } else {
            Complex_Print((Complex*)result);
            printf("\n");
            free(result);
        }
    }

    Vector3D_Destroy(v2);
}

void handle_cross(Vector3D* v1) {
    printf("Enter second vector:\n");
    Vector3D* v2 = create_vector_same_type(v1);
    if (!v2) { printf("Failed to create vector.\n"); return; }

    Vector3D* result = Vector3D_CrossProduct(v1, v2);

    if (result) {
        printf("v1 =\n");
        Vector3D_Print(v1);
        printf("v2 =\n");
        Vector3D_Print(v2);
        printf("v1 x v2 =\n");
        Vector3D_Print(result);
        Vector3D_Destroy(result);
    }

    Vector3D_Destroy(v2);
}
