#include<stdio.h>
#include<string.h>

int ACheck(char *s) {
    int i, l = strlen(s);
    for (i=0;i<l;i++) if (s[i] != 'A') return 0;
    return 1;
}


int main() {
    printf("%d\n", ACheck("AAAAAAA"));
    printf("%d\n", ACheck("AAAAaAA"));
    printf("%d\n", ACheck("phoom"));
    printf("%d\n", ACheck("xas"));
    printf("%d\n", ACheck("hhhh"));

    return 0;
}