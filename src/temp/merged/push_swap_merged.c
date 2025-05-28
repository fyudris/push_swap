
#include "../includes/push_swap.h"

/**
 * Checks for syntax error
 * @return 0 for success, 1 for error
 */
int	is_error_syntax(char *str)
{
	if (!(*str == '+' || *str == '-' || ft_isdigit(*str)))
		return (1);
	if ((*str == '+' || *str == '-') && !ft_isdigit(str[1]))
		return (1);
	while (*++str)
	{
		if (!ft_isdigit(*str))
			return (1);
	}
	return (0);

	// int	i;

	// if (!str || !*str)
	// 	return (1);
	// i = 0;
	// if (str[i] == '+' || str[i] == '-')
	// 	i++;
	// if (!str[i])
	// 	return (1);
	// while (str[i])
	// {
	// 	if (!ft_isdigit(str[i]))
	// 		return (1);
	// 	i++;
	// }
	// return (0);
}

/**
 * Checks for duplicate value in a stack
 */
int	is_error_duplicate(t_stack_node *stack, int n)
{
	if (!stack)
		return (0);
	while (stack)
	{
		if (stack->value == n)
			return (1);
		stack = stack->next;
	}
	return (0);
}

/**
 * Free stack in case of error cleanly
 */
void	free_stack(t_stack_node **stack)
{
	t_stack_node	*temp;
	t_stack_node	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		temp = current->next;
		current->value = 0;
		free(current);
		current = temp;
	}
	*stack = NULL;
}

/**
 * Free stack and print an error message in case of encountering a unique error
 */

 void	free_and_print_error(t_stack_node **stack)
 {
	free_stack(stack);
	ft_printf("Error\n");
	exit(1);
 }

 #include "../includes/push_swap.h"

// TODO: Int inputs works but String input is not hadled properly
/**
 * int inputs are sorted correctly, but input in form of String has different output (not sorted)
 */
// TODO: You have not handled int overflow (when you have a really long number value!)

// TODO: Implement more streamlined testing mechanism


/**
 * Returns the substring count in a string separated by delimiter
 */
static int	count_words(char *s, char del)
{
	int		count;
	bool	inside_word;

	count = 0;
	while (*s)
	{
		inside_word = false;
		while (*s == del)
			++s;
		while (*s != del && *s)
		{
			if (!inside_word)
			{
				++count;
				inside_word = true;
			}
			++s;
		}
	}
	return (count);
}

/**
 * Returns the new substring found within a string
 * @param s string
 * @param del delimiter
 */
static char	*get_next_word(char *s, char del)
{
	static int	post = 0;
	char		*next_word;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (s[post] == del)
		++post;
	while ((s[post + len] != del) && s[post + len])
		++len;
	next_word = malloc((size_t)len * sizeof(char) + 1);
	if (!next_word)
		return (NULL);
	while ((s[post] != del) && s[post])
		next_word[i++] = s[post++];
	next_word[i] = '\0';
	return (next_word);
}

/**
 * Splits a string into words or world-like units (tokenization) based on a delimiter. In case of error, exit with error code (1).
 *
 * @param s string
 * @param del delimiter
 */
char	**parse_args(char *s, char del)
{
	int		word_count;
	char	**result;
	int		i;

	i = 0;
	word_count = count_words(s, del);
	if (!word_count)
		exit(1);
	result = malloc((size_t)(word_count + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < word_count)
	{
		if (i == 0)
		{
			// result[i] = malloc(sizeof(char));
			if (!result)
				return (NULL);
			result[i++] = get_next_word(s, del);
			continue;
		}
		result[i++] = get_next_word(s, del);
	}
	result[i] = NULL;
	return (result);
}

/**
 * Entry point for the push_swap program.
 * Parse command-line arguments and initialize stack `a`.
 * If stack `a` is not already sorted:
 * 		- Sort two or three elements directly.
 * 		- Calls push_swap() for more complex sorting.
 * Frees all allocated memory at the end.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of argument strings.
 *
 * @return int - Returns 0 on success, 1 if input is empty or invalid.
 */
int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;

	a = NULL;
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		argv = parse_args(argv[1], ' ');
	init_stack_a(&a, argv + 1);
	if (!is_stack_sorted(a))
	{
		if (stack_size(a) == 2)
			sa(&a, false);
		else if (stack_size(a) == 3)
			sort_three(&a);
		else
			push_swap(&a, &b);
	}
	free_stack(&a);
	return (0);
}

