/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:30:30 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/24 18:36:01 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	simStop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->dead_lock);
	stop = philo->dead || philo->num_times_to_eat;
	pthread_mutex_unlock(&philo->dead_lock);
	return (stop);
}

void	routine(t_philo philo)
{
	while (!simStop(&philo))
	{
		/*
		eat
		sleep
		think
		*/
	}
}