/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:15:41 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 19:16:17 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * calculate_push_costs:
 *   For each node in A, compute how many moves it would take to:
 *     1) rotate A so that this node is at the top, and
 *     2) rotate B so that its target_node is at the top,
 *   then sum them.  We store that in node->push_cost.
 *
 *   We use the index + above_median flags to choose:
 *     - if above_median, cost = index (ra RA)
 *     - else            cost = size - index (rra RRA)
 *
 *   Later we’ll pick the node with the smallest total cost.
 */
void	calculate_push_costs(t_stack_node *a, t_stack_node *b)
{
	int size_a = stack_size(a);
	int size_b = stack_size(b);

	while (a)
	{
		/* cost to bring this A-node to top */
		int cost = a->index;
		if (!a->above_median)
			cost = size_a - a->index;

		/* cost to bring its target in B to top */
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
 * Scan all A-nodes and set the one with minimal push_cost to cheapest=true.
 * That tells our controller: “this is the best next move.”
 */
void	mark_cheapest_node(t_stack_node *a)
{
	long     min = LONG_MAX;
	t_stack_node *best = NULL;

	while (a)
	{
		if (a->push_cost < min)
		{
			min  = a->push_cost;
			best = a;
		}
		a = a->next;
	}
	if (best)
		best->cheapest = true;
}
