/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:08:33 by maelgini          #+#    #+#             */
/*   Updated: 2025/06/24 18:36:50 by maelgini         ###   ########.fr       */
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
	init_input(ac, av, philo);
	printf("IN INIT_STRUCT\n");
	init_struct(program, philo);
	printf("IN CREATE_FORKS\n");
	create_forks(philo, program);
	printf("IN SETUP_FORKS\n");
	create_threads(program);
	printf("IN SETUP_FORKS\n");
	setup_forks(philo, program);
	printf("IN CREATE_THREADS\n");
	routine(philo);
	printf("IN ROUTINE\n");
	return (0);
}