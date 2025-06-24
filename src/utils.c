/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:56:35 by maelgini          #+#    #+#             */
/*   Updated: 2025/06/24 17:44:46 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//Array to integer conversion function to extract arguments from command line
int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	n = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
			n = n * 10 + *nptr - '0';
			nptr++;
	}
	return (n * sign);
}

//Returns allocated memory for philosophers
void	free_philos(t_philo *philos, int num_philos)
{
	int i;

	for (i = 0; i < num_philos; i++)
	{
		pthread_mutex_destroy(philos[i].r_fork);
		pthread_mutex_destroy(philos[i].l_fork);
	}
	free(philos);
}