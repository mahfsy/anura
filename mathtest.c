#include <stdio.h>
#include "math/AnuraMath.h"

int main() {
    Vec2 v = {5.3, 2.2};
    Vec2 w = {1.2, 2.6};

    Mat2 m = { v, w };
    Mat2 n = {
        { 1.0, 0.0 },
        { 0.0, 1.0 }
    };

    printf("%f\n", Vec2_length(v));
    printf("%f\n", Mat2_get_index(&m, 0, 0));

    Vec2_print(v);
    printf("----\n");
    Mat2_print(m);
    printf("====\n");

    Mat2 res = Mat2_mul(n, m);
    Mat2_print(res);

    printf("....\n");
    Mat2 a = {
        { 1, 34},
        { 2, 4},
    };

    Mat2 b = {
        {6,2},
        {1,4},
    };

    Mat2_print(Mat2_mul(a, b));

    printf("====\n");
    Vec2 v1 = {1.0, 0.0};
    Vec2_print(Vec2_rotated(v1, 3.14159265/ 2.0));

    printf("....\n");
    Mat3 a3 = {
        {1,4,7},
        {2,5,8},
        {3,6,9},
    };
    Mat3 b3 = {
        {5,8,6},
        {4,1,9},
        {3,2,7},
    };

    Mat3_print(Mat3_mul(a3, b3));
    Mat3_print(Mat3_transpose(a3));
    Mat2_print(Mat2_transpose(a));

    printf("....\n");
    Mat3 trans = 
        Mat3_with_origin(
            Mat3_with_basis(
                Mat3_identity(), 
                (Mat2) {{-1.0, 0.0}, {0.0, -1.0}}
            ), 
            (Vec2) {5.0, 7.2}
        );
    printf("original...\n");
    Mat3_print(trans);
    //Vec2_print(Mat3_transform(trans, (Vec2) {1,2}));

    //Mat3_print(Mat3_translated(trans, (Vec2) {2,8}));

    printf("transformed...\n");
    Mat3_print(Mat3_mul(trans, Mat3_with_origin(Mat3_identity(), (Vec2) {2,3})));
}
