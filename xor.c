#define NN_IMPLEMENTATION
#include "nn.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

int train_input[][3] = {
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,0}    
};

float cost(Mat layer1, Mat layer2) {
    Mat input = mat_alloc(1, 3);
    Mat interm1 = mat_alloc(1,3);
    Mat result = mat_alloc(1,1);

    float rms = 0.0f;
    for(size_t i = 0; i < 4; i++ ) {

        // Set the input
        MAT_AT(input, 0, 0) = train_input[i][0];
        MAT_AT(input, 0, 1) = train_input[i][1];

        // Cost
        mat_multi(interm1, input, layer1);
        mat_sig(interm1);
        mat_multi(result, interm1, layer2);
        mat_sig(result);

        float d = *result.data - train_input[i][2];
        rms += d*d;
    }
    return sqrtf(rms/4);
}

int main() {

    // Create random seed
    srand(time(0));

    // Row by column
    // 1x3 * 3x3 = 1x3 * 3x1 = 
    // [x1, x2, 1] * [w1_1 w1_2 0] = [x1w1_1 + x2w2_1 + b3_1] = [w1_1 w1_2 b1_3] * [a1] = ...
    //               [w2_1 w2_2 0]   [x1w1_2 + x2w2_2 + b3_2]                      [a2]
    //               [b3_1 b3_2 1]   [1]                                           [1]

    // Create all the matrix
    Mat layer1 = mat_alloc(3, 3);
    Mat layer2 = mat_alloc(3, 1);
    Mat grad1 = mat_alloc(3, 3);
    Mat grad2 = mat_alloc(3, 1);

    // Initialize
    mat_random(layer1, 0, 1);
    mat_random(layer2, 0, 1);

    int training = 10000000;
    float eps = 1e-1;
    float rate = -1e-1;

    for(int train = 0; train < training; train++) {

        // float rms = 0.0f;
        // for(size_t i = 0; i < count; i++ ) {
        //     // Set the input
        //     MAT_AT(input, 0, 0) = train_input[i][0];
        //     MAT_AT(input, 0, 1) = train_input[i][1];

        //     float d = cost(input, layer1, layer2) - train_input[i][2];
        //     rms += d*d;
        // }
        // rms = sqrtf(rms/4);

        // Train
        float saved_value = 0.f;
        float c = cost(layer1, layer2);

        // Finite diff
        for(size_t row = 0; row < layer1.rows; row++) {
            for(size_t col = 0; col < layer1.cols; col++) {
                saved_value = MAT_AT(layer1, row, col);
                MAT_AT(layer1, row, col) += eps;

                // Compute the loss with the updated weights
                float new_cost = cost(layer1, layer2);
                float grad = (new_cost - c) / eps;
                MAT_AT(grad1, row, col) = rate*grad;
                MAT_AT(layer1, row, col) = saved_value;
            }
        }

        for(size_t row = 0; row < layer2.rows; row++) {
            for(size_t col = 0; col < layer2.cols; col++) {
                saved_value = MAT_AT(layer2, row, col);
                MAT_AT(layer2, row, col) += eps;

                // Compute the loss with the updated weights
                float new_cost = cost(layer1, layer2);
                float grad = (new_cost - c) / eps;
                MAT_AT(grad2, row, col) = rate*grad;
                MAT_AT(layer2, row, col) = saved_value;            
            }
        } 

        mat_sum(layer1, layer1, grad1);
        mat_sum(layer2, layer2, grad2);

        if (c < 0.05) {
            printf("\n------------------\n");
            printf("Found solution at: %d with a cost of: %f\n", train, c);
            printf("------------------\n");
            break;
        }
    }

    mat_print(layer1, "Layer 1");
    mat_print(layer2, "Layer 2");

    Mat input = mat_alloc(1, 3);
    Mat interm1 = mat_alloc(1,3);
    Mat result = mat_alloc(1,1);

    printf("\n------------------\n");
    printf("Results:\n");
    printf("------------------\n");

    for(size_t i = 0; i < 4; i++ ) {

        // Set the input
        MAT_AT(input, 0, 0) = train_input[i][0];
        MAT_AT(input, 0, 1) = train_input[i][1];

        // Cost
        mat_multi(interm1, input, layer1);
        mat_sig(interm1);
        mat_multi(result, interm1, layer2);
        mat_sig(result);

        int y = round(*result.data);
        printf("%zu: %d ^ %d = %d\n", 
            i, 
            train_input[i][0], 
            train_input[i][1], 
            y
        );
    }
    printf("\n");

   
    // mat_print(input, "input");
    // mat_print(layer1, "layer1");
    // mat_print(interm1, "interm1");
    // mat_print(layer2, "layer2");
    // mat_print(result, "result");
    
    return 0;    
}