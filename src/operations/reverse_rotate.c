/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:16:03 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 23:36:31 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * reverse_rotate: shift all down by one
 */
static void reverse_rotate(t_stack_node **stack)
{
	t_stack_node *last;
    t_stack_node *before_last;

    if (!stack || !*stack || !(*stack)->next)
        return;
    last = *stack;
    while (last->next)
        last = last->next;
    before_last = last->prev;
    if (before_last)
        before_last->next = NULL;
    last->next = *stack;
    last->prev = NULL;
    (*stack)->prev = last;
    *stack = last;
}

void rra(t_stack_node **a, bool write_op)
{
    reverse_rotate(a);
    if (write_op)
        ft_putstr_fd("rra\n", 1);
}

void rrb(t_stack_node **b, bool write_op)
{
    reverse_rotate(b);
    if (write_op)
        ft_putstr_fd("rrb\n", 1);
}

void rrr(t_stack_node **a, t_stack_node **b, bool write_op)
{
    reverse_rotate(a);
    reverse_rotate(b);
    if (write_op)
        ft_putstr_fd("rrr\n", 1);
}
