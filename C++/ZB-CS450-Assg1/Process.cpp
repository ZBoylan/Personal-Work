//
//  Process.cpp
//  ZB-CS450-Assg1
//
//  Created by Zachary Boylan on 12/10/17.
//  Copyright © 2017 Zachary Boylan. All rights reserved.
//

#include <stdio.h>
#include "Process.h"

Process::Process()
{
    processCount++;
    
    arrivalTime = 0;
    burstTime = 0;
    processID = processCount;
}
Process::Process(float arrival, int burst)
{
    processCount++;
    
    arrivalTime = arrival;
    burstTime = burst;
    processID = processCount;
}
Process::Process(int id, float arrival, int burst)
{
    //processCount++;
    
    arrivalTime = arrival;
    burstTime = burst;
    processID = id;
}
float Process::getArrivalTime()
{
    return arrivalTime;
}
int Process::getBurstTime()
{
    return burstTime;
}
int Process::getProcessID()
{
    return processID;
}
int Process::getLastRan()
{
    return lastRan;
}
int Process::getWaitTime()
{
    return waitTime;
}
void Process::setLastRan(int x)
{
    lastRan = x;
}
void Process::addWaitTime(int x)
{
    waitTime += x;
}
void Process::reduceBurstTime(int x)
{
    burstTime -= x;
}
