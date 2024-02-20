#include <iostream>
#include <unistd.h>
#include <algorithm>
using namespace std;
struct process {
  int id;
  int priority;
  int burstTime;
  int completionTime;
};

bool comparator(process a, process b) {
  return a.priority < b.priority;
}



int main() {
  int n;
  cout << "Enter Number of Process :" << endl;
  cin >> n;
  process processes[n];
  int id = 0;
  for (auto &p : processes) {        //when we want to change p at its location i.e inside the array use &p
    p.id = id;
    cout << "Enter priority and burst time for process ID : " << id
         << " => ";
    cin >> p.priority >>p.burstTime;
  }
  sort(processes, processes + n, comparator);
  int currentTime=0;
  for(auto &p:processes){
    currentTime+=p.burstTime;
    p.completionTime=currentTime;
  }
  // turnaround time for a process=> completionTime-arrivalTime
  int totalTurnaround = 0;
  for (auto p : processes) { // we are not changing any property of "p" hence
                             // not need of &p
    totalTurnaround += p.completionTime;
  }
  // waiting Time for a process => total time it spent on ready queue =>
  // turnaroundTime-burstTime
  int totalWaitingTime = totalTurnaround; //=> totalWaitingTime=totalTurnaround-totalBurstTime
  for (auto p : processes) {
    totalWaitingTime -= p.burstTime;
  }
  cout << "Average Turnaround time : " << (totalTurnaround / n)
       << " , Average Waiting time : " << (totalWaitingTime / n) << endl;
  return 1;
}