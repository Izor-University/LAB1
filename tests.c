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
    double* z = (double*)t->create_zero();
    TEST_ASSERT_NOT_NULL(z);
    ASSERT_DOUBLE_EQ(0.0, *z);
    free(z);
}

void test_double_add(void) {
    TypeInfo* t = ofDouble();
    double a = 3.0, b = 4.0;
    double* r = (double*)t->add(&a, &b);
    ASSERT_DOUBLE_EQ(7.0, *r);
    free(r);
}

void test_double_subtract(void) {
    TypeInfo* t = ofDouble();
    double a = 10.0, b = 3.0;
    double* r = (double*)t->subtract(&a, &b);
    ASSERT_DOUBLE_EQ(7.0, *r);
    free(r);
}

void test_double_multiply(void) {
    TypeInfo* t = ofDouble();
    double a = 3.0, b = 4.0;
    double* r = (double*)t->multiply(&a, &b);
    ASSERT_DOUBLE_EQ(12.0, *r);
    free(r);
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
    Complex* z = (Complex*)t->create_zero();
    TEST_ASSERT_NOT_NULL(z);
    Complex* expected = Complex_Zero();
    TEST_ASSERT_TRUE(Complex_Equal(z, expected));
    free(expected);
    free(z);
}

void test_complex_add(void) {
    TypeInfo* t = ofComplex();
    Complex* a = Complex_Create(1.0, 2.0);
    Complex* b = Complex_Create(3.0, 4.0);
    Complex* r = (Complex*)t->add(a, b);
    Complex* expected = Complex_Create(4.0, 6.0);
    TEST_ASSERT_TRUE(Complex_Equal(r, expected));
    free(a); free(b);
    free(r); free(expected);
}

void test_complex_multiply(void) {
    TypeInfo* t = ofComplex();
    /* (1+i)(1-i) = 1 - i^2 = 2 */
    Complex* a = Complex_Create(1.0,  1.0);
    Complex* b = Complex_Create(1.0, -1.0);
    Complex* r = (Complex*)t->multiply(a, b);
    Complex* expected = Complex_Create(2.0, 0.0);
    TEST_ASSERT_TRUE(Complex_Equal(r, expected));
    free(a); free(b);
    free(r); free(expected);
}

void test_complex_compare_equal(void) {
    TypeInfo* t = ofComplex();
    Complex* a = Complex_Create(1.0, 2.0);
    Complex* b = Complex_Create(1.0, 2.0);
    Complex* c = Complex_Create(0.0, 0.0);
    TEST_ASSERT_EQUAL_INT(0, t->compare(a, b));   /* равны  → 0 */
    TEST_ASSERT_NOT_EQUAL(0, t->compare(a, c));   /* разные → !=0 */
    free(a); free(b); free(c);
}

/* ─── Vector3D: создание ────────────────────────────────── */

void test_vector3d_create_double(void) {
    TypeInfo* t = ofDouble();
    double x=1.0, y=2.0, z=3.0;
    Vector3D* v = Vector3D_Create(&x, &y, &z, t);
    TEST_ASSERT_NOT_NULL(v);
    ASSERT_DOUBLE_EQ(1.0, *(double*)Vector3D_GetX(v));
    ASSERT_DOUBLE_EQ(2.0, *(double*)Vector3D_GetY(v));
    ASSERT_DOUBLE_EQ(3.0, *(double*)Vector3D_GetZ(v));
    TEST_ASSERT_EQUAL_PTR(t, Vector3D_GetTypeInfo(v));
    Vector3D_Destroy(v);
}

void test_vector3d_create_complex(void) {
    TypeInfo* t = ofComplex();
    Complex* cx = Complex_Create(1.0, 2.0);
    Complex* cy = Complex_Create(3.0, 4.0);
    Complex* cz = Complex_Create(5.0, 6.0);
    Vector3D* v = Vector3D_Create(cx, cy, cz, t);
    TEST_ASSERT_NOT_NULL(v);
    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetX(v), cx));
    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetY(v), cy));
    TEST_ASSERT_TRUE(Complex_Equal((Complex*)Vector3D_GetZ(v), cz));
    free(cx); free(cy); free(cz);
    Vector3D_Destroy(v);
}

