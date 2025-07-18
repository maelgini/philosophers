/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:18:44 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/18 15:05:23 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <string.h>

// Print a status message with the philosopher's ID and the message
void	status_msg(t_program *program, t_philo *philo, char *msg, char *color)
{
	// printf("DEBUG: philo->start_time=%llu, get_time()=%llu, philo->id=%d\n",
	// philo->start_time, get_time(), philo->id);
	pthread_mutex_lock(&program->dead_lock);
	if (strcmp(msg, MSG_DEAD) == 0)
	{
		pthread_mutex_lock(&program->write_lock);
		printf("%s%llu\t%d\t%s\033[0m\n", color, get_time() - philo->start_time, philo->id, msg);
		pthread_mutex_unlock(&program->write_lock);
	}
	else if (!program->stop_flag)
	{
		pthread_mutex_lock(&program->write_lock);
		printf("%s%llu\t%d\t%s\033[0m\n", color, get_time() - philo->start_time, philo->id, msg);
		pthread_mutex_unlock(&program->write_lock);
	}
	pthread_mutex_unlock(&program->dead_lock);
}

// Philosopher eats, locks the right and left forks, updates meal count and time
void	p_eat(t_philo *philo)
{
	t_program	*program = philo->program;

	if (sim_stop(program))
		return ;
	// printf("Philo %d → left=%d, right=%d\n", philo->id, philo->left_fork_id, philo->right_fork_id);
	int first_fork = philo->left_fork_id;
	int second_fork = philo->right_fork_id;
	if (first_fork > second_fork)
	{
		int tmp = first_fork;
		first_fork = second_fork;
		second_fork = tmp;
	}
	pthread_mutex_lock(&program->forks[first_fork]);
	status_msg(program, philo, MSG_FORK, WHITE);
	pthread_mutex_lock(&program->forks[second_fork]);
	pthread_mutex_lock(&program->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&program->meal_lock);
	status_msg(program, philo, MSG_FORK, WHITE);
	status_msg(program, philo, MSG_EAT, RED);

	my_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&program->forks[second_fork]);
	pthread_mutex_unlock(&program->forks[first_fork]);
	pthread_mutex_lock(&program->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&program->meal_lock);
}

// Philosopher prints sleep message, and sleeps for the specified time
void	p_sleep(t_philo *philo)
{
	status_msg(philo->program, philo, MSG_SLEEP, BLUE);
	my_usleep(philo->time_to_sleep);
}

// Philosopher prints think message
void	p_think(t_philo *philo)
{
	status_msg(philo->program, philo, MSG_THINK, GREEN);
	my_usleep(100);
}