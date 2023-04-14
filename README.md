# CPU Usage Tracker

## COMPLETED PART

### Please run "setterm -linewrap off" command before running the code. Because I tried to implement a progression bar but it moves if linewrap is not set off.

Program has 5 threads except main threads. These are: 
1) Reader,which read "proc/stats",
2) Analyzer,which operates analytical calculations,
3) Printer,which prints the output,
4) Watchdog, which tries to detect if any deadlock is happening
5) Logger ,which records the CUT data in txt file.
6) Unit test for testing the correctness of array_comp function is added.


* Also this program contains a sigterm handler function. To close the program properly and relase the heap memory.

## Will add later

1) The program doesn't contain enough condition variables yet. I will implement it to increase efficiency.

2) I will add more useful data to logger text. So far it just add cpu usage values.
