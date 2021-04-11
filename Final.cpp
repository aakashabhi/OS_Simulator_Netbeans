#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#include<algorithm>
#include <vector>
#include<climits>
#include<cmath>
#include <bits/stdc++.h>
using namespace std;
struct Row
{
    int AT;//Arrival Time//
    int BT;//Burst Time//
    int CT;//Completion Time//
    int serial;//Process Number//
    int TAT;//Turn Around Time//
    int WT;//Waiting Time//
    bool completed;//To check if Process is completed before or not//
};
struct RowRR
{
    int AT;//Arrival Time//
    int BT;//Burst Time//
    int CT;//Completion Time//
    int serial;//Process Number//
    int TAT;//Turn Around Time//
    int WT;//Waiting Time//
    bool completed;//Checking If Process is Completed//
    bool inqueue;//Checking If it Was Added to Queue EARLIER//
};
struct partitio
{
	int process;
	int size;
};
//Funct
bool comp(const Row &a,const Row &b)
{
    return a.AT<b.AT;
}
bool comp2(const RowRR &a,const RowRR &b)
{
    return a.AT<b.AT;
}
void sjfjob()
{
    cout<<"Shortest Job First"<<endl;
    cout<<"Enter number of programs"<<endl;
    int n,a,b;
    cin>>n;
    vector<struct Row>table(n);
    //Taking input of AT and BT//
    for(int i=0;i<n;i++)
    {
        cout<<"Enter Arrival and Burst Time of Program "<<i+1<<endl;
        cin>>a>>b;
        table[i].serial=i+1;
        table[i].AT=a;
        table[i].BT=b;
        table[i].completed=false;
    }
    int t=0;
    int index;
    int done=n;
    int shortest;
    float avgtat=0,avgwt=0;
    cout<<"P.No  AT  BT  CT  TAT  WT"<<endl;
    while(done!=0)// To check if all processes are completed//
    {
        index=-1;
        shortest=INT_MAX;

        for(int i=0;i<n;i++)//Traversing through All processes//
        {

            if(table[i].completed==false &&table[i].AT<=t)//Checking if the process is not completed and is on the ready queue//
            {
                //Finding process with Shortest CT//
                if(table[i].BT<shortest)
                {
                    shortest=table[i].BT;
                    index=i;

                }
                else if(table[i].BT==shortest)//If two processes have same shortest time,the one which arrived first comes first//
                {
                    if(table[i].AT<table[index].AT)
                    {
                        index=i;//Updating  Index//
                    }
                }


            }
        }
        if(index==-1)//Checking if there is any process on the ready queue//
        {
            t++;//Incrementing Current time//
        }
        else
        {
            table[index].completed=true;
            t+=table[index].BT;
            table[index].CT=t;

            table[index].TAT=table[index].CT-table[index].AT;//TAT=CT-AT//
            table[index].WT=table[index].TAT-table[index].BT;//WT=CT-BT//
            done--;//Decrementing as a process is done//
            avgtat+=table[index].TAT;
            avgwt+=table[index].WT;
            //Printing Output//
            cout<<table[index].serial<<"    "<<table[index].AT<<"   "<<table[index].BT<<"   "<<table[index].CT<<"   "<<table[index].TAT<<"   "<<table[index].WT<<endl;


        }

    }
    //Printing average TAT and Average WT//
    cout<<endl<<"Average Turn Around Time: "<<avgtat/n<<endl<<"Average Waiting time: "<<avgwt/n<<endl;

}

void fcfsjob()
{
    cout<<"FIRST COME FIRST SERVE"<<endl;
    cout<<"Enter number of Processes"<<endl;
    int n,a,b;
    cin>>n;
    vector<struct Row>table(n);
    //Taking AT and BT as Inputs//
    for(int i=0;i<n;i++)
    {
        cout<<"Enter Arrival and Burst Time of Program "<<i+1<<endl;
        cin>>a>>b;\
        table[i].serial=i+1;
        table[i].AT=a;
        table[i].BT=b;
    }
    //Sorting in increasing order of AT//
    sort(table.begin(),table.end(),comp);
    int t=0;
    cout<<"P.No  AT  BT  CT  TAT  WT"<<endl;
    float avgtat=0,avgwt=0;
    for(int i=0;i<n;i++)
    {
        t=max(t,table[i].AT);
        t+=table[i].BT;
        table[i].CT=t;
        table[i].TAT=table[i].CT-table[i].AT;//TAT=CT-AT//
        table[i].WT=table[i].TAT-table[i].BT;//WT=TAT-BT//
        avgtat+=table[i].TAT;
        avgwt+=table[i].WT;
        //Printing Output//
        cout<<table[i].serial<<"     "<<table[i].AT<<"   "<<table[i].BT<<"   "<<table[i].CT<<"   "<<table[i].TAT<<"   "<<table[i].WT<<endl;

    }
    //Printing Avg TAT and Avg WT//
    cout<<endl<<"Average Turn Around Time: "<<avgtat/n<<endl<<"Average Waiting time: "<<avgwt/n<<endl;

   
}
void rrjob()
{
    cout<<"Round Robin"<<endl;
    cout<<"Enter number of programs"<<endl;
    int n,a,b;
    cin>>n;
    vector<struct RowRR>table(n);
    //Taking input of AT and BT//
    for(int i=0;i<n;i++)
    {
        cout<<"Enter Arrival and Burst Time of Program "<<i+1<<endl;
        cin>>a>>b;
        table[i].serial=i+1;
        table[i].AT=a;
        table[i].BT=b;
        table[i].completed=false;
    }
    //Sorting//
    sort(table.begin(),table.end(),comp2);
    int timeslice;
    //Taking Input as Time Slice//
    cout<<"Enter Time Slice"<<endl;
    cin>>timeslice;
    int t=0;
    t=max(t,table[0].AT);
    //Initialising Queue and pushing in the first process//
    queue<int>ready;
    ready.push(0);//Pushing in first Process to Ready Queue//
    table[0].inqueue=true;
    int i;
    vector<int>BurstReal(n);
    //Storing Values of Burst Times in BurstReal//
    for(i=0;i<n;i++)
    {
        BurstReal[i]=table[i].BT;
    }
    i=0;

    while(!ready.empty())//Keep on DOing until the queue is empty//
    {
        i=ready.front();//Choosing the Process in the front//
        t+=min(timeslice,table[i].BT);
        table[i].BT=table[i].BT-min(timeslice,table[i].BT);
        //Pushing in Processes that are available to be pushed into Ready Queue//
        for(int j=0;j<n;j++)
        {
            if(t>=table[j].AT&&table[j].inqueue==false)//Checking if process has  arrived and not in the ready queue//
            {
                table[j].inqueue=true;
                ready.push(j);
            }

        }
        if(table[i].BT>0)//Checking if process is yet to be completed//
        {
            ready.push(i);
        }
        else//Checking if Process is Completed//
        {
            table[i].completed=true;
            table[i].CT=t;//Assigning CT//

        }
        ready.pop();
    }
    cout<<"P.No  AT  BT  CT  TAT  WT"<<endl;
    float avgtat=0,avgwt=0;
    for(int i=0;i<n;i++)
    {
        table[i].BT=BurstReal[i];//Initialising Burst values to original burst values//
        table[i].TAT=table[i].CT-table[i].AT;//TAT=CT-AT//
        table[i].WT=table[i].TAT-table[i].BT;//WT=TAT-BT//
        avgtat+=table[i].TAT;
        avgwt+=table[i].WT;
        //Printing Output//
        cout<<"P"<<table[i].serial<<"     "<<table[i].AT<<"   "<<table[i].BT<<"   "<<table[i].CT<<"   "<<table[i].TAT<<"   "<<table[i].WT<<endl;

    }
        //Printing Avg TAT and Avg WT//
    cout<<endl<<"Average Turn Around Time: "<<avgtat/n<<endl<<"Average Waiting time: "<<avgwt/n<<endl;

}
 /*structure for contents of gantt chart */
struct gantt_chartljf{
    int P_no;   //process number
    int AT;     //arrival time
    int BT;     //burst time
    int CT;     //completion time
    int TAT;    //turnaround time
    int WT;     //waiting time
    int is_completed;  //boolean variable to track whether process is completed or not
};

/* printing gantt table */
void printTable(struct gantt_chartljf arr[], int n)
{
    printf("\nGantt table: \n");
    printf("P no.   AT    BT    CT   TAT    WT\n");
    for(int i=0; i<n; i++){
        printf("%5d %5d %5d %5d %5d %5d \n",arr[i].P_no,arr[i].AT,arr[i].BT, arr[i].CT, arr[i].TAT, arr[i].WT );
    }
}

