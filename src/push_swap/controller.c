/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:27:01 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 19:31:22 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * push_cheapest_a_to_b:
 *   Fully prepare and push the cheapest node from A to B,
 *   doing simultaneous rotates when advantageous.
 */
void push_cheapest_a_to_b(t_stack_node **a, t_stack_node **b)
{
    t_stack_node *cheapest = get_cheapest_node(*a);

    if (cheapest->above_median
        && cheapest->target_node->above_median)
        rotate_both_for_push(a, b, cheapest);
    else if (!cheapest->above_median
        && !cheapest->target_node->above_median)
        reverse_rotate_both_for_push(a, b, cheapest);

    push_to_top(a, cheapest, 'a');
    push_to_top(b, cheapest->target_node, 'b');
    pb(b, a, true);
}

/**
 * push_b_to_target_in_a:
 *   Rotate A so that B->top's target_node is at head, then push.
 */
void push_b_to_target_in_a(t_stack_node **a, t_stack_node **b)
{
    t_stack_node *target = (*b)->target_node;

    push_to_top(a, target, 'a');
    pa(a, b, true);
}

/**
 * rotate_min_to_top:
 *   After sorting, rotate A so that the minimum value lands at head.
 */
void rotate_min_to_top(t_stack_node **a)
{
    t_stack_node *min_node = get_min_node(*a);

    while ((*a)->value != min_node->value)
    {
        if (min_node->above_median)
            ra(a, true);
        else
            rra(a, true);
    }
}
