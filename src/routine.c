/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:30:30 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/16 14:39:47 by maelgini         ###   ########.fr       */
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

void	sync_start(long long start, t_philo *philo)
{
	long long	now;
	long long	time;
	long long	delay;
	
	now = get_time();
	time = start - now;
	delay = philo->time_to_eat / (philo->program->num_philos - 1);
	if (philo->program->num_philos % 2)
	{
		time += delay * (philo->id);
		if (philo->id % 2)
			time += philo->time_to_eat - 100;
	}
	else if (philo->id % 2)
	{
		time += philo->time_to_eat;
		my_usleep(time);
	}
}

// Main routine for each philosopher
void	*routine(void *arg)
{
	t_philo	*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	// if (!philo)
	// {
	// 	printf("Error: routine received NULL philo\n");
	// 	return NULL;
	// }
	// program = philo->program;
	// if (!program)
	// {
	// 	printf("Error: philo->program is NULL (philo id = %d)\n", philo->id);
	// 	return NULL;
	// }
	// printf("Routine start: philo=%p, program=%p\n", philo, philo->program);
	//attendre tout pour avoir depasser start_time
	while (get_time() < philo->start_time)
	{
		sync_start(program->philos->start_time, program->philos);
		usleep(100);
	}
	while (!sim_stop(program))
	{
		p_eat(philo);
		if (sim_stop(program))
			break;
		p_sleep(philo);
		if (sim_stop(program))
			break;
		p_think(philo);
		my_usleep(100);
	}
	return (NULL);
}

// Check if all philosophers have eaten enough meals
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

//Monitor thread that checks if a philosopher has died or if all have eaten enough
void	*monitor_routine(void *arg)
{
	t_program	*program;
	int	i;
	
	program = (t_program *)arg;
	// if (!program)
	// {
	//     printf("Error: monitor_routine received NULL program\n");
	//     pthread_exit(NULL);
	// }
	// printf("Monitor routine started with program = %p\n", program);
	while (get_time() < program->philos[0].start_time)
	{
		usleep(100);
	}
	while (1)
	{
		i = 0;
		while (i < program->num_philos)
		{
			pthread_mutex_lock(&program->meal_lock);
			size_t last_meal = program->philos[i].last_meal;
			int eating = program->philos[i].eating;
			pthread_mutex_unlock(&program->meal_lock);

			size_t now = get_time();
			size_t diff = now - last_meal;

			// printf("philo[%d] last_meal = %zu, now = %zu, diff = %zu\n",
			// program->philos[i].id, last_meal, now, diff);

			if (!eating && diff > program->philos[i].time_to_die)
			{
				pthread_mutex_lock(&program->dead_lock);
				program->stop_flag = 1;
				pthread_mutex_unlock(&program->dead_lock);
				status_msg(program, &program->philos[i], MSG_DEAD, RESET);
				return (NULL);
			}
			i++;
		}
		if (all_philos_ate_enough(program))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->stop_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return (NULL);
		}
		usleep(10); // Sleep for a short time to avoid busy waiting
	}
}
