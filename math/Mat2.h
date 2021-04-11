#ifndef MAT2_H
#define MAT2_H

#include "Vec2.h"

//a and b are the two columns of this matrix
typedef struct {
    Vec2 x;
    Vec2 y;
} Mat2;

float Mat2_get_index(Mat2* m, int r, int c);
Vec2 Mat2_col(Mat2 m, int c);
Vec2 Mat2_row(Mat2 m, int r);

Mat2 Mat2_transpose(Mat2 m);
Mat2 Mat2_mul(Mat2 m, Mat2 u);
Mat2 Mat2_scale(Mat2 m, float s);
Vec2 Mat2_apply(Mat2 m, Vec2 v);

Mat2 Mat2_rotation(float theta);
Mat2 Mat2_rotated(Mat2 m, float theta);

void Mat2_print(Mat2 m);

#endif
