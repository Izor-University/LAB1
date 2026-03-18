#include "unity.h"
#include "TypeInfo.h"
#include "Vector3D.h"
#include "Complex.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* ─── Setup / Teardown ──────────────────────────────────── */
void setUp(void)    {}
void tearDown(void) {}

/* ─── Suite Setup / Teardown ────────────────────────────── */
void suiteSetUp(void) {}
int suiteTearDown(int num_failures) { return num_failures; }

/* ─── Вспомогательные макросы ───────────────────────────── */
#define DOUBLE_EPS 1e-9
#define ASSERT_DOUBLE_EQ(exp, got) \
    TEST_ASSERT_TRUE(fabs((exp) - (got)) < DOUBLE_EPS)

/* ─── TypeInfo: Double ──────────────────────────────────── */
void test_ofDouble_not_null(void) {
    TEST_ASSERT_NOT_NULL(ofDouble());
}

void test_ofDouble_singleton(void) {
    TEST_ASSERT_EQUAL_PTR(ofDouble(), ofDouble());
}

void test_double_add(void) {
    TypeInfo* t = ofDouble();
    double a = 3.0, b = 4.0, r;
    t->add(&r, &a, &b);
    ASSERT_DOUBLE_EQ(7.0, r);
}

void test_double_subtract(void) {
    TypeInfo* t = ofDouble();
    double a = 10.0, b = 3.0, r;
    t->subtract(&r, &a, &b);
    ASSERT_DOUBLE_EQ(7.0, r);
}

void test_double_multiply(void) {
    TypeInfo* t = ofDouble();
    double a = 3.0, b = 4.0, r;
    t->multiply(&r, &a, &b);
    ASSERT_DOUBLE_EQ(12.0, r);
}

void test_double_compare(void) {
    TypeInfo* t = ofDouble();
    double a = 1.0, b = 2.0, c = 1.0;
    TEST_ASSERT_EQUAL_INT(-1, t->compare(&a, &b));
    TEST_ASSERT_EQUAL_INT( 1, t->compare(&b, &a));
    TEST_ASSERT_EQUAL_INT( 0, t->compare(&a, &c));
}

/* ─── TypeInfo: Complex ─────────────────────────────────── */
void test_ofComplex_not_null(void) {
    TEST_ASSERT_NOT_NULL(ofComplex());
}

void test_ofComplex_singleton(void) {
    TEST_ASSERT_EQUAL_PTR(ofComplex(), ofComplex());
}

/* УДАЛЕНО: test_complex_create_zero - нет create_zero в TypeInfo */

void test_complex_add(void) {
    TypeInfo* t = ofComplex();
    Complex* a = malloc(Complex_SizeOf());
    Complex* b = malloc(Complex_SizeOf());
    Complex* r = malloc(Complex_SizeOf());
    Complex* expected = malloc(Complex_SizeOf());

    Complex_Create(a, 1.0, 2.0);
    Complex_Create(b, 3.0, 4.0);
    t->add(r, a, b);
    Complex_Create(expected, 4.0, 6.0);
    TEST_ASSERT_TRUE(Complex_Equal(r, expected));

    free(a); free(b); free(r); free(expected);
}

void test_complex_multiply(void) {
    TypeInfo* t = ofComplex();
    Complex* a = malloc(Complex_SizeOf());
    Complex* b = malloc(Complex_SizeOf());
    Complex* r = malloc(Complex_SizeOf());
    Complex* expected = malloc(Complex_SizeOf());

    Complex_Create(a, 1.0,  1.0);
    Complex_Create(b, 1.0, -1.0);
    t->multiply(r, a, b);
    Complex_Create(expected, 2.0, 0.0);
    TEST_ASSERT_TRUE(Complex_Equal(r, expected));

    free(a); free(b); free(r); free(expected);
}

void test_complex_compare_equal(void) {
    TypeInfo* t = ofComplex();
    Complex* a = malloc(Complex_SizeOf());
    Complex* b = malloc(Complex_SizeOf());
    Complex* c = malloc(Complex_SizeOf());

    Complex_Create(a, 1.0, 2.0);
    Complex_Create(b, 1.0, 2.0);
    Complex_Create(c, 0.0, 0.0);
    TEST_ASSERT_EQUAL_INT(0, t->compare(a, b));
    TEST_ASSERT_NOT_EQUAL(0, t->compare(a, c));

    free(a); free(b); free(c);
}

