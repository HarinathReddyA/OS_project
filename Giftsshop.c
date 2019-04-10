
#include<stdio.h>
#include<stdlib.h>
#define M_size 10 // Maximum Size Limit

int N; // Number Of Processess

// A Structure Consists of :-
// Pid  :-  Name Of The Process or the process id
// atime  :-  Arrival Time
// btime  :-  Burest Time
// ftime  :-  Finished Time
// stime  :-  Starting Time
// wtime  :-  Waiting Time
// trtime :-  Total TurnAround Time

struct data {
    int num;
    char pid[5];
    int atime;
    int btime;
    int rtime;
    int ftime;
    int stime;
    int wtime;
    int trtime;
};

// Variables Which Are Usefull For The P_que
// P_front :- Priority Queue Front
// P_rwar :- Priority Queue Rear

int P_front = -1, P_rear = -1;

// Declaration of Array of Structures

struct data P_que[M_size];

// check is a function which put data into the desire position

void check(struct data x) {
    int i, j;
    for (i = 0; i <= P_rear; i++) {
        if (x.btime > P_que[i].btiem) {
            for (j = P_rear + 1; j > i; j--) {
                P_que[j] = P_que[j - 1];
            }
            P_que[i] = x;
            return;
        }
    }
    P_que[i] = x;
}

// PQ_push is a function which push data into the Priority Queue

void PQ_push(struct data x) {
    if (P_front == -1 && P_rear == -1) {
        P_front++;
        P_rear++;
        P_que[P_rear] = x;
        return;
    }
    else {
        check(x);
    }
    P_rear++;
}

// PQ_pop is a function which pop out the data P_frontom Priority Queue

void PQ_pop() {
    int i;
    if (P_front == -1 && P_rear == -1) {
        return;
    }
    for (i = 0; i < P_rear; i++) {
        P_que[i] = P_que[i + 1];
    }
    P_rear--;
    if (P_rear == -1)
        P_front = -1;
}

// PQ_empty is a function which tell Priority Queue is empty or not

int PQ_empty() {
    return ((P_front == -1 && P_rear == -1));
}

// PQ_top is a function which returns the top of the Priority Queue

struct data PQ_top() {
    return P_que[P_front];
}

int PQ_size() {
    return P_rear - P_front;
}

void calc(struct data p[], int g[], int n) {

    int i, j;
    float Avg_W_time = 0, Avg_TR_time = 0;

    for (i = 0; i < N; i++) {

        for (j = n; j >= 0; j--) {

            if (g[j] == p[i].num) {

                p[i].ftime = j + 1;
                break;
            }
        }
    }

    for (i = 0; i < N; i++) {

        for (j = 0; j < n; j++) {

            if (g[j] == p[i].num) {

                p[i].stime = j;
                break;
            }
        }
    }

    for (i = 0; i < N; i++) {

        p[i].wtime = p[i].ftime - p[i].atime - p[i].btime;
        p[i].trtime = p[i].wtime + p[i].btime;
        Avg_W_time += p[i].wtime;
        Avg_TR_time += p[i].trtime;
    }

    printf("Id \t ArrivalTime \t BurestTime \t WaitingTime \t TurnAroundTime \n");

    for (i = 0; i < N; i++) {

        printf("%d \t    %d \t\t    %d \t\t    %d \t\t    %d \n", p[i].num, p[i].atime, p[i].btime, p[i].wtime, p[i].trtime);
    }

    Avg_W_time /= N;
    Avg_TR_time /= N;

    printf("\n\n");
    printf("Average Waiting Time And Average Turn Around Time \n\n");

    printf("%f %f", Avg_W_time, Avg_TR_time);

    printf("\n");

}

void sort1(struct data p[]) {
    int i, j, mn;
    struct data tmp;
    for (i = 0; i < N - 1; i++) {
        mn = i;
        for (j = i + 1; j < N; j++) {
            if (p[j].num < p[mn].num)
                mn = j;
        }
        tmp = p[i];
        p[i] = p[mn];
        p[mn] = tmp;
    }
}

void LRT(struct data p[]) {
    int tt = 0;
    tt += p[0].atime + p[0].btime;
    for (int i = 1; i < N; i++) {
        if (tt < p[i].atime)
            tt = p[i].atime;
        tt += p[i].btime;
    }
    int gant[tt], status = 0;
    for (int i = 0; i < tt; i++)
        gant[i] = -1;
    struct data present;
    for (int i = 0 ;i < tt; i++) {
        for (int j = 0; j < N; j++) {
            if (i == p[j].atime) {
                PQ_push(p[j]);
            }
        }
        if (status == 0) {
            if (!PQ_empty()) {
                present = PQ_top();
                PQ_pop();
                status = 1;
            }
        }
        if (status == 1) {
            present.btime--;
            gant[i] = present.num;
            if (present.btime == 0) {
                status = 0;
            }
        }
    }

    for (int i = 0; i < tt; i++)
        printf("%d ", gant[i]);
    printf("\n");

    sort1(p);

    calc(p, gant, tt);
}

void sort(struct data p[]) {
    int i, j, mn;
    struct data tmp;
    for (i = 0; i < N - 1; i++) {
        mn = i;
        for (j = i + 1; j < N; j++) {
            if (p[j].at < p[mn].at)
                mn = j;
        }
        tmp = p[i];
        p[i] = p[mn];
        p[mn] = tmp;
    }
}

// It calculate the average waiting time and average turnaround time


int main() {
    //("%d", &N);
    N = 10;
    struct data p[N];
    int atime, btime;
    for (int i = 0; i < N; i++) {
        //scanf("%d%d%d", &p[i].num, &p[i].at, &p[i].bt);
        //p[i].num = i;
        p[i].num = i + 1;
        at = rand() % 10 + 1;
        p[i].atime = at;
        bt = rand() % 20 + 1;
        p[i].btime = btime;
    }

    sort(p);

    for (int i = 0; i < N; i++) {
        printf(" %d %d %d \n", p[i].num, p[i].atime, p[i].btime);
    }

    LRT(p);

    printf("\n");

    return 0;
}