void ljfjob()
{
    /* getting total number of processes */
    int n;
    printf("Enter total number of processes:");
    scanf("%d",&n);

    /* getting gantt chart from user */
    struct gantt_chartljf arr[n];
    for(int i=0; i<n; i++){
        arr[i].P_no=i+1;
        arr[i].is_completed=0;
        printf("Enter arrival time and burst time of process %d:", i+1);
        scanf("%d %d", &arr[i].AT, &arr[i].BT);
    }

    int total_TAT=0, total_WT=0;
    int current_time=0;
    int completed=0;    //keeps a track of total processes completed till current time

    /*
        a loop that will terminate only when all processes are completed
    */
    while(completed < n){
        int x=-1;   //keeps track of index of process
        int m=INT_MIN;  //maximum burst time among processes in ready block
        for(int i=0; i<n; i++){
            /*
                finding processes in ready block
            */
            if(arr[i].is_completed == 0 && arr[i].AT<=current_time){
                /*
                    searching for a process with maximum burst time in ready block
                */
                if(arr[i].BT > m){
                    m=arr[i].BT;
                    x=i;
                }
                else if(arr[i].BT == m){
                    if(arr[i].AT < arr[x].AT){
                        x=i;
                    }
                }
            }
        }

        if(x != -1){
            arr[x].CT=current_time+arr[x].BT;
            arr[x].TAT=arr[x].CT-arr[x].AT;
            arr[x].WT=arr[x].TAT-arr[x].BT;

            total_TAT+=arr[x].TAT;
            total_WT+=arr[x].WT;

            arr[x].is_completed=1;  //marking process as completed
            completed++;            //incrementing completed processes
            current_time+=arr[x].BT;
        }
        else{
            current_time++;
        }
    }


    // printing gantt table
    printTable(arr, n);

    // printing output
    printf("Average TAT: %d \nAverage WT: %d", total_TAT/n, total_WT/n);
}
/* structure for contents of gantt chart */
struct gantt_chart{
    int P_no;   //process number
    int AT;     //arrival time
    int BT;     //burst time
    int CT;     //completion time
    int TAT;    //turnaround time
    int WT;     //waiting time
    int is_completed;  //boolean variable to track whether process is completed or not
    int remaining_time;
};

