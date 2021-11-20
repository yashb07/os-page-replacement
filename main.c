#include <stdio.h>
void print(int frameno, int frame[]) {
    int j;
    for (j = 0; j < frameno; j++)
        printf("%d\t", frame[j]);
    printf("\n");
}

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for(i = 1; i < n; ++i) {
        if(time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
return pos;
}


int main() {
    int i, j, k, n, page[50], frameno, frame[10], move = 0, flag, count = 0, count1[10] = {0},
                                                  repindex, leastcount, counter = 0, time[10], flag1, flag2, pos, faults = 0;
    float LFUrate, LRUrate, FIFOrate;

    
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

    // LFU
    for (i = 0; i < frameno; i++)
        frame[i] = -1;
    // printf("Page \tFrames\n");
    // printf("---------------------------------\n");
    for (i = 0; i < n; i++){
            // printf("%d\t", page[i]);
            flag = 0;
            for (j = 0; j < frameno; j++) {
                if (page[i] == frame[j]) {
                    flag = 1;
                    count1[j]++;
                    // printf("No replacement\n");
                    break;
                }
            }
            if (flag == 0 && count < frameno) {
                frame[move] = page[i];
                count1[move] = 1;
                move = (move + 1) % frameno;
                count++;
                // print(frameno, frame);
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
                // print(frameno, frame);
            }
        }
        LFUrate = ((float)count / (float)n)*100;
    printf("\nLFU Rate: %.2f%%", LFUrate);

    // LRU
    for(i = 0; i < frameno; ++i) {
         frame[i] = -1;
        }
        
    for(i = 0; i < n; ++i) {
        flag1 = flag2 = 0;
    
         for(j = 0; j < frameno; ++j) {
             if(frame[j] == page[i]){
                 counter++;
                 time[j] = counter;
                 flag1 = flag2 = 1;
                 break;
             }
         }
        
         if(flag1 == 0){
            for(j = 0; j < frameno; ++j){
                 if(frame[j] == -1){
                     counter++;
                     faults++;
                     frame[j] = page[i];
                     time[j] = counter;
                     flag2 = 1;
                     break;
                }
            }
         }
        
         if(flag2 == 0) {
         pos = findLRU(time, frameno);
         counter++;
         faults++;
         frame[pos] = page[i];
         time[pos] = counter;
         }
        //  printf("\n");
        
         for(j = 0; j < frameno; ++j) {
        //  printf("%d\t", frame[j]);
         }
    }
    LRUrate = ((float)faults / (float)n)*100;
    printf("\nLFU Rate: %.2f%%", LRUrate);
    printf("\nPage \tFrames\n");
    printf("---------------------------------");
    //FIFO
    int pageFaults = 0;
    int temp[frameno];
      for(int m = 0; m < frameno; m++) {
            temp[m] = -1;
      }
      for(int m = 0; m < n; m++) {
            int s = 0;
            for(n = 0; n < frameno; n++) {
                  if(page[m] == temp[n]) {
                        s++;
                        pageFaults--;
                  }
            }     
            pageFaults++;
            if((pageFaults <= frameno) && (s == 0)) {
                  temp[m] = page[m];
            }   
            else if(s == 0) {
                  temp[(pageFaults - 1) % frameno] = page[m];
            }
            printf("\n");
            for(n = 0; n < frameno; n++) {     
                  printf("%d\t", temp[n]);
            }
      }
      FIFOrate = ((float)pageFaults / (float)n)*100;
      printf("\nFIFO Rate: %.2f%%", FIFOrate);
}