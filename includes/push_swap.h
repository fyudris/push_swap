/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:30:05 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/24 18:12:10 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef struct s_stack_node
{
	int						value;
	int						index;
	int						push_cost;
	bool					above_median;
	bool					cheapest;
	struct s_stack_node		*target_node;
	struct s_stack_node		*next;
	struct s_stack_node		*prev;
}	t_stack_node;

// Parsing
char			**parse_args(char *s, char del);

// Error Handling
int				is_error_syntax(char *str);
int				is_error_duplicate(t_stack_node *stack, int n);
void			free_stack(t_stack_node **stack);
void			free_and_print_error(t_stack_node **stack);

// Stack Initilalization
void			init_stack_a(t_stack_node **a, char **argv);
t_stack_node	*get_cheapest_node(t_stack_node *stack);
void			push_to_top(t_stack_node **stack, t_stack_node *head, char stack_name);


// Stack Utilities
int				stack_size(t_stack_node *stack);
int				is_stack_sorted(t_stack_node *stack);
t_stack_node	*get_min_node(t_stack_node *stack);
t_stack_node	*get_max_node(t_stack_node *stack);
t_stack_node	*get_last_node(t_stack_node *stack);
void			assign_index(t_stack_node *stack);
void			mark_cheapest_node(t_stack_node *stack);
void			prepare_stack_a_for_push(t_stack_node *a, t_stack_node *b);
void			prepare_stack_b_for_push(t_stack_node *, t_stack_node *b);

// Stack Operations
void	pa(t_stack_node **a, t_stack_node **b, bool suppress_output);
void	pb(t_stack_node **b, t_stack_node **a, bool suppress_output);
void	sa(t_stack_node **a, bool suppress_output);
void	sb(t_stack_node **b, bool suppress_output);
void	ss(t_stack_node **a, t_stack_node **b, bool suppress_output);
void	ra(t_stack_node **a, bool suppress_output);
void	rb(t_stack_node **b, bool suppress_output);
void	rr(t_stack_node **a, t_stack_node **b, bool suppress_ouput);
void	rra(t_stack_node **a, bool suppress_output);
void	rrb(t_stack_node **b, bool suppress_output);
void	rrr(t_stack_node **a, t_stack_node **b, bool suppress_output);
void	sort_three(t_stack_node **a);

// Algoritms
void	push_swap(t_stack_node **a, t_stack_node **b);
#endif
