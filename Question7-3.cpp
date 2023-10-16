//Implement the simulation of a time sharing system discussed in Chapter 5, Sec. 5.5, using
//linked queues.
#include<iostream>
#include<vector>
#include<algorithm>

class Process {
public: 
    int PID, AT, BT, PRI, CT, TAT, WT;
    bool GIG; // gone in Gantt chart
    Process() {
        PID = 0;
        AT = 0;
        BT = 0;
        PRI = 0;
        CT = 0;
        TAT = 0;
        WT = 0;
        GIG = false;
    }
    bool equals(Process obj) {
        if (this->PID == obj.PID)
            return true;
        else
            return false;
    }
};

void RoundRobin(std::vector<Process> &processes, int TQ) {
    int bt[processes.size()];
    for (int i = 0; i < processes.size(); i++) {
        bt[i] = processes[i].BT;
    }
    std::vector<Process> ready ;
    std::vector<Process> gantt ;
    std::vector<int> ganttArray ;
    ganttArray.push_back(processes[0].AT);
    ready.push_back(processes[0]);
    bool allProcessAdded = false;
    int pointer = 0;
    while (pointer < ready.size()) {
        gantt.push_back(ready[pointer]);
        if (ready[pointer].BT >= TQ) {
            ganttArray.push_back(TQ + ganttArray[pointer]);
            ready[pointer].BT -= TQ;
            if (!allProcessAdded) {
                for (int i = TQ - 1; i >= 0; i--) {
                    if (ganttArray[pointer + 1] - i == processes.size() - 1) {
                        allProcessAdded = true;
                    }
                    ready.push_back(processes[ganttArray[pointer + 1] - i]);
                }
            }
            if (ready[pointer].BT != 0) {
                ready.push_back(ready[pointer]);
            } 
            else {
                ready[pointer].CT = ganttArray[pointer + 1];
            }
        } 
        else {
            ganttArray.push_back(ready[pointer].BT + ganttArray[pointer]);
            if (!allProcessAdded) {
                for (int i = ready[pointer].BT - 1; i >= 0; i--) {
                    ready.push_back(processes[ganttArray[pointer + 1] - i]);
                }
            }
            ready[pointer].BT = 0;
            ready[pointer].CT = ganttArray[pointer + 1];
        }
        pointer++;
    }
    processes.clear();
    for (int i = 0; i < ready.size(); i++) {
        if( ready[i].CT != 0) {
            processes.push_back(ready[i]);
        }
    }

    std::sort(processes.begin(), processes.end(), [](Process o1, Process o2){
        return o1.AT <= o2.AT;
    });

    for (int i = 0; i < processes.size(); i++) {
        processes[i].BT = bt[i];
    }
    for (int i = 0; i < processes.size(); i++) {
    processes[i].TAT = processes[i].CT - processes[i].AT;
    processes[i].WT = processes[i].TAT - processes[i].BT;
    }
    std::cout << "Gantt Chart: -" << std::endl;
    for (int i = 0; i < gantt.size(); i++) {
    std::cout << ganttArray[i] << "\t" << "P[" << gantt[i].PID << "]\t";
    }
    std::cout << ganttArray[ganttArray.size() - 1] << std::endl;
}


int main() {
    std::cout << "Enter Number of Processes: ";
    int n;
    std::cin >> n;
    std::vector<Process> processes(0);
    std::cout << "Now Enter Arrival time and Burst time of processes" << std::endl ;
    for (int i = 0; i < n; i++) {
        Process p;
        p.PID = i;
        std::cin >> p.AT;
        std::cin >> p.BT;
        processes.push_back(p);
    }
    std::sort(processes.begin(), processes.end(), [](Process o1, Process o2){
        return o1.AT <= o2.AT;
    });
    std:: cout << "Enter time Quantum: ";
    int a;
    std::cin >> a;
    RoundRobin(processes, a);

    std::sort(processes.begin(), processes.end(), [] (Process o1, Process o2) {
        return (o1.PID < o2.PID);
    });
    int totalTAT = 0;
    int totalWT = 0;
    std::cout << "PID\tAT\tBT\tPRIORITY\tCT\tTAT\tWT" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "P[" << processes[i].PID <<
            "]\t" << processes[i].AT << "\t" << processes[i].BT << "\t" << processes[i].PRI << "\t\t"
            << processes[i].CT << "\t" << processes[i].TAT << "\t" << processes[i].WT << std::endl;
        totalTAT += processes[i].TAT;
        totalWT += processes[i].WT;
    }
    std::cout << "Average turn around time: " << (float) totalTAT / n << std::endl;
    std::cout << "Average waiting time: " << (float) totalWT / n;
    return 0;
}