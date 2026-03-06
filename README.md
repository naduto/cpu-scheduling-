# cpu-scheduling

## Overview

This project implements a CPU Scheduling Simulator in C/C++ for the Operating Systems course at Alexandria University – Faculty of Engineering.

The program analyzes and visualizes different CPU scheduling algorithms. It reads process information from stdin, simulates the scheduling policy, and prints either:

- Trace output showing how processes execute over time, or

- Statistics output summarizing scheduling performance.

The program follows the exact input/output format required for automatic grading.

Implemented Scheduling Algorithms

The simulator supports the following policies:

	- First Come First Serve (FCFS)
	- Round Robin (RR)
	- Shortest Process Next (SPN)
	- Shortest Remaining Time (SRT)
	- Highest Response Ratio Next (HRRN)
	- Feedback Queue (FB-1)
	- Feedback Queue (FB-2i)
	- Aging

Notes
- Round Robin requires a quantum parameter q.
- Aging also uses a quantum parameter.

## Input Format

The program reads input from stdin.

Line 1

- Mode of execution:``` trace ```or``` stats ```

- trace → visual timeline of process execution
- stats → scheduling statistics

Line 2

- Comma-separated scheduling policies.

Example:

```1,2-4,3```

Meaning:

- FCFS
- Round Robin (q=4)
- SPN

Line 3

```Last simulation time```

Example:
``` 20 ```

Line 4

``` Number of processes ```

Example: ``` 3 ```

Line 5+

``` Process description ```

For algorithms 1–7:

``` ProcessName,ArrivalTime,ServiceTime ```

Example:
```
A,0,3
B,2,6
C,4,4
```

For Aging (Algorithm 8):

``` ProcessName,ArrivalTime,Priority ```

## Output Format

The output is printed to stdout.

Trace Mode :

``` * ``` → process is executing

``` . ``` → process is waiting in the ready queue

Example:

```
time → 0123456789
A     ***.....
B     ..****..
C     ....****
```

Stats Mode

Displays scheduling statistics such as:

- Waiting time
- Turnaround time
- Completion time

The format must exactly match the provided test cases.

## Compilation

A Makefile is provided.

Compile the program using: ``` make ```

This will generate the executable: ``` scheduling ```

## Running the Program

Use input redirection:

``` ./scheduling < input.txt ```

or

``` cat input.txt | ./scheduling ```

## Testing With Provided Test Cases

You can compare your output with the expected output using:

``` cat 01a-input.txt | ./scheduling | diff 01a-output.txt - ```

If there is no output from diff, the test case passed.

## Docker

A Dockerfile is provided to build a lightweight image for the project.

Build Image
``` docker build -t cpu-scheduler . ```

Run Container
``` docker run -i cpu-scheduler < input.txt ```

## Project Structure
```
.
├── scheduling.cpp
├── scheduling.h
├── Makefile
├── Dockerfile
├── README.md
├── run_tests.sh
└── testcases/
```