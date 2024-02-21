#include <iostream>
#include <queue>
#include <unistd.h>
using namespace std;
struct process {
  int id;
  int arrivalTime;
  int burstTime;
  int timeLeft;
  int CompletionTime = 0;
  bool addedToReadyQueue = false;
};

int main() {
  int n, quantum;
  cout << "Enter Number of Process :" << endl;
  cin >> n;
  cout << "Enter Time Quantum :" << endl;
  cin >> quantum;
  process processes[n];
  int id = 0;
  for (auto &p : processes) {        //when we want to change p at its location i.e inside the array use &p
    p.id = id;
    cout << "Enter arrival time and burst time for process ID : " << id
         << " => ";
    cin >> p.arrivalTime >> p.burstTime;
    p.timeLeft = p.burstTime;
    id++;
  }
  int processesCompleted = 0;
  int currentTime = 0;
  queue<process> readyQueue;
  while (processesCompleted != n) {
    if (readyQueue.size() == 0) {
      for (auto &p : processes) {
        if (p.arrivalTime <= currentTime && !p.addedToReadyQueue) {
          readyQueue.push(p);
          p.addedToReadyQueue = true;
        }
      }
      if (readyQueue.size() == 0)
        currentTime++;
    }
    while (readyQueue.size() != 0) {
      process p = readyQueue.front();
      readyQueue.pop();
      int timeSpend = min(quantum, p.timeLeft);
      p.timeLeft -= timeSpend;
      currentTime += timeSpend;
      for (auto &p : processes) {
        if (p.arrivalTime <= currentTime && !p.addedToReadyQueue) {
          readyQueue.push(p);
          p.addedToReadyQueue = true;
        }
      }
      if (p.timeLeft == 0) {
        cout << "Process id : " << p.id
             << " completed at current time: " << currentTime << endl;
        processes[p.id].CompletionTime = currentTime;
        processesCompleted++;
      } else {
        readyQueue.push(p);
      }
    }
    // sleep(1); //not needed but to why not
  }
  // turnaround time for a process=> completionTime-arrivalTime
  int totalTurnaround = 0;
  for (auto p : processes) { // we are not changing any property of "p" hence
                             // not need of &p
    totalTurnaround += p.CompletionTime - p.arrivalTime;
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
