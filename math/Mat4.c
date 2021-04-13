#include "Mat4.h"
#include "Mat3.h"
#include "Vec3.h"

#include <stdio.h> 
#include <math.h>
#include <math/Defines.h> //M_PI

float Mat4_get_index(Mat4* m, int r, int c) {
    switch (c) {
        case 0: return Vec4_get_index(&m->x, r); break;
        case 1: return Vec4_get_index(&m->y, r); break;
        case 2: return Vec4_get_index(&m->z, r); break;
        case 3: return Vec4_get_index(&m->w, r); break;
        default: return (1.0f / 0.0f); break;
    }
}

Vec4 Mat4_col(Mat4 m, int c) {
    switch (c) {
        case 0: return m.x; break;
        case 1: return m.y; break;
        case 2: return m.z; break;
        case 3: return m.w; break;
        default: {
            printf("Mat4 col index out of range: %d\n", c); 
            return (Vec4) { (1.0f / 0.0f), (1.0f / 0.0f) , (1.0f / 0.0f), (1.0f / 0.0f)}; 
        } break;
    }   
}

Vec4 Mat4_row(Mat4 m, int r) {
    switch (r) {
        case 0: return (Vec4) { m.x.x, m.y.x, m.z.x, m.w.x }; break;
        case 1: return (Vec4) { m.x.y, m.y.y, m.z.y, m.w.y }; break;
        case 2: return (Vec4) { m.x.z, m.y.z, m.z.z, m.w.z }; break;
        case 3: return (Vec4) { m.x.w, m.y.w, m.z.w, m.w.w }; break;
        default: {
            printf("Mat4 row index out of range: %d\n", r); 
            return (Vec4) { (1.0f / 0.0f), (1.0f / 0.0f) , (1.0f / 0.0f), (1.0f / 0.0f)}; 
        } break;
    }
}

Mat4 Mat4_transpose(Mat4 m) {
    return (Mat4) {
        Mat4_row(m, 0),
        Mat4_row(m, 1),
        Mat4_row(m, 2),
        Mat4_row(m, 3),
    };
}

Mat4 Mat4_scale(Mat4 m, float s) {
    return (Mat4) {
        Vec4_mul(m.x, s),
        Vec4_mul(m.y, s),
        Vec4_mul(m.z, s),
        Vec4_mul(m.w, s),
    };
}

Mat4 Mat4_mul(Mat4 m, Mat4 u) {
    return (Mat4) {
        { 
            Vec4_dot(Mat4_row(m, 0), Mat4_col(u, 0)), 
            Vec4_dot(Mat4_row(m, 1), Mat4_col(u, 0)), 
            Vec4_dot(Mat4_row(m, 2), Mat4_col(u, 0)),
            Vec4_dot(Mat4_row(m, 3), Mat4_col(u, 0)),
        },
        { 
            Vec4_dot(Mat4_row(m, 0), Mat4_col(u, 1)), 
            Vec4_dot(Mat4_row(m, 1), Mat4_col(u, 1)), 
            Vec4_dot(Mat4_row(m, 2), Mat4_col(u, 1)),
            Vec4_dot(Mat4_row(m, 3), Mat4_col(u, 1)),
        },
        { 
            Vec4_dot(Mat4_row(m, 0), Mat4_col(u, 2)), 
            Vec4_dot(Mat4_row(m, 1), Mat4_col(u, 2)), 
            Vec4_dot(Mat4_row(m, 2), Mat4_col(u, 2)),
            Vec4_dot(Mat4_row(m, 3), Mat4_col(u, 2)),
        },
        { 
            Vec4_dot(Mat4_row(m, 0), Mat4_col(u, 3)), 
            Vec4_dot(Mat4_row(m, 1), Mat4_col(u, 3)), 
            Vec4_dot(Mat4_row(m, 2), Mat4_col(u, 3)),
            Vec4_dot(Mat4_row(m, 3), Mat4_col(u, 3)),
        },
    };
}

