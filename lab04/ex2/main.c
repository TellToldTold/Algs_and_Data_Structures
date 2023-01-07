#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_to_binary(int a) {
    int c;
    int next;
    if (a == 0) {
        return 0;
    }
    if (a % 2 == 0) {
        c = 0;
        next = a / 2;
    } else {
        c = 1;
        next = (a - 1) / 2;
    }

    return c + 10 * int_to_binary(next);
}

int palindrome(char *str, int len) {
    if (len == 0) {
        return 0;
    }
    if (len == 1 || str[0] != str[len - 1]) {
        return 1;
    }

    char substr[len-2];
    memcpy( substr, &str[1], len-2 );
    substr[len-1] = '\0';
    return palindrome(substr, len - 2);
}

int main() {
    printf("%d\n", int_to_binary(27));
    printf("%d", palindrome("cappac", strlen("cappac")));
    return 0;
}