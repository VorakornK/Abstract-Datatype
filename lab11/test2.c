#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    char *a = "cross";
    char h[30];
    strcpy(h, a);
    char *s = h;
    printf("%s\n", s);
    return 0;
}