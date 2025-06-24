/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:18:44 by maelgini          #+#    #+#             */
/*   Updated: 2025/06/24 17:59:31 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// Print a status message with the philosopher's ID and the message
void	status_msg(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%llu %d %s\n", get_time() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

// Philosopher eats, locks the right and left forks, updates meal count and time
void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (philo->num_philos == 1)
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

// Philosopher sleeps, prints sleep message, and sleeps for the specified time
void	p_sleep(t_philo *philo)
{
	status_msg(philo, MSG_SLEEP);
	my_usleep(philo->time_to_sleep);
}

// Philosopher thinks, prints think message
void	p_think(t_philo *philo)
{
	status_msg(philo, MSG_THINK);
}