/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:23:40 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/20 21:29:57 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/push_swap.h"

void	sort_three(t_stack_node **a)
{
	t_stack_node	*max_node;

	max_node = get_max_node(*a);
	if (max_node == *a)
		ra(a, false);
	else if ((*a)->next == max_node)
		rra(a, false);
	if ((*a)->value > (*a)->next->value)
		sa(a, false);
}
