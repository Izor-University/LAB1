#include "unity.h"

#include "TypeInfo.h"
#include "Vector3D.h"
#include "Complex.h"
#include <stdlib.h>
#include <math.h>

/* ─── Setup / Teardown ──────────────────────────────────── */

void setUp(void)    {}
void tearDown(void) {}

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

void test_double_create_zero(void) {
    TypeInfo* t = ofDouble();
    double z;
    t->create_zero(&z);
    ASSERT_DOUBLE_EQ(0.0, z);
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

void test_complex_create_zero(void) {
    TypeInfo* t = ofComplex();
    Complex z;
    t->create_zero(&z);
    Complex expected;
    Complex_Zero(&expected);
    TEST_ASSERT_TRUE(Complex_Equal(&z, &expected));
}

void test_complex_add(void) {
    TypeInfo* t = ofComplex();
    Complex a, b, r, expected;
    Complex_Create(&a, 1.0, 2.0);
    Complex_Create(&b, 3.0, 4.0);
    t->add(&r, &a, &b);
    Complex_Create(&expected, 4.0, 6.0);
    TEST_ASSERT_TRUE(Complex_Equal(&r, &expected));
}

void test_complex_multiply(void) {
    TypeInfo* t = ofComplex();
    /* (1+i)(1-i) = 1 - i^2 = 2 */
    Complex a, b, r, expected;
    Complex_Create(&a, 1.0,  1.0);
    Complex_Create(&b, 1.0, -1.0);
    t->multiply(&r, &a, &b);
    Complex_Create(&expected, 2.0, 0.0);
    TEST_ASSERT_TRUE(Complex_Equal(&r, &expected));
}

void test_complex_compare_equal(void) {
    TypeInfo* t = ofComplex();
    Complex a, b, c;
    Complex_Create(&a, 1.0, 2.0);
    Complex_Create(&b, 1.0, 2.0);
    Complex_Create(&c, 0.0, 0.0);
    TEST_ASSERT_EQUAL_INT(0, t->compare(&a, &b));   /* равны  → 0 */
    TEST_ASSERT_NOT_EQUAL(0, t->compare(&a, &c));   /* разные → !=0 */
}

/* ─── Vector3D: создание ────────────────────────────────── */

void test_vector3d_create_double(void) {
    TypeInfo* t = ofDouble();
    double xb, yb, zb;
    double x=1.0, y=2.0, z=3.0;

    xb = x; yb = y; zb = z;

    Vector3D vec;
    Vector3D_Create(&vec, &xb, &yb, &zb, t);

    ASSERT_DOUBLE_EQ(1.0, *(double*)Vector3D_GetX(&vec));
    ASSERT_DOUBLE_EQ(2.0, *(double*)Vector3D_GetY(&vec));
    ASSERT_DOUBLE_EQ(3.0, *(double*)Vector3D_GetZ(&vec));
    TEST_ASSERT_EQUAL_PTR(t, Vector3D_GetTypeInfo(&vec));
}

void test_vector3d_create_complex(void) {
    TypeInfo* t = ofComplex();
    Complex xb, yb, zb;
    Complex cx, cy, cz;
    Complex_Create(&cx, 1.0, 2.0);
    Complex_Create(&cy, 3.0, 4.0);
    Complex_Create(&cz, 5.0, 6.0);

    Complex_Copy(&xb, &cx);
    Complex_Copy(&yb, &cy);
    Complex_Copy(&zb, &cz);

    Vector3D vec;
    Vector3D_Create(&vec, &xb, &yb, &zb, t);

    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetX(&vec), &xb));
    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetY(&vec), &yb));
    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetZ(&vec), &zb));
}

void test_vector3d_create_null_args(void) {
    TypeInfo* t = ofDouble();
    double xb=1.0, yb=2.0, zb=3.0;

    Vector3D vec;
    Vector3D_Create(&vec, NULL, &yb, &zb, t);
    TEST_ASSERT_NULL(Vector3D_GetTypeInfo(&vec));

    Vector3D_Create(&vec, &xb, NULL, &zb, t);
    TEST_ASSERT_NULL(Vector3D_GetTypeInfo(&vec));

    Vector3D_Create(&vec, &xb, &yb, NULL, t);
    TEST_ASSERT_NULL(Vector3D_GetTypeInfo(&vec));

    Vector3D_Create(&vec, &xb, &yb, &zb, NULL);
    TEST_ASSERT_NULL(Vector3D_GetTypeInfo(&vec));
}

