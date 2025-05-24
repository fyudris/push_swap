/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:45:18 by fyudris           #+#    #+#             */
/*   Updated: 2025/05/24 19:27:56 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// TODO: Int inputs works but String input is not hadled properly
/**
 * int inputs are sorted correctly, but input in form of String has different output (not sorted)
 */
// TODO: You have not handled int overflow (when you have a really long number value!)

// TODO: Implement more streamlined testing mechanism


/**
 * Returns the substring count in a string separated by delimiter
 */
static int	count_words(char *s, char del)
{
	int		count;
	bool	inside_word;

	count = 0;
	while (*s)
	{
		inside_word = false;
		while (*s == del)
			++s;
		while (*s != del && *s)
		{
			if (!inside_word)
			{
				++count;
				inside_word = true;
			}
			++s;
		}
	}
	return (count);
}

/**
 * Returns the new substring found within a string
 * @param s string
 * @param del delimiter
 */
static char	*get_next_word(char *s, char del)
{
	static int	post = 0;
	char		*next_word;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (s[post] == del)
		++post;
	while ((s[post + len] != del) && s[post + len])
		++len;
	next_word = malloc((size_t)len * sizeof(char) + 1);
	if (!next_word)
		return (NULL);
	while ((s[post] != del) && s[post])
		next_word[i++] = s[post++];
	next_word[i] = '\0';
	return (next_word);
}

/**
 * Splits a string into words or world-like units (tokenization) based on a delimiter. In case of error, exit with error code (1).
 *
 * @param s string
 * @param del delimiter
 */
char	**parse_args(char *s, char del)
{
	int		word_count;
	char	**result;
	int		i;

	i = 0;
	word_count = count_words(s, del);
	if (!word_count)
		exit(1);
	result = malloc((size_t)(word_count + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < word_count)
	{
		if (i == 0)
		{
			// result[i] = malloc(sizeof(char));
			if (!result)
				return (NULL);
			result[i++] = get_next_word(s, del);
			continue;
		}
		result[i++] = get_next_word(s, del);
	}
	result[i] = NULL;
	return (result);
}