/* sort function for sorting gantt chart in ascending order
of arrival time */
void insertionSort(struct gantt_chart arr[], int n){
    int i, key, j;
    struct gantt_chart temp;
    for(i=1; i<n; i++){
        key = arr[i].AT;
        temp = arr[i];
        j=i-1;

        while(j>=0 && arr[j].AT>key){
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=temp;
    }
}


/* printing gantt table */
void printTable2(struct gantt_chart arr[], int n){
    printf("\nGantt table: \n");
    printf("P no.   AT    BT    CT   TAT    WT\n");
    for(int i=0; i<n; i++){
        printf("%5d %5d %5d %5d %5d %5d \n",arr[i].P_no,arr[i].AT,arr[i].BT, arr[i].CT, arr[i].TAT, arr[i].WT );
    }
}

void lrtfjob()
{
    /* getting total number of processes */
    int n;
    printf("Enter total number of processes:");
    scanf("%d",&n);

    /* getting gantt chart from user */
    struct gantt_chart arr[n];
    for(int i=0; i<n; i++){
        arr[i].P_no=i+1;
        arr[i].is_completed=0;
        printf("Enter arrival time and burst time of process %d:", i+1);
        scanf("%d %d", &arr[i].AT, &arr[i].BT);
        arr[i].remaining_time=arr[i].BT;
    }

    /*  sort function for sorting gantt chart in ascending order
        of arrival time
    */
    insertionSort(arr, n);

    int total_TAT=0, total_WT=0;
    int current_time=0;
    int completed=0;    //keeps a track of total processes completed till current time



    /*
        a loop that will terminate only when all processes are completed
    */
    while(completed < n){

        int x=-1;   //keeps track of index of process
        int m=INT_MIN;  //maximum burst time among processes in ready block
        for(int i=0; i<n; i++){
            /*
                finding processes in ready block
            */
            if(arr[i].is_completed == 0 && arr[i].AT<=current_time){
                /*
                    searching for a process with maximum burst time in ready block
                */
                if(arr[i].BT > m){
                    m=arr[i].BT;
                    x=i;
                }
                else if(arr[i].BT == m){
                    if(arr[i].AT < arr[x].AT){
                        x=i;
                    }
                }
            }
        }

        if(x != -1){
            arr[x].remaining_time--;
            if(arr[x].remaining_time == 0){
                arr[x].is_completed=1;  //marking process as completed
                completed++;            //incrementing completed processes

                arr[x].CT=current_time+1;
                arr[x].TAT=arr[x].CT-arr[x].AT;
                arr[x].WT=arr[x].TAT-arr[x].BT;

                total_TAT+=arr[x].TAT;
                total_WT+=arr[x].WT;
            }
            current_time++;

        }
        else{
            current_time++;
        }
    }


    // printing gantt table
    printTable2(arr, n);

    // printing output
    printf("Average TAT: %d \nAverage WT: %d", total_TAT/n, total_WT/n);

}
void srtfjob()
{
    /* getting total number of processes */
    int n;
    printf("Enter total number of processes:");
    scanf("%d",&n);

    /* getting gantt chart from user */
    struct gantt_chart arr[n];
    for(int i=0; i<n; i++){
        arr[i].P_no=i+1;
        arr[i].is_completed=0;
        printf("Enter arrival time and burst time of process %d:", i+1);
        scanf("%d %d", &arr[i].AT, &arr[i].BT);
        arr[i].remaining_time=arr[i].BT;
    }

    /*  sort function for sorting gantt chart in ascending order
        of arrival time
    */
    insertionSort(arr, n);

    int total_TAT=0, total_WT=0;
    int current_time=0;
    int completed=0;    //keeps a track of total processes completed till current time



    /*
        a loop that will terminate only when all processes are completed
    */
    while(completed < n){

        int x=-1;   //keeps track of index of process
        int m=INT_MAX;  //minimum burst time among processes in ready block
        for(int i=0; i<n; i++){
            /*
                finding processes in ready block
            */
            if(arr[i].is_completed == 0 && arr[i].AT<=current_time){
                /*
                    searching for a process with minimum burst time in ready block
                */
                if(arr[i].BT < m){
                    m=arr[i].BT;
                    x=i;
                }
                else if(arr[i].BT == m){
                    if(arr[i].AT < arr[x].AT){
                        x=i;
                    }
                }
            }
        }

        if(x != -1){
            arr[x].remaining_time--;
            if(arr[x].remaining_time == 0){
                arr[x].is_completed=1;  //marking process as completed
                completed++;            //incrementing completed processes

                arr[x].CT=current_time+1;
                arr[x].TAT=arr[x].CT-arr[x].AT;
                arr[x].WT=arr[x].TAT-arr[x].BT;

                total_TAT+=arr[x].TAT;
                total_WT+=arr[x].WT;
            }
            current_time++;

        }
        else{
            current_time++;
        }
    }


    // printing gantt table
    printTable2(arr, n);

    // printing output
    printf("Average TAT: %d \nAverage WT: %d", total_TAT/n, total_WT/n);

}
// Defining process details
struct process {
    char name;
    int at, bt, ct, wt, tt;
    int completed;
    float ntt;
} p[10];

// Sorting Processes by Arrival Time
void sortByArrival(int n)
{
    struct process temp;
    int i, j;

    // Selection Sort applied
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {

            // Check for lesser arrival time
            if (p[i].at > p[j].at) {

                // Swap earlier process to front
                temp = p[i];
                  p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
void hrrnjob()//TO BE CHECKED ONCE
{
    int i, j, t, sum_bt = 0;
    char c;
    int n;
    float avgwt = 0, avgtt = 0;
    printf("Enter no of process : ");
    scanf("%d",&n);

    // predefined arrival times
    int arriv[n];

    // predefined burst times
    int burst[n];
    for(int i=0;i<n;i++)
    {
        printf("\nAT   BT   of  P%d  : ",i);
        scanf("%d %d",&arriv[i],&burst[i]);
    }

    // Initializing the structure variables
    for (i = 0, c = 'A'; i < n; i++, c++) {
        p[i].name = c;
        p[i].at = arriv[i];
        p[i].bt = burst[i];
          p[i].completed = 0;

        // Variable for sum of all Burst Times
        sum_bt += p[i].bt;
    }

    // Sorting the structure by arrival times
    sortByArrival(n);
    printf("\nProcess Name\tArrival Time\tBurst Time\tWaiting Time");
    printf("\tTurnAround Time\t Normalized TT");
    for (t = p[0].at; t < sum_bt;) {

        // Set lower limit to response ratio
        float hrr = -9999;

        // Response Ratio Variable
        float temp;

        // Variable to store next processs selected
        int loc;
        for (i = 0; i < n; i++) {

            // Checking if process has arrived and is Incomplete
            if (p[i].at <= t && p[i].completed != 1) {

                 // Calculating Response Ratio
                temp = (p[i].bt + (t - p[i].at)) / p[i].bt;

                // Checking for Highest Response Ratio
                if (hrr < temp) {

                    // Storing Response Ratio
                    hrr = temp;

                    // Storing Location
                    loc = i;
                }
            }
        }

        // Updating time value
        t += p[loc].bt;

        // Calculation of waiting time
        p[loc].wt = t - p[loc].at - p[loc].bt;

        // Calculation of Turn Around Time
        p[loc].tt = t - p[loc].at;

        // Sum Turn Around Time for average
        avgtt += p[loc].tt;

                 p[loc].ntt = ((float)p[loc].tt / p[loc].bt);

        // Updating Completion Status
        p[loc].completed = 1;

        // Sum Waiting Time for average
        avgwt += p[loc].wt;
        printf("\n%c\t\t%d\t\t", p[loc].name, p[loc].at);
        printf("%d\t\t%d\t\t", p[loc].bt, p[loc].wt);
        printf("%d\t\t%f", p[loc].tt, p[loc].ntt);
    }
    printf("\nAverage waiting time:%f\n", avgwt / n);
    printf("Average Turn Around time:%f\n", avgtt / n);
}
void fcfsds()
{
	int n,h;
    vector<int>track(n);
    cout<<"Enter total tracks:";
    cin>>n;
    cout<<"Enter requested track position:"<<endl;
    for(int i=0; i<n; i++){
        cout<<"\t"<<i+1<<":";
        cin>>track[i];
    }
    cout<<"Enter initial head position:";
    cin>>h;
    int seek_time=0;
    vector<int>seek_sequence;
    for(int i=0; i<n; i++){
        seek_time+=abs(track[i]-h);
        h=track[i];
        seek_sequence.push_back(track[i]);
    }
    cout<<"Final output:"<<endl;
    cout<<"Total seek time = "<<seek_time<<endl;
    cout<<"Seek sequence is: ";
    for(int i=0; i<n; i++){
        cout<<seek_sequence[i]<<" ";
    }
}
void sstfds()
{
	int n,h;
    vector<int>track(n);
    cout<<"Enter total tracks:";
    cin>>n;
    cout<<"Enter requested track position:"<<endl;
    for(int i=0; i<n; i++){
        cout<<"\t"<<i+1<<":";
        cin>>track[i];
    }
    cout<<"Enter initial head position:";
    cin>>h;
    int seek_time=0;
    vector<int>seek_sequence;
    int remaining=n;
    while(remaining){
        int temp=INT_MAX;
        int j=-1;
        for(int i=0; i<n; i++){
            int x;
            x=abs(h-track[i]);
            if(track[i]>=0 && x<temp){
                temp=x;
                j=i;
            }
        }
        seek_sequence.push_back(track[j]);
        seek_time+=abs(h-track[j]);
        h=track[j];
        track[j]=-1;
        remaining--;
    }
    cout<<"Final output:"<<endl;
    cout<<"Total seek time = "<<seek_time<<endl;
    cout<<"Seek sequence is: ";
    for(int i=0; i<n; i++){
        cout<<seek_sequence[i]<<" ";
    }
}
void scands()
{
	int n,h;
    vector<int>track(n);
    cout<<"Enter total tracks:";
    cin>>n;
    cout<<"Enter requested track position:"<<endl;
    for(int i=0; i<n; i++){
        cout<<"\t"<<i+1<<":";
        cin>>track[i];
    }
    cout<<"Enter initial head position:";
    cin>>h;
    int direction,a,b;
    cout<<"Right=1, left=-1 :";
    cin>>direction;
    cout<<"Enter max and min:";
    cin>>a>>b;
    int seek_time=0;
    vector<int>seek_sequence;
    sort(track.begin(),track.end());
    if(direction>0){
        int x;
        for(int i=0; i<n; i++){
            if(h>=track[i]){
                x=i;
            }
        }
        for(int i=x+1; i<n; i++){
            seek_time+=track[i]-h;
            h=track[i];
            seek_sequence.push_back(track[i]);
        }
        if(h!=b){
            seek_time+=b-h;
            h=b;
            seek_sequence.push_back(b);
        }
        for(int i=0; i<=x; i++){
            seek_time+=h-track[i];
            h=track[i];
            seek_sequence.push_back(track[i]);
        }
    }
    else{
        int x;
        for(int i=0; i<n; i++){
            if(h>=track[i]){
                x=i;
            }
        }
        for(int i=x; i>=0; i--){
            seek_time+=h-track[i];
            h=track[i];
            seek_sequence.push_back(track[i]);
        }
        if(h!=a){
            seek_time+=h-a;
            h=a;
            seek_sequence.push_back(a);
        }
        for(int i=x+1; i<n; i++){
            seek_time+=track[i]-h;
            h=track[i];
            seek_sequence.push_back(track[i]);
        }
    }

    cout<<"Final output:"<<endl;
    cout<<"Total seek time = "<<seek_time<<endl;
    cout<<"Seek sequence is: ";
    for(int i=0; i<n; i++){
        cout<<seek_sequence[i]<<" ";
    }
}
void cscands()
{
	int n,h;
    cout<<"Enter total tracks:";
    cin>>n;
    vector<int>track(n);
    cout<<"Enter requested track position:"<<endl;
    for(int i=0; i<n; i++){
        cout<<"\t"<<i+1<<":";
        cin>>track[i];
    }
    cout<<"Enter initial head position:";
    cin>>h;
    int direction,a,b;
    cout<<"Right=1, left=-1 :";
    cin>>direction;
    cout<<"Enter min and max:";
    cin>>a>>b;
    int seek_time=0;
    vector<int>seek_sequence;
    sort(track.begin(),track.end());
    if(direction>0){
        int x;
        for(int i=0; i<n; i++){
            if(h>=track[i]){
                x=i;
            }
        }
        for(int i=x+1; i<n; i++){
            seek_time+=track[i]-h;
            h=track[i];
            seek_sequence.push_back(track[i]);
        }
        if(h<=b){
            seek_time+=b-h;
            seek_sequence.push_back(b);
            seek_time+=b-a;
            h=a;
            seek_sequence.push_back(a);
        }
        for(int i=0; i<=x; i++){
            seek_time+=track[i]-h;
            h=track[i];
            seek_sequence.push_back(track[i]);
        }
    }
    else{
        int x;
        for(int i=0; i<n; i++){
            if(h>=track[i]){
                x=i;
            }
        }
        for(int i=x; i>=0; i--){
            seek_time+=h-track[i];
            h=track[i];
            seek_sequence.push_back(track[i]);
        }
        if(h>=a){
            seek_time+=h-a;
            seek_sequence.push_back(a);
            seek_time+=b-a;
            h=b;
            seek_sequence.push_back(b);
        }
        for(int i=x+1; i<n; i++){
            seek_time+=h-track[i];
            h=track[i];
            seek_sequence.push_back(track[i]);
        }
    }

    cout<<"Final output:"<<endl;
    cout<<"Total seek time = "<<seek_time<<endl;
    cout<<"Seek sequence is: ";
    for(int i=0; i<n; i++){
        cout<<seek_sequence[i]<<" ";
    }
}
void lookds()//TO BE CHANGED.WRONGCODE
{
	int queue[20], head, q_size, i,j, seek=0, diff, max, temp, queue1[20], queue2[20], temp1=0, temp2=0;
  float avg;
  int HIGH;
  cout<<"Enter Number of Tracks"<<endl;
  cin>>HIGH;
  HIGH--;
  int LOW=0;

  printf("%s\t", "Input the number of disk locations");
  scanf("%d", &q_size);


  printf("%s\t", "Enter initial head position");
  scanf("%d", &head);

  printf("%s\n", "Enter disk positions to read");

  for(i=0; i<q_size; i++){
    scanf("%d", &temp);
    //queue1 - elems greater than head
    if(temp >= head){
        queue1[temp1] = temp;
        temp1++;
    } else {
        queue2[temp2] = temp;
        temp2++;
    }
  }

  //sort queue1 - increasing order
  for(i=0; i<temp1-1; i++){
   for(j=i+1; j<temp1; j++){
       if(queue1[i] > queue1[j]){
         temp = queue1[i];
         queue1[i] = queue1[j];
         queue1[j] = temp;
       }
    }
  }

  //sort queue2 - decreasing order
  for(i=0; i<temp2-1; i++){
    for(j=i+1; j<temp2; j++){
      if(queue2[i] < queue2[j]){
          temp = queue2[i];
          queue2[i] = queue2[j];
          queue2[j] = temp;
      }
    }
  }

  if(abs(head-LOW) >= abs(head-HIGH)){

      for(i=1,j=0; j<temp1; i++,j++){
          queue[i] = queue1[j];
      }

      for(i=temp1+1, j=0; j<temp2; i++, j++){
          queue[i] = queue2[j];
      }

  } else {

      for(i=1,j=0; j<temp2; i++,j++){
          queue[i] = queue2[j];
      }

      for(i=temp2+1, j=0; j<temp1; i++, j++){
          queue[i] = queue1[j];
      }

  }

  queue[0] = head;

  for(j=0; j<q_size; j++){
      diff=abs(queue[j+1] - queue[j]);
        seek += diff;
        printf("Disk head moves from %d to %d with seek %d\n",queue[j],queue[j+1],diff);

  }

  printf("Total seek time is %d\n", seek);
  avg = seek/(float)q_size;
  printf("Average seek time is %f\n", avg);

}
void clookds()//TO BE CHANGED WRONGCODE
{
	int queue[20], head, q_size, i,j, seek=0, diff, max, min, range, temp, queue1[20], queue2[20], temp1=0, temp2=0;
  float avg;
  int HIGH;
  cout<<"Enter Number of Tracks"<<endl;
  cin>>HIGH;
  HIGH--;
  int LOW=0;

  printf("%s\t", "Input the number of disk locations");
  scanf("%d", &q_size);

  printf("%s\t", "Enter initial head position");
  scanf("%d", &head);

  printf("%s\n", "Enter disk positions to read");

  for(i=0; i<q_size; i++){
    scanf("%d", &temp);
    //queue1 - elems greater than head
    if(temp >= head){
      queue1[temp1] = temp;
      temp1++;
    } else {
      queue2[temp2] = temp;
      temp2++;
    }
  }


  //sort queue1 - increasing order
  for(i=0; i<temp1-1; i++){
    for(j=i+1; j<temp1; j++){
      if(queue1[i] > queue1[j]){
        temp = queue1[i];
        queue1[i] = queue1[j];
        queue1[j] = temp;
      }
    }
  }

  //sort queue2
  for(i=0; i<temp2-1; i++){
    for(j=i+1; j<temp2; j++){
      if(queue2[i] > queue2[j]){
        temp = queue2[i];
        queue2[i] = queue2[j];
        queue2[j] = temp;
      }
    }
  }

  if(abs(head-LOW) <= abs(head-HIGH)){

    for(i=1,j=temp2-1; j>=0; i++,j--){
        queue[i] = queue2[j];
    }

    queue[i] = LOW;
    queue[i+1] = HIGH;

    for(i=temp2+3,j=temp1-1; j>=0; i++,j--){
        queue[i] = queue1[j];
    }

  } else {

    for(i=1,j=0; j<temp1; i++,j++){
        queue[i] = queue1[j];
    }

    queue[i] = HIGH;
    queue[i+1] = LOW;

    for(i=temp1+3,j=0; j<temp2; i++,j++){
        queue[i] = queue2[j];
    }


  }
  queue[0] = head;

  for(j=0; j<q_size; j++){
    diff=abs(queue[j+1] - queue[j]);
    seek += diff;
    printf("Disk head moves from %d to %d with seek %d\n",queue[j],queue[j+1],diff);

  }


  printf("Total seek time is %d\n", seek);
  avg = seek/(float)q_size;
  printf("Average seek time is %f\n", avg);
}
void bankersalgo()
{

    int resources;
    cout<<"Enter total number of resources:"<<endl;
    cin>>resources;
    vector<int> resource_instances(resources);
    for(int i=0; i<resources; i++){
        fflush(stdin);
        cout<<"Enter number of instances of resource "<<i+1<<":"<<endl;
        cin>>resource_instances[i];
    }
    int processes;
    cout<<"Enter total number of processes:"<<endl;
    cin>>processes;

    vector< vector<int> > allocated(processes, vector<int> (resources));
    for(int i=0; i<processes; i++){
        cout<<"Enter current allocation of resources for process "<<i+1<<":"<<endl;
        for(int j=0; j<resources; j++){
            fflush(stdin);
            cout<<"Resource "<<j+1<<":"<<endl;
            cin>>allocated[i][j];
        }
    }

    vector< vector<int> > max_need(processes, vector<int> (resources));
    for(int i=0; i<processes; i++){
        cout<<"Enter maximum need of resources for process "<<i+1<<":"<<endl;
        for(int j=0; j<resources; j++){
            fflush(stdin);
            cout<<"Resource "<<j+1<<":"<<endl;
            cin>>max_need[i][j];
        }
    }

    vector< vector<int> > remaining_need(processes, vector<int> (resources));
    for(int i=0; i<processes; i++){
        for(int j=0; j<resources; j++){
                remaining_need[i][j]=max_need[i][j]-allocated[i][j];
        }
    }

	//finding remaining resources left by first adding all used up resources then subtracting it by total resources
    vector<int> available(resources,0);
    for(int i=0; i<processes; i++){
        for(int j=0; j<resources; j++){
            available[j]+=allocated[i][j];
        }
    }
    for(int j=0; j<resources; j++){
        available[j]=resource_instances[j]-available[j];
    }

	//an array to keep track of completed processes
    vector<int> isComplete(processes,0);
    int complete=0;
    cout<<"Answer:"<<endl;

    while(complete<processes){
        for(int i=0; i<processes; i++){
            int t=0;
            if(isComplete[i] == 0){
                for(int j=0; j<resources; j++){
				//checking if available resources are greater than or eual to remaining resources
                    if(remaining_need[i][j] > available[j]){
                        t=1;
                        break;
                    }
                }
                if(t == 0){
                    complete++;
                    isComplete[i]=1;

                    if(complete == processes)
                            cout<<"P"<<i+1<<endl;
                    else
                        cout<<"P"<<i+1<<"->";

				//re-allocating resources 
                    for(int k=0; k<resources ; k++){
                        available[k]+=allocated[i][k];
                    }
                }
            }
        }
    }
}

void firstfit()
{
	int totalmemory;
	cout<<"Enter total memory available"<<endl;
	cin>>totalmemory;
	int processno=0;
	int choice;
	int size;
	int leftover=totalmemory;
	partitio p;
	vector<partitio>blocks;
	p.process=-1;
	p.size=totalmemory;
	blocks.push_back(p);
	int count=0;



	while(1)
	{
		cout<<"Enter 1 to add a new process Enter 2 to remove a process Enter 3 to exit"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				cout<<"Enter size of process "<<processno+1<<endl;
				cin>>size;
				int index=-1;
				processno++;
				if(leftover<size)
				{
					cout<<"Process "<<processno<<" of size "<<size<<" cant be allocated in memory due to less memory available"<<endl;
					break;
				}
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks.size()==1)
					{
						index=0;
						break;
					}
					else if(blocks[i].size>=size&&blocks[i].process==-1)
					{
						index=i;
						break;
					}

				}
				if(index==-1)
				{
					cout<<"Process "<<processno<<" of size "<<size<<" cant be allocated in memory due to external Fragmentation"<<endl;
					break;
				}
				p.process=processno;
				p.size=size;
				leftover-=size;
				blocks[index].size-=size;
				blocks.push_back(p);
				for(int i=blocks.size()-1;i>index;i--)
				{

					swap(blocks[i-1],blocks[i]);
				}
				cout<<"Process "<<processno<<" of size "<<size<<" has been allocated in memory"<<endl;

				count++;

				/*for(int i=0;i<(int)blocks.size();i++)
				{
					cout<<blocks[i].size<<" "<<blocks[i].process<<endl;
				}*/
				cout<<endl;
				break;

			}
			case 2:
			{
				cout<<"Enter process number to be removed"<<endl;
				int pno,index;
				cin>>pno;
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks[i].process==pno)
					{
						index=i;
						break;

					}

				}
				blocks[index].process=-1;
				leftover+=blocks[index].size;
				cout<<"Process "<<pno<<" Has been removed successfully"<<endl;
				for(int i=0;i<(int)blocks.size();i++)
				{
					for(int j=i+1;j<(int)blocks.size();j++)
					{
						if(blocks[i].process==-1&&blocks[j].process==-1)
						{
							blocks[i].size+=blocks[j].size;
							blocks[j].size=0;
						}
						else
						{
							break;
						}

					}

				}
				/*for(int i=0;i<(int)blocks.size();i++)
				{
					cout<<blocks[i].size<<" "<<blocks[i].process<<endl;
				}
				cout<<endl;*/
				break;


			}
			case 3:
			{
				cout<<"Left Over Memory:"<<leftover<<endl;
				cout<<"No of processes executed "<<count<<endl;
				int partno=1;
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks[i].size!=0)
					{
						if(blocks[i].process==-1)
						{
							cout<<"Partition "<<partno<<" of size "<<blocks[i].size<<" Is empty"<<endl;
						}
						else
						{
							cout<<"Partition "<<partno<<" of size "<<blocks[i].size<<" Has the process "<<blocks[i].process<<endl;
						}
						partno++;
					}
				}
				cout<<endl;
				return ;
			}


		}
	}
}
void bestfit()
{
	int totalmemory;
	cout<<"Enter total memory available"<<endl;
	cin>>totalmemory;
	int processno=0;
	int choice;
	int size;
	int leftover=totalmemory;
	partitio p;
	vector<partitio>blocks;
	p.process=-1;
	p.size=totalmemory;
	blocks.push_back(p);
	int count=0;



	while(1)
	{
		cout<<"Enter 1 to add a new process Enter 2 to remove a process Enter 3 to exit"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				cout<<"Enter size of process "<<processno+1<<endl;
				cin>>size;
				int index=-1;
				processno++;
				int minsize=INT_MAX;
				if(leftover<size)
				{
					cout<<"Process "<<processno<<" of size "<<size<<" cant be allocated in memory due to less memory available"<<endl;
					break;
				}
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks.size()==1)
					{
						index=0;
						minsize=blocks[i].size;
					}
					else if(blocks[i].size>=size&&blocks[i].size<minsize&&blocks[i].process==-1)
					{
						index=i;
						minsize=blocks[i].size;
					}

				}
				if(index==-1)
				{
					cout<<"Process "<<processno<<" of size "<<size<<" cant be allocated in memory due to external Fragmentation"<<endl;
					break;
				}
				p.process=processno;
				p.size=size;
				leftover-=size;
				blocks[index].size-=size;
				blocks.push_back(p);
				for(int i=blocks.size()-1;i>index;i--)
				{

					swap(blocks[i-1],blocks[i]);
				}
				cout<<"Process "<<processno<<" of size "<<size<<" has been allocated in memory"<<endl;

				count++;

				/*for(int i=0;i<(int)blocks.size();i++)
				{
					cout<<blocks[i].size<<" "<<blocks[i].process<<endl;
				}
				cout<<endl;*/
				break;

			}
			case 2:
			{
				cout<<"Enter process number to be removed"<<endl;
				int pno,index;
				cin>>pno;
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks[i].process==pno)
					{
						index=i;
						break;

					}

				}
				blocks[index].process=-1;
				leftover+=blocks[index].size;
				cout<<"Process "<<pno<<" Has been removed successfully"<<endl;
				for(int i=0;i<(int)blocks.size();i++)
				{
					for(int j=i+1;j<(int)blocks.size();j++)
					{
						if(blocks[i].process==-1&&blocks[j].process==-1)
						{
							blocks[i].size+=blocks[j].size;
							blocks[j].size=0;
						}
						else
						{
							break;
						}

					}

				}
				/*for(int i=0;i<(int)blocks.size();i++)
				{
					cout<<blocks[i].size<<" "<<blocks[i].process<<endl;
				}
				cout<<endl;*/
				break;


			}
			case 3:
			{
				cout<<"Left Over Memory:"<<leftover<<endl;
				cout<<"No of processes executed "<<count<<endl;
				int partno=1;
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks[i].size!=0)
					{
						if(blocks[i].process==-1)
						{
							cout<<"Partition "<<partno<<" of size "<<blocks[i].size<<" Is empty"<<endl;
						}
						else
						{
							cout<<"Partition "<<partno<<" of size "<<blocks[i].size<<" Has the process "<<blocks[i].process<<endl;
						}
						partno++;
					}
				}
				return ;
			}


		}
	}
}
void worstfit()
{
	int totalmemory;
	cout<<"Enter total memory available"<<endl;
	cin>>totalmemory;
	int processno=0;
	int choice;
	int size;
	int leftover=totalmemory;
	partitio p;
	vector<partitio>blocks;
	p.process=-1;
	p.size=totalmemory;
	blocks.push_back(p);
	int count=0;



	while(1)
	{
		cout<<"Enter 1 to add a new process Enter 2 to remove a process Enter 3 to exit"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				cout<<"Enter size of process "<<processno+1<<endl;
				cin>>size;
				int index=-1;
				processno++;
				int maxsize=INT_MIN;
				if(leftover<size)
				{
					
					cout<<"Process "<<processno<<" of size "<<size<<" cant be allocated in memory due to less memory available"<<endl;
					break;
				}
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks.size()==1)
					{
						index=0;
						maxsize=blocks[i].size;
					}
					else if(blocks[i].size>=size&&blocks[i].size>maxsize&&blocks[i].process==-1)
					{
						index=i;
						maxsize=blocks[i].size;
					}

				}
				if(index==-1)
				{
					cout<<"Process "<<processno<<" of size "<<size<<" cant be allocated in memory due to external Fragmentation"<<endl;
					break;
				}
				p.process=processno;
				p.size=size;
				leftover-=size;
				blocks[index].size-=size;
				blocks.push_back(p);
				for(int i=blocks.size()-1;i>index;i--)
				{

					swap(blocks[i-1],blocks[i]);
				}
				cout<<"Process "<<processno<<" of size "<<size<<" has been allocated in memory"<<endl;
				count++;


				break;

			}
			case 2:
			{
				cout<<"Enter process number to be removed"<<endl;
				int pno,index;
				cin>>pno;
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks[i].process==pno)
					{
						index=i;
						break;

					}

				}
				blocks[index].process=-1;
				leftover+=blocks[index].size;
				cout<<"Process "<<pno<<" Has been removed successfully"<<endl;
				for(int i=0;i<(int)blocks.size();i++)
				{
					for(int j=i+1;j<(int)blocks.size();j++)
					{
						if(blocks[i].process==-1&&blocks[j].process==-1)
						{
							blocks[i].size+=blocks[j].size;
							blocks[j].size=0;
						}
						else
						{
							break;
						}

					}

				}
				/*for(int i=0;i<(int)blocks.size();i++)
				{
					cout<<blocks[i].size<<" "<<blocks[i].process<<endl;
				}
				cout<<endl;*/
				break;


			}
			case 3:
			{
				cout<<"Left Over Memory:"<<leftover<<endl;
				cout<<"No of processes executed"<<count<<endl;
				int partno=1;
				for(int i=0;i<(int)blocks.size();i++)
				{
					if(blocks[i].size!=0)
					{
						if(blocks[i].process==-1)
						{ 
							cout<<"Partition "<<partno<<" of size "<<blocks[i].size<<" Is empty"<<endl;
						}
						else
						{
							cout<<"Partition "<<partno<<" of size "<<blocks[i].size<<" Has the process "<<blocks[i].process<<endl;
						}
						partno++;
					}
				}
				return ;
			}


		}
	}
}
struct frame
{
	int pageno;
	int time;
};
void vmpaging()
{
	int virtualmemsize,physicalmemsize,pagesize;
	cout<<"Enter size of Virtual Memory in KB"<<endl;
	cin>>virtualmemsize;
	cout<<"Enter size of physical memory in KB"<<endl;
	cin>>physicalmemsize;
	cout<<"Enter Page Size in KB"<<endl;
	cin>>pagesize;
	cout<<"No of Pages in Virtual Memory="<<virtualmemsize/pagesize<<endl;
	cout<<"No of pages in Physical memory="<<physicalmemsize/pagesize<<endl;
	int choice;
	int frames=physicalmemsize/pagesize;
	vector<frame> mem(frames);
	struct frame f;
	int pagefault=0;
	int empty=frames;
	for(int i=0;i<frames;i++)
	{
		mem[i].pageno=-1;
		mem[i].time=INT_MAX;
	}
	vector<int>pagetable(virtualmemsize/pagesize,-1);
	int t=0;
	int total=0;
	while(1)
	{
		cout<<"1->Enter  Virtual Memory Address 2->Stop "<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				cout<<"Enter Virtual Address in the format: PAGENO | OFFSET"<<endl;
				int pageno,offset;
				cin>>pageno>>offset;
				int flag=0;
				if(offset>=512*pagesize||pageno>=virtualmemsize/pagesize)
				{
					if(pageno<virtualmemsize/pagesize)
					{
						total++;
					}
					cout<<"Incorrect Input"<<endl;
					break;
				}
				total++;
				for(int j=0;j<frames;j++)
				{
					if(mem[j].pageno==pageno)
					{
						flag=1;
						cout<<"Page "<<pageno<<" already in memory"<<endl;
						cout<<"Physical Address for the above virtual address is"<<endl;
						cout<<j<<"|"<<offset<<endl;
						break;

					}


				}
				if(flag==1)
				{
					continue;
				}
				else
				{
					cout<<"Page Fault has Occured as Page "<<pageno<<" isnt in memory"<<endl;
					pagefault++;
					struct frame f;
					f.pageno=pageno;
					f.time=t;
					t++;
					if(empty>0)
					{
						mem[frames-empty].pageno=pageno;
						mem[frames-empty].time=t;
						cout<<"Page "<<pageno<<"accomodated in  frame "<<frames-empty<<endl;
						pagetable[pageno]=frames-empty;

					}
					else
					{
						int index=-1;
						int min_time=INT_MAX;
						for(int j=0;j<frames;j++)
						{
							if(mem[j].time<min_time)
							{
								index=j;
								min_time=mem[j].time;
							}

						}
						cout<<"Page "<<mem[index].pageno<<" has been selected for replacement"<<endl;
						cout<<"Page "<<pageno<<" accomodated in  frame "<<index<<endl;
						pagetable[mem[index].pageno]=-1;
						mem[index].pageno=pageno;
						mem[index].time=t;
						pagetable[pageno]=index;

					}
					empty--;

				}
				break;



			}
			case 2: 
			{
				cout<<"No of Page Faults= "<<pagefault;
				cout<<"Page Fault Ratio= "<<(double)pagefault/total<<endl;
				cout<<"Final Page Table"<<endl;

				for(int i=0;i<(int)pagetable.size();i++)
				{
					cout<<"Pageno "<<i<<" Frame "<<pagetable[i]<<endl;
				}
				cout<<"Final Physical Memory"<<endl;
				for(int i=0;i<frames;i++)
				{
					cout<<"Frame "<<i<<" PageNo "<<mem[i].pageno<<endl;
				}
				cout<<endl;
				return ;



			}
		}
	}
}
void fifopr()
{
	int noOfFrames,noOfPages=0;
    cout<<"Enter number of frames:";
    cin>>noOfFrames;
    vector<int>pages;
    deque<int>q;
    int pageFaults=0;
    while(true){
        int c;
        cout<<"1.add page 2.Stop adding\nEnter your choice:";
        cin>>c;
        switch(c){
            case 1: {
                int t;
                cout<<"Enter referenced page numbers:";
                cin>>t;
                pages.push_back(t);
                int i=pages.size()-1;
                if(find(q.begin(), q.end(), pages[i]) != q.end()){
                    cout<<i<<": "<<pages[i]<<" was already in a frame."<<endl;
                }
                else if(q.size()<noOfFrames){
                    pageFaults++;
                    cout<<i<<": PAGE FAULT: "<<pages[i]<<" is now allocated in a frame."<<endl;
                    q.push_back(pages[i]);
                }
                else{
                    pageFaults++;
                    cout<<i<<": "<<"PAGE FAULT: "<<pages[i]<<" is allocated in a frame by replacing Page "<<q.front()<<endl;
                    q.pop_front();
                    q.push_back(pages[i]);
                }

                cout<<endl;
                noOfPages++;
                break;
            }
            default: {
                cout<<"Total no. of times page fault occurred:"<<pageFaults<<endl;
                cout<<"Page ratio:"<<(double)pageFaults/noOfPages<<endl;
                return ;
            }
        }
    }
}
int s=1;//Defining Semaphore Variable
int empty=6;//Defining Empty Variable
int full=0;//Defining Full Variable
int t=0;//Defining Time Variable
//Structure for Process
struct Rowpnc
{
    bool producer;
    int AT;
    int BT;
    int serial;
    bool completed;
};
struct output
{
  string message;
  int t;
};
bool comp4(const output &a,const output &b)
{
    return a.t<b.t;
}
vector<output>ans;
//Comparision Function for Ordering Processes
bool comp3(const Rowpnc &a,const Rowpnc &b)
{
    if(a.producer==false&&b.producer==true&&a.AT==b.AT)//Checking if one of the two is producer
    {
        return b.AT<a.AT;//Producer Given more priority before consumer

    }

    return a.AT<b.AT;//If they are of same type,the one that arrives first gets more priority
}
//Signal Function
int signal(int s)
{
    s++;
    return s;
}
//Wait Function
int wait(int s)
{
    while(s<=0);

    s--;
    return s;
}
//Producer Function
void producer(int bt,int serial)//Argument:Burst Time of the Process
{
    s=wait(s);
    full=signal(full);
    empty=wait(empty);
    output o;
    t+=bt;//Incrementing t to t+bt
    o.message="Producer "+to_string(serial)+" Producing Finished at t=";
    o.t=t;
    ans.push_back(o);

    s=signal(s);
}
void consumer(int bt,int serial)//Argument:Burst Time of Porcess
{
    s=wait(s);
    full=wait(full);
    empty=signal(empty);
    t+=bt;
    output o;
    o.message="Consumer "+to_string(serial)+" Consuming Finished at t=";
    o.t=t;
    ans.push_back(o);
    s=signal(s);
}

