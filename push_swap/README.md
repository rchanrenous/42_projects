# Push_swap

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
- verify the validity of the output instructions

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

The following command will generate a random input list of integers in the specified range (here, the set of integers between 1 and 10):
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

## Sorting algorithm

The sorting problem introduced in this project is quite atypical compared to classical sorting problems using lists for instance.

In this last section we present our solution and discuss it.

The problem introduced above focuses on the number of operations it takes the algorithm to sort the integers using the stacks. In particular, the running time of the algorithm to output the sorting instructions is irrelevant in this project, though it is of course fundamental in practice.

There are two steps in the algorithm.

First all the elements will be pushed to stack b in a particular way. Second, the elements are inserted back in  a building on the pattern of the elements in stack b obtained in the first step.

### Step 1: gathering the elements in batches in stack b

The algorithm uses stack b to prepare the elements to be pushed back to stack a as a sorted list.
The key idea of the algorithm is to gather the elements in batches by their value in stack b, so that close values will be close in position in stack b. That way, when the values will be inserted back into stack a at their correct position, there will be less operations to perform since the values are close.

To create the batches, the algorithm starts finding the median value in stack a, then pushes all the elements lesser than that value from stack a to stack b. When there are no more values lesser than the median, the process is repeated until there are no more values in stack a: the median is re-computed with the remaining values in stack a at each step.  

### Step 2: inserting the elements back in stack a
At this point of the algorithm, the values are gathered in batches of values in stack b. The sizes of the batches are powers of 2. 

Next, the values are inserted back in stack a, by order of number of operations to insert the value in stack a. Two factors are taken into account:
- the number of operations the get the value at the top of stack b
- the number of operations to get the minorant of the value among the elements already inserted in stack a

The fact that elements are gathered in batches in step 1 limits the number of operations to insert consecutive values: once a value is inserted, the values at the top and/or bottom of stack b are close to that value, unless it was the last value from its batch. In case there are no values left in stack b from the previous batch, the next value batch will be at the top and/or bottom of stack b, and the insertion of the next value will be guided by the ordering of the batches.

The batch structure defined in step 1 is crucial to an efficient insertion of the elements back into stack a.

### Complexity of the algorithm

Common complexity measures of an algorithm include the worst-case complexity. In this project we are interested in the number of instructions and time to output the set of stack instructions. The number of value comparisons will be the reference for the latter measure.

We only show in this study that the algorithm's worst-case complexity is at least O(n²) in terms of stack instructions and execution time.

We identify at the end of the section how the analysis could be fine-grained, and possible areas of improvement for the algorithm.

Let *n* be the number of integers to be sorted in an instance of the *push_swap* problem.

**Step 1**:
- Finding a median among *n* values in stack a is in O(n²): finding each value's rank is in O(n) and there are *n* values to rank.
- Once the median is computed, it suffices to pass through the stack only once, using `ra` instructions, to push the elements smaller than the median to stack b; this process requires *n* comparisons and *n* stack instructions
- Notice that the algorithm minimizes the number of stack instructions, by passing through the full stack at each element inspection to find the shortest way to get the element at the top of the stack if necessary (either the natural rotate order or the inverted); the time complexity is still in O(n²) and the number of stack instructions still in O(n) but with a smaller number of instructions in practice

Overall the complexity of step 1 is the sum of the successive batch gathering processes as the number of elements in stack a decreases. There are log2(n) batches. Pushing the elements from the largest batch being computationally heavier and requiring more stack instructions when the number of elements is higher, the complexity of step 1 can be upper-bounded by O(log2(n) n²) in terms of execution time and O(log2(n) n) stack instructions.

However, ranking the values to find the median could probably be done differently since it is independent of the stack data structure constraint. One could use auxiliary data structures and perform a merge sort to complete this step, resulting in a O(log(n)² n) time complexity instead, and also an extra memory use.

**Step 2**:

Let us observe that any element in stack b requires O(n) comparisons and stack instructions to get inserted back on top of the its minorant in stack a.

Indeed, any element needs at most n `rotate` instructions in stack a and b to get the element at the top of stack b, and its minorant at top of stack a. Similarly, finding the minorant in stack a takes O(n) comparisons by doing a simple pass on stack a. Therefore the insertion phase can be done in O(n²) both in number of comparisons and stack instructions.

The complete complexity analysis of step 2 is quite tedious. The advantageous batch structure of the elements at the end of step 1 is a strong asset when inserting back the elements in stack a. We defer such analysis to further work.

**Conclusion**:

Putting the complexity analyses from step 1 and step 2 together, yields a O(log2(n) n²) worst-case time complexity and O(n²) stack instructions.
We believe it possible to close the gap between the worst-case complexity of the number of instructions of step 2 and that of step 1 (O(log2(n) n) for step 1 and O(n²) for step 2 currently).

In the absence of the complete analysis of the algorithm when using the successive medians to form the batches, we can only mention other strategies to fix the batch sizes. Further work could explore using a fixed number of batches, or try other strategies depending on the integer list size.