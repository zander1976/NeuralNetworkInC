#include <stdio.h>
#include <math.h>
#include <time.h>

// a1 = x1*w1 + x2*w3 + b
// a2 = x1*w2 + x2*w4 + b

// Row by column
// Mmxn * Nnxp = Omxp
// 1x3 * 3x2 = 1x2
// [x1, x2, 1] * [w1_1 w1_2] = [x1w1_1 + x2w2_1 + b3_1] = [a1]
//               [w2_1 w2_2]   [x1w1_2 + x2w2_2 + b3_2]   [a2]
//               [b3_1 b3_2]   
int input[] = {0,0,0};
int weights[][2] = {
    {0, 0},
    {0, 0},
    {0, 0}
};
