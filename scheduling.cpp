#include "lab7.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <math.h>

using namespace std;

void Scheduler::execute()
{
    for (int i = 0; i < schedulongPoliceis.size(); i++)
    {
        clearTables();
        if (schedulongPoliceis[i].first == 1)
        {
            FCFS();
            if (type == "trace")
                trace(1, -1);
            else
                stats(1, -1);
        }
        else if (schedulongPoliceis[i].first == 2)
        {
            RR(schedulongPoliceis[i].second);
            if (type == "trace")
                trace(2, schedulongPoliceis[i].second);
            else
                stats(2, schedulongPoliceis[i].second);
        }
        else if (schedulongPoliceis[i].first == 3)
        {
            SPN();
            if (type == "trace")
                trace(3, -1);
            else
                stats(3, -1);
        }
        else if (schedulongPoliceis[i].first == 4)
        {
            SRT();
            if (type == "trace")
                trace(4, -1);
            else
                stats(4, -1);
        }
        else if (schedulongPoliceis[i].first == 5)
        {
            HRRN();
            if (type == "trace")
                trace(5, -1);
            else
                stats(5, -1);
        }
        else if (schedulongPoliceis[i].first == 6)
        {
            FB1();
            if (type == "trace")
                trace(6, -1);
            else
                stats(6, -1);
        }
        else if (schedulongPoliceis[i].first == 7)
        {
            FB2i();
            if (type == "trace")
                trace(7, -1);
            else
                stats(7, -1);
        }
        else if (schedulongPoliceis[i].first == 8)
        {
            AGE(schedulongPoliceis[i].second);
            if (type == "trace")
                trace(8, -1);
        }
    }
}
void Scheduler::trace(int policy, int argument)
{
    if (policy == 1)
    {
        cout << "FCFS  ";
        printHeader();
        cout << '\n';
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 2)
    {
        if (argument > 10)
            cout << "RR-" << argument << " ";
        else
            cout << "RR-" << argument << "  ";
        printHeader();
        cout << '\n';
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 3)
    {
        cout << "SPN   ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 4)
    {
        cout << "SRT   ";
        printHeader();
        cout << '\n';
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 5)
    {
        cout << "HRRN  ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 6)
    {
        cout << "FB-1  ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 7)
    {
        cout << "FB-2i ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
    else if (policy == 8)
    {
        cout << "Aging ";
        printHeader();
        cout << "\n";
        printTracing();
        printDashes();
        cout << "\n\n";
    }
}
void Scheduler::stats(int policy, int argument)
{
    if (policy == 1)
    {
        cout << "FCFS" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 2)
    {
        cout << "RR-" << argument << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 3)
    {
        cout << "SPN" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 4)
    {
        cout << "SRT" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 5)
    {
        cout << "HRRN" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 6)
    {
        cout << "FB-1" << endl;
        printStats();
        cout << '\n';
    }
    else if (policy == 7)
    {
        cout << "FB-2i" << endl;
        printStats();
        cout << '\n';
    }
}
void Scheduler::FCFS()
{
    int prev_finish = 0;
    for (auto &it : processes)
    {
        for (int t = 0; t < it.serveTime; t++)
        {
            *(processesPrintingArray + it.id * maxSeconds + prev_finish + t) = '*';
        }
        for (int i = it.arrivalTime; i < prev_finish; i++)
            *(processesPrintingArray + it.id * maxSeconds + i) = '.';
        it.waitingTime = max(0, prev_finish - it.arrivalTime);
        it.finishTime = it.serveTime + max(it.arrivalTime, prev_finish);
        prev_finish = it.finishTime;
        it.turnAroundTime = it.finishTime - it.arrivalTime;
        it.NormTurnTime = (float)it.turnAroundTime / it.serveTime;
        it.remainingTime = 0;
    }
}

void Scheduler::RR(int quantum)
{
    queue<int> tempQueue;
    int time = 0;
    int processesCompleted = 0;

    while (processesCompleted < numberOfProcesses)
    {
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (tempQueue.empty() && processes[i].arrivalTime <= time && processes[i].remainingTime > 0)
            {
                tempQueue.push(i);
            }
        }
        if (!tempQueue.empty())
        {
            int index_current = tempQueue.front();
            tempQueue.pop();
            int time_running = min(quantum, processes[index_current].remainingTime);
            for (int t = 0; t < time_running; t++)
            {
                if (t + time >= maxSeconds)
                    break;
                *(processesPrintingArray + index_current * maxSeconds + time + t) = '*';
                for (int p = 0; p < numberOfProcesses; p++)
                {
                    if (p != index_current && processes[p].arrivalTime <= (time + t) && processes[p].remainingTime > 0)
                        *(processesPrintingArray + processes[p].id * maxSeconds + (time + t)) = '.';
                }
            }
            processes[index_current].remainingTime -= time_running;
            time += time_running;
            if (processes[index_current].remainingTime > 0)
            {
                for (int i = 0; i < numberOfProcesses; i++)
                {
                    if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0 && i != index_current)
                    {
                        queue<int> teQueue;
                        bool found = false;
                        while (!tempQueue.empty())
                        {
                            if (tempQueue.front() == i)
                            {
                                found = true;
                            }
                            teQueue.push(tempQueue.front());
                            tempQueue.pop();
                        }
                        while (!teQueue.empty())
                        {
                            tempQueue.push(teQueue.front());
                            teQueue.pop();
                        }
                        if (!found)
                            tempQueue.push(i);
                    }
                }
                tempQueue.push(index_current);
            }
            else
            {
                processes[index_current].finishTime = time;
                processes[index_current].turnAroundTime = processes[index_current].finishTime - processes[index_current].arrivalTime;
                processes[index_current].NormTurnTime = (float)processes[index_current].turnAroundTime / processes[index_current].serveTime;
                processesCompleted++;
            }
        }
        else
        {
            time++;
        }
    }
}

void Scheduler::SPN()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> SPNQueue;
    int time = 0;
    int processesCompleted = 0;
    while (processesCompleted < numberOfProcesses)
    {
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0)
            {
                queue<pair<int, int>> tempSet;
                bool found = false;
                while (!SPNQueue.empty())
                {
                    if (SPNQueue.top().second == i)
                    {
                        found = true;
                    }
                    tempSet.push(SPNQueue.top());
                    SPNQueue.pop();
                }
                while (!tempSet.empty())
                {
                    SPNQueue.push(tempSet.front());
                    tempSet.pop();
                }
                if (!found)
                    SPNQueue.push({processes[i].serveTime, i});
            }
        }
        if (!SPNQueue.empty())
        {
            int index_current = SPNQueue.top().second;
            SPNQueue.pop();
            for (int t = 0; t < processes[index_current].serveTime; t++)
            {
                if (time + t >= maxSeconds)
                    break;
                *(processesPrintingArray + index_current * maxSeconds + time + t) = '*';
                for (int p = 0; p < numberOfProcesses; p++)
                {
                    if (p != index_current && processes[p].arrivalTime <= (time + t) && processes[p].remainingTime > 0)
                        *(processesPrintingArray + processes[p].id * maxSeconds + (time + t)) = '.';
                }
            }
            time += processes[index_current].serveTime;
            processes[index_current].remainingTime = 0;
            processes[index_current].finishTime = time;
            processes[index_current].turnAroundTime = processes[index_current].finishTime - processes[index_current].arrivalTime;
            processes[index_current].NormTurnTime = (float)processes[index_current].turnAroundTime / processes[index_current].serveTime;
            processesCompleted++;
        }
        else
        {
            time++;
        }
    }
}

