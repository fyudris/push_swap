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
