/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:09:05 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/30 19:20:47 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * assign_targets_in_b:
 * For each node in stack A (let's call it nodeA), this function finds its
 * target_node in stack B. The logic is to find the node in B (nodeB_target)
 * such that nodeB_target->value is the largest value in B that is still less than nodeA->value.
 *
 * If no such node exists (e.g., nodeA is smaller than all elements in B, or B is empty/small),
 * nodeA->target_node is set to the node with the maximum value in stack B. This helps place nodeA
 * correctly relative to B's current largest element.
 *
 * Later we’ll rotate B so that this target_node is at the top, then pa.
 */
void	assign_targets_in_b(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_a;
	long			best;
	t_stack_node	*target_in_b;
	t_stack_node	*current_b;

	current_a = a;
	while (current_a)
	{
		best = LONG_MIN;
		target_in_b = NULL;
		current_b = b;
		while (current_b)
		{
			if (current_b->value < current_a->value && current_b->value > best)
			{
				best = current_b->value;
				target_in_b = current_b;
			}
			current_b = current_b->next;
		}
		if (target_in_b == NULL)
			target_in_b = get_max_node(b);
		current_a->target_node = target_in_b;
		current_a = current_a->next;
	}
}

/**
 * assign_targets_in_a:
 * The mirror image of the above—after we’ve moved everything to B, when
 * we’re reinserting, each b needs to know which a to push on top of.
 */
void	assign_targets_in_a(t_stack_node *a, t_stack_node *b)
{
	long			best_val;
	t_stack_node	*best_node;
	t_stack_node	*cur;

	while (b)
	{
		best_val = LONG_MAX;
		best_node = NULL;
		cur = a;
		while (cur)
		{
			if (cur->value > b->value && cur->value < best_val)
			{
				best_val = cur->value;
				best_node = cur;
			}
			cur = cur->next;
		}
		if (!best_node)
			best_node = get_min_node(a);
		b->target_node = best_node;
		b = b->next;
	}
}