/* ─── Vector3D: создание ────────────────────────────────── */
void test_vector3d_create_double(void) {
    TypeInfo* t = ofDouble();
    double* xb = malloc(sizeof(double));
    double* yb = malloc(sizeof(double));
    double* zb = malloc(sizeof(double));
    *xb = 1.0; *yb = 2.0; *zb = 3.0;

    Vector3D* vec = malloc(Vector3D_SizeOf());
    Vector3D_Create(vec, xb, yb, zb, t);

    ASSERT_DOUBLE_EQ(1.0, *(double*)Vector3D_GetX(vec));
    ASSERT_DOUBLE_EQ(2.0, *(double*)Vector3D_GetY(vec));
    ASSERT_DOUBLE_EQ(3.0, *(double*)Vector3D_GetZ(vec));
    TEST_ASSERT_EQUAL_PTR(t, Vector3D_GetTypeInfo(vec));

    Vector3D_Destroy(vec);  /* Освобождает xb, yb, zb и vec */
}

void test_vector3d_create_complex(void) {
    TypeInfo* t = ofComplex();
    Complex* xb = malloc(Complex_SizeOf());
    Complex* yb = malloc(Complex_SizeOf());
    Complex* zb = malloc(Complex_SizeOf());
    Complex* cx = malloc(Complex_SizeOf());
    Complex* cy = malloc(Complex_SizeOf());
    Complex* cz = malloc(Complex_SizeOf());

    Complex_Create(cx, 1.0, 2.0);
    Complex_Create(cy, 3.0, 4.0);
    Complex_Create(cz, 5.0, 6.0);
    Complex_Copy(xb, cx);
    Complex_Copy(yb, cy);
    Complex_Copy(zb, cz);

    Vector3D* vec = malloc(Vector3D_SizeOf());
    Vector3D_Create(vec, xb, yb, zb, t);

    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetX(vec), xb));
    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetY(vec), yb));
    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetZ(vec), zb));

    Vector3D_Destroy(vec);  /* Освобождает xb, yb, zb и vec */
    free(cx); free(cy); free(cz);
}

void test_vector3d_create_null_args(void) {
    TypeInfo* t = ofDouble();
    double* xb = malloc(sizeof(double)); *xb = 1.0;
    double* yb = malloc(sizeof(double)); *yb = 2.0;
    double* zb = malloc(sizeof(double)); *zb = 3.0;

    Vector3D* vec = malloc(Vector3D_SizeOf());
    memset(vec, 0, Vector3D_SizeOf());

    /* Эти вызовы должны просто вернуться без изменений */
    Vector3D_Create(vec, NULL, yb, zb, t);
    TEST_ASSERT_NULL(vec->typeInfo);

    Vector3D_Create(vec, xb, NULL, zb, t);
    TEST_ASSERT_NULL(vec->typeInfo);

    Vector3D_Create(vec, xb, yb, NULL, t);
    TEST_ASSERT_NULL(vec->typeInfo);

    Vector3D_Create(vec, xb, yb, zb, NULL);
    TEST_ASSERT_NULL(vec->typeInfo);

    free(vec); free(xb); free(yb); free(zb);
}

/* ─── Vector3D: Clone ───────────────────────────────────── */
void test_vector3d_clone(void) {
    TypeInfo* t = ofDouble();
    double* xb = malloc(sizeof(double)); *xb = 1.0;
    double* yb = malloc(sizeof(double)); *yb = 2.0;
    double* zb = malloc(sizeof(double)); *zb = 3.0;

    Vector3D* src = malloc(Vector3D_SizeOf());
    Vector3D_Create(src, xb, yb, zb, t);

    Vector3D* clone = Vector3D_Clone(src);
    TEST_ASSERT_NOT_NULL(clone);
    TEST_ASSERT_TRUE(src != clone);
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetX(src), *(double*)Vector3D_GetX(clone));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetY(src), *(double*)Vector3D_GetY(clone));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetZ(src), *(double*)Vector3D_GetZ(clone));

    Vector3D_Destroy(clone);
    Vector3D_Destroy(src);
}

/* ─── Vector3D: Setters ─────────────────────────────────── */
void test_vector3d_setters(void) {
    TypeInfo* t = ofDouble();
    double* xb = malloc(sizeof(double)); *xb = 1.0;
    double* yb = malloc(sizeof(double)); *yb = 2.0;
    double* zb = malloc(sizeof(double)); *zb = 3.0;

    Vector3D* vec = malloc(Vector3D_SizeOf());
    Vector3D_Create(vec, xb, yb, zb, t);

    double* nx = malloc(sizeof(double)); *nx = 10.0;
    double* ny = malloc(sizeof(double)); *ny = 20.0;
    double* nz = malloc(sizeof(double)); *nz = 30.0;

    Vector3D_SetX(vec, nx);
    Vector3D_SetY(vec, ny);
    Vector3D_SetZ(vec, nz);

    ASSERT_DOUBLE_EQ(10.0, *(double*)Vector3D_GetX(vec));
    ASSERT_DOUBLE_EQ(20.0, *(double*)Vector3D_GetY(vec));
    ASSERT_DOUBLE_EQ(30.0, *(double*)Vector3D_GetZ(vec));

    free(nx); free(ny); free(nz);
    Vector3D_Destroy(vec);
}

