#include<stdio.h>
#include<string.h>

int ACheck(char *s) {
    int i, l = strlen(s);
    for (i=0;i<l;i++) if (s[i] != 'A') return 0;
    return 1;
}

void Check(char *w1, char *w2) {
    char check[51];
    strcpy(check, w2);
    int l1 = strlen(w1), l2 = strlen(w2), i, at;
    if (l1 == l2) {
        for (at = 0; at < l1; at++) {
            for (i = 0; i < l1; i++) {
                if (w1[at] == check[i]) {
                    check[i] = 'A';
                    break;
                }
            }
        }
        if (ACheck(check)) printf("%s ", w2);
    }
}


int main() {
    mergeS
    int m, n, i, j;
    scanf("%d %d", &m, &n);
    char Dict[m][51], Cur[51];
    for (i=0; i<m; i++) scanf("%s", Dict[i]);
    for (i=0; i<n; i++) {
        scanf("%s", Cur);
        for (j=0; j<m; j++) Check(Cur, Dict[j]);
        printf("\n");
    }
    return 0;
}

/*
8 3
final
fnali
fnial
fianl
title
ttile
tilte
equal

fanil
reply
title

*/