void test_vector3d_create_null_args(void) {
    TypeInfo* t = ofDouble();
    double x=1.0, y=2.0, z=3.0;
    TEST_ASSERT_NULL(Vector3D_Create(NULL, &y, &z, t));
    TEST_ASSERT_NULL(Vector3D_Create(&x, NULL, &z, t));
    TEST_ASSERT_NULL(Vector3D_Create(&x, &y, NULL, t));
    TEST_ASSERT_NULL(Vector3D_Create(&x, &y, &z, NULL));
}

/* ─── Vector3D: Clone ───────────────────────────────────── */

void test_vector3d_clone(void) {
    TypeInfo* t = ofDouble();
    double x=1.0, y=2.0, z=3.0;
    Vector3D* v     = Vector3D_Create(&x, &y, &z, t);
    Vector3D* clone = Vector3D_Clone(v);
    TEST_ASSERT_NOT_NULL(clone);
    TEST_ASSERT_TRUE(v != clone);
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetX(v), *(double*)Vector3D_GetX(clone));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetY(v), *(double*)Vector3D_GetY(clone));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetZ(v), *(double*)Vector3D_GetZ(clone));
    Vector3D_Destroy(v); Vector3D_Destroy(clone);
}

/* ─── Vector3D: Setters ─────────────────────────────────── */

void test_vector3d_setters(void) {
    TypeInfo* t = ofDouble();
    double x=1.0, y=2.0, z=3.0;
    Vector3D* v = Vector3D_Create(&x, &y, &z, t);
    double nx=10.0, ny=20.0, nz=30.0;
    Vector3D_SetX(v, &nx);
    Vector3D_SetY(v, &ny);
    Vector3D_SetZ(v, &nz);
    ASSERT_DOUBLE_EQ(10.0, *(double*)Vector3D_GetX(v));
    ASSERT_DOUBLE_EQ(20.0, *(double*)Vector3D_GetY(v));
    ASSERT_DOUBLE_EQ(30.0, *(double*)Vector3D_GetZ(v));
    Vector3D_Destroy(v);
}

/* ─── Vector3D: Add ─────────────────────────────────────── */

void test_vector3d_add_double(void) {
    TypeInfo* t = ofDouble();
    double x1=1, y1=2, z1=3, x2=4, y2=5, z2=6;
    Vector3D* v1  = Vector3D_Create(&x1, &y1, &z1, t);
    Vector3D* v2  = Vector3D_Create(&x2, &y2, &z2, t);
    Vector3D* sum = Vector3D_Add(v1, v2);
    TEST_ASSERT_NOT_NULL(sum);
    ASSERT_DOUBLE_EQ(5.0, *(double*)Vector3D_GetX(sum));
    ASSERT_DOUBLE_EQ(7.0, *(double*)Vector3D_GetY(sum));
    ASSERT_DOUBLE_EQ(9.0, *(double*)Vector3D_GetZ(sum));
    Vector3D_Destroy(v1); Vector3D_Destroy(v2); Vector3D_Destroy(sum);
}

void test_vector3d_add_null(void) {
    TypeInfo* t = ofDouble();
    double x=1, y=2, z=3;
    Vector3D* v = Vector3D_Create(&x, &y, &z, t);
    TEST_ASSERT_NULL(Vector3D_Add(v, NULL));
    TEST_ASSERT_NULL(Vector3D_Add(NULL, v));
    Vector3D_Destroy(v);
}

/* ─── Vector3D: DotProduct ──────────────────────────────── */

void test_vector3d_dot_product(void) {
    TypeInfo* t = ofDouble();
    /* (1,2,3)·(4,5,6) = 4+10+18 = 32 */
    double x1=1, y1=2, z1=3, x2=4, y2=5, z2=6;
    Vector3D* v1 = Vector3D_Create(&x1, &y1, &z1, t);
    Vector3D* v2 = Vector3D_Create(&x2, &y2, &z2, t);
    double* dot  = (double*)Vector3D_DotProduct(v1, v2);
    TEST_ASSERT_NOT_NULL(dot);
    ASSERT_DOUBLE_EQ(32.0, *dot);
    free(dot);
    Vector3D_Destroy(v1); Vector3D_Destroy(v2);
}

