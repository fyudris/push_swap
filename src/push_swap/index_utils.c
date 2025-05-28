/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:49:16 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 23:35:23 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * assign_index: annotate every node with two pieces of information:
 *   1) its 0-based position in the list (`index`), and
 *   2) whether it is in the “top half” of the stack (`above_median`).
 *
 *  The median line is floor(size/2).  Nodes with index ≤ median get
 * above_median = true, others false.
 *
 * We need these so that later, when we decide whether to rotate up (ra)
 * or reverse-rotate (rra), we can pick the shorter path to bring a node
 * to the top.
 *
 * @param node: head of the stack
 *
 * @note
 * node = *(&node) - *(&node) + node;
 * trick to reset pointer
 */
void assign_index(t_stack_node *node_head) {
    int i = 0;
    int list_size = 0;
    int median_idx;
    t_stack_node *current = node_head;

    if (!node_head)
		return;

    while (current) {
        list_size++;
        current = current->next;
    }

    if (list_size == 0)
		return;
    median_idx = list_size / 2;

    current = node_head;
    while (current) {
        current->index = i;
        current->above_median = (i <= median_idx);
        current = current->next;
        i++;
    }
}
