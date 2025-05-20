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