void Scheduler::SRT()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> SRTQueue;
    int time = 0;
    int processesCompleted = 0;
    while (processesCompleted < numberOfProcesses)
    {
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (processes[i].arrivalTime == time && processes[i].remainingTime > 0)
            {
                SRTQueue.push({processes[i].remainingTime, i});
            }
        }
        if (!SRTQueue.empty())
        {
            int index_current = SRTQueue.top().second;
            SRTQueue.pop();
            *(processesPrintingArray + index_current * maxSeconds + time) = '*';
            processes[index_current].remainingTime -= 1;
            for (int p = 0; p < numberOfProcesses; p++)
            {
                if (p != index_current && processes[p].arrivalTime <= time && processes[p].remainingTime > 0)
                    *(processesPrintingArray + processes[p].id * maxSeconds + time) = '.';
            }
            if (processes[index_current].remainingTime > 0)
            {
                SRTQueue.push({processes[index_current].remainingTime, index_current});
            }
            else
            {
                processes[index_current].finishTime = time + 1;
                processes[index_current].turnAroundTime = processes[index_current].finishTime - processes[index_current].arrivalTime;
                processes[index_current].NormTurnTime = (float)processes[index_current].turnAroundTime / processes[index_current].serveTime;
                processesCompleted++;
            }
            time++;
        }
        else
        {
            time++;
        }
    }
}

