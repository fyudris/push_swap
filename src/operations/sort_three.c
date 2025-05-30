/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:23:40 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/30 18:29:32 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 *
 * @brief Sort a stack of exactly three elements in ascending order.
 *
 * Having a dedicated three-element sorter lets us handle this small case
 * optimally (in at most two operations) before invoking the general algorithm.
 * This both minimize total moves and keeps the main algorithm simpler.
 *
 * There are exactly 6 permutations of three distinct values; for each we choose
 * the minimal sequence:
 *
 *   Initial    Operations        Result
 *   [1, 2, 3]  --                [1, 2, 3]  (already sorted)
 *   [2, 1, 3]  sa                [1, 2, 3]
 *   [3, 2, 1]  sa + rra          [1, 2, 3]
 *   [3, 1, 2]  ra                [1, 2, 3]
 *   [1, 3, 2]  sa + ra           [1, 2, 3]
 *   [2, 3, 1]  rra               [1, 2, 3]
 *
 * By isolating these into their own function, we guarantee optimal movecounts
 * on three elements and simplify the general n-element routine that pushes
 * all but three elements to stack B.
 *
 */
void	sort_three(t_stack_node **a)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if (first > second && second < third && first < third)
		sa(a, true);
	else if (first > second && second > third)
	{
		sa(a, true);
		rra(a, true);
	}
	else if (first > second && second < third && first > third)
		ra(a, true);
	else if (first < second && second > third && first < third)
	{
		sa(a, true);
		ra(a, true);
	}
	else if (first < second && second > third && first > third)
		rra(a, true);
}
