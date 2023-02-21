#include <stdio.h>
#include <string.h>
char convert(int x) {
  char y = x + '0';
  return y;
}
void append(char *all, char add) {
  int size = strlen(all);
  all[size] = add;
  all[size+1] = '\0';
}
void re(char *all) {
  int lena = strlen(all),i;
  char ne[lena];
  for (i=lena-1;i>-1;i--) {
    append(ne, all[i]);
  }
  printf("%s\n", ne);
}
int main()
{
  char str1[1000000], str2[1000000];
  scanf("%s", str1);
  scanf("%s", str2);
  while (strlen(str1) > strlen(str2)) {
    char str[1000000] = "0";
    strcat(str, str2);
    strcpy(str2, str);
  }
  while (strlen(str2) > strlen(str1)) {
    char str[1000000] = "0";
    strcat(str, str1);
    strcpy(str1, str);
  }
  int l1 = strlen(str1), tod = 0, now = 0, i, a, b, nnow;
  char ans[1000000] = "", anow;
  for (i=l1-1;i>-1;i--) {
    //printf("%s\n", ans);
    a = str1[i]-'0';
    b = str2[i]-'0';
    now = a + b + tod;
    nnow = now%10;
    tod = now/10;
    anow = convert(nnow);
    append(ans, anow);
  }
  if (tod != 0) {
    anow = convert(tod);
    append(ans, anow);
  }
  re(ans);
}