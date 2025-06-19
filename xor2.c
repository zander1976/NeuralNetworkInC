#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//matrix row x col
// training data is 4x2
int train_input[][3] = {
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,0}    
};

float weights[][3] = {
    {0.f,0.f,0.f}, // Or weights w, w, b
    {0.f,0.f,0.f}, // Nand weights
    {0.f,0.f,0.f}  // And Weights
};

float deltas[][3] = {
    {0.f,0.f,0.f}, // Or weights w, w, b
    {0.f,0.f,0.f}, // Nand weights
    {0.f,0.f,0.f}  // And Weights
};


float sigmoidf(float x) {
    return 1.f / (1.f + expf(-x));
}

float forward(int x1, int x2) {
    // y = mx + mx + b
    float a = sigmoidf(weights[0][0] * x1 + weights[0][1] * x2 + weights[0][2]); // OR
    float b = sigmoidf(weights[1][0] * x1 + weights[1][1] * x2 + weights[1][2]); // NAND

    // Layer two
    return sigmoidf(weights[2][0] * a + weights[2][1] * b + weights[2][2]); // AND
}

float cost() {
    float result = 0.0f;

    for(int i = 0; i < 4; i++) {
        //float y = sigmoidf(train_input[i][0] * weight[0] + train_input[i][1] * weight[1] + train_input[i][2]);
        float y = forward(train_input[i][0], train_input[i][1]);
        float d = y - train_input[i][2];
        result += d*d;
    }

    return sqrtf(result/4);
}

void print_weights() {
    printf("--------------------\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%f", weights[i][j]);
        }
        printf("\n");
    }    
    printf("--------------------\n");
}

void finite_diff(float eps) {
    float saved_value = 0.f;
    float c = cost();
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            saved_value = weights[i][j];
            weights[i][j] += eps;
            deltas[i][j] = (cost() - c) / eps;
            weights[i][j] = saved_value;
        }
    }      
}

int main() {
    // Create random weights
    srand(time(0));
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            weights[i][j] = (float)rand() / RAND_MAX;
        }
    }

    int training = 100000;
    float eps = 1e-1;
    // Train the model
    for(int i = 0; i < training; i++) {
        finite_diff(eps);
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                weights[i][j] -= deltas[i][j];

            }
        }
        float c = cost();
        if (c < 0.001) {
            printf("--------------------\n");
            printf("Cost: %f at %d\n", c, i);
            break;
        }
    }
    print_weights();

    for(int i = 0; i < 4; i++) {
        int y = roundf(forward(train_input[i][0], train_input[i][1]));
        printf("%d %d %d\n", train_input[i][0], train_input[i][1], y);
    }

    printf("--------------------\n");
    printf("a\tb\tN1\tN2\tN3\n");
    for(int i = 0; i < 4; i++) {
        float a = sigmoidf(weights[0][0] * train_input[i][0] + weights[0][1] * train_input[i][1] + weights[0][2]); // OR
        float b = sigmoidf(weights[1][0] * train_input[i][0] + weights[1][1] * train_input[i][1] + weights[1][2]); // NAND

        // Layer two
        float r = sigmoidf(weights[2][0] * a + weights[2][1] * b + weights[2][2]); // AND
        printf("%d\t%d\t%d\t%d\t%d\n", 
            train_input[i][0],
            train_input[i][1],
            (int)roundf(a),
            (int)roundf(b),
            (int)roundf(r)
        );
    }

    return 0;
}