/* ─── Vector3D: Add ─────────────────────────────────────── */
void test_vector3d_add_double(void) {
    TypeInfo* t = ofDouble();
    double* x1 = malloc(sizeof(double)); *x1 = 1;
    double* y1 = malloc(sizeof(double)); *y1 = 2;
    double* z1 = malloc(sizeof(double)); *z1 = 3;
    double* x2 = malloc(sizeof(double)); *x2 = 4;
    double* y2 = malloc(sizeof(double)); *y2 = 5;
    double* z2 = malloc(sizeof(double)); *z2 = 6;

    Vector3D* v1 = malloc(Vector3D_SizeOf());
    Vector3D* v2 = malloc(Vector3D_SizeOf());
    Vector3D* sum = malloc(Vector3D_SizeOf());

    double* sx = malloc(sizeof(double)); *sx = 0;
    double* sy = malloc(sizeof(double)); *sy = 0;
    double* sz = malloc(sizeof(double)); *sz = 0;
    Vector3D_Create(sum, sx, sy, sz, t);

    Vector3D_Create(v1, x1, y1, z1, t);
    Vector3D_Create(v2, x2, y2, z2, t);

    Vector3D_Add(sum, v1, v2);
    ASSERT_DOUBLE_EQ(5.0, *(double*)Vector3D_GetX(sum));
    ASSERT_DOUBLE_EQ(7.0, *(double*)Vector3D_GetY(sum));
    ASSERT_DOUBLE_EQ(9.0, *(double*)Vector3D_GetZ(sum));

    Vector3D_Destroy(v1);
    Vector3D_Destroy(v2);
    Vector3D_Destroy(sum);
}

void test_vector3d_add_null(void) {
    TypeInfo* t = ofDouble();
    double* xb = malloc(sizeof(double)); *xb = 1;
    double* yb = malloc(sizeof(double)); *yb = 2;
    double* zb = malloc(sizeof(double)); *zb = 3;

    Vector3D* v1 = malloc(Vector3D_SizeOf());
    Vector3D* sum = malloc(Vector3D_SizeOf());

    double* sx = malloc(sizeof(double)); *sx = 100;
    double* sy = malloc(sizeof(double)); *sy = 100;
    double* sz = malloc(sizeof(double)); *sz = 100;
    Vector3D_Create(sum, sx, sy, sz, t);
    Vector3D_Create(v1, xb, yb, zb, t);

    double orig_x = *(double*)Vector3D_GetX(sum);
    double orig_y = *(double*)Vector3D_GetY(sum);
    double orig_z = *(double*)Vector3D_GetZ(sum);

    Vector3D_Add(sum, v1, NULL);
    ASSERT_DOUBLE_EQ(orig_x, *(double*)Vector3D_GetX(sum));
    ASSERT_DOUBLE_EQ(orig_y, *(double*)Vector3D_GetY(sum));
    ASSERT_DOUBLE_EQ(orig_z, *(double*)Vector3D_GetZ(sum));

    Vector3D_Add(sum, NULL, v1);
    ASSERT_DOUBLE_EQ(orig_x, *(double*)Vector3D_GetX(sum));
    ASSERT_DOUBLE_EQ(orig_y, *(double*)Vector3D_GetY(sum));
    ASSERT_DOUBLE_EQ(orig_z, *(double*)Vector3D_GetZ(sum));

    Vector3D_Destroy(v1);
    Vector3D_Destroy(sum);
}

/* ─── Vector3D: DotProduct ──────────────────────────────── */
void test_vector3d_dot_product(void) {
    TypeInfo* t = ofDouble();
    double* x1 = malloc(sizeof(double)); *x1 = 1;
    double* y1 = malloc(sizeof(double)); *y1 = 2;
    double* z1 = malloc(sizeof(double)); *z1 = 3;
    double* x2 = malloc(sizeof(double)); *x2 = 4;
    double* y2 = malloc(sizeof(double)); *y2 = 5;
    double* z2 = malloc(sizeof(double)); *z2 = 6;

    Vector3D* v1 = malloc(Vector3D_SizeOf());
    Vector3D* v2 = malloc(Vector3D_SizeOf());
    Vector3D_Create(v1, x1, y1, z1, t);
    Vector3D_Create(v2, x2, y2, z2, t);

    double* dot = malloc(sizeof(double));
    Vector3D_DotProduct(dot, v1, v2);
    ASSERT_DOUBLE_EQ(32.0, *dot);

    Vector3D_Destroy(v1);
    Vector3D_Destroy(v2);
    free(dot);
}

