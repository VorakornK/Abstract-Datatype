#include <stdio.h>
char months[][10] = {"Nothing","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
int dmonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
char days[][5] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
typedef struct datetime {
    int date;       //1-31
    int month;      //1-12
    int year;       //1970+++
    int dayOfWeek;  //0-6
    int hour;       //0-23
    int minute;     //0-59
    int second;     //0-59
} datetime_t;

struct datetime createDate(int time) {
    struct datetime Date;
    //Thu 1 JAN 1970 00.00.00
    int d=1,mo=1,y=1970,dw=3,h=0,m=0,s=0;
    int ix=0,i=0;
    h = time/3600;
    m = (time%3600)/60;
    s = time - h*3600 - m*60;
    printf("%d %d %d\n", h, m, s);
    for (ix=0;ix<time;ix++) {
        i += 1;
        //min
        if (i > 59) {
            i = i%60;
            m += 1;
        }
        //hour
        if (m > 59) {
            m = m%60;
            h += 1;
        }
        //day
        if (h > 23) {
            h = h%24;
            d += 1;
            dw += 1;
            dw = dw%7;
        }
        //month
        if (d > 28 && mo == 2 && y%4==0 && (y%100!=0||y%400==0)) {
            d = d%29;
            mo += 1;
        }
        else if (d>dmonth[mo]) {
            //Check normal
            d = d%dmonth[mo];
            mo += 1;
        }
        //year
        if (mo > 12) {
            mo = mo%12;
            y += 1;
        }
    }
    Date.date = d;
    Date.month = mo;
    Date.year = y;
    Date.dayOfWeek = dw;
    Date.hour = h;
    Date.minute = m;
    Date.second = s;
    return Date;
}
struct datetime printDate(struct datetime Date) {
    printf("%s %d %s %d ", days[Date.dayOfWeek], Date.date, months[Date.month], Date.year);
    if (Date.hour <= 9) printf("0%d", Date.hour);
    else printf("%d", Date.hour);
    printf(":");
    if (Date.minute <= 9) printf("0%d", Date.minute);
    else printf("%d", Date.minute);
    printf(":");
    if (Date.second <= 9) printf("0%d", Date.second);
    else printf("%d", Date.second);
    printf("\n");
}
int main(void) {
    struct datetime inputDate;
    int timestamp;
    scanf("%d", &timestamp);
    inputDate = createDate(timestamp);
    printDate(inputDate);
    return 0;
}