#include <stdio.h>
#include <string.h>
#include <math.h>

/**
 * @brief convert binary to float
 * There is the float data structure:
 * Sign bit（1 bit） | Exponent（8 bits） | Fraction（23 bits）
 * @param binaryStr 
 * @return float 
 */
float binaryToFloat(const char *binaryStr) {
    int len = strlen(binaryStr);
    float result = 0.0;
    int sign = 1;
    float exponent = 0.0;
    float fraction = 1.0;

    if (binaryStr[0] == '1')
    {
        sign = -1;
    } else {
        sign = 1;
    }
    
    for (int i = 1; i < 9; i++) {
        if (binaryStr[i] == '1') {
            exponent += pow(2, len - 23 -i - 1);
        }
    }
    
    exponent = exponent - 127;
    
    for (int i = 9; i < 31; i++)
    {
        if (binaryStr[i] == '1') {
            fraction += pow(2, 8 - i);
        }
    }

    // printf("sign: %d\n", sign);
    // printf("exponent: %f\n", exponent);
    // printf("fraction: %f\n", fraction);

    result = sign * pow(2, exponent) * fraction;

    return result;
}

int main() {

    // using binary string to express the float
    const char *binaryStr = "01000001010100000000000000000000";

    // convert binary string to float
    float result = binaryToFloat(binaryStr);

    // print the result
    printf("Binary floating-point numbers: %s\n", binaryStr);
    printf("Decimal floating-point number: %.9f\n", result);

    return 0;
}
