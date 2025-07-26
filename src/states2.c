/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:18:03 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/25 18:28:55 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	get_fork_order(t_philo *philo, int *first, int *second)
{
	int	tmp;

	*first = philo->left_fork_id;
	*second = philo->right_fork_id;
	if (*first > *second)
	{
		tmp = *first;
		*first = *second;
		*second = tmp;
	}
}

static void	lock_forks_and_log(t_philo *philo, int first, int second)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&program->forks[first]);
	status_msg(program, philo, MSG_FORK, WHITE);
	pthread_mutex_lock(&program->forks[second]);
	status_msg(program, philo, MSG_FORK, WHITE);
}

static void	update_meal_info(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&program->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&program->meal_lock);
}

static void	finish_meal(t_philo *philo, int first, int second)
{
	t_program	*program;

	program = philo->program;
	status_msg(program, philo, MSG_EAT, RED);
	my_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&program->forks[second]);
	pthread_mutex_unlock(&program->forks[first]);
	pthread_mutex_lock(&program->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&program->meal_lock);
}

void	p_eat(t_philo *philo)
{
	t_program	*program;
	int			first;
	int			second;

	program = philo->program;
	if (sim_stop(program))
		return ;
	get_fork_order(philo, &first, &second);
	lock_forks_and_log(philo, first, second);
	update_meal_info(philo);
	finish_meal(philo, first, second);
}
