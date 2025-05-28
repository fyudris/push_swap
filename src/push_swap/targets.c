/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:09:05 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 22:59:49 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * assign_targets_in_b:
 * For every node `a` in stack A, find the node in B that should come
 * immediately **before** `a` when re-inserting.
 * That is, the largest b->value
 * which is still < a->value.  If none exists, we wrap around and pick the
 * current maximum in B.
 *
 * We record this in `a->target_node`.  Later we’ll rotate B so that
 * this target_node is at the top, then pa.
 */
void	assign_targets_in_b(t_stack_node *a, t_stack_node *b)
{
	t_stack_node *current_a = a;

 	while (current_a) {
        long best_val = LONG_MIN;
        t_stack_node *target_in_b = NULL;
        t_stack_node *current_b = b;

        while (current_b) {
            if (current_b->value < current_a->value && current_b->value > best_val) {
                best_val = current_b->value;
                target_in_b = current_b;
            }
            current_b = current_b->next;
        }

        if (target_in_b == NULL) { // No node in B is smaller than current_a OR B is empty
            target_in_b = get_max_node(b); // Get the largest element in B
                                                // If b_stack is empty, get_max_node returns NULL.
        }
        current_a->target_node = target_in_b; // This can assign NULL if b_stack was empty.
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
	while (b)
	{
		long best_val = LONG_MAX;
		t_stack_node *best_node = NULL;
		t_stack_node *cur = a;

		while (cur)
		{
			if (cur->value > b->value && cur->value < best_val)
			{
				best_val  = cur->value;
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
