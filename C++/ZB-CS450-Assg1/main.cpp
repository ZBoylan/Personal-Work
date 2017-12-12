//
//  main.cpp
//  Zach Boylan CS450 Fall 2017 Assignment 1
//  Simulate two OS process scheduling algorithms
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <vector>
#include <queue>
#include <stdlib.h> // for srand and rand
#include <time.h> // also needed
#include <fstream> //needed to send results to output txt file
#include "Process.h"

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::vector;
using std::queue;

int Process::processCount = 0;  //set counter of Processes to 0
// or just have this as a variable in main that you pass to constructor??

bool sortByArrival(Process &lhs, Process &rhs) {
    return lhs.getArrivalTime() < rhs.getArrivalTime();
}

int main() {
    
    srand(time(NULL));  //generate random seed
    
    float avgFCFSTime = 0;
    
    ofstream myfile;  //file stream object
    
    // Open file to print results to
    myfile.open("/Users/zacharyboylan/Documents/Xcode/ZB-CS450-Assg1/ZB-CS450-Assg1/algorithmResults.txt", std::ios::out); // | std::ios::app);
    if (myfile.is_open())
    {
        cout << "Output file opened successfully" << endl;
    }
    else
    {
        cout << "Unable to open file";
        return 2;
    }
    
    myfile << "OS Process Scheduling - Zach Boylan - CS 450\n";
    myfile << "Algorithm performance and trend analysis\n";
    myfile << "FCFS and Round Robin algorithms\nToday's date: ";
    
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    myfile << (now->tm_year + 1900) << '-'
    << (now->tm_mon + 1) << '-'
    <<  now->tm_mday
    << "\n\n";
    
    
    
    // generate 10-20 random Processes
    vector<Process> processes;
    int numProcesses = rand() % 11 + 10; // 10-20
    cout << "  Number of processes = " << numProcesses << endl;
    myfile << "   Number of processes = " << numProcesses << "\n\n";
    myfile << "PID ArrivalTime BurstTime" << endl;
    float arrival;
    int burst;
    
    for (int i = 0; i < numProcesses; i++){
        // generate random arrivalTime -> 0.0 - 5.0
        arrival = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5));
        // generate random burstTime -> 1 - 10
        burst = rand() % 10 + 1;
        //insert process into vector
        processes.push_back(Process(arrival, burst));
    }
    
    for (int i = 0; i < processes.size(); i++){
        cout << processes[i].getProcessID() << " " << std::setw(4) << std::setprecision(3) << processes[i].getArrivalTime() << " " << processes[i].getBurstTime() << endl;
        
        myfile << std::setw(2) << processes[i].getProcessID() << "     " << std::setw(4) << std::setprecision(3) << std::fixed << processes[i].getArrivalTime() << "       " << std::setw(2) << processes[i].getBurstTime() << endl;
    }
    
    
    // Storage for the different algorithms
    queue<Process> RRProcesses;
    vector<Process> FCFSProcesses = processes;
    
    // Fill in RR queue - WORKS
    //myfile << processes.size() << endl;
    for (int i = 0; i < processes.size(); i++){
        RRProcesses.push(processes[i]);
    }
    
    // Test data - go back to ^ when good
//    RRProcesses.push(Process(1, 0, 3));
//    RRProcesses.push(Process(2, 0, 1));
//    RRProcesses.push(Process(3, 0, 2));
//    RRProcesses.push(Process(4, 0, 4));
    
    //checking that all Processes are in the queue
