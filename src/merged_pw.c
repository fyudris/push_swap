/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merged_pw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:05:52 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/27 13:38:59 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/**
 * Checks for syntax error
 * @return 0 for success, 1 for error
 */
int	is_error_syntax(char *str)
{
	if (!(*str == '+' || *str == '-' || ft_isdigit(*str)))
		return (1);
	if ((*str == '+' || *str == '-') && !ft_isdigit(str[1]))
		return (1);
	while (*++str)
	{
		if (!ft_isdigit(*str))
			return (1);
	}
	return (0);
}

/**
 * Checks for duplicate value in a stack
 */
int	is_error_duplicate(t_stack_node *stack, int n)
{
	if (!stack)
		return (0);
	while (stack)
	{
		if (stack->value == n)
			return (1);
		stack = stack->next;
	}
	return (0);
}

/**
 * Free stack in case of error cleanly
 */
void	free_stack(t_stack_node **stack)
{
	t_stack_node	*temp;
	t_stack_node	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		temp = current->next;
		current->value = 0;
		free(current);
		current = temp;
	}
	*stack = NULL;
}

/**
 * Free stack and print an error message in case of encountering a unique error
 */

 void	free_and_print_error(t_stack_node **stack)
 {
	free_stack(stack);
	ft_printf("Error\n");
	exit(1);
 }
