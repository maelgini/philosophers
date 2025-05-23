/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:43:57 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/15 14:25:59 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char set)
{
	return (c == set);
}

int	count_words(char const *s, char c)
{
	int	cw;

	cw = 0;
	while (*s)
	{
		while (*s && is_set(*s, c))
			s++;
		if (*s)
			cw++;
		while (*s && !is_set(*s, c))
			s++;
	}
	return (cw);
}

char	*ft_strndup(const char *s, unsigned int n)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	dest = malloc(sizeof(char ) * (n + 1));
	if (!dest)
		return (NULL);
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	char		**tab;
	int			i;
	const char	*start;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && is_set(*s, c))
			s++;
		start = s;
		while (*s && !is_set(*s, c))
			s++;
		if (start != s)
			tab[i++] = ft_strndup(start, s - start);
	}
	tab[i] = NULL;
	return (tab);
}
