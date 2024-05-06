# Minishell

## Description

Minishell is a shell program. This project aims at getting familiar with unix-based systems and understand how shell commands work.
In particular, it required understanding how the commands are parsed and interpreted, and how programs are launched. 

Key features include:
- parsing the commands, ie. reading the input, dealing with the environment variables, interpret single- and double-quotes strings
- handling basic signals such as SINGINT and SIGKILL
- run programs, wait for children processes to end
- manage environment variables
- handle pipes and redirections

The project is entirely coded in C language with limited standard library function usage, and uses a Makefile to build the program.

## Requirements

Following packages:
- gcc
- git
- libreadline-dev
- make

## Usage

First, build the project
```
git clone https://github.com/rchanrenous/minishell.git minishell
cd minishell
make
```

Next, run the program
```
./minishell
```

Finally, have fun trying out shell commands!
```
echo 'Hello World!'
pwd
cd srcs
export var1=FOO var2=BAR
echo "$var1 $var2"
unset var1 var2
echo "$var1 $var2"
grep << END HELLO > tmp
cat Makefile | grep minishell
./minishell
ls >> tmp
cat < Makefile >> tmp
make clean
exit
cat | cat | ls
exit
```
