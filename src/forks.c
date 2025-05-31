/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:28:41 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/31 16:25:51 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//Initialize mutexes for forks
void	create_forks(t_philo *philo, t_program *program)
{
	int	i;
	
	program->forks = malloc(sizeof(pthread_mutex_t) * philo->num_philos);
	if (!program->forks)
	{
		perror("Failed to allocate memory for forks");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < philo->num_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
		{
			perror("Failed to initialize mutex for fork");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

//Assigns left and right forks to each philosopher
void	setup_forks(t_philo *philo, t_program *program)
{
	int	i;

	i = 0;
	while (i < philo->num_philos)
	{
		philo[i].l_fork = &program->forks[i];
		philo[i].r_fork = &program->forks[(i + 1) % philo->num_philos];
		i++;
	}
}