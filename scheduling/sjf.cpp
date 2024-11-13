#include <bits/stdc++.h>
using namespace std;

// Function to find the Completion Time for each process
void findCompletionTime(int n, int at[], int bt[], int completion[], int start[]) {
    vector<pair<int, int>> processes;
    for (int i = 0; i < n; i++) {
        processes.push_back({at[i], i});  // Pair of arrival time and index
    }
    sort(processes.begin(), processes.end());  // Sort by arrival time

    int currentTime = 0;  // Track the current time in the scheduler
    vector<bool> done(n, false);  // Track if a process is completed

    for (int i = 0; i < n; i++) {
        int idx = -1;
        int minBurstTime = INT_MAX;

        // Find the process with the shortest burst time that has arrived
        for (int j = 0; j < n; j++) {
            int procIndex = processes[j].second;
            if (!done[procIndex] && at[procIndex] <= currentTime && bt[procIndex] < minBurstTime) {
                minBurstTime = bt[procIndex];
                idx = procIndex;
            }
        }

        // If no process has arrived, skip to the next arrival time
        if (idx == -1) {
            currentTime = processes[i].first;
            i--;
            continue;
        }

        // Set start and completion times for the selected process
        start[idx] = currentTime;
        completion[idx] = currentTime + bt[idx];
        currentTime = completion[idx];
        done[idx] = true;
    }
}

// Function to find the Turnaround Time for each process
void findTurnAroundTime(int n, int at[], int completion[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = completion[i] - at[i]; // TAT = CT - AT
    }
}

// Function to find the Waiting Time for each process
void findWaitingTime(int n, int bt[], int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i]; // WT = TAT - BT
    }
}

// Function to print the Gantt Chart for the processes based on increasing time
void printGanttChart(int n, int start[], int bt[], int completion[]) {
    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n";

    // Sort processes by start time for time-based ordering in the Gantt chart
    vector<pair<int, int>> timeline;
    for (int i = 0; i < n; i++) {
        timeline.push_back({start[i], i});
    }
    sort(timeline.begin(), timeline.end());

    // Top row with process numbers
    for (int i = 0; i < n; i++) {
        int idx = timeline[i].second;
        cout << "|  P" << (idx + 1) << "  ";
    }
    cout << "|\n";

    cout << "-------------------------------------------------\n";

    // Bottom row with start and end times in time order
    for (int i = 0; i < n; i++) {
        int idx = timeline[i].second;
        cout << start[idx] << "      ";
    }
    cout << completion[timeline.back().second] << "\n";
}

// Function to find and display average waiting and turnaround times
void findAvgTime(int n, int at[], int bt[]) {
    int completion[n], wt[n], tat[n], start[n];
    
    findCompletionTime(n, at, bt, completion, start);
    findTurnAroundTime(n, at, completion, tat);
    findWaitingTime(n, bt, tat, wt);

    int totalWt = 0, totalTat = 0;

    cout << "\nProcess No.\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tWait Time\tTurnaround Time\n";
    for(int i = 0; i < n; i++) {
        totalWt += wt[i];
        totalTat += tat[i];
        
        cout << "P" << (i+1) << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << start[i] << "\t\t" 
             << completion[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }
    cout << "Average Waiting Time: " << ((float)totalWt / n) << endl;
    cout << "Average Turnaround Time: " << ((float)totalTat / n) << endl;

    // Print Gantt Chart
    printGanttChart(n, start, bt, completion);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int at[n], bt[n];
    for(int i = 0; i < n; i++) {
        cout << "Enter the Arrival Time and Burst Time of process " << (i+1) << ": ";
        cin >> at[i] >> bt[i];
    }

    findAvgTime(n, at, bt);
    return 0;
}