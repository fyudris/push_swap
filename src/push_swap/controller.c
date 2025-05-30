/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:27:01 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/30 18:31:03 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * push_cheapest_a_to_b:
 *   Fully prepare and push the cheapest node from A to B,
 *   doing simultaneous rotates when advantageous.
 */
void	push_cheapest_a_to_b(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*cheapest;

	cheapest = get_cheapest_node(*a);
	if (cheapest->above_median && cheapest->target_node->above_median)
		rotate_both_for_push(a, b, cheapest);
	else if (!cheapest->above_median && !cheapest->target_node->above_median)
		reverse_rotate_both_for_push(a, b, cheapest);
	push_to_top(a, cheapest, 'a');
	push_to_top(b, cheapest->target_node, 'b');
	pb(b, a, true);
}

/**
 * push_b_to_target_in_a:
 *   Rotate A so that B->top's target_node is at head, then push.
 */
void	push_b_to_target_in_a(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*target;

	target = (*b)->target_node;
	push_to_top(a, target, 'a');
	pa(a, b, true);
}

/**
 * rotate_min_to_top:
 *   After sorting, rotate A so that the minimum value lands at head.
 */
void	rotate_min_to_top(t_stack_node **a)
{
	t_stack_node	*current_min_node;

	if (!a || !*a || !(*a)->next)
		return ;
	current_min_node = get_min_node(*a);
	if (!current_min_node)
		return ;
	while ((*a)->value != current_min_node->value)
	{
		if (get_min_node(*a)->above_median)
			ra(a, true);
		else
			rra(a, true);
	}
}
