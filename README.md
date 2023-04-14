# CPU Usage Tracker

## COMPLETED PART

Please run "setterm -linewrap off" command before running the code. Because I tried to implement a progression bar but it moves if linewrap is not set off.

Program has 5 threads except main threads. These are: 
1) Reader,which read "proc/stats",
2) Analyzer,which operates analytical calculations,
3) Printer,which prints the output,
4) Watchdog, which tries to detect if any deadlock is happening
5) Logger ,which records the CUT data in txt file.

Also this program contains a sigterm handler function. To close the program properly and relase the heap memory.

## Will add later

The program doesn't contains enough condition variables yet. I will implement it to increase efficiency.
I will add some assert() functions to implement unit test. So far I didn't add it because I tried to check each output of any function using if condition.
I will add more useful data to logger text. So far it just add cpu usage values.
