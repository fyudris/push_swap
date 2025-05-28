/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:40:59 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 20:11:26 by fyudris          ###   ########.fr       */
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
int main(int argc, char **argv)
{
    char          **nums;
    t_stack_node  *a;
    t_stack_node  *b;

    a = NULL;
    b = NULL;
    if (argc < 2 || (argc == 2 && argv[1][0] == '\0'))
        return (1);

    /* 2) Parse tokens */
    if (argc == 2)
        nums = parse_args(argv[1]);
    else
        nums = &argv[1];
    validator(nums);
    init_stack(&a, nums);
    if (!is_stack_sorted(a))
        push_swap(&a, &b);

    /* 6) Clean up */
    free_stack(&a);
    return (0);
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
void push_swap(t_stack_node **a, t_stack_node **b)
{
    int len = stack_size(*a);

    /* Step 1: seed B with two only if >3 */
    if (len > 3)
    {
        pb(b, a, true);
        pb(b, a, true);
    }

    /* Step 2: while more than 3 remain in A, push cheapest */
    while (stack_size(*a) > 3)
    {
        assign_index(*a);
        assign_index(*b);
        assign_targets_in_b(*a, *b);
        calculate_push_costs(*a, *b);
        mark_cheapest_node(*a);
        push_cheapest_a_to_b(a, b);
    }

    /* Step 3: sort the final small A */
    len = stack_size(*a);
    if (len == 2)
    {
        sa(a, true);
    }
    else if (len == 3)
    {
        sort_three(a);
    }

    /* Step 4: reinsert everything from B */
    while (*b)
    {
        assign_index(*a);
        assign_index(*b);
        assign_targets_in_a(*a, *b);
        push_b_to_target_in_a(a, b);
    }

    /* Step 5: final rotate so min is on top */
    assign_index(*a);
    rotate_min_to_top(a);
}

// void	push_swap(t_stack_node **a, t_stack_node **b)
// {
//     pb(b, a, true);
//     pb(b, a, true);
//     while (stack_size(*a) > 3)
//     {
//         assign_index(*a);
//         assign_index(*b);
//         assign_targets_in_b(*a, *b);
//         calculate_push_costs(*a, *b);
//         mark_cheapest_node(*a);
//         push_cheapest_a_to_b(a, b);
//     }
//     sort_three(a);
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
