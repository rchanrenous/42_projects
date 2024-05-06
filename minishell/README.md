# Minishell

## Description

Minishell is a shell program. This project aims at getting familiar with unix-based systems and understand how shell commands work.

In particular, it required understanding how the commands are parsed and interpreted, and how programs are launched.

Minishell's behavior is based on Bash behavior.

Key features include:
- parsing the commands, ie. reading the input, dealing with the environment variables, interpret single- and double-quotes strings
- handling basic signals such as `SINGINT` and `SIGKILL`
- run programs, wait for children processes to end
- manage environment variables
- handle pipes and redirections
- manage a command history
- built-in function implementations: `echo` and `-n` option, `cd`, `pwd`, `exit`  

The project is entirely coded in C language with limited standard library function usage, and uses a Makefile to build the program.

Special care is given to program error management and avoiding memory leaks at all times.

## Requirements

Following packages:
- gcc
- git
- libreadline-dev
- make

## Usage

The program can either be built locally or run in a Docker container.

### Build locally

First, install the packages from the requirements section, then build the project:
```
git clone https://github.com/rchanrenous/minishell.git minishell
cd minishell
make
```

Next, run the program:
```
./minishell
```

### Use the Docker container

Build locally the Docker image running:
```
docker build -t minishell .
```
or directly pull from DockerHub the image:
```
docker pull rchanrenous/minishell:latest
```
Run the program in the container:
```
docker run -d -ti minishell --name docker_minishell # run the container in detached mode
docker exec -ti docker_minishell bash # open a terminal in the container
./minishell # run the program
```

### Examples

Finally, have fun trying out shell commands!
```
echo 'Hello World!'
pwd
cd src
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
