#include "../include/date.h"

void print_month(Date** month) {
    printf("\n------------------------------------------------------------------\nMONTH\n------------------------------------------------------------------\n");
    for (int i = 0; i < get_day_count(month[0]->month, month[0]->year); i++) {
        if (i != 0 && i % 7 == 0) {
            printf("\n");
        }
        printf("%d.%d.%d - %s | ", month[i]->day, month[i]->month, month[i]->year, month[i]->day_name);
    }
}

int main(void) {
    Date*** year = create_year(2025);
    printf("\n\n------------------------------------------------------------------\nYEAR\n------------------------------------------------------------------\n\n");

    for (int i = 0; i < 12; i++) {
        printf("[%d] \n", i + 1);
        printf("---- \n");
        Date** month = year[i];
        print_month(month);

        printf("\n------------------------------------------------------------------\n");
    }
}