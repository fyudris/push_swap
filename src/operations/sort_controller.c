/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:38:37 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 23:23:02 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * rotate_both_for_push - Rotate both stacks A and B upwards simultaneously
 *                        until the given nodes are at the top.
 * @a: Pointer to stack A
 * @b: Pointer to stack B
 * @cheapest_node: Node in A identified as the cheapest to push
 */
static void	rotate_both_for_push(t_stack_node **a,
								t_stack_node **b,
								t_stack_node *cheapest_node)
{
	while (*b != cheapest_node->target_node
		&& *a != cheapest_node)
		rr(a, b, false); // Rotate both stacks
	assign_index(*a);
	assign_index(*b);
}

/**
 * reverse_rotate_both_for_push - Reverse rotate both stacks A and B simultaneously
 *                                until the given nodes are at the top.
 * @a: Pointer to stack A
 * @b: Pointer to stack B
 * @cheapest_node: Node in A identified as the cheapest to push
 */
static void	reverse_rotate_both_for_push(t_stack_node **a,
										  t_stack_node **b,
										  t_stack_node *cheapest_node)
{
	while (*b != cheapest_node->target_node
		&& *a != cheapest_node)
		rrr(a, b, false);
	assign_index(*a);
	assign_index(*b);
}

/**
 * push_cheapest_a_to_b - Prepares and pushes the cheapest node from A to B.
 *                        Includes rotating both stacks optimally.
 * @a: Pointer to stack A
 * @b: Pointer to stack B
 */
static void	push_cheapest_a_to_b(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*cheapest_node;

	cheapest_node = get_cheapest_node(*a);
	if (cheapest_node->above_median
		&& cheapest_node->target_node->above_median)
		rotate_both_for_push(a, b, cheapest_node);
	else if (!(cheapest_node->above_median)
		&& !(cheapest_node->target_node->above_median))
		reverse_rotate_both_for_push(a, b, cheapest_node);
	push_to_top(a, cheapest_node, 'a');
	push_to_top(b, cheapest_node->target_node, 'b');
	pb(b, a, false);
}

/**
 * push_b_to_target_in_a - Pushes the top node from B to its target position in A.
 *                         Ensures the target node is on top of A.
 * @a: Pointer to stack A
 * @b: Pointer to stack B
 */
static void	push_b_to_target_in_a(t_stack_node **a, t_stack_node **b)
{
	push_to_top(a, (*b)->target_node, 'a');
	pa(a, b, false);
}

/**
 * rotate_min_to_top - Rotates stack A so that the minimum value is at the top.
 *                     Used at the end of sorting to finalize order.
 * @a: Pointer to stack A
 */
static void	rotate_min_to_top(t_stack_node **a)
{
	while ((*a)->value != get_min_node(*a)->value)
	{
		if (get_min_node(*a)->above_median)
			ra(a, false);
		else
			rra(a, false);
	}
}

/**
 * perform_push_swap_sort - Main controller function for sorting using the Turk algorithm.
 *                          Sorts stack A by pushing elements to B, then reinserting them.
 * @a: Pointer to stack A
 * @b: Pointer to stack B
 */
void	perform_push_swap_sort(t_stack_node **a, t_stack_node **b)
{
	int	len_a;

	len_a = stack_size(*a);
	if (len_a-- > 3 && !is_stack_sorted(*a))
	{
		while (len_a-- > 3)
			push_cheapest_a_to_b(a, b);
		sort_three(a);
	}
	while (*b)
	{
		prepare_stack_b_for_push(*a, *b);
		push_b_to_target_in_a(a, b);
	}
	if (!is_stack_sorted(*a))
		rotate_min_to_top(a);
}

