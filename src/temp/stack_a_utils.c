/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_a_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:28:11 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 20:31:07 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

