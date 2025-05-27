/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:39:45 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/25 18:10:53 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static const char	*get_arg_name(int index)
{
	const char	*arg_names[] = {
		NULL,
		ARG_NB_PHILO,
		ARG_TIME_DIE,
		ARG_TIME_EAT,
		ARG_TIME_SLEEP,
		ARG_NB_EAT_OPTIONAL
	};

	return (arg_names[index]);
}

bool	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static bool	validate_arg(char *arg, int i, int ac)
{
	int	value;

	if (!is_number(arg))
		return (printf("Error: argument %s must be a number\n"
				, get_arg_name(i)), false);
	value = ft_atoi(arg);
	if (i == 1 && value > 200)
		return (printf("Error: %s must be <= 200\n", get_arg_name(i)), false);
	if (i == 5 && ac == 6)
	{
		if (value < 0)
			return (printf("Error: %s must be >= 0\n", get_arg_name(i)), false);
	}
	else if (value <= 0)
		return (printf("Error: %s must be > 0\n", get_arg_name(i)), false);
	return (true);
}

bool	check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (printf("Error: wrong number of arguments\n"), false);
	i = 1;
	while (i < ac)
	{
		if (!validate_arg(av[i], i, ac))
			return (false);
		i++;
	}
	return (true);
}
