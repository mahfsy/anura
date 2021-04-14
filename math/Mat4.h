#ifndef MAT4_H
#define MAT4_H

#include "Mat2.h"
#include "Mat3.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

//a and b are the two columns of this matrix
typedef struct {
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Vec4 w;
} Mat4;

float Mat4_get_index(Mat4* m, int r, int c);
Vec4 Mat4_col(Mat4 m, int c);
Vec4 Mat4_row(Mat4 m, int r);

Mat4 Mat4_transpose(Mat4 m);
Mat4 Mat4_mul(Mat4 m, Mat4 u);
Vec4 Mat4_apply(Mat4 m, Vec4 v);
Vec3 Mat4_transform(Mat4 m, Vec3 v);

Mat3 Mat4_basis(Mat4 m);
Vec3 Mat4_origin(Mat4 m);

Mat4 Mat4_identity();

Mat4 Mat4_remove_translation(Mat4 m);
Mat4 Mat4_with_basis(Mat4 m, Mat3 basis);
Mat4 Mat4_with_origin(Mat4 m, Vec3 origin);
Mat4 Mat4_with_basis_origin(Mat3 basis, Vec3 origin);

Mat4 Mat4_rotate_around_x(float theta);
Mat4 Mat4_rotate_around_y(float theta);
Mat4 Mat4_rotate_around_z(float theta);

Mat4 Mat4_rotate_around(Vec3 axis, float theta);

Mat4 Mat4_translate(Vec3 delta);
Mat4 Mat4_from_basis(Mat3 basis);

Mat4 Mat4_rotated(Mat4 m, Vec3 axis, float theta);
Mat4 Mat4_translated(Mat4 m, Vec3 delta);

Mat4 Mat4_perspective(float fov, float aspect_ratio, float near, float far);
Mat4 Mat4_lookat(Vec3 camera_location, Vec3 camera_up, Vec3 looking_at_location);

void Mat4_print(Mat4 m);

#endif