void pnc()
{
    int prod=0,consum=0;
    cout<<"Enter Number of Producers"<<endl;
    cin>>prod;
    cout<<"Enter Number of Consumers"<<endl;
    cin>>consum;
    vector<Rowpnc>Arr(prod+consum);
    queue<Rowpnc>producerqueue;
    queue<Rowpnc>consumerqueue;
    output o;
    //Taking Input//
    for(int i=0;i<prod;i++)
    {
        cout<<"Enter Arrival Time and Burst Time of Producer "<<i+1<<endl;
        Arr[i].producer=true;
        Arr[i].serial=i+1;
        Arr[i].completed=false;
        cin>>Arr[i].AT>>Arr[i].BT;
    }

    for(int i=0;i<consum;i++)
    {
        cout<<"Enter Arrival Time and Burst Time of Consumer "<<i+1<<endl;
        Arr[prod+i].producer=false;
        Arr[prod+i].serial=i+1;
        Arr[prod+i].completed=false;
        cin>>Arr[prod+i].AT>>Arr[prod+i].BT;
    }
    //Sorting Processes As per FCFS//
    sort(Arr.begin(),Arr.end(),comp3);
    int n=prod+consum;
    int leftover=n;
    for(int i=0;i<n;i++)
    {
        if(Arr[i].producer==true)
        {
            if(s==1&&empty!=0)//Checking if Buffer is Full//
            {
                producerqueue.push(Arr[i]);
                Rowpnc f=producerqueue.front();//Making producer in front of Readers Queue to produce//
                t=max(t,f.AT);
                o.message="Producer "+to_string(f.serial)+" starts production at t=";
                o.t=t;
                ans.push_back(o);
                for(int j=0;j<n;j++)
                {
                    if(Arr[j].serial==f.serial&&Arr[j].producer==Arr[j].producer)
                    {
                        Arr[j].completed=true;
                        break;
                    }
                }
                //Producers &Consumers Who need to wait//
                for(int j=i;j<n;j++)
                {
                    if(Arr[j].AT<=f.AT&&Arr[j].completed==false)
                    {
                        if(Arr[j].producer==true)
                        {
                            o.message="Producer "+to_string(Arr[j].serial)+" needs to wait at t=  ";
                            o.t=Arr[j].AT;
                            ans.push_back(o);

                        }
                        else
                        {

                            o.message="Consumer "+to_string(Arr[j].serial)+" needs to wait at t=  ";
                            o.t=Arr[j].AT;
                            ans.push_back(o);
                        }
                    }

                }

                producer(f.BT,f.serial);

                producerqueue.pop();
                leftover--;
            }
            else
            {
                o.message="Buffer is Full.Producer "+to_string(Arr[i].serial)+" Needs to wait At t= ";
                o.t=t;
                ans.push_back(o);
                producerqueue.push(Arr[i]);//Pushing producer to queue//
            }

        }
        else
        {
            if(s==1&&full!=0)//Checking if Buffer is empty//
            {
                consumerqueue.push(Arr[i]);
                Rowpnc f=consumerqueue.front();//Getting Consumer in the front of the queue//
                 t=max(t,f.AT);
                o.message="Consumer "+to_string(f.serial)+" starts production at t=";
                o.t=t;
                ans.push_back(o);
                for(int j=i+1;j<n;j++)
                {
                    if(Arr[j].AT<=f.AT&&Arr[j].completed==false)
                    {
                        if(Arr[j].producer==true)
                        {
                            o.message="Producer "+to_string(Arr[j].serial)+" needs to wait at t=  ";
                            o.t=Arr[j].AT;
                            ans.push_back(o);
                        }
                        else
                        {
                            o.message="Consumer "+to_string(Arr[j].serial)+" needs to wait at t=  ";
                            o.t=Arr[j].AT;
                            ans.push_back(o);
                        }
                    }

                }
                consumer(f.BT,f.serial);
                for(int j=0;j<n;j++)
                {
                    if(Arr[j].serial==f.serial&&Arr[j].producer==Arr[j].producer)
                    {
                        Arr[j].completed=true;
                        break;
                    }
                }
                consumerqueue.pop();
                leftover--;
            }
            else
            {
                o.message="Buffer is Empty.Consumer "+to_string(Arr[i].serial)+" Needs to wait at t= ";
                o.t=t;
                ans.push_back(o);
                consumerqueue.push(Arr[i]);
            }

        }
        t=0;
    }
    vector<Rowpnc>left;
    while(producerqueue.size()!=0)//Pushing remainig producers to new array//
    {
        cout<<producerqueue.front().serial<<endl;
        left.push_back(producerqueue.front());
        producerqueue.pop();
    }
    while(consumerqueue.size()!=0)//Pushing remaining consumers to neew array//
    {
        left.push_back(consumerqueue.front());
        consumerqueue.pop();
    }
    sort(left.begin(),left.end(),comp3);//Sorting new array as per FCFS//
    n=left.size();

    for(int i=0;i<n;i++)
    {
        if(left[i].producer==true)
        {
            if(s==1&&empty!=0)
            {
                producerqueue.push(left[i]);
                Rowpnc f=producerqueue.front();
                 t=max(t,f.AT);
                o.message="Producer "+to_string(f.serial)+" starts production at t=";
                o.t=t;
                ans.push_back(o);
                for(int j=i+1;j<n;j++)
                {
                    if(left[j].AT<=f.AT&&left[j].completed==false)
                    {
                        if(left[j].producer==true)
                        {
                            o.message="Producer "+to_string(left[j].serial)+" needs to wait at t=";
                            o.t=left[j].AT;
                            ans.push_back(o);
                        }
                        else
                        {
                            o.message="Consumer "+to_string(left[j].serial)+" needs to wait at t=";
                            o.t=left[j].AT;
                            ans.push_back(o);
                        }
                    }

                }
                producer(f.BT,f.serial);
                for(int j=0;j<n;j++)
                {
                    if(left[j].serial==f.serial&&left[j].producer==f.producer)
                    {
                        left[j].completed=true;
                        break;
                    }
                }
                producerqueue.pop();
                leftover--;
            }
            else
            {
                o.message="Buffer is Full.Producer "+to_string(left[i].serial)+" Needs to wait for Consumer at t";
                o.t=t;
                ans.push_back(o);
                producerqueue.push(left[i]);
            }

        }
        else
        {
            if(s==1&&full!=0)
            {
                consumerqueue.push(left[i]);
                Rowpnc f=consumerqueue.front();
                 t=max(t,f.AT);
                o.message="Consumer "+to_string(f.serial)+" starts consuming at t=";
                o.t=t;
                ans.push_back(o);
                for(int j=i+1;j<n;j++)
                {
                    if(left[j].AT<=f.AT&&left[j].completed==false)
                    {
                        if(left[j].producer==true)
                        {
                            o.message="Producer "+to_string(left[j].serial)+" needs to wait at t=";
                            o.t=left[j].AT;
                            ans.push_back(o);
                        }
                        else
                        {
                            o.message="Consumer "+to_string(left[j].serial)+" needs to wait at t=";
                            o.t=left[j].AT;
                            ans.push_back(o);
                        }
                    }

                }
                consumer(f.BT,f.serial);
                for(int j=0;j<n;j++)
                {
                    if(left[j].serial==f.serial&&left[j].producer==f.producer)
                    {
                        left[j].completed=true;
                        break;
                    }
                }
                consumerqueue.pop();
                leftover--;
            }
            else
            {
                o.message="Buffer is Empty.Consumer "+to_string(left[i].serial)+" Needs to wait for Producer at t=";
                o.t=t;
                ans.push_back(o);
                consumerqueue.push(left[i]);
            }

        }
    }
    sort(ans.begin(),ans.end(),comp4);
    for(int i=0;i<(int)ans.size();i++)
    {
        cout<<ans[i].message<<ans[i].t<<endl;
    }

}
int readcount=0;//No of readers//
int writecount=0;//No of writers//
struct Rowrw
{
    int AT;
    int BT;
    bool reader;
    int serial;
    int endtime;
};
//comparision fnc for scheduling.Writer has more priority//
bool comp5(const Rowrw &a,const Rowrw &b)
{
    if(a.reader==true&&b.reader==false&&a.AT==b.AT)
    {
        return 2<1;
    }

    return a.AT<b.AT;
}
bool comp6(const output &a,const output &b)
{


    return a.t<b.t;
}
void rnw()
{
    vector<output>print;
    int read=0,write=0;
    cout<<"Enter Number of Readers"<<endl;
    cin>>read;
    cout<<"Enter Number of Writers"<<endl;
    cin>>write;
    vector<Rowrw>Arr(read+write);
    //Input//
    for(int i=0;i<read;i++)
    {
        cout<<"Enter Arrival Time and Burst Time of Reader "<<i+1<<endl;
        Arr[i].reader=true;
        Arr[i].serial=i+1;

        cin>>Arr[i].AT>>Arr[i].BT;
        Arr[i].endtime=Arr[i].BT+Arr[i].AT;
    }

    for(int i=0;i<write;i++)
    {
        cout<<"Enter Arrival Time and Burst Time of Writer "<<i+1<<endl;
        Arr[read+i].reader=false;
        Arr[read+i].serial=i+1;
        cin>>Arr[read+i].AT>>Arr[read+i].BT;
        Arr[read+i].endtime=Arr[read+i].BT+Arr[read+i].AT;
    }
    queue<Rowrw>readers;//Queue of Readers//
    queue<Rowrw>writers;//Queue of writers//
    sort(Arr.begin(),Arr.end(),comp5);
    int n=read+write;
    for(int i=0;i<n;i++)
    {
        if(Arr[i].reader==true)
        {
            readers.push(Arr[i]);
        }
        else
        {
            writers.push(Arr[i]);
        }
    }
    queue<Rowrw>ongoing;
    output o;
    while(readers.size()!=0||writers.size()!=0)
    {

        Rowrw f;
        //Printing processes who are finished at time t//
        while(ongoing.size()!=0&&ongoing.front().endtime<=t)
        {
            f=ongoing.front();
            if(f.reader==true)
            {
                o.message="Reader "+to_string(f.serial)+" Finished reading at t= ";
                o.t=f.endtime;
                print.push_back(o);
                readcount--;
            }
            else
            {
                o.message="Writer "+to_string(f.serial)+" Finished Writing at t= ";
                o.t=f.endtime;
                print.push_back(o);
                writecount--;
            }
            ongoing.pop();
        }
        Rowrw turn;
        if(readcount==0&&writecount==0)//Checking if Reader and write count is//
        {

            if(writers.size()!=0&&writers.front().AT<=t)
            {
                if(readers.size()!=0&&readers.front().AT<writers.front().AT)//If reaader arrived before writer//
                {
                    goto readsec;
                }

                turn=writers.front();
                writecount++;
                turn.endtime=t+turn.BT;
                //Writer Begins Writing//
                o.message="Writer "+to_string(turn.serial)+" Started Writing at t= ";
                o.t=t;
                print.push_back(o);
                ongoing.push(turn);
                writers.pop();

            }
            else if(readers.size()!=0&&readers.front().AT<=t)//Checking if a reader can read//
            {

                while(readers.size()!=0&&readers.front().AT<=t)//Making readers read //
                {
                    readsec:
                    turn=readers.front();
                    o.message="Reader "+to_string(turn.serial)+" Started Reading at t= ";
                    o.t=t;
                    print.push_back(o);
                    turn.endtime=t+turn.BT;
                    readcount++;
                    ongoing.push(turn);
                    readers.pop();
                }

            }

        }
        else if(writecount==0)//Checking if a reader can read//
        {
            if(readers.size()!=0&&readers.front().AT<=t)
            {
                while(readers.size()!=0&&readers.front().AT<=t)
                {

                    turn=readers.front();
                    o.message="Reader "+to_string(turn.serial)+" Started Reader at t= ";
                    o.t=t;
                    print.push_back(o);
                    turn.endtime=t+turn.BT;
                    readcount++;
                    ongoing.push(turn);
                    readers.pop();
                }

            }


        }

        queue<Rowrw>temp=readers;
        //Printng waiting list//
        while(temp.size()!=0)
        {
            if(temp.front().AT==t)
            {
                    o.message="Reader "+to_string(temp.front().serial)+" Waiting at t= ";
                    o.t=t;
                    print.push_back(o);

            }
            temp.pop();
        }
        temp=writers;
        while(temp.size()!=0)
        {
            if(temp.front().AT==t)
            {
                    o.message="Writer "+to_string(temp.front().serial)+" Waiting at t= ";
                    o.t=t;
                    print.push_back(o);

            }
            temp.pop();



        }
        t++;



    }
    Rowrw f;
    //Dequeuing Ongoing processes and finishing them //
    while(ongoing.size()!=0)
    {
            f=ongoing.front();
            if(f.reader==true)
            {
                o.message="Reader "+to_string(f.serial)+" Finished reading at t= ";
                o.t=f.endtime;
                print.push_back(o);
                readcount--;
            }
            else
            {
                o.message="Writer "+to_string(f.serial)+" Finished writing at t= ";
                o.t=f.endtime;
                print.push_back(o);
                writecount--;
            }
            ongoing.pop();
            t++;
    }
    //Sorting all outputs as per the time they are associated with//
    sort(print.begin(),print.end(),comp6);
    for(int i=0;i<(int)print.size();i++)
    {
        cout<<print[i].message<<print[i].t<<endl;
    }
    t=0;
}
int timedp= 0;
struct user
{
    int id; //avoid deadlock
    int arvl;
    int arvl_i; // used during waiting
    int bust;
    int bust_i; // remaining bust time
    int left_hand;
    int right_hand; //right hand first
    struct user *left;
    struct user *right;
    int comp;
};

