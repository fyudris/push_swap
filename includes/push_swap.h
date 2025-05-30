/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:30:05 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/30 18:02:20 by fyudris          ###   ########.fr       */
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

/* Parsing Input Arguments */
char			**parse_args(char *s);
void			exit_error(void);
void			validator(char **nums);
int				is_error_syntax(char *str);
int				is_error_duplicate(t_stack_node *stack, int n);

/* Stack Initialization */
void			init_stack(t_stack_node **a, char **nums);
void			free_stack(t_stack_node **stack);
void			free_str_array(char **arr);

/* Stack Utils */
int				stack_size(t_stack_node *stack);
t_stack_node	*get_min_node(t_stack_node *stack);
t_stack_node	*get_max_node(t_stack_node *stack);
int				is_stack_sorted(t_stack_node *stack);

/* Stack Operations */
void			sa(t_stack_node **a, bool write_op);
void			sb(t_stack_node **b, bool write_op);
void			ss(t_stack_node **a, t_stack_node **b, bool write_op);
void			pa(t_stack_node **a, t_stack_node **b, bool write_op);
void			pb(t_stack_node **b, t_stack_node **a, bool write_op);
void			ra(t_stack_node **a, bool write_op);
void			rb(t_stack_node **b, bool write_op);
void			rr(t_stack_node **a, t_stack_node **b, bool write_op);
void			rra(t_stack_node **a, bool write_op);
void			rrb(t_stack_node **b, bool write_op);
void			rrr(t_stack_node **a, t_stack_node **b, bool write_op);

/* Sorting Operations */
void			sort_three(t_stack_node **a);

/* Algorithm / push_swap controller*/
void			assign_index(t_stack_node *node);
void			calculate_push_costs(t_stack_node *a, t_stack_node *b);
void			mark_cheapest_node(t_stack_node *a);
void			assign_targets_in_a(t_stack_node *a, t_stack_node *b);
void			assign_targets_in_b(t_stack_node *a, t_stack_node *b);
void			push_swap(t_stack_node **a, t_stack_node **b);
void			push_cheapest_a_to_b(t_stack_node **a, t_stack_node **b);
void			push_b_to_target_in_a(t_stack_node **a, t_stack_node **b);
void			rotate_min_to_top(t_stack_node **a);
t_stack_node	*get_cheapest_node(t_stack_node *stack);
void			rotate_both_for_push(t_stack_node **a, t_stack_node **b,
					t_stack_node *cheapest);
void			reverse_rotate_both_for_push(t_stack_node **a, t_stack_node **b,
					t_stack_node *cheapest);
void			push_to_top(t_stack_node **stack, t_stack_node *node,
					char name);
#endif