/* ─── Vector3D: Clone ───────────────────────────────────── */

void test_vector3d_clone(void) {
    TypeInfo* t = ofDouble();
    double x=1.0, y=2.0, z=3.0;

    double xb, yb, zb;
    xb = x; yb = y; zb = z;

    Vector3D src;
    Vector3D_Create(&src, &xb, &yb, &zb, t);

    Vector3D* clone = Vector3D_Clone(&src);
    TEST_ASSERT_NOT_NULL(clone);
    TEST_ASSERT_TRUE(&src != clone);
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetX(&src), *(double*)Vector3D_GetX(clone));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetY(&src), *(double*)Vector3D_GetY(clone));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetZ(&src), *(double*)Vector3D_GetZ(clone));
    Vector3D_Destroy(clone);
}

/* ─── Vector3D: Setters ─────────────────────────────────── */

void test_vector3d_setters(void) {
    TypeInfo* t = ofDouble();
    double xb=1.0, yb=2.0, zb=3.0;

    Vector3D vec;
    Vector3D_Create(&vec, &xb, &yb, &zb, t);

    double nx=10.0, ny=20.0, nz=30.0;
    Vector3D_SetX(&vec, &nx);
    Vector3D_SetY(&vec, &ny);
    Vector3D_SetZ(&vec, &nz);

    ASSERT_DOUBLE_EQ(10.0, *(double*)Vector3D_GetX(&vec));
    ASSERT_DOUBLE_EQ(20.0, *(double*)Vector3D_GetY(&vec));
    ASSERT_DOUBLE_EQ(30.0, *(double*)Vector3D_GetZ(&vec));
}

/* ─── Vector3D: Add ─────────────────────────────────────── */

void test_vector3d_add_double(void) {
    TypeInfo* t = ofDouble();
    double x1=1, y1=2, z1=3, x2=4, y2=5, z2=6;

    double xb1, yb1, zb1, xb2, yb2, zb2;
    xb1 = x1; yb1 = y1; zb1 = z1;
    xb2 = x2; yb2 = y2; zb2 = z2;

    Vector3D v1, v2, sum;
    Vector3D_Create(&v1, &xb1, &yb1, &zb1, t);
    Vector3D_Create(&v2, &xb2, &yb2, &zb2, t);

    Vector3D_Add(&sum, &v1, &v2);

    ASSERT_DOUBLE_EQ(5.0, *(double*)Vector3D_GetX(&sum));
    ASSERT_DOUBLE_EQ(7.0, *(double*)Vector3D_GetY(&sum));
    ASSERT_DOUBLE_EQ(9.0, *(double*)Vector3D_GetZ(&sum));
}

void test_vector3d_add_null(void) {
    TypeInfo* t = ofDouble();
    double xb=1, yb=2, zb=3;

    Vector3D v1, v2, sum;
    Vector3D_Create(&v1, &xb, &yb, &zb, t);

    Vector3D_Add(&sum, &v1, NULL);
    TEST_ASSERT_NULL(Vector3D_GetTypeInfo(&sum));

    Vector3D_Add(&sum, NULL, &v1);
    TEST_ASSERT_NULL(Vector3D_GetTypeInfo(&sum));
}

/* ─── Vector3D: DotProduct ──────────────────────────────── */

void test_vector3d_dot_product(void) {
    TypeInfo* t = ofDouble();
    /* (1,2,3)·(4,5,6) = 4+10+18 = 32 */
    double x1=1, y1=2, z1=3, x2=4, y2=5, z2=6;

    double xb1, yb1, zb1, xb2, yb2, zb2;
    xb1 = x1; yb1 = y1; zb1 = z1;
    xb2 = x2; yb2 = y2; zb2 = z2;

    Vector3D v1, v2;
    Vector3D_Create(&v1, &xb1, &yb1, &zb1, t);
    Vector3D_Create(&v2, &xb2, &yb2, &zb2, t);

    double dot;
    Vector3D_DotProduct(&dot, &v1, &v2);

    ASSERT_DOUBLE_EQ(32.0, dot);
}

void test_vector3d_dot_orthogonal(void) {
    TypeInfo* t = ofDouble();
    /* (1,0,0)·(0,1,0) = 0 */
    double x1=1,y1=0,z1=0, x2=0,y2=1,z2=0;

    double xb1, yb1, zb1, xb2, yb2, zb2;
    xb1 = x1; yb1 = y1; zb1 = z1;
    xb2 = x2; yb2 = y2; zb2 = z2;

    Vector3D v1, v2;
    Vector3D_Create(&v1, &xb1, &yb1, &zb1, t);
    Vector3D_Create(&v2, &xb2, &yb2, &zb2, t);

    double dot;
    Vector3D_DotProduct(&dot, &v1, &v2);

    ASSERT_DOUBLE_EQ(0.0, dot);
}