void dp()
{
    int i = 0;
    int users;
    printf("no.of people");
    scanf("%d", &users);
    struct user phil[users];
    for (i = 0; i < users; i++) //input of all processes
    {
        phil[i].id = i + 1;
        phil[i].left_hand = phil[i].right_hand = 0;
        printf("enter the avrl and bust time of philosopher %d", phil[i].id);
        scanf("%d", &phil[i].arvl);
        scanf("%d", &phil[i].bust);
        phil[i].arvl_i = phil[i].arvl;
        phil[i].bust_i = phil[i].bust;
        phil[i].comp = -1;
        if (i == users - 1)
        {
            phil[i].right = &phil[0];
            phil[0].left = &phil[i];
        }
        else
        {
            phil[i].right = &phil[i + 1];
            phil[i + 1].left = &phil[i];
        }
    }
    int left = users;
    int p = 1;
    while (left) // runs until all the processes are completed
    {
        for (i = 0; i < users; i++)
        {
            if (phil[i].comp >= 0)
                continue;
            if (phil[i].comp == -1 && phil[i].arvl_i <= timedp)
            {
                if (phil[i].right->left_hand == 0 && phil[i].right_hand == 0)
                {
                    phil[i].right_hand = 1;
                    printf("philosopher %d has taken the right stick and checking for left stick if available \n", phil[i].id);
                }
            }
        }
        int dead = users;
        for (i = 0; i < users; i++)
        {
            if (phil[i].right_hand)
                dead--;
        }
        if (dead == 0)
        {
            printf("\ndeadend ......solving!!!! by giving  %d th stick to the philosopher 1\n", users);

            phil[0].left_hand = 1;
            phil[0].left->right_hand = 0;
            phil[0].left->comp = -1;
            phil[0].comp = 0;
        }

        for (i = 0; i < users; i++)
        {
            if (phil[i].comp >= 0 || phil[i].right_hand == 0)
                continue; //phil[i].comp==-1 && phil[i].arvl_i<=time &&

            if (phil[i].right_hand)
            {
                if (phil[i].left->right_hand == 0 && phil[i].left_hand == 0)
                {
                    phil[i].left_hand = 1;
                    phil[i].comp = 0;
                    printf("philosopher %d has picked up the left stick and right stick and ready to dine\n", phil[i].id);
                }
                else
                {
                    if (p)
                        printf("philosopher %d is waiting for the left stick till the left  philosopher to complete his/her turn\n", phil[i].id);
                }
            }
        }
        p = 0;
        for (i = 0; i < users; i++)
        {
            if (phil[i].comp < 0)
                continue;
            if (phil[i].comp == 0)
            {

                phil[i].bust_i--;
                if (phil[i].bust_i == 0)
                {
                    printf("philosopher %d has finished his job and sticks are placed back\n", phil[i].id);
                    p = 1;
                    left--;
                    phil[i].right_hand = 0;
                    phil[i].left_hand = 0;
                    phil[i].comp = timedp + 1;
                    //printf
                }
            }
            else if (phil[i].comp == 0)
            {
                phil[i].arvl_i++;
            }
        }
        timedp++;
    }
    int dead = 1;
    for (i = 0; i < users; i++)
    {
        if (phil[i].comp > 0)
            dead = 0;
        printf(" philosopher id: %d -> arrival %d bust time %d completed at  %d  \n", phil[i].id, phil[i].arvl, phil[i].bust, phil[i].comp);
    }
    if (dead)
    {
        printf("-1 in comp indicates deadend");
    }
    
}
/*Pending and Questions
  1)Change LOOK and CLOOK 
  2)Edit Print Stataments of Dining Philosophers
  3)Should we add MFT too
  4)Add Next Fit
  5)Add LRU ,Optimal and MRU
  6)Test HRRN*/
