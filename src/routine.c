/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:30:30 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/18 15:49:01 by maelgini         ###   ########.fr       */
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

// Synchronize the start time for all philosophers
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

// small routine for the 1-philosopher case
void	lone_philo_case(t_program *program)
{
	if (program->num_philos == 1)
	{
		program->philos->start_time = get_time();
		status_msg(program, &program->philos[0], MSG_FORK, WHITE);
		my_usleep(program->time_to_die);
		status_msg(program, &program->philos[0], MSG_DEAD, RESET);
		free_program(program);
		return;
	}
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

//Monitor thread that checks cases that should stop the simulation
void	*monitor_routine(void *arg)
{
	int			i;
	t_program	*program;
	
	program = (t_program *)arg;
	while (get_time() < program->philos[0].start_time)
		usleep(100);
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
		usleep(10);
	}
}
