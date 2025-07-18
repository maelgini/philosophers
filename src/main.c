/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:08:33 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/18 14:07:20 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_program	*program;
	
	program = malloc(sizeof(t_program));
	if (!program)
		return (1);
	if (!check_args(ac, av))
	{
		free(program);
		return (1);
	}
	init_input(ac, av, program);
	init_mutexes(program);
	pthread_mutex_lock(&program->sim_lock);
	init_struct(program);
	if (handle_lone_philo(program))
		exit (0);
	create_forks(program);
	setup_forks(program);
	create_threads(program);
	pthread_mutex_unlock(&program->sim_lock);
	join_threads(program);
	free_program(program);
	return (0);
}