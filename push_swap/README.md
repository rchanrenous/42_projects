# Push_swap

![so_long_gameplay1](img/so_long_gameplay1.png)

## Description

Push_swap is a sorting algorithm project. In this problem, the user is provided two stacks with a set of possible actions, and has to sort a list of integers using the stacks with the fewest number of stack actions.

There are two stacks, stack a and stack b. At the beginning, stack a is filled with the input list of integers.

The only possible operations on the stacks are:
- `sa` (swap a): swap the first 2 elements at the top of stack a; do nothing if there is only one or no elements
- `sb` (swap b): swap the first 2 elements at the top of stack b; do nothing if there is only one or no elements
- `ss` (swap both): `sa` and `sb` at the same time
- `pa` (push a): take the first element at the top of b and put it at the top of a; do nothing if b is empty
- `pb` (push b): take the first element at the top of a and put it at the top of b; do nothing if a is empty
- `ra` (rotate a): shift up all elements of stack a by 1; the first element becomes the last one
- `rb` (rotate b): shift up all elements of stack b by 1; the first element becomes the last one
- `rr` (rotate both): `ra` and `rb` at the same time
- `rra` (reverse rotate a): shift down all elements of stack a by 1; the last element becomes the first one
- `rrb` (reverse rotate b): shift down all elements of stack b by 1; the last element becomes the first one
- `rrr` (reverse rotate both): `rra` and `rrb` at the same time

The program should output a correct list of operations to perform on the stacks to get the sorted list of integers in stack a.

In addition to coding such a sorting program, a checker program also needs to be coded to ensure the input list of integers is sorted after the output operations of the sorting program.

Key features include:
- parsing the input list of integers, checking there are no duplicates
- implement the stack data structures and associated operations
- implement the sorting algorithm

The project is entirely coded in C language with limited standard library function usage, and uses a Makefile to build the program.

Special care is given to program error management and avoiding memory leaks at all times.

The project is implemented according to Ecole 42's code norm: https://github.com/42School/norminette/tree/a9e1a3dde004b4f997194b3594292a7ee6eb49b3.



## Requirements

Following packages:
- gcc
- git
- make

## Build the project

The program can either be built locally using the source files or run in a Docker container.

### Build locally

First, install the packages from the requirements section, then build the project:
```
git clone https://github.com/rchanrenous/42_projects.git 42_projects
cd push_swap
make
```

### Use the Docker container

First, install and run Docker.

Run the container by building locally the Docker image:
```
docker build -t push_swap .
docker run -d -ti push_swap
```
or by pulling the image from DockerHub:
```
docker pull rchanrenous/push_swap:latest
docker run -d -ti rchanrenous/push_swap:latest
```
Open a bash terminal in the container:
```
docker run -d -ti --name docker_push_swap # run the container in detached mode
docker exec -ti docker_push_swap bash # open a terminal in the container
```
Then you can type in the terminal the command to launch the program (see Usage section).

When finished, stop the container:
```
docker stop docker_push_swap
docker rm docker_push_swap
```

## Usage

The program takes a list of integer values as arguments. There must not be any duplicate values in the list (it results in an error otherwise).

Here is a sample command to run the program:
```
./push_swap 1 4 6 5 2 3
```

The checker program reads from the standard input the instructions, and requires the same input list of integers as the `push_swap` program:
```
./push_swap 1 4 6 5 2 3 | ./checker 1 4 6 5 2 3
```

The following command will generate random an input list of integers in the specified range (here, the set of integers between 1 and 10):
```
ARG=$(ruby -e "puts (1..10).to_a.shuffle.join(' ')")
```

Combining the the commands:
```
ARG=$(ruby -e "puts (1..10).to_a.shuffle.join(' ')")
./push_swap $ARG
./push_swap $ARG | ./checker $ARG
```

And the number of instructions to sort the integers can be counted as follow:
```
./push_swap $ARG | wc -l
```

### Examples


```
./so_long maps/map.ber
./so_long maps/map2.ber
./so_long maps/map3.ber
```
![so_long_gameplay2](img/so_long_gameplay2.png)
![so_long_gameplay3](img/so_long_gameplay3.png)


## Sorting algorithm

The sorting problem introduced in this project is quite atypical compared to classical sorting problems using lists for instance.

In this last section we present our solution and discuss it.

The problem introduced above focuses on the number of operations it takes the algorithm to sort the integers using the stacks. In particular, the running time of the algorithm to output the sorting instructions is irrelevant in this project, though it is of course fundamental in practice.

There are two steps in the algorithm.

