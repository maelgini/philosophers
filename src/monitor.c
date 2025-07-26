/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:32:50 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/26 17:59:19 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*	Check if all philosophers have eaten enough meals,
	updates the ith philo's field */		
int	all_philos_ate_enough(t_program *program)
{
	int	i;
	int	meals;

	if (program->num_meals <= 0)
		return (0);
	i = 0;
	while (i < program->num_philos)
	{
		pthread_mutex_lock(&program->meal_lock);
		meals = program->philos[i].meals_eaten;
		pthread_mutex_unlock(&program->meal_lock);
		if (meals < program->num_meals)
			return (0);
		i++;
	}
	return (1);
}

/*	Check if a philosopher has died by comparing the time since their last meal
	with their time_to_die, updates the stop_flag if a philosopher has died */
static bool	philo_died(t_program *program, int i)
{
	int		eating;
	size_t	last_meal;
	size_t	now;
	size_t	diff;

	pthread_mutex_lock(&program->meal_lock);
	last_meal = program->philos[i].last_meal;
	eating = program->philos[i].eating;
	pthread_mutex_unlock(&program->meal_lock);
	now = get_time();
	diff = now - last_meal;
	if (!eating && diff > program->philos[i].time_to_die)
	{
		pthread_mutex_lock(&program->dead_lock);
		program->stop_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		status_msg(program, &program->philos[i], MSG_DEAD, RESET);
		return (true);
	}
	return (false);
}

/*	Check if all philosophers have either died or eaten enough meals
	Returns true if any philosopher has died or if all have eaten enough */
static bool	all_ate_or_died(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		if (philo_died(program, i))
			return (true);
		i++;
	}
	if (all_philos_ate_enough(program))
	{
		pthread_mutex_lock(&program->dead_lock);
		program->stop_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		return (true);
	}
	return (false);
}

/*	Monitor thread that checks cases that should stop the simulation
	if every philo ate number_of_times_each_philosopher_must_eat or
	if a philo reached time_to_die */
void	*monitor_routine(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (get_time() < program->philos[0].start_time)
		usleep(50);
	while (1)
	{
		if (all_ate_or_died(program))
			return (NULL);
		usleep(10);
	}
}
