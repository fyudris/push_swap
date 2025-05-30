/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:52:32 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/30 19:13:21 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * swap: swap first two elemets of stack
 *
 * @param top: pointer to stack head
 */
static void	swap(t_stack_node **top)
{
	t_stack_node	*first;
	t_stack_node	*second;

	if (!*top || !(*top)->next)
		return ;
	first = *top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*top = second;
}

/**
 * Swap the first 2 elements at the top of stack a.
 */
void	sa(t_stack_node **a, bool write_op)
{
	swap(a);
	if (write_op)
		ft_putstr_fd("sa\n", 1);
}

/**
 * Swap the first 2 elements at the top of stack b.
 */
void	sb(t_stack_node **b, bool write_op)
{
	swap(b);
	if (write_op)
		ft_putstr_fd("sb\n", 1);
}

/**
 * sa and sb at the same time.
 */
void	ss(t_stack_node **a, t_stack_node **b, bool write_op)
{
	swap(a);
	swap(b);
	if (write_op)
		ft_putstr_fd("ss\n", 1);
}
