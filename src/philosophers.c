/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:15:48 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/24 18:49:54 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//Initialize arguments
void	init_input(int ac, char **av, t_philo philo)
{
	philo.num_of_philos = ft_atoi(av[1]);
	philo.time_to_die = ft_atoi(av[2]);
	philo.time_to_eat = ft_atoi(av[3]);
	philo.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo.num_times_to_eat = ft_atoi(av[5]);
	else
		philo.num_times_to_eat = -1;
}

void	init_struct(int ac, char **av, t_philo *philo)
{
	int	i;

	i = 0;
	philo[i].id = i + 1;
	philo[i].eating = 0;
	philo[i].meals_eaten = 0;
	philo[i].start_time = get_time();
	philo[i].num_of_philos = ac - 1;
	philo[i].num_times_to_eat = ft_atoi(av[5]);
}

void	create_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_create(&program->philos[i].thread, NULL, routine,
			&program->philos[i]);
			i++;
	}
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}