Vec4 Mat4_apply(Mat4 m, Vec4 v) {
    return (Vec4) {
        Vec4_dot(Mat4_row(m, 0), v),
        Vec4_dot(Mat4_row(m, 1), v),
        Vec4_dot(Mat4_row(m, 2), v),
        Vec4_dot(Mat4_row(m, 3), v),
    };
}

Mat3 Mat4_basis(Mat4 m) {
    return (Mat3) {
        { m.x.x, m.x.y, m.x.z },
        { m.y.x, m.y.y, m.y.z },
        { m.z.x, m.z.y, m.z.z },
    };
}

Vec3 Mat4_origin(Mat4 m) {
    return (Vec3) {
        m.w.x, m.w.y, m.w.z
    };
}

Vec3 Mat4_transform(Mat4 m, Vec3 v) {
    Vec4 dummy = Vec4_from_Vec3(v, 1.0f);
    Vec4 applied = Mat4_apply(m, dummy);
    //return (Vec3) { applied.x / applied.w, applied.y / applied.w, applied.z / applied.w };
    return (Vec3) { applied.x , applied.y , applied.z };
}

Mat4 Mat4_identity() {
    return (Mat4) {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0},
    };
}

Mat4 Mat4_with_basis(Mat4 m, Mat3 basis) {
    return (Mat4) {
        Vec4_from_Vec3(basis.x, m.x.w),
        Vec4_from_Vec3(basis.y, m.y.w),
        Vec4_from_Vec3(basis.z, m.z.w),
        m.w,
    };
}

Mat4 Mat4_with_origin(Mat4 m, Vec3 origin) {
    return (Mat4) {
        m.x,
        m.y,
        m.z,
        Vec4_from_Vec3(origin, m.z.z),
    };
}

Mat4 Mat4_with_basis_origin(Mat3 basis, Vec3 origin) {
    return (Mat4) {
        Vec4_from_Vec3(basis.x, 0.0f),
        Vec4_from_Vec3(basis.y, 0.0f),
        Vec4_from_Vec3(basis.z, 0.0f),
        Vec4_from_Vec3(origin, 1.0f),
    };
}

Mat4 Mat4_rotate_around_x(float theta) {
    
}

Mat4 Mat4_rotate_around_y(float theta) {
    float c = cos(theta);
    float s = sin(theta);

    return (Mat4) {
        {c, 0.0f, -1 * s, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {s, 0.0f, c, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f},
    };
}

Mat4 Mat4_rotate_around_z(float theta);

/*
Mat4 Mat4_rotated(Mat4 m, float theta) {
    return Mat4_with_basis(m, Mat2_rotated(Mat4_basis(m), theta));
}
*/

Mat4 Mat4_translated(Mat4 m, Vec3 delta) {
    return Mat4_with_origin(m, Vec3_plus(Mat4_origin(m), delta));
}

Mat4 Mat4_perspective(float fov, float aspect_ratio, float near, float far) {
    float top = (float) tan(fov * 0.5 * M_PI/180.0f) * near;
    float bottom = -top;

    float right = top * aspect_ratio;
    float left = bottom * aspect_ratio;

    return (Mat4) {
        {2 * near / (right - left), 0, 0, 0},
        {0, 2 * near/ (top - bottom), 0, 0 },
        { 
          (right + left) / (right - left), 
          (top + bottom) / (top - bottom), 
          -(far + near)/(far - near), 
          -1
        },
        {0, 0, -2*far*near/(far - near), 0},
    };
}

Mat4 Mat4_lookat(Vec3 camera_location, Vec3 camera_up, Vec3 looking_at_location) {
    Vec3 camera_to_look = Vec3_normalized(Vec3_minus(looking_at_location, camera_location));
    Vec3 right = Vec3_cross(camera_to_look, camera_up);
    Mat3 new_basis = (Mat3) {
        right,
        camera_up,
        Vec3_mul(camera_to_look, -1.0f),
    };

    return Mat4_with_basis_origin(new_basis, camera_location);
}

void Mat4_print(Mat4 m) {
    Vec4_print(Mat4_row(m, 0));
    Vec4_print(Mat4_row(m, 1));
    Vec4_print(Mat4_row(m, 2));
    Vec4_print(Mat4_row(m, 3));
}