void test_vector3d_dot_orthogonal(void) {
    TypeInfo* t = ofDouble();
    double* x1 = malloc(sizeof(double)); *x1 = 1;
    double* y1 = malloc(sizeof(double)); *y1 = 0;
    double* z1 = malloc(sizeof(double)); *z1 = 0;
    double* x2 = malloc(sizeof(double)); *x2 = 0;
    double* y2 = malloc(sizeof(double)); *y2 = 1;
    double* z2 = malloc(sizeof(double)); *z2 = 0;

    Vector3D* v1 = malloc(Vector3D_SizeOf());
    Vector3D* v2 = malloc(Vector3D_SizeOf());
    Vector3D_Create(v1, x1, y1, z1, t);
    Vector3D_Create(v2, x2, y2, z2, t);

    double* dot = malloc(sizeof(double));
    Vector3D_DotProduct(dot, v1, v2);
    ASSERT_DOUBLE_EQ(0.0, *dot);

    Vector3D_Destroy(v1);
    Vector3D_Destroy(v2);
    free(dot);
}

/* ─── Vector3D: CrossProduct ────────────────────────────── */
void test_vector3d_cross_product(void) {
    TypeInfo* t = ofDouble();
    double* x1 = malloc(sizeof(double)); *x1 = 1;
    double* y1 = malloc(sizeof(double)); *y1 = 0;
    double* z1 = malloc(sizeof(double)); *z1 = 0;
    double* x2 = malloc(sizeof(double)); *x2 = 0;
    double* y2 = malloc(sizeof(double)); *y2 = 1;
    double* z2 = malloc(sizeof(double)); *z2 = 0;

    Vector3D* v1 = malloc(Vector3D_SizeOf());
    Vector3D* v2 = malloc(Vector3D_SizeOf());
    Vector3D* cross = malloc(Vector3D_SizeOf());

    double* cx = malloc(sizeof(double)); *cx = 0;
    double* cy = malloc(sizeof(double)); *cy = 0;
    double* cz = malloc(sizeof(double)); *cz = 0;
    Vector3D_Create(cross, cx, cy, cz, t);

    Vector3D_Create(v1, x1, y1, z1, t);
    Vector3D_Create(v2, x2, y2, z2, t);

    Vector3D_CrossProduct(cross, v1, v2);
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetX(cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetY(cross));
    ASSERT_DOUBLE_EQ(1.0, *(double*)Vector3D_GetZ(cross));

    Vector3D_Destroy(v1);
    Vector3D_Destroy(v2);
    Vector3D_Destroy(cross);
}

void test_vector3d_cross_anticommutativity(void) {
    TypeInfo* t = ofDouble();
    double* x1 = malloc(sizeof(double)); *x1 = 1;
    double* y1 = malloc(sizeof(double)); *y1 = 2;
    double* z1 = malloc(sizeof(double)); *z1 = 3;
    double* x2 = malloc(sizeof(double)); *x2 = 4;
    double* y2 = malloc(sizeof(double)); *y2 = 5;
    double* z2 = malloc(sizeof(double)); *z2 = 6;

    Vector3D* v1 = malloc(Vector3D_SizeOf());
    Vector3D* v2 = malloc(Vector3D_SizeOf());
    Vector3D* c12 = malloc(Vector3D_SizeOf());
    Vector3D* c21 = malloc(Vector3D_SizeOf());

    double* cx12 = malloc(sizeof(double)); *cx12 = 0;
    double* cy12 = malloc(sizeof(double)); *cy12 = 0;
    double* cz12 = malloc(sizeof(double)); *cz12 = 0;
    double* cx21 = malloc(sizeof(double)); *cx21 = 0;
    double* cy21 = malloc(sizeof(double)); *cy21 = 0;
    double* cz21 = malloc(sizeof(double)); *cz21 = 0;

    Vector3D_Create(v1, x1, y1, z1, t);
    Vector3D_Create(v2, x2, y2, z2, t);
    Vector3D_Create(c12, cx12, cy12, cz12, t);
    Vector3D_Create(c21, cx21, cy21, cz21, t);

    Vector3D_CrossProduct(c12, v1, v2);
    Vector3D_CrossProduct(c21, v2, v1);

    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetX(c12), -*(double*)Vector3D_GetX(c21));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetY(c12), -*(double*)Vector3D_GetY(c21));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetZ(c12), -*(double*)Vector3D_GetZ(c21));

    Vector3D_Destroy(v1);
    Vector3D_Destroy(v2);
    Vector3D_Destroy(c12);
    Vector3D_Destroy(c21);
}

