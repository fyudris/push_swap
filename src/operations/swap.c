/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:52:32 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 23:07:45 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

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
