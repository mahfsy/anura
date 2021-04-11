#include "Mat2.h"
#include "Vec2.h"

#include <stdio.h> 
#include <math.h>

float Mat2_get_index(Mat2* m, int r, int c) {
    switch (c) {
        case 0: return Vec2_get_index(&m->x, r); break;
        case 1: return Vec2_get_index(&m->y, r); break;
        default: return (1.0f / 0.0f); break;
    }
}

Vec2 Mat2_col(Mat2 m, int c) {
    switch (c) {
        case 0: return m.x; break;
        case 1: return m.y; break;
        default: {
            printf("Mat2 col index out of range: %d\n", c); 
            return (Vec2) { (1.0f / 0.0f), (1.0f / 0.0f) }; 
        } break;
    }   
}

Vec2 Mat2_row(Mat2 m, int r) {
    switch (r) {
        case 0: return (Vec2) { m.x.x, m.y.x }; break;
        case 1: return (Vec2) { m.x.y, m.y.y }; break;
        default: {
            printf("Mat2 row index out of range: %d\n", r); 
            return (Vec2) { (1.0f / 0.0f), (1.0f / 0.0f) }; 
        } break;
    }
}

Mat2 Mat2_transpose(Mat2 m) {
    return (Mat2) {
        Mat2_row(m, 0),
        Mat2_row(m, 1),
    };
}

Mat2 Mat2_scale(Mat2 m, float s) {
    return (Mat2) {
        Vec2_mul(m.x, s),
        Vec2_mul(m.y, s),
    };
}

Mat2 Mat2_mul(Mat2 m, Mat2 u) {
    return (Mat2) {
        { Vec2_dot(Mat2_row(m, 0), Mat2_col(u, 0)), Vec2_dot(Mat2_row(m, 1), Mat2_col(u, 0)) },
        { Vec2_dot(Mat2_row(m, 0), Mat2_col(u, 1)), Vec2_dot(Mat2_row(m, 1), Mat2_col(u, 1)) },
    };
}

Vec2 Mat2_apply(Mat2 m, Vec2 v) {
    return (Vec2) {
        Vec2_dot(Mat2_row(m, 0), v),
        Vec2_dot(Mat2_row(m, 1), v),
    };
}

Mat2 Mat2_rotation(float theta) {
    float c = cos(theta);
    float s = sin(theta);
    return (Mat2) {
        {c, s},
        {-1*s, c},
    };
}

Mat2 Mat2_rotated(Mat2 m, float theta) {
    Mat2 rot = Mat2_rotation(theta);
    return (Mat2) {
        Mat2_apply(rot, m.x),
        Mat2_apply(rot, m.y),
    };
}

void Mat2_print(Mat2 m) {
    Vec2_print(Mat2_row(m, 0));
    Vec2_print(Mat2_row(m, 1));
}
