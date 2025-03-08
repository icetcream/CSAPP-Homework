#include <stdio.h>

// 多项式求值函数
double polynomial_evaluation(double coefficients[], int degree, double x) {
    double result = coefficients[0]; // 从最高次系数开始
    double xpwr = x;
    for (int i = 1; i <= degree; i++) {
        result += coefficients[i]*xpwr;
        xpwr = x*xpwr;
    }
    return result;
}

int main() {
    // 示例：多项式 2x^3 - 6x^2 + 0x + 3
    double coefficients[] = {2, -6, 0, 3}; // 系数数组
    int degree = 3; // 多项式的最高次
    double x_value = 5.0; // 要求值的点

    double result = polynomial_evaluation(coefficients, degree, x_value);
    printf("多项式在 x = %.2f 处的值为: %.2f\n", x_value, result);

    return 0;
}