/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:18:44 by maelgini          #+#    #+#             */
/*   Updated: 2025/06/25 16:28:17 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// Print a status message with the philosopher's ID and the message
void	status_msg(t_program *program, t_philo *philo, char *msg)
{
	pthread_mutex_lock(&program->write_lock);
	printf("%llu %d %s\n", get_time() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(&program->write_lock);
}

// Philosopher eats, locks the right and left forks, updates meal count and time
void	p_eat(t_philo *philo)
{
	t_program	*program;
	
	program = philo->program;
	if (sim_stop(philo->program))
		return ;
	pthread_mutex_lock(&program->forks[philo->right_fork_id]);
	if (program->num_philos == 1)
	{
		status_msg(program, philo, MSG_FORK);
		my_usleep(philo->time_to_die + 1);
		pthread_mutex_unlock(&program->forks[philo->right_fork_id]);
		return ;
	}
	pthread_mutex_lock(&program->forks[philo->left_fork_id]);
	status_msg(program, philo, MSG_FORK);
	status_msg(program, philo, MSG_EAT);
	pthread_mutex_lock(&program->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&program->meal_lock);
	my_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&program->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&program->forks[philo->right_fork_id]);
	pthread_mutex_lock(&program->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&program->meal_lock);
}

// Philosopher prints sleep message, and sleeps for the specified time
void	p_sleep(t_philo *philo)
{
	status_msg(philo->program, philo, MSG_SLEEP);
	my_usleep(philo->time_to_sleep);
}

// Philosopher prints think message
void	p_think(t_philo *philo)
{
	status_msg(philo->program, philo, MSG_THINK);
}