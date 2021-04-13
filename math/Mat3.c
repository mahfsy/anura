#include "Mat3.h"
#include "Vec3.h"

#include <stdio.h> 
#include <math.h>

float Mat3_get_index(Mat3* m, int r, int c) {
    switch (c) {
        case 0: return Vec3_get_index(&m->x, r); break;
        case 1: return Vec3_get_index(&m->y, r); break;
        case 2: return Vec3_get_index(&m->z, r); break;
        default: return (1.0f / 0.0f); break;
    }
}

Vec3 Mat3_col(Mat3 m, int c) {
    switch (c) {
        case 0: return m.x; break;
        case 1: return m.y; break;
        case 2: return m.z; break;
        default: {
            printf("Mat3 col index out of range: %d\n", c); 
            return (Vec3) { (1.0f / 0.0f), (1.0f / 0.0f) , (1.0f / 0.0f)}; 
        } break;
    }   
}

Vec3 Mat3_row(Mat3 m, int r) {
    switch (r) {
        case 0: return (Vec3) { m.x.x, m.y.x, m.z.x }; break;
        case 1: return (Vec3) { m.x.y, m.y.y, m.z.y }; break;
        case 2: return (Vec3) { m.x.z, m.y.z, m.z.z }; break;
        default: {
            printf("Mat3 row index out of range: %d\n", r); 
            return (Vec3) { (1.0f / 0.0f), (1.0f / 0.0f) , (1.0f / 0.0f)}; 
        } break;
    }
}

Mat3 Mat3_transpose(Mat3 m) {
    return (Mat3) {
        Mat3_row(m, 0),
        Mat3_row(m, 1),
        Mat3_row(m, 2),
    };
}

Mat3 Mat3_scale(Mat3 m, float s) {
    return (Mat3) {
        Vec3_mul(m.x, s),
        Vec3_mul(m.y, s),
        Vec3_mul(m.z, s),
    };
}

Mat3 Mat3_mul(Mat3 m, Mat3 u) {
    return (Mat3) {
        { 
            Vec3_dot(Mat3_row(m, 0), Mat3_col(u, 0)), 
            Vec3_dot(Mat3_row(m, 1), Mat3_col(u, 0)), 
            Vec3_dot(Mat3_row(m, 2), Mat3_col(u, 0)) 
        },
        { 
            Vec3_dot(Mat3_row(m, 0), Mat3_col(u, 1)), 
            Vec3_dot(Mat3_row(m, 1), Mat3_col(u, 1)), 
            Vec3_dot(Mat3_row(m, 2), Mat3_col(u, 1)) 
        },
        { 
            Vec3_dot(Mat3_row(m, 0), Mat3_col(u, 2)), 
            Vec3_dot(Mat3_row(m, 1), Mat3_col(u, 2)), 
            Vec3_dot(Mat3_row(m, 2), Mat3_col(u, 2)) 
        },
    };
}

Vec3 Mat3_apply(Mat3 m, Vec3 v) {
    return (Vec3) {
        Vec3_dot(Mat3_row(m, 0), v),
        Vec3_dot(Mat3_row(m, 1), v),
        Vec3_dot(Mat3_row(m, 2), v),
    };
}

Mat2 Mat3_basis(Mat3 m) {
    return (Mat2) {
        { m.x.x, m.x.y },
        { m.y.x, m.y.y },
    };
}

Vec2 Mat3_origin(Mat3 m) {
    return (Vec2) {
        m.z.x, m.z.y
    };
}

Vec2 Mat3_transform(Mat3 m, Vec2 v) {
    Vec3 dummy = Vec3_from_Vec2(v, 1.0f);
    Vec3 applied = Mat3_apply(m, dummy);
    return (Vec2) { applied.x / applied.z, applied.y / applied.z };
}

Mat3 Mat3_identity() {
    return (Mat3) {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
    };
}

Mat3 Mat3_with_basis(Mat3 m, Mat2 basis) {
    return (Mat3) {
        Vec3_from_Vec2(basis.x, m.x.z),
        Vec3_from_Vec2(basis.y, m.y.z),
        m.z,
    };
}

Mat3 Mat3_with_origin(Mat3 m, Vec2 origin) {
    return (Mat3) {
        m.x,
        m.y,
        Vec3_from_Vec2(origin, m.z.z),
    };
}

Mat3 Mat3_rotated(Mat3 m, float theta) {
    return Mat3_with_basis(m, Mat2_rotated(Mat3_basis(m), theta));
}

Mat3 Mat3_translated(Mat3 m, Vec2 delta) {
    return Mat3_with_origin(m, Vec2_plus(Mat3_origin(m), delta));
}

void Mat3_print(Mat3 m) {
    Vec3_print(Mat3_row(m, 0));
    Vec3_print(Mat3_row(m, 1));
    Vec3_print(Mat3_row(m, 2));
}
