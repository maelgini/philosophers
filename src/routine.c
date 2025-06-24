/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:30:30 by maelgini          #+#    #+#             */
/*   Updated: 2025/06/24 17:43:25 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// Check if the simulation should stop
int	sim_stop(t_program *program)
{
	int	stop;

	pthread_mutex_lock(&program->dead_lock);
	stop = program->stop_flag;
	pthread_mutex_unlock(&program->dead_lock);
	return (stop);
}

// Main routine for each philosopher
void	*routine(void *arg)
{
	t_philo	*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	while (!sim_stop(program))
	{
		if (sim_stop(program))
			break;
		p_eat(philo);
		if (sim_stop(program))
			break;
		p_sleep(philo);
		if (sim_stop(program))
			break;
		p_think(philo);
	}
	return (NULL);
}

// Check if all philosophers have eaten enough meals
int	all_philos_ate_enough(t_program *program, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philos)
	{
		pthread_mutex_lock(program->philos[i].meal_lock);
		if (program->philos[i].meals_eaten < philo->num_meals)
		{
			pthread_mutex_unlock(program->philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(program->philos[i].meal_lock);
		i++;
	}
	return (1);
}

//Monitor thread that checks if a philosopher has died or if all have eaten enough
void	*monitor_routine(t_program *program, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->num_philos)
		{
			pthread_mutex_lock(program->philos[i].meal_lock);
			if (!program->philos[i].eating && 
				(get_time() - program->philos[i].last_meal > program->philos[i].time_to_die))
			{
				pthread_mutex_lock(&program->dead_lock);
				program->stop_flag = 1;
				pthread_mutex_unlock(&program->dead_lock);
				status_msg(&program->philos[i], "died");
				pthread_mutex_unlock(program->philos[i].meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(program->philos[i].meal_lock);
			i++;
		}
		if (all_philos_ate_enough(program, philo))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->stop_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return (NULL);
		}
	}
}