/**
 * Finds, for each node in B, the best insertion point in A.
 */
static void	assign_targets_in_a(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_a;
	t_stack_node	*target;
	long			closest_bigger_nbr;

	while (b)
	{
		closest_bigger_nbr = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value && current_a->value < closest_bigger_nbr)
			{
				closest_bigger_nbr = current_a->value;
				target = current_a;
			}
			current_a = current_a->next;
		}
		if (closest_bigger_nbr == LONG_MAX)
			b->target_node = get_min_node(a);
		else
			b->target_node = target;
		b = b->next;
	}
}

/**
 * Prepares stack b for pushing back to a
 */
void	prepare_stack_b_for_push(t_stack_node *a, t_stack_node *b)
{
	assign_index(a);
	assign_index(b);
	assign_targets_in_a(a, b);
}

/**
 * Entry point for the push_swap program.
 * Parse command-line arguments and initialize stack `a`.
 * If stack `a` is not already sorted:
 * 		- Sort two or three elements directly.
 * 		- Calls push_swap() for more complex sorting.
 * Frees all allocated memory at the end.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of argument strings.
 *
 * @return int - Returns 0 on success, 1 if input is empty or invalid.
 */
int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;

	a = NULL;
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		argv = parse_args(argv[1], ' ');
	init_stack_a(&a, argv + 1);
	if (!is_stack_sorted(a))
	{
		if (stack_size(a) == 2)
			sa(&a, false);
		else if (stack_size(a) == 3)
			sort_three(&a);
		else
			push_swap(&a, &b);
	}
	free_stack(&a);
	return (0);
}

#include "../includes/push_swap.h"

/**
 * Assign index values and a median flag to each node in a stack.
 */
void	assign_index(t_stack_node *stack)
{
	int	i;
	int	median;

	i = 0;
	if (!stack)
		return ;
	median = stack_size(stack) / 2;
	while (stack)
	{
		stack->index = i;
		if (i <= median)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		++i;
	}
}

/**
 * Assigns targets in B for each node in A.
 */
static void	assign_targets_in_b(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_b;
	t_stack_node	*target;
	long			closest_smaller_nbr;

	while (a)
	{
		closest_smaller_nbr = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->value < a->value && current_b->value > closest_smaller_nbr)
			{
				closest_smaller_nbr = current_b->value;
				target = current_b;
			}
			current_b = current_b->next;
		}
		if (closest_smaller_nbr == LONG_MIN)
			a->target_node = get_max_node(b);
		else
			a->target_node = target;
		a = a->next;
	}
}

/**
 * Calculates the total cost (number of operations) needed to bring:
 * 	1. A node in stack A, and
 * 	2. Its corresponding target node in B
 * to the top of their respective stacks, so that a push a -> b operation can happen efficiently.
 *
 * This cost is stored in the `push_cost` field of each node in stack `a`.
 */
static void	calculate_push_costs(t_stack_node *a, t_stack_node *b)
{
	int	size_a;
	int	size_b;

	size_a = stack_size(a);
	size_b = stack_size(b);
	while (a)
	{
		a->push_cost = a->index;
		if (!(a->above_median))
			a->push_cost = size_a - (a->index);
		if (a->target_node->above_median)
			a->push_cost += a->target_node->index;
		else
			a->push_cost += size_b - (a->target_node->index);
		a = a->next;
	}
}

/**
 * Find the node with the lowest `push_cost` and set its `cheapest` flag to `true`
 */
