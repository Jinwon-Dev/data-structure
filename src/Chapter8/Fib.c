#include <stdio.h>

int fib(int n);

int main(int arc, char **argv) {
    int i = 0, input_value = 10;
    int result = 0;

    for (i = 0; i < input_value; i++) {
        result = fib(i);
        printf("fib( %d ) = %d\n", i, result);
    }
    return 0;
}

int fib(int n) {
    int ret = 0;

    if (n == 0) {
        ret = 0;
    } else if (n == 1) {
        ret = 1;
    } else {
        ret = fib(n - 1) + fib(n - 2);
    }

    return ret;
}

int fib_iter(int n) {
    int ret = 0;

    if (n < 2) {
        ret = n;
    } else {
        int i = 0, temp = 0, current = 1, last = 0;

        for (i = 2; i <= n; i++) {
            temp = current;
            current += last;
            last = temp;
        }

        ret = current;
    }

    return ret;
}
