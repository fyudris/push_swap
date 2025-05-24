/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:40:59 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/24 18:21:45 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
