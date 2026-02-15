Dane Backbier, dbackbie@u.rochester.edu, CSC 173, Project 1

Project 1 is aimed at implementing DFAs and NFAs through code and using examples. Also, to understand and implement  the
subset construction algorithm to convert NFAs to DFAs to speed up the execution of NFAs.

// Build instructions
- Open command prompt or similar
- cd "Project_1 PATH" (PATH can easily be found by right-clicking in file explorer and selecting copy PATH)
- execute: gcc -std=c11 -Wall -Werror -o Project_1 *.c

// Run instructions
- execute: Project_1.exe (this is for command prompt, if in PowerShell, do ./Project_1.exe)

REPL is of the form:
Testing "some NFA/DFA"
Enter inputs then input 'Q' when done.
'input'
The input is accepted/ rejected by the NFA/DFA
etc.

The final NFA to DFA conversion shouldn't take very long (at most a minute or two though I've had it run in seconds
depends on your computer's processing power)