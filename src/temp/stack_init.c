/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:54:06 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 23:18:18 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
