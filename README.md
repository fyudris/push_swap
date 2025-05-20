# PUSH_SWAP

## The Rules
You have 2 stacks named `a` and `b`.
- At the beginning:
	- The stack `a` contains a random number of unique negative and/or positive integers.
	- The stack `b` is empty.
- The goal is to sort the numbers in stack `a` in ascending order.
- To achieve this, you have the following operations at your disposal:
  - `sa (swap a)`: Swap the first 2 elements at the top of stack `a`. Do nothing if there is only one element or none.
  - `sb (swap b)`: Swap the first 2 elements at the top of stack `b`. Do nothing if there is only one element or none.
  - `ss` : `sa` and `sb` at the same time.
  - `pa (push a)`: Take the first element at the top of `b` and put it at the top of `a`. Do nothing if b is empty.
  - `pb (push b)`: Take the first element at the top of `a` and put it at the top of `b`. Do nothing if a is empty.
  - `ra (rotate a)`: Shift up all elements of stack `a` by 1. The first element becomes the last one.
  - `rb (rotate b)`: Shift up all elements of stack `b` by 1. The first element becomes the last one.
  - `rr` : `ra` and `rb` at the same time.
  - `rra (reverse rotate a)`: Shift down all elements of stack `a` by 1. The last element becomes the first one.
  - `rrb (reverse rotate b)`: Shift down all elements of stack `b` by 1. The last element becomes the first one.
  - `rrr` : `rra` and `rrb` at the same time.


Our program should output the list of operations that it has done:

```
$ ./push_swap 2 1 3 6 5 8
sa
pb
pb
pb
sa
pa
pa
pa

$ ./push_swap 0 one 2 3
Error
```

## Benchmark

You must perform certain sorts with a minimal number of oper-
ations:
- For maximum project validation (100%) and eligibility for bonuses, you must:
	- Sort 100 random numbers in fewer than 700 operations.
	- Sort 500 random numbers in no more than 5500 operations.
- For minimal project validation (which implies a minimum grade of 80%), you can succeed with different averages:
  - 100 numbers in under 1100 operations and 500 numbers in under 8500 operations
  - 100 numbers in under 700 operations and 500 numbers in under 11500 operations
  - 100 numbers in under 1300 operations and 500 numbers in under 5500 operations

Return `n` size of instructions for sorting `x` random number of values:
- If `x = 3` then `n < 3`
- If `x = 5` then `n < 12`
- If `x = 100` then `n < 1500`


According to binary checker, run:
```
$ ARG="<100 random values>"; ./push_swap $ARG | ./checker_OS $ARG
```
and replace the placeholder by 100 random valid values.

Points will be given in accordance:
- less than 700: 5
- less than 900: 4
- less than 1100: 3
- less than 1300: 2
- less than 1500: 1

## Project Plan
- [ ] Implement the stack and its initialization
- [ ] Implement swap (`sa`, `sb`, `ss`), rotate (`ra`, `rb`, `rr`), reverse rotate (`rra`, `rrb`, `rrr`), and push (`pa`, `pb`)
- [ ] Choose a sorting algorithm
- [ ] Create pseudo code
- [ ] Implement pseudo code
- [ ] Test with a checker (provided)


## Implementing The Project

### 1. Stack & Double Linked List
#### What is a Stack?
- A stack of object piled on top of each other
- Has a top / `head` and a bottom / `tail`
- Our stack will be implemented as a `double linked list`
- Our `nodes` will contain:
  ```
  Node = {
	Value : 42		//saved value (type int)
	Index : 4		//position in the stack
	Pointers:	*next
			*previous
  }
  ```
### 2. The Turk Algorithm
- Push the nodes from stack `a` to stack `b` until there are only three nodes left in the stack `a`.
- During each push, `b` is sorted in `descending order`.

Step-by-step:
- Push the first two `a` nodes to `b` without checking anything.
  - Now we have the current `min` and `max` number in `b`.
- Now we look for a `target` node:
  - Every `a` node needs a `target` node in `b`.
    - A `target` node is the `closest smaller` number to the current `a` node.
  - If no `closest smaller` number is found, then the `target` node is the `max` value in `b`.
- After configuring all `target` nodes for each node in `a`, we can run a `cost analysis` to determine which node with `minimum cost` to be pushed to `b`:
  - Formula to find the `cheapest` node to push:
	```
	Sum:
		x operation to bring `a` on top
	+	x operation to bring `a`-> target node on top
	--------------------------------------------------------
	=	push cost
	```
- Keep pushing until we have three nodes left in `a`.
- **Sort Three**:
  - TODO
- Push back to stack `b`:
  - Every `b` node has a `target` / `closest bigger` `a` node
  - If a `closest bigger` `a` node not found, then the target node is the `min` value in `a`
  - Determining when to do `rotate` or `reverse-rotate` with the help of the `median` value:
  - If target node above `median`, do `ra()`.
  - If below, do `rra()`

### 3. Pseudo **Code**
```
// Declare pointers to the two data structures (double linked list), one for stack `a` and one for stack `b`
	// Set both pointers to NULL to avoid undefined behaviour and indicate we're starting with empty stacks

// Handle input count errors. Argument count must be 2 or more, and the second input must not be empty.
	// If input errors return "ERROR" followed by a "\n"

// Handle both case of input, whether a variable number of command arguments, or as a string
	// If the input of numbers is a string, call `split()` to split the substrings.

// Initialize stack `a` by appending each input number as a node to stack `a`
	// Handle integer overflow, duplicates, and syntax errors, e.g. input must only contain digits, or `-`, `+` signs
		// If errors found, free stack `a` and return error
	// Check for each input, if it is a long integer
		// If the input is a string, convert it to a long integer
	// Append the nodes to stack `a`

// Check if stack `a` is sorted
	// If not sorted, implemement our sorting algorithm
		// Check for 2 numbers
			// If so, simply swap the numbers.
		// Check for 3 numbers
			// If so, implememnt our simple `sort three` algorithm
		// Check if the stack has more than 3 numbers
```

### 4. Basic Utility Functions
- [ ] Functions to hanlde errors
- [ ] Operations
- [ ] Stack length
- [ ] Last node
- [ ] Min and Max node

### 5. Data Structure
```
typedef struct s_stack_node
{
	int				nbr;
	int				index;
	int				push_cost;
	bool				above_median;
	bool				**cheapest**;

	struct s_stack_node		*target_node;
	struct s_stack_node		*next;
	struct s_stack_node		*prev;
}	t_stack_node;
```

## How to Test

### 1. Test using provided checker
```
ARG="5 -3 42"; ./push_swap $ARG | ./checker_linux $ARG
```
./push_swap ""             # Should output Error
./push_swap "2" "1" "2"    # Should output Error (duplicate)
./push_swap "2147483648"   # Should output Error (too big)
./push_swap "-2147483649"  # Should output Error (too small)
./push_swap "2a"           # Should output Error (invalid integer)
