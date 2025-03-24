#include "../include/date.h"

void print_month(Date** month) {
    printf("\n------------------------------------------------------------------\n[%s %d]\n------------------------------------------------------------------\n", month[0]->month_name, month[0]->year);
    for (int i = 0; i < get_day_count(month[0]->month, month[0]->year); i++) {
        if (i != 0 && i % 7 == 0) {
            printf("\n");
        }
        printf("%02d.%02d.%d - %s | ", month[i]->day, month[i]->month, month[i]->year, month[i]->day_name);
    }
}

int main(void) {
    int exit = 0;
    while (exit != 1) {
        int type;
        printf("\n0 - day | 1 - month | 2 - year | 3 - exit\n");
        scanf("%d", &type);
        printf("selected - %d\n", type);
        int day_nbr, month_nbr, year_nbr;
        if (type == 0) {
            printf("day : ");
            scanf("%d", &day_nbr);
            printf("month : ");
            scanf("%d", &month_nbr);
            printf("year : ");
            scanf("%d", &year_nbr);
            Date* date = create_day(day_nbr, month_nbr, year_nbr);
            printf("%d.%d.%d - %s\n", date->day, date->month, date->year, date->day_name);
            free(date);
            date = NULL;
        }
        else if (type == 1) {
            printf("month : ");
            scanf("%d", &month_nbr);
            printf("year : ");
            scanf("%d", &year_nbr);
            Date** month = create_month(month_nbr, year_nbr);
            print_month(month);
            free(month);
            month = NULL;

        }
        else if (type == 2) {
            printf("year : ");
            scanf("%d", &year_nbr);
            Date*** year = create_year(year_nbr);
            for (int i = 0; i < 12; i++) {
                Date** month = year[i];
                print_month(month);

                free(month);
                month = NULL;
            }
            free(year);
            year = NULL;

        }
        else {
            exit = 1;
        }
    }

    return 1;
}