# minishell

Submitted on 14 October 2023 (100%)

Minishell is literally you create your own version of bash.
In 42 Minishell you only need to handle the operator of 
- ">" left redirection 
- ">>" double left redirection
- "<" right redirection
- "<<" double right redirection (special case of heredoc)
- "|" pipe

Buildins that you have to handle
- EXIT -> to exit from the minishell (no argument)
- UNSET -> to remove one variable in ENV (with agruments ex. `unset PATH`)
- EXPORT -> to add one varibale in ENV (with agruments ex. export `PATH=ls`)
- ENV -> to show the all the ENV Variable (no argument)
- CD -> to move to another directory (with agruments ex. `cd /bin/ls`)
- PWD -> to see your current directory (no argument)
- ECHO -> to diplay a line of text that is passed as argumen in ECHO (with agruments ex. `echo hello`)

The leaks.sh file is a command to check your leak only in valgrind
(NOTE : The leaks only suppresed the leaks from readline)
how to use the `leaks.sh`
- start your valgrind
- use `make` to compile your program
- then call the leaks `./leaks.sh`
- it will run your program inside of the valgrind
- type any command to try

example of command you can try
```
echo hello > a | ls | wc -l
ls | wc -l | "echo" "hello"
```
