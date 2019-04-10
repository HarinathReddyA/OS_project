#include<stdio.h>
 // Maximum Size Limit
int M_size = 100;
int N; // Number Of Processess

// A Structure Consists of :-
// Id  :-  Name Of The Process = id
// A_time  :-  Arrival Time = atime 
// B_time  :-  Burest Time = btime
// p   :-  Priority = p
// F_time  :-  Finished Time = ftime
// S_time  :-  Starting Time = stime
// W_time  :-  Waiting Time = wtime
// TA_time :-  Total TurnAround Time = trtime

struct data {
    int num,atime,btime,p,rtime,ftime,stime,wtime,trtime;
    
   
};
// P_Qfront :- Priority q Front
// P_Qrear :- Priority q Rear
// RR_front :- q Front
// RRQ_rear :- q Rear

int P_Qfront = -1, P_Qrear = -1;
int RR_front = -1, RRQ_rear = -1;




// Declaration of Array of Structures

struct data* pq[M_size];
struct data* q[M_size];

// Sorting the Process
// Sort According to the arrival time if any two arrival time are equal then
// Sort According to there Process Id


void sort(struct data p[])
 {
    int i, j;
    struct data temp;
    for (i=0; i< N; i++)
     {
        for (j=i; j>=1; j--) 
        {
            if (p[j].atime < p[j - 1].atime)
             {
                temp = p[j - 1];
                p[j - 1] =p[j];
                p[j] = temp;
            }
            else if (p[j].atime == p[j - 1].atime)
             {
                if (p[j].num < p[j].num) 
                {
                    temp=p[j - 1];
                    p[j - 1] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}

// pqEmpty is a function which tell Priority q is empty or not

int pqEmpty() 
{
    return (P_Qfront == -1 && P_Qrear == -1); // If P_Qfront and P_Qrear both are equal to -1 then Priority q is Empty else not empty
}

// pqTop is a function which returns the top of the Priority q

struct data* pqTop() 
{
    return pq[P_Qfront];
}

// P_order is a function which put data into the desire position

void P_order(struct data *x) 
{
    int i, j;
    for (i = 0; i <= P_Qrear; i++) 
    {
        if (x->p < pq[i]->p) 
        {
            for (j = P_Qrear + 1; j > i; j--) 
            {
                pq[j] = pq[j - 1];
            }
            pq[i] = x;
            return;
        }
    }
    pq[i] = x;
}
// pqPush is a function which push data into the Priority q
void pqPush(struct data* x) 
{
    if (P_Qfront == -1 && P_Qrear == -1)
     { // If Priority q is empty then
        P_Qfront++; // Increment the both the values to 1
        P_Qrear++;
        pq[P_Qrear] = x;
        return;
    }
    else 
    {
        P_order(x);
    }
    P_Qrear++;
}

// pqPop is a function which pop out the data from Priority q
void pqPop() 
{
    int i;
    if (P_Qfront == -1 && P_Qrear == -1)
     {
        return;
    }
    for (i =0; i < P_Qrear; i++) 
    {
        pq[i] = pq[i + 1];
    }
    P_Qrear--;
    if (P_Qrear == -1)
        P_Qfront = -1;
}

// rpEmpty is a function which tells q is Empty or Not

int RRQ_empty() 
{
    return (RR_front == -1 && RRQ_rear == -1);
}

// RRQ_front is a function which returns the top of elemeent from q

struct data* RRQ_front() 
{
    return q[RR_front];
}

// RRQ_push ia a function which push elements into the q

void RRQ_push(struct data* x) 
{
    if (RR_front == -1 && RRQ_rear == -1)
    {
        RR_front++;
        RRQ_rear++;
        q[RRQ_rear] = x;
        return;
    }
    else
    {
        RRQ_rear++;
    }
    q[RRQ_rear] = x;
}

// RRQ_pop is a function which pop out the element from q

void RRQ_pop() 
{
    if (RR_front == -1 && RRQ_rear == -1) 
    {
        return;
    }
    for (int i = 0; i <= RRQ_rear; i++) 
    {
        q[i] = q[i + 1];
    }
    RRQ_rear--;
    if (RRQ_rear == -1)
        RR_front = -1;
}

// It calculate the average waiting time and average turnaround time

void calc(struct data p[], int g[], int n)
{
    int i, j;
    float Avg_Wtime = 0, Avg_TRtime = 0;
    for (i = 0; i < N; i++)
    {
        for (j = n; j >= 0; j--) 
        {
            if (g[j] == i + 1) 
            {
                p[i].ftime = j + 1;
                break;
            }
        }
    }
    for (i = 0; i < N; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            if (g[j] == i + 1) 
            {
                p[i].stime = j;
                break;
            }
        }
    }
    for (i = 0; i < N; i++) 
    {
        p[i].wtime = p[i].ftime - p[i].atime - p[i].btime;
        p[i].trtime = p[i].wtime + p[i].btime;
        Avg_Wtime += p[i].wtime;
        Avg_TRtime += p[i].trtime;
    }
    printf("Id \t ArrivalTime \t Burst_Time \t WaitingTime \t TurnAroundTime \n");
    for (i = 0; i < N; i++) 
    {
        printf("%d \t    %d \t\t    %d \t\t    %d \t\t    %d \n", p[i].num, p[i].atime, p[i].btime, p[i].wtime, p[i].trtime);
    }
    Avg_Wtime /= N;
    Avg_TRtime /= N;
    printf("\n\n");
    printf("Average Waiting Time And Average Turn Around Time \n\n");
    printf("%f %f", Avg_Wtime, Avg_TRtime);
    printf("\n");
}
// Implementatio of Multi Level q
void Multi_level_Q(struct data p[])
{
    int Total_time = 0; // Sum of all burst
    Total_time += p[0].atime + p[0].btime;
    for (int i = 1; i < N; i++)
    {
        if (Total_time < p[i].atime)
            Total_time = p[i].atime;
        Total_time += p[i].btime;
    }
    int ghant[Total_time]; // Ghant Chart
    int status = 0; // Status of the CPU
    for (int i = 0; i < Total_time; i++){
        ghant[i] = -1;}
    struct data* present;
    int pq_process = 0; // Status of the Priority q
    int rq_process = 0; // Status of the q
    int q = 2; // Time Quantum for Round Robin
    for (int i = 0; i < Total_time; i++) {
        for (int j = 0; j < N; j++) {
            if (i == p[j].atime) {
                pqPush(&p[j]); // Pushing all elements which has arrived
            }
        }
        if (status == 0) { // Checking Status of CPU
            if (!pqEmpty()) {
                present = pqTop();
                pqPop();
                pq_process = 1;
                status = 1;
            }
            else if (!RRQ_empty()) {
                present = RRQ_front();
                RRQ_pop();
                rq_process = 1;
                q = 2;
                status = 1;
            }
        }
        else if (status == 1) 
        {
            if (pq_process == 1 && !pqEmpty()) 
            {
                if (pqTop()->p < present->p) 
                {
                    RRQ_push(present);
                    present = pqTop();
                    pqPop();
                }
            }
            else if (rq_process == 1 && !pqEmpty()) 
            {
                RRQ_push(present);
                present = pqTop();
                pqPop();
                rq_process = 0;
                pq_process = 1;
            }
        }
        if (status == 1) {
            if (pq_process == 1) {
                present->rtime--;
                ghant[i] = present->num;
                if (present->rtime == 0) {
                    status = 0;
                    pq_process = 0;
                }
            }
            else if (rq_process == 1) {
                present->rtime--;
                q--;
                ghant[i] = present->num;
                if (present->rtime == 0) {
                    status = 0;
                    rq_process = 0;
                }
                else if (q == 0) {
                    status = 0;
                    rq_process = 1;
                    RRQ_push(present);
                }
            }
        }
    }
    // Printing ghant Chart
    printf("\n\n");
    for (int i = 0; i < Total_time; i++) {
        printf("%d ", ghant[i]);
    }
    printf("\n\n");
    calc(p, ghant, Total_time);
}

int main() {
    printf("Enter number of process: \n");
    scanf("%d", &N);
    struct data p[N];
    printf("Enter process id, arrival time, burest time, priority \n");
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d%d", &p[i].num, &p[i].atime, &p[i].btime, &p[i].p);
        p[i].rtime = p[i].btime;
    }
    sort(p);
    Multi_level_Q(p);
    return 0;
}
