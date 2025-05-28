/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:23:19 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 19:49:24 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * Return the number of nodes in a stack
 */
int	stack_size(t_stack_node *stack)
{
	int	count;

	count = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		count++;
	}
	return (count);
}

/**
 * get_min_node:
 *   Walk the stack and return the node whose value is minimum.
 *   Returns NULL if the stack is empty.
 */
t_stack_node *get_min_node(t_stack_node *stack)
{
    t_stack_node *min_node;
    long          min_val;

    if (!stack)
        return (NULL);
    min_node = stack;
    min_val  = stack->value;
    while (stack)
    {
        if (stack->value < min_val)
        {
            min_val  = stack->value;
            min_node = stack;
        }
        stack = stack->next;
    }
    return (min_node);
}

/**
 * get_max_node:
 *   Walk the stack and return the node whose value is maximum.
 *   Returns NULL if the stack is empty.
 */
t_stack_node *get_max_node(t_stack_node *stack)
{
    t_stack_node *max_node;
    long          max_val;

    if (!stack)
        return (NULL);
    max_node = stack;
    max_val  = stack->value;
    while (stack)
    {
        if (stack->value > max_val)
        {
            max_val  = stack->value;
            max_node = stack;
        }
        stack = stack->next;
    }
    return (max_node);
}

int is_stack_sorted(t_stack_node *stack)
{
    while (stack && stack->next)
    {
        if (stack->value > stack->next->value)
            return (0);
        stack = stack->next;
    }
    return (1);
}


