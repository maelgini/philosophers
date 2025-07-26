/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:15:48 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/25 18:25:36 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// Initializes mutexes for the program
void	init_mutexes(t_program *program)
{
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->sim_lock, NULL);
}

// Fills the philosopher structure with input values
void	init_input(int ac, char **av, t_program *program)
{
	program->num_philos = ft_atoi(av[1]);
	program->time_to_die = ft_atoi(av[2]);
	program->time_to_eat = ft_atoi(av[3]);
	program->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		program->num_meals = ft_atoi(av[5]);
	else
		program->num_meals = -1;
}

// Initializes the philosopher structure with default values
void	init_struct(t_program *program)
{
	int			i;
	long long	start_time;

	i = 0;
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	start_time = get_time() + 1000;
	program->stop_flag = 0;
	while (i < program->num_philos)
	{
		program->philos[i].time_to_die = program->time_to_die;
		program->philos[i].time_to_eat = program->time_to_eat;
		program->philos[i].time_to_sleep = program->time_to_sleep;
		program->philos[i].program = program;
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].meals_eaten = 0;
		program->philos[i].start_time = start_time;
		program->philos[i].last_meal = program->philos[i].start_time;
		i++;
	}
}

/*	Create threads for each philosopher and assigns them to the routine
	Create monitor thread separately beforehand */
void	create_threads(t_program *program)
{
	int	i;

	i = 0;
	pthread_create(&program->monitor_thread, NULL, monitor_routine, program);
	while (i < program->num_philos)
	{
		pthread_create(&program->philos[i].thread,
			NULL, routine, &program->philos[i]);
		i++;
	}
}

// Joins all philosopher threads and the monitor thread
void	join_threads(t_program *program)
{
	int	i;

	pthread_join(program->monitor_thread, NULL);
	i = 0;
	while (i < program->num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}