void test_vector3d_cross_self_is_zero(void) {
    TypeInfo* t = ofDouble();
    double* x = malloc(sizeof(double)); *x = 3;
    double* y = malloc(sizeof(double)); *y = 7;
    double* z = malloc(sizeof(double)); *z = 2;

    Vector3D* v = malloc(Vector3D_SizeOf());
    Vector3D* cross = malloc(Vector3D_SizeOf());

    double* cx = malloc(sizeof(double)); *cx = 0;
    double* cy = malloc(sizeof(double)); *cy = 0;
    double* cz = malloc(sizeof(double)); *cz = 0;
    Vector3D_Create(cross, cx, cy, cz, t);
    Vector3D_Create(v, x, y, z, t);

    Vector3D_CrossProduct(cross, v, v);
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetX(cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetY(cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetZ(cross));

    Vector3D_Destroy(v);
    Vector3D_Destroy(cross);
}

/* ─── TypeInfo синглтон не портится после операций ──────── */
void test_typeinfo_singleton_survives_ops(void) {
    TypeInfo* t_before = ofDouble();
    double* x1 = malloc(sizeof(double)); *x1 = 1;
    double* y1 = malloc(sizeof(double)); *y1 = 0;
    double* z1 = malloc(sizeof(double)); *z1 = 0;
    double* x2 = malloc(sizeof(double)); *x2 = 0;
    double* y2 = malloc(sizeof(double)); *y2 = 1;
    double* z2 = malloc(sizeof(double)); *z2 = 0;

    Vector3D* v1 = malloc(Vector3D_SizeOf());
    Vector3D* v2 = malloc(Vector3D_SizeOf());
    Vector3D* cross = malloc(Vector3D_SizeOf());

    double* cx = malloc(sizeof(double)); *cx = 0;
    double* cy = malloc(sizeof(double)); *cy = 0;
    double* cz = malloc(sizeof(double)); *cz = 0;

    Vector3D_Create(v1, x1, y1, z1, t_before);
    Vector3D_Create(v2, x2, y2, z2, t_before);
    Vector3D_Create(cross, cx, cy, cz, t_before);

    Vector3D_CrossProduct(cross, v1, v2);
    TypeInfo* t_after = ofDouble();

    TEST_ASSERT_EQUAL_PTR(t_before, t_after);
    TEST_ASSERT_NOT_NULL(t_after->add);

    Vector3D_Destroy(v1);
    Vector3D_Destroy(v2);
    Vector3D_Destroy(cross);
}

/* ─── main ──────────────────────────────────────────────── */
int main(void) {
    UNITY_BEGIN();

    /* TypeInfo: double */
    RUN_TEST(test_ofDouble_not_null);
    RUN_TEST(test_ofDouble_singleton);
    RUN_TEST(test_double_add);
    RUN_TEST(test_double_subtract);
    RUN_TEST(test_double_multiply);
    RUN_TEST(test_double_compare);

    /* TypeInfo: Complex */
    RUN_TEST(test_ofComplex_not_null);
    RUN_TEST(test_ofComplex_singleton);
    RUN_TEST(test_complex_add);
    RUN_TEST(test_complex_multiply);
    RUN_TEST(test_complex_compare_equal);

    /* Vector3D: Create */
    RUN_TEST(test_vector3d_create_double);
    RUN_TEST(test_vector3d_create_complex);
    RUN_TEST(test_vector3d_create_null_args);

    /* Vector3D: Clone / Setters */
    RUN_TEST(test_vector3d_clone);
    RUN_TEST(test_vector3d_setters);

    /* Vector3D: Add */
    RUN_TEST(test_vector3d_add_double);
    RUN_TEST(test_vector3d_add_null);

    /* Vector3D: DotProduct */
    RUN_TEST(test_vector3d_dot_product);
    RUN_TEST(test_vector3d_dot_orthogonal);

    /* Vector3D: CrossProduct */
    RUN_TEST(test_vector3d_cross_product);
    RUN_TEST(test_vector3d_cross_anticommutativity);
    RUN_TEST(test_vector3d_cross_self_is_zero);

    /* Синглтон не разрушается */
    RUN_TEST(test_typeinfo_singleton_survives_ops);

    TypeInfo_FreeAll();
    return UNITY_END();
}