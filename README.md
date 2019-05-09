# Execl-and-sigaction-structure 
Code written in C language using Linux system functions.
## Description
A program that creates new processes that wait for the signal to end. Each new procces create his own procces group.
The signal starts propagation from the stem process.

## How to run
compile source file using gcc by console:
```
>> gcc main.c
```

run program and enter a custom string as a program argument (default program name is "a.out"):
```
>> ./a.out test
```

#### System functions using in code:
* fork
* execl
* kill
* stop
* wait

##### _Author Grzegorz Rocławski_
