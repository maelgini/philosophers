/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:15:48 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/31 17:33:35 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//Fills the philosopher structure with input values
void	init_input(int ac, char **av, t_philo *philo)
{
	philo->num_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->num_meals = ft_atoi(av[5]);
	else
		philo->num_meals = -1;
}

// Initializes the philosopher structure with default values
void	init_struct(t_program *program, t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < philo->num_philos)
	{
		program->philos[i].program = program;
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = 0;
		program->philos[i].start_time = get_time();
		program->philos[i].num_philos = philo->num_philos;
		program->philos[i].time_to_die = philo->time_to_die;
		program->philos[i].time_to_eat = philo->time_to_eat;
		program->philos[i].time_to_sleep = philo->time_to_sleep;
		program->philos[i].num_meals = philo->num_meals;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		i++;
	}
}

// Creates threads for each philosopher and waits for them to finish
void	create_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philos[0].num_philos)
	{
		pthread_create(&program->philos[i].thread, NULL, routine,
			&program->philos[i]);
			i++;
	}
	i = 0;
	while (i < program->philos[0].num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}
