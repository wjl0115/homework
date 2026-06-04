#include <stdio.h>
char* input() {
    static char str[100];
    printf("input:\n");
    scanf("%s", str);
    return str;
}

int main() {
    char* Input = input(); 
    printf("%s\n", Input);
    return 0;
}