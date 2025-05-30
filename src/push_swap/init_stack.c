/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:54:06 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/30 18:34:33 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * append_node: allocate a new node and append it to the end of stack
 *
 * @param stack: pointer to stack head
 * @param n: integer value to store
 */
static void	append_node(t_stack_node **stack, int n)
{
	t_stack_node	*node;
	t_stack_node	*tail;

	node = malloc(sizeof(t_stack_node));
	if (!node)
		exit_error();
	node->value = n;
	node->index = 0;
	node->push_cost = 0;
	node->above_median = false;
	node->cheapest = false;
	node->target_node = NULL;
	node->next = NULL;
	node->prev = NULL;
	if (!*stack)
	{
		*stack = node;
		return ;
	}
	tail = *stack;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
	node->prev = tail;
}

/**
 * init_stack: build a linked list of t_stack_node from tokens
 *
 * @param a: pointer to stack head
 * @param nums: NULL-terminated array of validated numeric strings
 */
void	init_stack(t_stack_node **a, char **nums)
{
	long	val;
	int		i;

	i = 0;
	while (nums[i])
	{
		val = ft_atol(nums[i]);
		append_node(a, (int)val);
		i++;
	}
}

/**
 * free_stack: free all nodes in a stack
 * @param stack: pointer to stack head
 */
void	free_stack(t_stack_node **stack)
{
	t_stack_node	*current;
	t_stack_node	*temp;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	*stack = NULL;
}

/**
 * To deallocate memory used by an array of strings (char **), where both the
 * array itself and each individual string within it were dynamically allocated.
 * Used for the nums variable when it's populated by splitting a command-line
 * argument string.
 */
void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
