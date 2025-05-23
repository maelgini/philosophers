/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:18:44 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/23 16:43:36 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d is eating\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->eating = 0;
}

// void	p_sleep(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->write_lock);
// 	printf("%zu %d is sleeping\n", get_time() - philo->start_time, philo->id);
// 	pthread_mutex_unlock(philo->write_lock);
// 	philo->last_meal = get_time();
// 	philo->meals_eaten++;
// 	philo->eating = 0;
// }