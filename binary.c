#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Row by Col if I wanted to multiply then i need mxn * n*p (n=3)
int and_data[][3] = {
    {0,0,0},
    {0,1,0},
    {1,0,0},
    {1,1,1}
};

int or_data[][3] = {
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1}
};

int xor_data[][3] = {
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,0}
};

#define AND_TRAINING_COUNT (sizeof(and_data) / sizeof(and_data[3]))
#define OR_TRAINING_COUNT (sizeof(or_data) / sizeof(or_data[3]))
#define XOR_TRAINING_COUNT (sizeof(xor_data) / sizeof(xor_data[3]))

float loss(int data[][3], int n, float wa, float wb) {
    float results = 0.0f;
    for(int i = 0; i < n; i++) {
        results += pow((data[i][0] * wa + data[i][1] * wb) - data[i][2], 2);
        //printf("\t%d %d %d %f\n", data[i][0], data[i][1], data[i][2], results);
    }
    results /= n;
    return sqrtf(results);
}

void train(int data[][3], int n, float *wa, float *wb) {
    float result, d_wa, d_wb = 0.0f;
    float eps = 1e-3;
    float learning_rate = 1e-2;
    for(int i = 0; i < 100000; i++) {
        result = loss(data, n, *wa, *wb);
        d_wa = (loss(data, n, *wa + eps, *wb) - loss(data, n, *wa, *wb))/eps;
        d_wb = (loss(data, n, *wa, *wb + eps) - loss(data, n, *wa, *wb))/eps;
        //printf("%d %f %f %f\n", i, d_wa, d_wb, result);
        *wa -= d_wa*learning_rate;
        *wb -= d_wb*learning_rate;
    }
}

int inference(int a, int b, float wa, float wb) {
    //float result = round(a * wa + b * wb);
    float result = a * wa + b * wb;
    return result >= 0.5 ? 1 : 0;    //printf("%f %d\n", result, (int)result);
    //return (int)result;
}

int main() {
    srand(time(0));
    float and_wa = ((float)rand() / (float)RAND_MAX);
    float and_wb = ((float)rand() / (float)RAND_MAX);

    train(and_data, AND_TRAINING_COUNT, &and_wa, &and_wb);

    printf("\n\nAND Results:\n");
    for(int i = 0; i < AND_TRAINING_COUNT; i++) {
        printf("%d %d %d\n", and_data[i][0], and_data[i][1], inference(and_data[i][0],and_data[i][1], and_wa, and_wb));
    }

    float or_wa = ((float)rand() / (float)RAND_MAX);
    float or_wb = ((float)rand() / (float)RAND_MAX);

    train(or_data, OR_TRAINING_COUNT, &or_wa, &or_wb);

    printf("\n\nOR Results:\n");
    for(int i = 0; i < OR_TRAINING_COUNT; i++) {
        printf("%d %d %d\n", or_data[i][0], or_data[i][1], (int)round(inference(or_data[i][0],or_data[i][1], or_wa, or_wb)));
    }

    printf("\n\nXOR Results:\n");
    for(int i = 0; i < XOR_TRAINING_COUNT; i++) {
        int a = xor_data[i][0];
        int b = xor_data[i][1];
        int n_a = a ? 0 : 1;
        int n_b = b ? 0 : 1;
        int c = inference(
            inference(a, n_b, and_wa, and_wb),
            inference(n_a, b, and_wa, and_wb), 
            or_wa,
            or_wb
        );
        printf("%d %d %d\n", a, b, c);
    }        

    return 0;
}