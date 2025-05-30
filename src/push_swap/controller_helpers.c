/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:31:01 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/30 18:31:29 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * get_cheapest_node: find the node flagged cheapest in A
 */
t_stack_node	*get_cheapest_node(t_stack_node *stack)
{
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

/**
 * rotate_both_for_push:
 *   While neither the cheapest A-node nor its target in B is at the head,
 *   rotate both stacks upward together.
 */
void	rotate_both_for_push(t_stack_node **a, t_stack_node **b,
		t_stack_node *cheapest)
{
	while (*a != cheapest && *b != cheapest->target_node)
	{
		rr(a, b, true);
	}
	assign_index(*a);
	assign_index(*b);
}

/**
 * reverse_rotate_both_for_push:
 *   While neither the cheapest A-node nor its target in B is at the head,
 *   reverse-rotate both stacks together.
 */
void	reverse_rotate_both_for_push(t_stack_node **a, t_stack_node **b,
									t_stack_node *cheapest)
{
	while (*a != cheapest && *b != cheapest->target_node)
	{
		rrr(a, b, true);
	}
	assign_index(*a);
	assign_index(*b);
}

/**
 * push_to_top: bring a given node to the head of its stack
 * @stack: pointer to the stack head
 * @node:  the node that should end up at head
 * @name:  'a' or 'b' to pick ra/rra vs rb/rrb
 */
void	push_to_top(t_stack_node **stack, t_stack_node *node,
					char name)
{
	while (*stack != node)
	{
		if (name == 'a')
		{
			if (node->above_median)
				ra(stack, true);
			else
				rra(stack, true);
		}
		else
		{
			if (node->above_median)
				rb(stack, true);
			else
				rrb(stack, true);
		}
	}
}
