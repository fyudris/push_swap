/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:45:18 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/27 13:58:02 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
