#include "../../includes/push_swap.h"

/**
 * Push a top node from one stack to another
 */
static void	push(t_stack_node **dest_stack, t_stack_node **src_stack)
{
	t_stack_node	*node_to_push;

	if (!*src_stack)
		return ;
	node_to_push = *src_stack;
	*src_stack = (*src_stack)->next;
	if (*src_stack)
		(*src_stack)->prev = NULL;
	node_to_push->prev = NULL;
	if (!*dest_stack)
	{
		*dest_stack = node_to_push;
		node_to_push->next = NULL;
	}
	else
	{
		node_to_push->next = *dest_stack;
		node_to_push->next->prev = node_to_push;
		*dest_stack = node_to_push;
	}
}

/**
 * "Push (a)"
 * Take the first element at the top of b and put it at the top of a, then print the respective operation.
 * Do nothing if b is empty.
 */
void	pa(t_stack_node **a, t_stack_node **b, bool suppress_output)
{
	push(a, b);
	if (!suppress_output)
		ft_printf("pa\n");
}

/**
 * "Push (b)"
 * Take the top element from `a` and push it to the top of `b`, then print the respective operation.
 * Do nothing if a is empty
 */
void	pb(t_stack_node **b, t_stack_node **a, bool suppress_output)
{
	push(b,a);
	if (!suppress_output)
		ft_printf("pb\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:16:03 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 21:23:29 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * Shift down all elements of a stack by 1. The last element becomes the first one.
 */
static void	reverse_rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;

	if (!*stack || !(*stack)->next)
		return ;
	last_node = get_last_node(*stack);
	last_node->prev->next = NULL;
	last_node->next = *stack;
	last_node->prev = NULL;
	*stack = last_node;
	last_node->next->prev = last_node;
}

/**
 * Shift down all elements of stack a by 1.
 * The last element becomes the first one.
 */
void	rra(t_stack_node **a, bool suppress_output)
{
	reverse_rotate(a);
	if (!suppress_output)
		ft_printf("rra\n");
}

/**
 * Shift down all elements of stack b by 1.
 * The last element becomes the first one.
 */
void	rrb(t_stack_node **b, bool suppress_output)
{
	reverse_rotate(b);
	if (!suppress_output)
		ft_printf("rrb\n");
}

void	rrr(t_stack_node **a, t_stack_node **b, bool suppress_output)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (!suppress_output)
		ft_printf("rrr\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:05:12 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 21:15:19 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * Shift up all elements of stack a by 1.
 * The first element becomes the last one.
 */
static void	rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;

	if (!*stack || !(*stack)->next)
		return ;
	last_node = get_last_node(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
}

/**
 * (rotate a): Shift up all elements of stack a by 1 in stack a.
 * The first element becomes the last one.
 */
void	ra(t_stack_node **a, bool suppress_output)
{
	rotate(a);
	if (!suppress_output)
		ft_printf("ra\n");
}

/**
 * (rotate b): Shift up all elements of stack a by 1 in stack b.
 * The first element becomes the last one.
 */
void	rb(t_stack_node **b, bool suppress_output)
{
	rotate(b);
	if (!suppress_output)
		ft_printf("rb\n");
}

/**
 * rr : ra and rb at the same time.
 */
void	rr(t_stack_node **a, t_stack_node **b, bool suppress_ouput)
{
	rotate(a);
	rotate(b);
	if (!suppress_ouput)
		ft_printf("rr\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:38:37 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/24 18:11:57 by fyudris          ###   ########.fr       */
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
// static void	rotate_min_to_top(t_stack_node **a)
// {
// 	while ((*a)->value != get_min_node(*a)->value)
// 	{
// 		if (get_min_node(*a)->above_median)
// 			ra(a, false);
// 		else
// 			rra(a, false);
// 	}
// }

/**
 * perform_push_swap_sort - Main controller function for sorting using the Turk algorithm.
 *                          Sorts stack A by pushing elements to B, then reinserting them.
 * @a: Pointer to stack A
 * @b: Pointer to stack B
 */
void	push_swap(t_stack_node **a, t_stack_node **b)
{
	// int	len_a;

	// len_a = stack_size(*a);
	// if (len_a-- > 3 && !is_stack_sorted(*a))
	// {
	// 	while (len_a-- > 3)
	// 		push_cheapest_a_to_b(a, b);
	// 	sort_three(a);
	// }
	// while (*b)
	// {
	// 	prepare_stack_b_for_push(*a, *b);
	// 	push_b_to_target_in_a(a, b);
	// }
	// if (!is_stack_sorted(*a))
	// 	rotate_min_to_top(a);

	int	len_a;

	len_a = stack_size(*a);
	if (len_a-- > 3 && !is_stack_sorted(*a))
		pb(b, a, false);
	if (len_a-- > 3 && !is_stack_sorted(*a))
		pb(b, a, false);
	while (len_a-- > 3 && !is_stack_sorted(*a))
	{
		prepare_stack_a_for_push(*a, *b);
		push_cheapest_a_to_b(a, b);
	}
	sort_three(a);
	while (*b)
	{
		prepare_stack_b_for_push(*a, *b);
		push_b_to_target_in_a(a, b);
	}
	assign_index(*a);
	rotate_min_to_top(a);
}


#include"../../includes/push_swap.h"

void	sort_three(t_stack_node **a)
{
	t_stack_node	*max_node;

	max_node = get_max_node(*a);
	if (max_node == *a)
		ra(a, false);
	else if ((*a)->next == max_node)
		rra(a, false);
	if ((*a)->value > (*a)->next->value)
		sa(a, false);
}

/**
 * Swaps the top two nodes of a stack, and updates all the relevant next and prev pointers
 */
static void	swap(t_stack_node **top)
{
	if (!*top || !(*top)->next)
		return ;
	*top = (*top)->next;
	(*top)->prev->prev = *top;
	(*top)->prev->next = (*top)->next;
	if ((*top)->next)
		(*top)->next->prev = (*top)->prev;
	(*top)->next = (*top)->prev;
	(*top)->prev = NULL;
}

/**
 * "Swap (a)""
 * Swap the first 2 elements at the top of stack a.
 * Do nothing if there is only one element or none.
 */
void	sa(t_stack_node **a, bool suppress_output)
{
	swap(a);
	if (!suppress_output)
		ft_printf("sa\n");
}

/**
 * Swap the first 2 elements at the top of stack b.
 * Do nothing if there is only one element or none.
 */
void	sb(t_stack_node **b, bool suppress_output)
{
	swap(b);
	if (!suppress_output)
		ft_printf("sb\n");
}

/**
 * Do sa and sb at the same time.
 */
void	ss(t_stack_node **a, t_stack_node **b, bool suppress_output)
{
	swap(a);
	swap(b);
	if (!suppress_output)
		ft_printf("ss\n");
}

