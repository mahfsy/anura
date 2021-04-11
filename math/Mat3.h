#ifndef MAT3_H
#define MAT3_H

#include "Mat2.h"
#include "Vec2.h"
#include "Vec3.h"

//a and b are the two columns of this matrix
typedef struct {
    Vec3 x;
    Vec3 y;
    Vec3 z;
} Mat3;

float Mat3_get_index(Mat3* m, int r, int c);
Vec3 Mat3_col(Mat3 m, int c);
Vec3 Mat3_row(Mat3 m, int r);

Mat3 Mat3_transpose(Mat3 m);
Mat3 Mat3_mul(Mat3 m, Mat3 u);
Vec3 Mat3_apply(Mat3 m, Vec3 v);

Mat2 Mat3_basis(Mat3 m);
Vec2 Mat3_origin(Mat3 m);
Vec2 Mat3_transform(Mat3 m, Vec2 v);

Mat3 Mat3_identity();

Mat3 Mat3_with_basis(Mat3 m, Mat2 basis);
Mat3 Mat3_with_origin(Mat3 m, Vec2 origin);

Mat3 Mat3_rotated(Mat3 m, float theta);
Mat3 Mat3_translated(Mat3 m, Vec2 delta);

void Mat3_print(Mat3 m);

#endif
