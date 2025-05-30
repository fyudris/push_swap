/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:40:59 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/30 19:16:39 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/**
 * main: entry point for push_swap
 *
 * 1) Handle no‐input or empty‐string as an error (return 1).
 * 2) If single string argument, split it; else take argv[1..].
 * 3) Validate tokens (syntax, duplicates, overflow).
 * 4) Build stack A.
 * 5) If not already sorted, run the full push_swap algorithm.
 * 6) Free all nodes and exit 0.
 */
int	main(int argc, char **argv)
{
	char			**nums;
	t_stack_node	*a;
	t_stack_node	*b;

	a = NULL;
	b = NULL;
	if (argc < 2 || (argc == 2 && argv[1][0] == '\0'))
		return (1);
	if (argc == 2)
	{
		nums = parse_args(argv[1]);
		if (!nums)
			return (1);
	}
	else
		nums = &argv[1];
	validator(nums);
	init_stack(&a, nums);
	if (!is_stack_sorted(a))
		push_swap(&a, &b);
	free_stack(&a);
	free_stack(&b);
	if (argc == 2)
		free_str_array(nums);
	return (0);
}

/**
 * Helper function to execute moves from stack A to stack B
 * until only 3 or fewer elements remain in A.
 * This part involves identifying the "cheapest" element to move.
 */
static void	execute_a_to_b_phase(t_stack_node **a, t_stack_node **b)
{
	while (stack_size(*a) > 3)
	{
		assign_index(*a);
		assign_index(*b);
		assign_targets_in_b(*a, *b);
		calculate_push_costs(*a, *b);
		mark_cheapest_node(*a);
		push_cheapest_a_to_b(a, b);
	}
}

/**
 * Helper function to execute moves from stack B back to stack A
 * until stack B is empty.
 * This part involves finding the correct sorted position in A for B-elements.
 */
static void	execute_b_to_a_phase(t_stack_node **a, t_stack_node **b)
{
	while (*b)
	{
		assign_index(*a);
		assign_index(*b);
		assign_targets_in_a(*a, *b);
		push_b_to_target_in_a(a, b);
	}
}

/**
 * push_swap: the main controller that sorts stack A.
 *
 * 1) Push the first two elements to B as a seed.
 * 2) While A has more than 3 elements:
 *      - assign indices/median flags on A and B
 *      - assign target nodes in B for each A
 *      - compute push_costs on A
 *      - mark the cheapest A-node
 *      - perform the optimal sequence of rotates/pushes to move it to B
 * 3) Sort the remaining 3 in A with sort_three (optimal ≤2 ops).
 * 4) While B is not empty:
 *      - assign indices/median flags
 *      - assign target nodes in A for each B
 *      - rotate A so its target is on top, then pa
 * 5) Finally rotate A so that its  minimum value is at the head.
 */
void	push_swap(t_stack_node **a, t_stack_node **b)
{
	int	initial_len_a;
	int	current_len_a;

	if (is_stack_sorted(*a))
		return ;
	initial_len_a = stack_size(*a);
	if (initial_len_a > 3)
	{
		pb(b, a, true);
		pb(b, a, true);
	}
	execute_a_to_b_phase(a, b);
	current_len_a = stack_size(*a);
	if (current_len_a == 2)
	{
		if ((*a)->value > (*a)->next->value)
			sa(a, true);
	}
	else if (current_len_a == 3)
	{
		sort_three(a);
	}
	execute_b_to_a_phase(a, b);
	assign_index(*a);
	rotate_min_to_top(a);
}

// void push_swap(t_stack_node **a, t_stack_node **b)
// {
//     int len;

// 	len = stack_size(*a);
//     if (len > 3)
//     {
//         pb(b, a, true);
//         pb(b, a, true);
//     }
//     while (stack_size(*a) > 3)
//     {
//         assign_index(*a);
//         assign_index(*b);
//         assign_targets_in_b(*a, *b);
//         calculate_push_costs(*a, *b);
//         mark_cheapest_node(*a);
//         push_cheapest_a_to_b(a, b);
//     }
//     len = stack_size(*a);
//     if (len == 2)
//         sa(a, true);
//     else if (len == 3)
//         sort_three(a);
//     while (*b)
//     {
//         assign_index(*a);
//         assign_index(*b);
//         assign_targets_in_a(*a, *b);
//         push_b_to_target_in_a(a, b);
//     }
//     assign_index(*a);
//     rotate_min_to_top(a);
// }
