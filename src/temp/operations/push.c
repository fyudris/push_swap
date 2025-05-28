/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:29:51 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 21:06:57 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