//    myfile << "\nA listing of all the elements in RRQueue\n";
//    for (int i = 0; i < processes.size(); i++){
//        myfile << RRProcesses.front().getProcessID() << endl;
//        RRProcesses.pop();
//    }
    
    // front() then pop()
    Process current;
    int time = 0;
    float avgRRWaitTime = 0;
    int timeSlice;
    cout << "What time quantum would you like to use for Round Robin?\n";
    cin >> timeSlice;
    myfile << "\nRound Robin algorithm running now with a time quantum of " << timeSlice << endl;
    while (!RRProcesses.empty()){
        current = RRProcesses.front();
        if (current.getBurstTime() > timeSlice){
            //myfile << "     Pre-Time = " << time << endl;
            current.reduceBurstTime(timeSlice);
            //myfile << "Process " << current.getProcessID() << " reduced by timeSlice. BT now = " << current.getBurstTime() << endl;
            current.addWaitTime(time - current.getLastRan());
            //myfile << "Process " << current.getProcessID() << " current wait time = " << current.getWaitTime() << endl;
            time += timeSlice;
            //myfile << "     Post-Time = " << time << endl;
            current.setLastRan(time);
            RRProcesses.pop(); // Ran for timeSlice now take off queue
            RRProcesses.push(current);  // and put in the back of the queue
        }
        else{
            //myfile << "     Pre-Time = " << time << endl;
            current.addWaitTime(time - current.getLastRan());
            time += current.getBurstTime();
            current.reduceBurstTime(current.getBurstTime());
            myfile << "  Process " << std::setw(2) << current.getProcessID() << " has finished with wait time = " << std::setw(3) << current.getWaitTime() << endl;
            //myfile << "     Post-Time = " << time << endl;
            avgRRWaitTime += current.getWaitTime();
            RRProcesses.pop(); // Ran for remaining Burst Time - take off queue
        }
    }
    avgRRWaitTime = avgRRWaitTime / processes.size();
    myfile << "\n *** RR - Average wait time = " << avgRRWaitTime << endl;
    
    
    
    // Turnaround time = completion time – arrival time
    
    // Sort for FCFS - WORKS
    sort(FCFSProcesses.begin(), FCFSProcesses.end(), sortByArrival);
    
    // FCFS - execute in arrival time order
    myfile << "\n Processes sorted for FCFS:\n";
    myfile << "PID ArrivalTime BurstTime WaitTime   Turnaround_Time" << endl;
    float completionTime = 0;
    float waitTime = 0;
    float avgWaitTimeFCFS = 0;
    float tTime = 0;
    for (int i = 0; i < FCFSProcesses.size(); i++){
        if (i != 0)
            waitTime = completionTime - FCFSProcesses[i].getArrivalTime();
        if (i == 0){
            // Not every first process arrives at time = 0.0
            completionTime += FCFSProcesses[i].getBurstTime() + FCFSProcesses[i].getArrivalTime();
        }
        else
            completionTime += FCFSProcesses[i].getBurstTime();
        
        tTime = completionTime - FCFSProcesses[i].getArrivalTime();
        avgFCFSTime += tTime;
        avgWaitTimeFCFS += waitTime;
        
        myfile << std::setw(2) << FCFSProcesses[i].getProcessID() << "     " << std::setw(4) << std::setprecision(3) << std::fixed << FCFSProcesses[i].getArrivalTime() << "       " << std::setw(2) << FCFSProcesses[i].getBurstTime() << "      " << std::setw(7) << waitTime << " |  " << completionTime << " - " << FCFSProcesses[i].getArrivalTime() << " = " << tTime << endl;
    }
    myfile << "\n *** FCFS - Average wait time = " << avgWaitTimeFCFS / FCFSProcesses.size() << endl;
    myfile << " *** FCFS - Average turnaround time = " << avgFCFSTime / FCFSProcesses.size() << endl;
    
    
    //    ***FCFS IS DONE**** ^^^^
    
    
    
    bool singleMode = false;
    int mode;
    
    cout << "Scheduling Algorithm Evaluation using Deterministic Modeling" << endl;
    cout << "\nPress 1 for single algorithm performance evaluation mode\n";
    cout << "\nPress 2 for algorithm comparing mode\n";
    cin >> mode;
    
    if (mode == 1)
    {
        singleMode = true;
        cout << "Proceeding in single algorithm performance evaluation mode\n";
        myfile << "\n   Evaluating single algorithm: ";
    }
    else if (mode == 2)
    {
        cout << "Proceeding in algorithm comparing mode\n";
        myfile << "\n   Comparing both algorithms\n";
    }
    else{
        cout << "Invalid choice. Goodbye.\n";
        myfile << "\n   Invalid choice. Goodbye.\n";
        return 3;
    }
    
    
    
    
    // at end of single - ask if they want to run another algorithm
    //     do some loop for single run
    int algorithm;
    if (singleMode){
        cout << "Press 1 to evaluate using the FCFS algorithm \n";
        cout << "Press 2 to evaluate using the Round Robin algorithm\n";
        cin >> algorithm;
        
        if (algorithm == 1)
        {
            cout << "FCFS algorithm chosen\n";
            myfile << "FCFS\n";
        }
        else if (algorithm == 2)
        {
            cout << "Round Robin algorithm chosen\n";
            myfile << "SJF Preemptive\n";
        }
        else{
            cout << "Invalid algorithm choice. Goodbye.\n";
            myfile << "\n   Invalid algorithm choice. Goodbye.\n";
            return 3;
        }
    }
    
    
    
    
    
    
    
    // Turnaround time = completion time – arrival time
    
    // FCFS - first come first serve – execute in arrival order
    
    
    
    myfile.close();
    
    return 0;
}
