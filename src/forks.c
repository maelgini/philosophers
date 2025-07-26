/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:28:41 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/25 17:02:21 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//	Initializes num_philos mutexes for forks
void	create_forks(t_program *program)
{
	int	i;

	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
	{
		perror("Failed to allocate memory for forks");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
		{
			perror("Failed to initialize mutex for fork");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

//	Assigns left and right forks to each philosopher
void	setup_forks(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		program->philos[i].left_fork_id = i;
		program->philos[i].right_fork_id = (i + 1) % program->num_philos;
		i++;
	}
}
