/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:18:44 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/27 16:45:54 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	status_msg(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d %s\n", get_time() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (philo->num_of_philos == 1)
	{
		status_msg(philo, MSG_FORK);
		my_usleep(philo->time_to_die + 1);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	status_msg(philo, MSG_FORK);
	status_msg(philo, MSG_EAT);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	my_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
}

void	p_sleep(t_philo *philo)
{
	status_msg(philo, MSG_SLEEP);
	my_usleep(philo->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	status_msg(philo, MSG_THINK);
}