void Scheduler::HRRN()
{
    priority_queue<pair<float, int>> HRRNQueue;
    int time = 0;
    int processesCompleted = 0;
    while (processesCompleted < numberOfProcesses)
    {
        while (!HRRNQueue.empty())
        {
            HRRNQueue.pop();
        }
        for (int i = 0; i < numberOfProcesses; i++)
        {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0)
            {
                HRRNQueue.push({processes[i].responseRatio, i});
                // cout << "Process " << processes[i].waitingTime << " " << processes[i].processName << " with response ratio " << processes[i].responseRatio << " added to HRRN queue at time " << time << endl;
            }
        }
        if (!HRRNQueue.empty())
        {
            int index_current = HRRNQueue.top().second;
            HRRNQueue.pop();
            for (int t = 0; t < processes[index_current].serveTime; t++)
            {
                if (time + t >= maxSeconds)
                    break;
                *(processesPrintingArray + index_current * maxSeconds + time + t) = '*';
                for (int p = 0; p < numberOfProcesses; p++)
                {
                    if (p != index_current && processes[p].arrivalTime <= (time + t) && processes[p].remainingTime > 0)
                        *(processesPrintingArray + processes[p].id * maxSeconds + (time + t)) = '.';
                }
            }
            time += processes[index_current].serveTime;
            processes[index_current].remainingTime = 0;
            processes[index_current].finishTime = time;
            processes[index_current].turnAroundTime = processes[index_current].finishTime - processes[index_current].arrivalTime;
            processes[index_current].NormTurnTime = (float)processes[index_current].turnAroundTime / processes[index_current].serveTime;
            processesCompleted++;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0)
                {

                    processes[i].waitingTime += (time - processes[i].arrivalTime);
                    processes[i].responseRatio = (float)(processes[i].waitingTime + processes[i].serveTime) / processes[i].serveTime;
                }
            }
        }
        else
        {
            time++;
        }
    }
}

void Scheduler::FB1()
{
    vector<queue<int>> FBQueues(numberOfProcesses);
    int time = 0;
    int processesCompleted = 0;
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].arrivalTime == time && processes[i].remainingTime > 0)
        {
            FBQueues[0].push(i);
        }
    }
    while (processesCompleted < numberOfProcesses)
    {

        int level = -1;
        for (int l = 0; l < numberOfProcesses; l++)
        {
            if (!FBQueues[l].empty())
            {
                level = l;
                break;
            }
        }
        if (level != -1)
        {
            int index_current = FBQueues[level].front();
            FBQueues[level].pop();
            *(processesPrintingArray + index_current * maxSeconds + time) = '*';
            processes[index_current].remainingTime -= 1;

            for (int p = 0; p < numberOfProcesses; p++)
            {
                if (p != index_current && processes[p].arrivalTime <= time && processes[p].remainingTime > 0)
                    *(processesPrintingArray + processes[p].id * maxSeconds + time) = '.';
            }
            time++;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (processes[i].arrivalTime == time && processes[i].remainingTime > 0)
                {
                    FBQueues[0].push(i);
                }
            }
            bool emptysystem = true;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (!FBQueues[i].empty())
                {
                    emptysystem = false;
                }
            }
            if (processes[index_current].remainingTime > 0 && !emptysystem)
            {
                int next_level = min(level + 1, numberOfProcesses - 1);
                FBQueues[next_level].push(index_current);
            }
            else if (processes[index_current].remainingTime > 0 && emptysystem)
            {
                FBQueues[level].push(index_current);
            }
            else
            {
                processes[index_current].finishTime = time;
                processes[index_current].turnAroundTime = processes[index_current].finishTime - processes[index_current].arrivalTime;
                processes[index_current].NormTurnTime = (float)processes[index_current].turnAroundTime / processes[index_current].serveTime;
                processesCompleted++;
            }
        }
        else
        {
            time++;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (processes[i].arrivalTime == time && processes[i].remainingTime > 0)
                {
                    FBQueues[0].push(i);
                }
            }
        }
    }
}

