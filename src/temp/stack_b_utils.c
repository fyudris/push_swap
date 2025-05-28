/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_b_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:15:11 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 20:23:21 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
