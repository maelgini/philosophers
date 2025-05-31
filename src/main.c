/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:08:33 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/31 16:22:18 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av, t_philo *philo, t_program *program)
{
	check_args(ac, av);
	init_struct(&program, program->philos);
	init_input(ac, av, *philo);
	create_forks(philo, &program);
	create_threads(&program);
	setup_forks(philo, &program);
	routine(philo, &program);
	return (0);
}