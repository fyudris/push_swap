/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:15:41 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/02 14:37:51 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * calculate_push_costs:
 *   For each nodeA in stack A, it calculates nodeA->push_cost.
 * This cost is the sum of:
 * 		1. Moves to bring nodeA to the top of A = nodeA->index
 * 			(if nodeA->above_median)
 * 		OR  = stack_size(A) - nodeA->index
 * 			(if not above_median).
 *
 * 		2. Moves to bring nodeA->target_node to the top of B = target_node->index
 * 			(if target_node->above_median)
 * 		OR = stack_size(B) - target_node->index
 * 			(if not above_median).
 */
void	calculate_push_costs(t_stack_node *a, t_stack_node *b)
{
	int	size_a;
	int	size_b;
	int	cost;

	size_a = stack_size(a);
	size_b = stack_size(b);
	while (a)
	{
		cost = a->index;
		if (!a->above_median)
			cost = size_a - a->index;
		if (a->target_node->above_median)
			cost += a->target_node->index;
		else
			cost += size_b - a->target_node->index;
		a->push_cost = cost;
		a = a->next;
	}
}

/**
 * mark_cheapest_node:
 * Scan all A-nodes and set the one with minimal push_cost to
 * node->cheapest = true.
 *
 * That tells our controller: “this is the best next move.”
 */
void	mark_cheapest_node(t_stack_node *a)
{
	long			min;
	t_stack_node	*best;

	min = LONG_MAX;
	best = NULL;
	while (a)
	{
		if (a->push_cost < min)
		{
			min = a->push_cost;
			best = a;
		}
		a = a->next;
	}
	if (best)
		best->cheapest = true;
}