First all the elements will be pushed to stack b, in such a way that the insertion of the elements back in stack a will be eased.

### Step 1: gathering the elements in batches in stack b
The algorithm uses stack b to prepare the elements to be pushed back to stack a as a sorted list.
The key idea of the algorithm is to gather the elements in batches by their value in stack b, so that close values will be close in position in stack b. That way, when the values will be inserted back into stack a, there will be less operations to perform since the values are close.

To create the batches, the algorithm starts finding the median value in stack a, then pushes all the elements lesser than that value from stack a to stack b. When there are no more values lesser than the median, the process is repeated until there are no more values in stack a: the median is re-computed with the remaining values in stack a at each step.  

### Step 2: inserting the elements back in stack a
At this point of the algorithm, the values are gathered in batches of values in stack b. The sizes of the batches are powers of 2. 

Next, the values are inserted back in stack a, by order of number of operations to insert the value in stack a. Two factors are taken into account:
- the number of operations the get the value at the top of stack b
- the number of operations to get the minorant of the value among the elements already inserted in stack a

The fact that elements are gathered in batches in step 1 limits the number of operations to insert consecutive values: once a value is inserted, the values at the top and/or bottom of stack b are close to that value, unless it was the last value from its batch. In case there are no values left in stack b from the previous batch, the next value batch will be at the top and/or bottom of stack b, and the insertion of the next value will be guided by the batches.

The batch structure defined in step 1 is crucial to an effecient insertion of the elements back to stack a.

### Discussion

A few remarks are in order.

#### Complexity of the algorithm

Recall we are interested most in the number of instructions it takes to sort the list of integers, not the time complexity of finding the list of instructions.

Common complexity measure of an algorithm include the worst-case time complexity.

We propose a worst-case complexity study of the number of instructions and time to elaborate the set of stack instructions. The number of value comparisons will be the reference for the latter measure.

This study is naive in that, a deeper analysis could probably lead to a tighter complexity upper-bound. Such analysis could better use the batch structure during the insertion step analysis for instance.

Let *n* be the number of integers to sort in an instance of the *push_swap* problem.

**Step 1**:
- Finding a median among *n* values in stack a is in O(n²): finding each value's rank is in O(n) and there are *n* values to rank.
- Pushing the elements smaller than the median is in O(n²): stack a is passed through to examine what elements should be pushed to stack b; any encountered element requires at most n/2 `ra` or `rra` operations and there n/2 such elements to push. The time complexity to achieve this process is in O(n²), the only difference being that the algorithm requires testing which order is best to minimize the number of `rotate` instructions (reverse order or not).

Overall the complexity of step 1 is the sum of the successive batch gathering processes as the number of elements in stack a descreases. There are log2(n) batches. Pushing the elements from the largest batch being computationally heavier and requiring more stack instructions when the number of elements is higher, the complexity of step 1 can be upper-bounded by O(n²).

**Step 2**:

First let us observe that any element in stack b requires O(n) comparisons and stack instructions to get inserted back on top of the its majorant in stack a. Indeed, any element needs at most n `rotate` instructions in stack a and b to get the element at the top of stack b, and its majorant at top of stack a. Similarly, finding the majorant in stack a takes O(n) comparisons by doing a simple pass on stack a. Therefore the insertion phase can be done in O(n²) both in number of comparisons and stack instructions.

The complete complexity analysis of step 2 is quite tedious and we will only give a few insghts about it.

Despite the advantageous batch structure of the elements in batch b, it seems that the worst-case scenario still incurs O(n²) stack operations and comparisons.

Let us explain why:
- once the elements are gathered in batches in stack b, the element on top of stack b - which is the biggest value by design - can be inserted at constant cost (1 `push` instruction)
- then, the batch with the next greatest values is on top of stack b and no matter the ordering of the batch, both values will be inserted in exactly 1 and at most 2 stack instruction/comparisons; any element coming from the bottom of the stack will take at least 2 operations to get inserted (any value at the bottom is smaller than the elements in stack a)
- at this point, there are 3 values in stack a (the 2 last values being either both at top, or one at the bottom and one at the top) and the next batch of values is on top of stack b; by design, the majorant of the element at the top of stack b is one of these 2 values and it will require at most 1 `rotate` instruction to get its majorant at the top of stack a; the majorant of any of the elements in the current batch in stack b can be be either the elements of the preivous batch of 2 elements or the first element from the current batch just inserted 
- next, the batch that comes second in increasing size (it has 2 elements) and comes second in decreasing element values is on top of stack b; any element can be insert 










#### Choice of the batch sizes

