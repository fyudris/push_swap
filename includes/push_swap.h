/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:30:05 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/16 22:09:53 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
#include "libft.h"

typedef struct s_stack_node
{
	int						nbr;
	int						index;
	int						push_cost;
	bool					above_median;
	bool					cheapest;
	struct s_stack_node		*target_node;
	struct s_stack_node		*next;
	struct s_stack_node		*prev;
}	t_stack_node;

// Parsing
bool	is_valid_input(int argc, char **argv);
bool	is_valid_input(int argc, char **argv);
char	**join_and_split_args(int argc, char **argv, int *count);
bool	is_number(char *str);
long	ft_atol(const char *str);
void	free_array(char **array);


// Error Handling

// Stack Initilalization

// Node Initilaization

// Stack Utilities

// Commands

// Algoritms

#endif
