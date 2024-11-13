#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;               
    int arrivalTime;      
    int burstTime;        
    int startTime;        
    int completionTime;   
    int waitingTime;      
    int turnaroundTime;   
};


bool compareByArrivalTime(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for Process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareByArrivalTime);

    int currentTime = 0;
    for (int i = 0; i < n; ++i) {
        // Start time is the max of current time or arrival time (whichever is later)
        processes[i].startTime = max(currentTime, processes[i].arrivalTime);
        // Completion time is start time plus burst time
        processes[i].completionTime = processes[i].startTime + processes[i].burstTime;
        // Turnaround time is completion time minus arrival time
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        // Waiting time is start time minus arrival time
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        // Update current time to reflect process completion
        currentTime = processes[i].completionTime;
    }

    // Display results
    cout << "\nProcess\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes) {
        cout << "P" << process.id << "\t\t" << process.arrivalTime << "\t\t"
             << process.burstTime << "\t\t" << process.startTime << "\t\t"
             << process.completionTime << "\t\t" << process.waitingTime << "\t\t"
             << process.turnaroundTime << '\n';
    }

    // Calculate and display average waiting and turnaround times
    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (const auto &process : processes) {
        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
    }

    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << '\n';
    cout << "Average Turnaround Time: " << totalTurnaroundTime / n << '\n';

    return 0;
}
