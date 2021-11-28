# Binary-Process-Tree

This 
program take a single command line argument, which is the depth of the tree, and 
each process take an integer value that shows its  traversal position at each level. 
If the user enters the value of 3 as the depth value, then this program construct a binary 
tree of processes with the following hierarchy: 

<img width="767" alt="Screen Shot 2021-11-28 at 05 37 57" src="https://user-images.githubusercontent.com/46750371/143726711-d10b27de-a746-4c7a-9e39-01ca64d8bbb2.png">


The steps of the program as follows: 
 Each  process  in  the  program   print  its  own  position  with  its  pid  and  parent  pid 
values. 
 When a process creates a new process, the  parent process print its position, its 
own pid and the pid of the newly created child process (as left child or right child). 
 When a child exits from the system, it return its  traversal id  to  the parent. This 
value obtained by the parent. Then, the parent  print the child (left or 
right child), the child pid and the exit status of the child process. 

Example Output

<img width="468" alt="Screen Shot 2021-11-28 at 05 39 48" src="https://user-images.githubusercontent.com/46750371/143726745-1438d71a-c7be-4d18-80d2-725ce52b8c75.png">
