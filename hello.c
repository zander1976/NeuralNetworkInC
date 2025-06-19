#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int data_size = 5;

typedef struct {
    int input;
    int output;
} training_data;

training_data* load_data() {
    training_data *data = (training_data*) malloc(data_size * sizeof(training_data));

    if (data == NULL) {
        printf("Unable to allocate memory!");
        exit(-1);
    }

    for(int i = 0; i < data_size; i++) {
        data[i].input = i;
        data[i].output = i * 2;
    }
    return data;
}

float loss(training_data* data, float* m1) { //, float* w1, float* b) {
    float result = 0.0f;

    float y = 0.0f;
    for(int i = 0; i < data_size; i++) {
        float y = *m1 * data[i].input;
        result += pow(y - data[i].output, 2);
    }
    return sqrtf(result);
}

float inference(float input, float* m1) {
    return *m1 * input;
}

int main() {
    srand(time(0));
    float m1 = ((float)rand() / RAND_MAX) * 10;
    //float w1 = ((float)rand() / RAND_MAX) * 10;
    //float b = ((float)rand() / RAND_MAX) * 10;
    printf("m1: %f\n", m1);

    training_data* data = load_data();

    float result = 0.0f;
    float resulth = 0.0f;
    float learning_rate = -1e-3f;
    float dresult = 0.0f;
    float mh = 0.0f;

    for(int i = 0; i < 10000; i++) {
        // Test the current version
        result = loss(data, &m1);
        mh = m1 + learning_rate;
        resulth = loss(data, &mh);

        if (result < 0.001) {
            printf("\n**********************\n");
            printf("Found at %d, Weight: %f, Loss: %f\n", i, m1, result);
            printf("**********************\n\n\n");
            break;
        }

        // f'(x) = f(x + h) - f(x) / h;
        dresult = (resulth - result) / learning_rate;
        m1 += learning_rate * dresult;
        printf("i: %d, m1: %f, Loss: %f\n", i, m1, result);
    }
    free(data);
    data = NULL;

    printf("\n**********************\n");
    printf("Inference: ");
    printf("\n**********************\n");
    for(int i = 0; i < 20; i=i + 2) {
        printf("Input: %d, Result: %.2f\n", i, round(inference(i, &m1)));
    }



    return 0;
}