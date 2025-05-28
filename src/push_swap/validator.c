/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:37:48 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 16:52:24 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * valid_number: returns 1 if s is a valid integer string
 * allows optional +/-, then digits only
 */
static	int	valid_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if(!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * validator: checks each token for valid integer ad no overflow or duplicates
 *
 * @param nums: NULL-terminated array of token strings
 * exits with Error if any check fails
 */
void	validator(char **nums)
{
	long	val;
	int		i;
	int		j;

	i = 0;
	while (nums[i])
	{
		if (!valid_number(nums[i]))
			exit_error();
		val = ft_atol(nums[i]);
		if (val > INT_MAX || val < INT_MIN)
			exit_error();
		j = i + 1;
		while (nums[j])
		{
			if (ft_atol(nums[j]) == val)
				exit_error();
			j++;
		}
		i++;
	}
}