void test_vector3d_dot_orthogonal(void) {
    TypeInfo* t = ofDouble();
    /* (1,0,0)·(0,1,0) = 0 */
    double x1=1,y1=0,z1=0, x2=0,y2=1,z2=0;
    Vector3D* v1 = Vector3D_Create(&x1, &y1, &z1, t);
    Vector3D* v2 = Vector3D_Create(&x2, &y2, &z2, t);
    double* dot  = (double*)Vector3D_DotProduct(v1, v2);
    ASSERT_DOUBLE_EQ(0.0, *dot);
    free(dot);
    Vector3D_Destroy(v1); Vector3D_Destroy(v2);
}

/* ─── Vector3D: CrossProduct ────────────────────────────── */

void test_vector3d_cross_product(void) {
    TypeInfo* t = ofDouble();
    /* e1 × e2 = e3 */
    double x1=1,y1=0,z1=0, x2=0,y2=1,z2=0;
    Vector3D* v1    = Vector3D_Create(&x1, &y1, &z1, t);
    Vector3D* v2    = Vector3D_Create(&x2, &y2, &z2, t);
    Vector3D* cross = Vector3D_CrossProduct(v1, v2);
    TEST_ASSERT_NOT_NULL(cross);
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetX(cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetY(cross));
    ASSERT_DOUBLE_EQ(1.0, *(double*)Vector3D_GetZ(cross));
    Vector3D_Destroy(v1); Vector3D_Destroy(v2); Vector3D_Destroy(cross);
}

void test_vector3d_cross_anticommutativity(void) {
    TypeInfo* t = ofDouble();
    /* v1×v2 = -(v2×v1) */
    double x1=1,y1=2,z1=3, x2=4,y2=5,z2=6;
    Vector3D* v1 = Vector3D_Create(&x1, &y1, &z1, t);
    Vector3D* v2 = Vector3D_Create(&x2, &y2, &z2, t);
    Vector3D* c12 = Vector3D_CrossProduct(v1, v2);
    Vector3D* c21 = Vector3D_CrossProduct(v2, v1);
    TEST_ASSERT_NOT_NULL(c12); TEST_ASSERT_NOT_NULL(c21);
    double cx12 = *(double*)Vector3D_GetX(c12);
    double cx21 = *(double*)Vector3D_GetX(c21);
    ASSERT_DOUBLE_EQ(cx12, -cx21);
    /* аналогично Y, Z */
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetY(c12), -*(double*)Vector3D_GetY(c21));
    ASSERT_DOUBLE_EQ(*(double*)Vector3D_GetZ(c12), -*(double*)Vector3D_GetZ(c21));
    Vector3D_Destroy(v1); Vector3D_Destroy(v2);
    Vector3D_Destroy(c12); Vector3D_Destroy(c21);
}

void test_vector3d_cross_self_is_zero(void) {
    TypeInfo* t = ofDouble();
    /* v × v = 0 */
    double x=3,y=7,z=2;
    Vector3D* v     = Vector3D_Create(&x, &y, &z, t);
    Vector3D* cross = Vector3D_CrossProduct(v, v);
    TEST_ASSERT_NOT_NULL(cross);
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetX(cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetY(cross));
    ASSERT_DOUBLE_EQ(0.0, *(double*)Vector3D_GetZ(cross));
    Vector3D_Destroy(v); Vector3D_Destroy(cross);
}

/* ─── TypeInfo синглтон не портится после операций ──────── */

void test_typeinfo_singleton_survives_ops(void) {
    TypeInfo* t_before = ofDouble();
    double x1=1,y1=0,z1=0, x2=0,y2=1,z2=0;
    Vector3D* v1    = Vector3D_Create(&x1, &y1, &z1, t_before);
    Vector3D* v2    = Vector3D_Create(&x2, &y2, &z2, t_before);
    Vector3D* cross = Vector3D_CrossProduct(v1, v2);
    Vector3D_Destroy(v1); Vector3D_Destroy(v2); Vector3D_Destroy(cross);
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