void Scheduler::FB2i()
{
    vector<queue<int>> FBQueues(numberOfProcesses);
    int time = 0;
    int processesCompleted = 0;
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].arrivalTime == time && processes[i].remainingTime > 0)
        {
            FBQueues[0].push(i);
        }
    }
    while (processesCompleted < numberOfProcesses)
    {

        int level = -1;
        for (int l = 0; l < numberOfProcesses; l++)
        {
            if (!FBQueues[l].empty())
            {
                level = l;
                break;
            }
        }
        if (level != -1)
        {
            int index_current = FBQueues[level].front();
            FBQueues[level].pop();

            int quantum = pow(2, level);
            int time_running = min(quantum, processes[index_current].remainingTime);
            for (int t = 0; t < time_running; t++)
            {
                *(processesPrintingArray + index_current * maxSeconds + time) = '*';
                processes[index_current].remainingTime -= 1;

                for (int p = 0; p < numberOfProcesses; p++)
                {
                    if (p != index_current && processes[p].arrivalTime <= time && processes[p].remainingTime > 0)
                        *(processesPrintingArray + processes[p].id * maxSeconds + time) = '.';
                }
                time++;
                for (int i = 0; i < numberOfProcesses; i++)
                {
                    if (processes[i].arrivalTime == time && processes[i].remainingTime > 0)
                    {
                        FBQueues[0].push(i);
                    }
                }
            }
            bool emptysystem = true;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (!FBQueues[i].empty())
                {
                    emptysystem = false;
                }
            }
            if (processes[index_current].remainingTime > 0 && !emptysystem)
            {
                int next_level = min(level + 1, numberOfProcesses - 1);
                FBQueues[next_level].push(index_current);
            }
            else if (processes[index_current].remainingTime > 0 && emptysystem)
            {
                FBQueues[level].push(index_current);
            }
            else
            {
                processes[index_current].finishTime = time;
                processes[index_current].turnAroundTime = processes[index_current].finishTime - processes[index_current].arrivalTime;
                processes[index_current].NormTurnTime = (float)processes[index_current].turnAroundTime / processes[index_current].serveTime;
                processesCompleted++;
            }
        }
        else
        {
            time++;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (processes[i].arrivalTime == time && processes[i].remainingTime > 0)
                {
                    FBQueues[0].push(i);
                }
            }
        }
    }
}
void Scheduler::AGE(int quantum)
{
    vector<int> readyList;
    int time = 0;
    int processesCompleted = 0;
    while (processesCompleted < numberOfProcesses)
    {
        for (int i = 0; i < numberOfProcesses; i++)
        {
            bool found = false;
            if (processes[i].arrivalTime == time)
            {
                for (int j = 0; j < readyList.size(); j++)
                {
                    if (readyList[j] == i)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    processes[i].currentPriority = processes[i].priority + 1;
                    readyList.push_back(i);
                }
            }
        }
        if (!readyList.empty())
        {
            int index_current = -1;
            int processIndex = -1;
            int maxPriority = -1;
            for (int i = 0; i < readyList.size(); i++)
            {
                if (processes[readyList[i]].currentPriority > maxPriority)
                {
                    maxPriority = processes[readyList[i]].currentPriority;
                    index_current = i;
                }
            }
            for (int i = 0; i < readyList.size(); i++)
            {
                if (processes[readyList[i]].currentPriority == maxPriority)
                {
                    index_current = i;
                    break;
                }
            }
            processIndex = readyList[index_current];
            readyList.erase(readyList.begin() + index_current);
            int time_running = quantum;
            for (int i = 0; i < readyList.size(); i++)
            {
                processes[readyList[i]].currentPriority += 1;
            }
            for (int t = 0; t < time_running; t++)
            {
                if (t + time >= maxSeconds)
                {
                    processesCompleted++;
                    break;
                    ;
                }
                *(processesPrintingArray + processIndex * maxSeconds + time) = '*';
                for (int p = 0; p < numberOfProcesses; p++)
                {
                    if (p != processIndex && processes[p].arrivalTime <= time)
                        *(processesPrintingArray + processes[p].id * maxSeconds + time) = '.';
                }
                        }
            time += time_running;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (processes[i].arrivalTime == time)
                {
                    processes[i].currentPriority = processes[i].priority + 1;
                    readyList.push_back(i);
                }
            }
            processes[processIndex].currentPriority = processes[processIndex].priority;
            readyList.push_back(processIndex);
        }
        else
        {
            time++;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (processes[i].arrivalTime == time)
                {
                    processes[i].currentPriority = processes[i].priority + 1;
                    readyList.push_back(i);
                }
            }
        }
    }
}

