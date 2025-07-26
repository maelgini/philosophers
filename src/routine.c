/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:30:30 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/26 19:55:37 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*	Check if the simulation should stop by looking at the stop flag
	It will be updated by the monitor thread when a philosopher dies */
int	sim_stop(t_program *program)
{
	int	stop;

	pthread_mutex_lock(&program->dead_lock);
	stop = program->stop_flag;
	pthread_mutex_unlock(&program->dead_lock);
	return (stop);
}

/*	Shifts the start time of each philosopher to avoid simultaneous eating
	Ensure that philosophers start at staggered times*/
// void	sync_start(long long start, t_philo *philo)
// {
// 	long long	now;
// 	long long	time;
// 	long long	delay;

// 	now = get_time();
// 	time = start - now;
// 	delay = philo->time_to_eat / (philo->program->num_philos - 1);
// 	if (philo->program->num_philos % 2)
// 	{
// 		time += delay * (philo->id);
// 		if (philo->id % 2)
// 			time += philo->time_to_eat - 100;
// 	}
// 	else if (philo->id % 2)
// 	{
// 		time += philo->time_to_eat;
// 		my_usleep(time);
// 	}
// }

/*	Main routine for each philosopher, we call the sim_stop function between
	each action to ensure the simulation stops instantly to avoid
	philosophers finishing their cycle */
void	*routine(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	while (get_time() < philo->start_time)
		usleep(50);
	my_usleep((philo->id % 2) * 10);
	while (!sim_stop(program))
	{
		p_eat(philo);
		if (sim_stop(program))
			break ;
		p_sleep(philo);
		if (sim_stop(program))
			break ;
		p_think(philo);
	}
	return (NULL);
}

// Small routine for the 1-philosopher case
void	lone_philo_case(t_program *program)
{
	if (program->num_philos == 1)
	{
		program->philos->start_time = get_time();
		status_msg(program, &program->philos[0], MSG_FORK, WHITE);
		my_usleep(program->time_to_die);
		status_msg(program, &program->philos[0], MSG_DEAD, RESET);
		return ;
	}
}
