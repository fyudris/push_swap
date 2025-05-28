/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:05:12 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 18:13:47 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * rotate: shift all up by one
 */
static void rotate(t_stack_node **stack)
{
    t_stack_node *first;
    t_stack_node *last;

    if (!*stack || !(*stack)->next)
        return ;
    first = *stack;
    last = *stack;
    while (last->next)
        last = last->next;
    *stack = first->next;
    (*stack)->prev = NULL;
    first->next = NULL;
    last->next = first;
    first->prev = last;
}

void ra(t_stack_node **a, bool write_op)
{
    rotate(a);
    if (write_op)
        ft_putstr_fd("ra\n", 1);
}

void rb(t_stack_node **b, bool write_op)
{
    rotate(b);
    if (write_op)
        ft_putstr_fd("rb\n", 1);
}

void rr(t_stack_node **a, t_stack_node **b, bool write_op)
{
    rotate(a);
    rotate(b);
    if (write_op)
        ft_putstr_fd("rr\n", 1);
}

