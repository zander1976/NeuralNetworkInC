#define NN_IMPLEMENTATION
#include "nn.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

int main() {
    srand(time(0));

    Mat A = mat_alloc(1, 2);
    Mat B = mat_alloc(2, 2);
    
    printf("------------\n");
    mat_fill(A, 1.0f);
    mat_print(A, "A");
   
    printf("------------\n");
    mat_random(B, 0.f, 10.f);
    mat_print(B, "B");
    
    printf("------------\n");
    Mat R = mat_alloc(1, 2);
    mat_multi(R, A, B);
    mat_print(R, "R");

    printf("------------\n");
    float identity_mat[] = { 
        1,0,
        0,1
    };
    Mat D = { .rows = 2, .cols = 2, .data = identity_mat};
    Mat R2 = mat_alloc(2, 2);
    mat_print(B, "B");
    mat_print(D, "D");
    mat_multi(R2, B, D);
    mat_print(R2, "R2");

    printf("------------\n");
    float transpose_mat[] = { 
        1,2,3,
        4,5,6
    };
    Mat E = { .rows = 2, .cols = 3, .data = transpose_mat};
    Mat F = mat_alloc(3,2);
    mat_transpose(F,E);
    mat_print(E, "E");
    mat_print(F, "F");

    return 0;
}