void Scheduler::printTracing()
{
    for (int process = 0; process < numberOfProcesses; process++)
    {
        cout << processes[process].processName << "     |";
        for (int time = 0; time < maxSeconds; time++)
            cout << *(processesPrintingArray + process * maxSeconds + time) << '|';
        cout << " \n";
        ;
    }
}
void Scheduler::printStats()
{
    float sum, mean, sum2;
    cout << "Process    |";
    for (int i = 0; i < numberOfProcesses; i++)
        cout << "  " << processes[i].processName << "  |";
    cout << endl;
    cout << "Arrival    |";
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].arrivalTime < 10)
            cout << "  " << processes[i].arrivalTime << "  |";
        else
            cout << " " << processes[i].arrivalTime << "  |";
    }
    cout << endl;
    cout << "Service    |";
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].arrivalTime < 10)
            cout << "  " << processes[i].serveTime << "  |";
        else
            cout << " " << processes[i].serveTime << "  |";
    }
    cout << " Mean|" << endl;
    cout << "Finish     |";
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].finishTime >= 10)
            cout << " " << processes[i].finishTime << "  |";
        else
            cout << "  " << processes[i].finishTime << "  |";
    }
    cout << "-----|" << endl;
    cout << "Turnaround |";
    for (int i = 0; i < numberOfProcesses; i++)
    {

        if (processes[i].turnAroundTime >= 10)
            cout << " " << (int)processes[i].turnAroundTime << "  |";
        else
            cout << "  " << (int)processes[i].turnAroundTime << "  |";
        sum += processes[i].turnAroundTime;
    }
    cout << fixed;
    cout << setprecision(2);
    mean = (sum * 1.0) / numberOfProcesses;
    if (mean >= 10)
        cout << mean << "|";
    else
        cout << " " << mean << "|";
    cout << endl;
    cout << "NormTurn   |";
    sum2 = 0;
    for (int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].NormTurnTime > 10)
            cout << processes[i].NormTurnTime << "|";
        else
            cout << " " << processes[i].NormTurnTime << "|";
        sum2 += (processes[i].NormTurnTime * 1.0);
    }

    mean = (sum2 * 1.0) / numberOfProcesses;
    if (mean > 10)
        cout << mean << "|";
    else
        cout << " " << mean << "|";
    cout << endl;
}
void Scheduler::clearTables()
{

    for (int i = 0; i < numberOfProcesses; i++)
    {
        for (int j = 0; j < maxSeconds; j++)
            *(processesPrintingArray + i * maxSeconds + j) = ' ';
    }
    for (int i = 0; i < numberOfProcesses; i++)
    {
        processes[i].finishTime = 0;
        processes[i].turnAroundTime = 0;
        processes[i].NormTurnTime = 0;
        processes[i].processState = ' ';
        processes[i].remainingTime = processes[i].serveTime;
    }
    processorBusy = false;
    while (!readyQueue.empty())
        readyQueue.pop();
    while (!readyPriorityQueue.empty())
        readyPriorityQueue.pop();
}
void Scheduler::splitPolicyAndParameter(string str)
{
    string w = "";
    pair<int, int> policies;
    bool parameterExists = false;
    policies.second = -1;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '-')
        {
            parameterExists = true;
            policies.first = stoi(w);
            w = "";
        }
        else if (str[i] == ',')
        {
            if (parameterExists)
                policies.second = stoi(w);
            else
            {
                policies.first = stoi(w);
                policies.second = -1;
            }
            w = "";
            schedulongPoliceis.push_back(policies);
            parameterExists = false;
        }
        else
            w = w + str[i];
    }
    if (parameterExists)
        policies.second = stoi(w);
    else
        policies.first = stoi(w);
    schedulongPoliceis.push_back(policies);
}
void Scheduler::splitPrcoessAndTimes(string str, int id)
{
    Process process;
    string w = "";
    process.processName = str[0];
    for (int i = 2; i < str.length(); i++)
    {
        if (str[i] == ',')
        {
            process.arrivalTime = stoi(w);
            w = "";
        }
        else
            w = w + str[i];
    }
    processorBusy = false;
    process.processState = ' ';
    if (schedulongPoliceis[0].first == 8)
    {
        process.priority = stoi(w);
        process.currentPriority = stoi(w);
    }
    else
        process.serveTime = stoi(w);
    process.remainingTime = process.serveTime;
    process.waitingTime = 0;
    process.id = id;
    processes.push_back(process);
}
void Scheduler::readFile()
{
    processorBusy = false;
    string temp1, temp2;
    cin >> type;
    cin >> temp1;
    splitPolicyAndParameter(temp1);
    cin >> maxSeconds;
    cin >> numberOfProcesses;

    for (int i = 0; i < numberOfProcesses; i++)
    {
        cin >> temp2;
        splitPrcoessAndTimes(temp2, i);
    }
    processesPrintingArray = new char[numberOfProcesses * maxSeconds];
    currentProcess.processName = 0;
    currentProcess.q = 0;
    clearTables();
}
void Scheduler::printHeader()
{
    for (int i = 0; i < maxSeconds + 1; i++)
        cout << i % 10 << ' ';
    cout << "\n";
    printDashes();
}
void Scheduler::printDashes()
{
    cout << "------------------------------------------------";
}
int main(void)
{
    Scheduler scheduler;
    scheduler.readFile();
    scheduler.execute();
    return 0;
}