/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:11:13 by maelgini          #+#    #+#             */
/*   Updated: 2024/11/14 16:08:08 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	char	c;

	c = (char)searchedChar;
	while (*string)
	{
		if (*string == c)
			return ((char *)string);
		string++;
	}
	if (c == '\0')
		return ((char *)string);
	return (NULL);
}
