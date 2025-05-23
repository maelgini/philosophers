/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:15:48 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/23 18:05:15 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//Initialize arguments
void	init_input(int ac, char **av, t_philo philo)
{
	int	i;

	i = 1;
	while (av[i])
	{
		philo.num_of_philos = ft_atoi(av[1]);
		philo.time_to_die = ft_atoi(av[2]);
		philo.time_to_eat = ft_atoi(av[3]);
		philo.time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo.num_times_to_eat = ft_atoi(av[5]);
		else
			philo.num_times_to_eat = -1;
		i++;
	}
}

// Initialize structure with given arguments
// void	init_struct(int ac, char **av)
// {
// 	t_program	*program;
// 	int			i;

// 	program = malloc(sizeof(t_program));
// 	if (!program)
// 		return ;
// 	program->dead_flag = 0;
// 	pthread_mutex_init(&program->dead_lock, NULL);
// 	pthread_mutex_init(&program->meal_lock, NULL);
// 	pthread_mutex_init(&program->write_lock, NULL);
// 	program->philos = malloc(sizeof(t_philo) * (ac - 1));
// 	if (!program->philos)
// 		return ;
// 	i = 0;
// 	while (i < ac - 1)
// 	{
// 		program->philos[i].id = i + 1;
// 		program->philos[i].eating = 0;
// 		program->philos[i].meals_eaten = 0;
// 		program->philos[i].start_time = get_time();
// 		program->philos[i].num_of_philos = ac - 1;
// 		program->philos[i].num_times_to_eat = ft_atoi(av[5]);
// 		i++;
// 	}
// }

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