int main()
{
	
	int choice;
	int algo;
	while(1)
	{
		 
		 cout<<"---OS SIMULATOR---"<<endl;
	    cout<<"Choose one of the options"<<endl;
	    cout<<"1.Job Scheduling\n2.Disk Scheduling\n3.Bankers Algorithm\n4.Methods of Contiguous Memory Allocation(Types of Fits)\n5.Page Replacement Algorithms\n6.Virtual Memory Paging Mechanism\n7.Process Synchronization Problems\n"<<endl;
		cout<<"Enter Choice"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1://Job Scheduling
			{
				system("cls");
				cout<<"---JOB SCHEDULING ALGORITHMS---";
				cout<<"Choose a Job Scheduling Algorithm"<<endl;
				cout<<"1.First Come First Serve \n2.Round Robin\n3.Shortest Job First\n4.Longest Job First \n5. Shortest Remaining Time First\n 6.Longest Remaining time first\n7.HRRN Premptive\n"<<endl;
				
				cin>>algo;
				switch(algo)
				{
					case 1:
					{
						
						fcfsjob();

						break;
					}
					case 2:
					{
						
						rrjob();
						break;
					}
					case 3:
					{
						
						sjfjob();
						break;
					}
					case 4:
					{
						
						ljfjob();
						break;
					}
					case 5:
					{
						
						srtfjob();
						break;
					}
					case 6:
					{
						
						lrtfjob();
						break;
					}
					case 7:
					{
						
						hrrnjob();
						break;
					}
					case 8:
					{
						system("cls");
						cout<<"Wrong Input"<<endl;
						break;
					}
				}
				break;
			}
			case 2://Disk Scheduling
			{ 
				system("cls");
				cout<<"---Disk Scheduling Algorithms---"<<endl;
				cout<<"Choose a Disk Scheduling Algorithm"<<endl;
				cout<<"1.FCFS Disk Scheduling\n2.SSTF Disk Scheduling\n3.SCAN Disk Scheduling\n4.CSCAN Disk Scheduling\n5.LOOK Disk Scheduling\n6.CLOOK CLOOK Disk Scheduling\n";
				cin>>algo;
				switch(algo)
				{
					case 1:
					{
						fcfsds();
						break;
					}
					case 2:
					{
						sstfds();
						break;
					}
					case 3:
					{
						scands();
						break;
					}
					case 4:
					{
						cscands();
						break;
					}
					case 5:
					{
						lookds();
						break;
					}
					case 6:
					{
						clookds();
						break;

					}
					default:
					{
						system("cls");
						cout<<"Wrong Input"<<endl;
						break;
					}

				}
				break;

			}
			case 3://Bankers Algorithm
			{
				system("cls");
				cout<<"---Bankers Algorithm"<<endl;
				bankersalgo();
				break;

			}
			case 4://Types of Fit
			{
				system("cls");
				cout<<"---Methods of Contiguous Memory Allocation(Types of Fits)---"<<endl;
				cout<<"1.First Fit\n2.Best Fit\n3.Worst Fit\n4.Next Fit"<<endl;
				cin>>algo;
				switch(algo)
				{
					case 1:
					{
						firstfit();
						break;
					}
					case 2:
					{
						bestfit();
						break;
					}
					case 3:
					{
						worstfit();
						break;
					}
					case 4:
					{
						//nextfit();
						break;

					}
					default:
					{
						break;
					}

				}

			}
			case 6://VM PagingTechnique
			{
				system("cls");
				cout<<"Virtual Memory Paging Mechanism"<<endl;
				vmpaging();
				break;

			}
			case 5://Page Replacement Algorithm
			{
				system("cls");
				cout<<"Page Replacement Algorithm"<<endl;
				cout<<"Choose an Algorithm"<<endl;
				cout<<"1.FIFO Page Replacement\n2.LRU Page Replacement\n3.MRU Page Replacement\n4.Optimal Page Replacement\n";
				cin>>algo;
				switch(algo)
				{
					case 1:
					{
						fifopr();
						break;
					}
					case 2:
					{
						//lrupr();
						break;
					}
					case 3:
					{
						//mrupr();
						break;
					}
					case 4:
					{
						//optimalpr();
						break;
					}
					default:
					{
						cout<<"Incorrect Input"<<endl;
						break;
					}
				}

			}
            case 7://Process Synchronization
            {
                system("cls");
                cout<<"---Process Synchronization---"<<endl;
                cout<<"Choose a Synchronization Problem"<<endl;
                cout<<"1.Producers-Consumers Problem\n2.Readers-Writers Problem\n3.Dining Philosophers Problem\n"<<endl;
                cin>>algo;
                switch(algo)
                {
                    case 1:
                    {
                        pnc();
                        break;
                    }
                    case 2:
                    {
                        rnw();
                        break;
                    }
                    case 3:
                    {
                        dp();
                        break;
                    }
                    default:
                    {
                        cout<<"Wrong Input!!"<<endl;
                        break;
                    }
                }
            }
			default:
			{
				break;
			}
		}

	}
}