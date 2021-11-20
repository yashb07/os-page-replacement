#include <stdio.h>
void print(int frameno, int frame[]) {
    int j;
    for (j = 0; j < frameno; j++)
        printf("%d\t", frame[j]);
    printf("\n");
}
int main() {
    int i, j, k, n, page[50], frameno, frame[10], move = 0, flag, count = 0, count1[10] = {0},
                                                  repindex, leastcount;
    float rate;
    printf("Enter the number of pages\n");
    scanf("%d", &n);
    printf("---------------------------------\n");
    printf("Enter the page reference numbers\n");
    for (i = 0; i < n; i++)
        scanf("%d", &page[i]);
    printf("---------------------------------\n");
    printf("Enter the number of frames\n");
    scanf("%d", &frameno);
    printf("---------------------------------\n");

    for (i = 0; i < frameno; i++)
        frame[i] = -1;
    printf("Page \tFrames\n");
    printf("---------------------------------\n");
    for (i = 0; i < n; i++){
        printf("%d\t", page[i]);
        flag = 0;
        for (j = 0; j < frameno; j++) {
            if (page[i] == frame[j]) {
                flag = 1;
                count1[j]++;
                printf("No replacement\n");
                break;
            }
        }
        if (flag == 0 && count < frameno) {
            frame[move] = page[i];
            count1[move] = 1;
            move = (move + 1) % frameno;
            count++;
            print(frameno, frame);
        }
        else if (flag == 0) {
            repindex = 0;
            leastcount = count1[0];
            for (j = 1; j < frameno; j++) {
                if (count1[j] < leastcount) {
                    repindex = j;
                    leastcount = count1[j];
                }
            }

            frame[repindex] = page[i];
            count1[repindex] = 1;
            count++;
            print(frameno, frame);
        }
    }
    rate = (float)count / (float)n;
    printf("---------------------------------\n");
    printf("Number of page faults is %d\n", count);
    printf("---------------------------------\n");
    printf("Fault rate is %.2f\n", rate * 100);
    printf("---------------------------------\n");
    return 0;
}