void	mark_cheapest_node(t_stack_node *stack)
{
	long			cheapest_cost;
	t_stack_node	*cheapest_node;

	if (!stack)
		return ;
	cheapest_cost = LONG_MAX;
	while (stack)
	{
		if (stack->push_cost < cheapest_cost)
		{

			cheapest_cost = stack->push_cost;
			cheapest_node = stack;
		}
		stack = stack->next;
	}
	cheapest_node->cheapest = true;
}

/**
 * Fully analyzes and prepares stack `a` for the most efficient push operation
 */
void	prepare_stack_a_for_push(t_stack_node *a, t_stack_node *b)
{
	assign_index(a);
	assign_index(b);
	assign_targets_in_b(a, b);
	calculate_push_costs(a, b);
	mark_cheapest_node(a);
}

/**
 * Finds, for each node in B, the best insertion point in A.
 */
static void	assign_targets_in_a(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_a;
	t_stack_node	*target;
	long			closest_bigger_nbr;

	while (b)
	{
		closest_bigger_nbr = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value && current_a->value < closest_bigger_nbr)
			{
				closest_bigger_nbr = current_a->value;
				target = current_a;
			}
			current_a = current_a->next;
		}
		if (closest_bigger_nbr == LONG_MAX)
			b->target_node = get_min_node(a);
		else
			b->target_node = target;
		b = b->next;
	}
}

/**
 * Prepares stack b for pushing back to a
 */
void	prepare_stack_b_for_push(t_stack_node *a, t_stack_node *b)
{
	assign_index(a);
	assign_index(b);
	assign_targets_in_a(a, b);
}

#include "../includes/push_swap.h"

/**
 * Append a `t_stack_node at the end of a linked list
 *
 * @param stack
 * @param n value to be stored
 */
static void	append_node(t_stack_node **stack, int n)
{
	t_stack_node	*node;
	t_stack_node	*tail;

	if (!stack)
		return ;
	node = malloc(sizeof(t_stack_node));
	if (!node)
		return ;
	node->value = n;
	node-> cheapest = false;
	node->index = 0;
	node->above_median = false;
	node->push_cost = 0;
	node->target_node = NULL;
	node->next = NULL;
	node->prev = NULL;

	if (!(*stack))
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		tail = get_last_node(*stack);
		tail->next = node;
		node->prev = tail;
	}
}

/**
 * Initialize a stack by appending nodes
 */
void	init_stack_a(t_stack_node **a, char **argv)
{
	long	n;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (is_error_syntax(argv[i]))
			free_and_print_error(a);
		n = ft_atol(argv[i]);
		if (n > INT_MAX || n < INT_MIN)
			free_and_print_error(a);
		if (is_error_duplicate(*a, (int) n))
			free_and_print_error(a);
		append_node(a, (int) n);
		i++;
	}

}

/**
 * Search for the cheapest node in a stack
 *
 * @return cheapest node
 */
t_stack_node	*get_cheapest_node(t_stack_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

/**
 * Push stack nodes to the top of a stack
 */
void	push_to_top(t_stack_node **stack, t_stack_node *head, char stack_name)
{
	while (*stack != head)
	{
		if (stack_name == 'a')
		{
			if (head->above_median)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (stack_name == 'b')
		{
			if (head->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}
	}
}

/**
 * Return the number of nodes in a stack
 */
int	stack_size(t_stack_node *stack)
{
	int	count;

	count = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		count++;
	}
	return (count);
}

/**
 * Returns a pointer to the last node in a stack
 */
t_stack_node	*get_last_node(t_stack_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

/**
 * Checks if a stack is already sorted in ascending order
 */
int	is_stack_sorted(t_stack_node *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

/**
 * Return a pointer to the node with minimum value in a stack
 */
t_stack_node	*get_min_node(t_stack_node *stack)
{
	long			min;
	t_stack_node	*min_node;

	if (!stack)
		return (NULL);
	min = LONG_MAX;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_node = stack;
		}
		stack = stack->next;
	}
	return (min_node);
}

/**
 * Returns a pointer to a node with maximum value in a stack
 */
t_stack_node	*get_max_node(t_stack_node *stack)
{
	long			max;
	t_stack_node	*max_node;

	if (!stack)
		return (NULL);
	max = LONG_MIN;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}
