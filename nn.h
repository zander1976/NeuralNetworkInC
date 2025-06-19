#ifndef __NN_H__
#define __NN_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

// Matrix Structure
typedef struct {
    size_t rows;
    size_t cols; 
    float *data; 
} Mat; 

// Helper to handling matrix locations
#define MAT_AT(m, row, col) (m).data[(row) * (m).cols + (col)]

// Matrix Lookup functions
Mat mat_alloc(size_t rows, size_t cols);
void mat_copy(Mat dst, Mat src);
void mat_sum(Mat dst, Mat a, Mat b);
void mat_multi(Mat dst, Mat a, Mat b);
void mat_fill(Mat dst, float value);
void mat_random(Mat dst, float low, float high);
void mat_sig(Mat m);
void mat_transpose(Mat dst, Mat src);
void mat_print(Mat m,  char* name);

// Activation functions
float sigmoidf(float x);

#endif // __NN_H__

#ifdef NN_IMPLEMENTATION

// Creates statically but copies it back (not returning a reference)
Mat mat_alloc(size_t rows, size_t cols) {
    Mat m = { .rows = rows, .cols = cols, .data = NULL };
    m.data = malloc(rows * cols * sizeof(*m.data));
    assert(m.data != NULL);
    return m;
}

void mat_copy(Mat dst, Mat src) {
    assert(dst.rows == src.rows);
    assert(dst.cols == src.cols);

    for(size_t row = 0; row < dst.rows; row++ ) {
        for(size_t col = 0; col < dst.cols; col++) {
            MAT_AT(dst, row, col) = MAT_AT(src, row, col);
        }
    }    
}


void mat_sum(Mat m, Mat a, Mat b) {
    for(size_t row = 0; row < m.rows; row++ ) {
        for(size_t col = 0; col < m.cols; col++) {
            MAT_AT(m, row, col) = MAT_AT(a, row, col) + MAT_AT(b, row, col);
        }
    }
}
// a1 = x1*w1 + x2*w3 + b
// a2 = x1*w2 + x2*w4 + b

// Row by column
// Mmxn * Nnxp = Omxp
// 1x3 * 3x2 = 1x2
// [x1, x2, 1] * [w1_1 w1_2] = [x1w1_1 + x2w2_1 + b3_1] = [a1]
//               [w2_1 w2_2]   [x1w1_2 + x2w2_2 + b3_2]   [a2]
//               [b3_1 b3_2]  
void mat_multi(Mat dst, Mat a, Mat b) {
    assert(a.cols = b.rows);
    size_t n = a.cols; // Inner size
    assert(a.rows == dst.rows);
    assert(b.cols = dst.cols);
    for(size_t i = 0; i < dst.rows; i++ ) {
        for(size_t j = 0; j < dst.cols; j++) {
           for(size_t k = 0; k < n; k++) {
               MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
           }
        }
    }
}

void mat_fill(Mat dst, float value) {
    for(size_t row = 0; row < dst.rows; row++ ) {
        for(size_t col = 0; col < dst.cols; col++) {
            MAT_AT(dst, row, col) = value;
        }
    }
}

void mat_random(Mat dst, float high, float low) {
    for(size_t row = 0; row < dst.rows; row++ ) {
        for(size_t col = 0; col < dst.cols; col++) {
            MAT_AT(dst, row, col) = ((float) rand() / RAND_MAX) * (high-low) + low;
        }
    }
}

void mat_sig(Mat m) {
    for(size_t row = 0; row < m.rows; row++ ) {
        for(size_t col = 0; col < m.cols; col++) {
            MAT_AT(m, row, col) = sigmoidf(MAT_AT(m, row, col));
        }
    }
}

void mat_transpose(Mat dst, Mat src) {
    dst.rows = src.cols;
    dst.cols = src.rows;
    for(size_t row = 0; row < src.rows; row++ ) {
        for(size_t col = 0; col < src.cols; col++) {
            MAT_AT(dst, col, row) = MAT_AT(src, row, col);
        }
    }    
}

// 2 rows and 4 cols
// So to get M2_1 // first element in second colum we would need 
// the 5th element. Position = 1 * 4 + 1 (i * cols) + j
// ****
// ****
void mat_print(Mat m, char* name) {
    printf("------------------\n");
    printf("%s\n",name);
    for(size_t row = 0; row < m.rows; row++ ) {
        printf("%zu[ ", row);
        for(size_t col = 0; col < m.cols; col++) {
            //printf("%f", m.data[i * m.cols + j]);
            printf("%f ", MAT_AT(m, row, col));
        }
        printf("]\n");
    }
    printf("------------------\n\n");
}

float sigmoidf(float x) {
    return 1.f / (1.f + expf(-x));
}


#endif //NN_IMPLEMENTATION

