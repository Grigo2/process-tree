# process-tree
Code written in C language using Linux system functions (execl and sigaction structure).
## Description
A program that creates new processes that wait for the signal to end (SIGINT). Each new procces create his own procces group and if is possible divide argv[1] value and create two procces by execl. The SIGINT signal starts propagation from the main process.

## Example 
enter 'abcd' as a argument

![clinux](https://user-images.githubusercontent.com/50334581/57586159-023d7300-74f2-11e9-95ea-476aaa656bbb.PNG)


## How to run
compile source file using gcc by console:
```
>> gcc main.c
```

run program and enter a custom string as a program argument (default program name is "a.out"):
```
>> ./a.out abcd
```

#### System functions using in code:
* fork
* execl
* kill
* stop
* wait
* getpid

##### _Author Grzegorz Rocławski_
