#include <stdio.h>
#define SQUARE(x) ((x) * (x))   
int counter = 0;
int add(int a, int b) {
    return a + b;
}

int main() {
    printf("Hello World\n");
    // 宏的使用
    int a = 3;
    printf("SQUARE(%d) = %d\n", a, SQUARE(a));
    // 调用函数
    int sum = add(5, 7);
    printf("Sum = %d\n", sum);
    // 全局变量
    for (int i = 0; i < 5; i++) {
        counter += i;
    }
    printf("Counter = %d\n", counter);

    return 0;
}
