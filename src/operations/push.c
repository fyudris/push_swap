/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:29:51 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 18:12:27 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * push: move top of src stack to dest
 */
static void	push(t_stack_node **dest, t_stack_node **src)
{
	t_stack_node *node;

	if (!*src)
		return ;
	node = *src;
	*src = node->next;
	if (*src)
		(*src)->prev = NULL;
	node->next = *dest;
	if (*dest)
		(*dest)->prev = node;
	node->prev = NULL;
	*dest = node;
}

void pa(t_stack_node **a, t_stack_node **b, bool write_op)
{
    push(a, b);
    if (write_op)
        ft_putstr_fd("pa\n", 1);
}

void pb(t_stack_node **b, t_stack_node **a, bool write_op)
{
    push(b, a);
    if (write_op)
        ft_putstr_fd("pb\n", 1);
}