/* ─── Vector3D: CrossProduct ────────────────────────────── */

void test_vector3d_cross_product(void) {
    TypeInfo* t = ofDouble();
    /* e1 × e2 = e3 */
    double x1=1,y1=0,z1=0, x2=0,y2=1,z2=0;

    double xb1, yb1, zb1, xb2, yb2, zb2;
    xb1 = x1; yb1 = y1; zb1 = z1;
    xb2 = x2; yb2 = y2; zb2 = z2;

    Vector3D v1, v2, cross;
    Vector3D_Create(&v1, &xb1, &yb1, &zb1, t);
    Vector3D_Create(&v2, &xb2, &yb2, &zb2, t);

    Vector3D_CrossProduct(&cross, &v1, &v2);

    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetX(&cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetY(&cross));
    ASSERT_DOUBLE_EQ(1.0, *(double*)Vector3D_GetZ(&cross));
}

void test_vector3d_cross_anticommutativity(void) {
    TypeInfo* t = ofDouble();
    /* v1×v2 = -(v2×v1) */
    double x1=1,y1=2,z1=3, x2=4,y2=5,z2=6;

    double xb1, yb1, zb1, xb2, yb2, zb2;
    xb1 = x1; yb1 = y1; zb1 = z1;
    xb2 = x2; yb2 = y2; zb2 = z2;

    Vector3D v1, v2, c12, c21;
    Vector3D_Create(&v1, &xb1, &yb1, &zb1, t);
    Vector3D_Create(&v2, &xb2, &yb2, &zb2, t);

    Vector3D_CrossProduct(&c12, &v1, &v2);
    Vector3D_CrossProduct(&c21, &v2, &v1);

    double cx12 = *(double*)Vector3D_GetX(&c12);
    double cx21 = *(double*)Vector3D_GetX(&c21);
    ASSERT_DOUBLE_EQ(cx12, -cx21);
    /* аналогично Y, Z */
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetY(&c12), -*(double*)Vector3D_GetY(&c21));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetZ(&c12), -*(double*)Vector3D_GetZ(&c21));
}

void test_vector3d_cross_self_is_zero(void) {
    TypeInfo* t = ofDouble();
    /* v × v = 0 */
    double x=3,y=7,z=2;

    double xb, yb, zb;
    xb = x; yb = y; zb = z;

    Vector3D v, cross;
    Vector3D_Create(&v, &xb, &yb, &zb, t);

    Vector3D_CrossProduct(&cross, &v, &v);

    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetX(&cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetY(&cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetZ(&cross));
}

/* ─── TypeInfo синглтон не портится после операций ──────── */

void test_typeinfo_singleton_survives_ops(void) {
    TypeInfo* t_before = ofDouble();
    double x1=1,y1=0,z1=0, x2=0,y2=1,z2=0;

    double xb1, yb1, zb1, xb2, yb2, zb2;
    xb1 = x1; yb1 = y1; zb1 = z1;
    xb2 = x2; yb2 = y2; zb2 = z2;

    Vector3D v1, v2, cross;
    Vector3D_Create(&v1, &xb1, &yb1, &zb1, t_before);
    Vector3D_Create(&v2, &xb2, &yb2, &zb2, t_before);

    Vector3D_CrossProduct(&cross, &v1, &v2);

    TypeInfo* t_after = ofDouble();
    /* синглтон должен быть тем же указателем и работоспособен */
    TEST_ASSERT_EQUAL_PTR(t_before, t_after);
    TEST_ASSERT_NOT_NULL(t_after->add);
}

/* ─── main ──────────────────────────────────────────────── */

int main(void) {
    UNITY_BEGIN();

    /* TypeInfo: double */
    RUN_TEST(test_ofDouble_not_null);
    RUN_TEST(test_ofDouble_singleton);
    RUN_TEST(test_double_create_zero);
    RUN_TEST(test_double_add);
    RUN_TEST(test_double_subtract);
    RUN_TEST(test_double_multiply);
    RUN_TEST(test_double_compare);

    /* TypeInfo: Complex */
    RUN_TEST(test_ofComplex_not_null);
    RUN_TEST(test_ofComplex_singleton);
    RUN_TEST(test_complex_create_zero);
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
