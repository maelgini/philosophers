/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:08:33 by maelgini          #+#    #+#             */
/*   Updated: 2025/06/25 17:08:00 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_program	*program;
	
	program = malloc(sizeof(t_program));
	if (!program)
		return (1);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	printf("IN CHECK_ARGS\n");
	check_args(ac, av);
	printf("IN INIT_INPUT\n");
	init_input(ac, av, program);
	printf("IN INIT_MUTEXES\n");
	init_mutexes(program);
	printf("IN INIT_STRUCT\n");
	init_struct(program);
	printf("IN CREATE_FORKS\n");
	create_forks(program);
	printf("IN SETUP_FORKS\n");
	setup_forks(program);
	printf("IN CREATE_THREADS\n");
	create_threads(program);
	printf("IN ROUTINE\n");
	routine(philo);
	return (0);
}