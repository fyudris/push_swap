/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:45:18 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/28 16:11:09 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/**
 * count_words: count the number of space delimited words
 * @param s:	input string
 * @param del:	delimiter character (space)
 *
 * This function iterates through th string, skipping delimiters and
 * increments the word count each time a new sequence of non-delimiter
 * characters begins.
 */
static	int count_words(char *s, char del)
{
	int	count;
	int	inside;

	count = 0;
	while (*s)
	{
		inside = 0;
		while (*s == del)
			s++;
		while (*s && *s != del)
		{
			if (!inside)
			{
				count++;
				inside = 1;
			}
			s++;
		}
	}
	return (count);
}
/**
 * get_word: extract the next word from string starting at index
 * @param s: input string
 * @param i: pointer to current index is s (updated past the word)
 * @param del: delimiter character
 *
 * This function skips delimiters, then measures the length of the next
 * token until the next delimiter or end, allocates a new string, and
 * returns it. On allocation failure, calls exit_error().
 */
static char *get_word(char *s, int *i, char del)
{
	int		start;
	int		len;
	char	*res;

	while (s[*i] && s[*i] == del)
		(*i)++;
	start = *i;
	len = 0;
	while (s[*i] && s[*i] != del)
	{
		(*i)++;
		len++;
	}
	res = ft_substr(s, start, len);
	if(!res)
		exit_error();
	return (res);
}

/**
 * parse_args: split a string of numbers by spaces into an argv-like array
 * @param str: input string of numbers separated by spaces
 *
 * This function validates input, counts tokens, allocates an array, and
 * populates it with substrings using get_word(), ending with NULL.
 * On any error, prints "Error" and exits.
 */
char	**parse_args(char *str)
{
	char	**res;
	int		words;
	int		i;
	int		idx;

	if (!str)
		exit_error();
	words = count_words(str, ' ');
	if (words < 1)
		exit_error();
	res = malloc((words + 1) * sizeof(char *));
	if (!res)
		exit_error();
	i = 0;
	idx = 0;
	while (i < words)
	{
		res[i] = get_word(str, &idx, ' ');
		i++;
	}
	res[i] = NULL;
	return (res);
}
/**
 * exit_error: writes "Error\n" to stderr and exits
 */
void	exit_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}
