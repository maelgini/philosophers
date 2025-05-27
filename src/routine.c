/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:30:30 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/27 18:07:09 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	sim_stop(t_program *program)
{
	int	stop;

	pthread_mutex_lock(&program->dead_lock);
	stop = program->stop_flag;
	pthread_mutex_unlock(&program->dead_lock);
	return (stop);
}

void	routine(t_philo *philo, t_program *program)
{
	while (!sim_stop(&philo))
	{
		p_eat(&philo);
		p_think(&philo);
		p_sleep(&philo);
	}
}