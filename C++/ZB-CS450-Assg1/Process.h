//
//  Process.h
//  ZB-CS450-Assg1
//
//  Created by Zachary Boylan on 12/10/17.
//  Copyright © 2017 Zachary Boylan. All rights reserved.
//

#ifndef Process_h
#define Process_h

class Process
{
public:
    Process();
    Process(float arrival, int burst);
    Process(int id, float arrival, int burst);
    
    float getArrivalTime();
    int getBurstTime();
    int getProcessID();
    int getLastRan();
    int getWaitTime();
    
    void setLastRan(int x);
    void addWaitTime(int x);
    void reduceBurstTime(int x);
    
    static int processCount;
    
private:
    float arrivalTime;
    int burstTime;
    int processID;
    int lastRan = 0;
    int waitTime = 0;
    
};



#endif /* Process_h */
