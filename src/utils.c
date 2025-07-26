/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:56:35 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/25 18:26:32 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// may use this later
// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	size_t			total;
// 	size_t			i;
// 	unsigned char	*ptr;

// 	total = nmemb * size;
// 	if (nmemb != 0 && total / nmemb != size)
// 		return (NULL); // protection overflow
// 	ptr = malloc(total);
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	while (i < total)
// 		ptr[i++] = 0;
// 	return ((void *)ptr);
// }

//Array to integer conversion function to extract arguments from command line
int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	n = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
			n = n * 10 + *nptr - '0';
			nptr++;
	}
	return (n * sign);
}

// launches the 1-philosopher case
bool	handle_lone_philo(t_program *program)
{
	if (program->num_philos == 1)
	{
		lone_philo_case(program);
		pthread_mutex_unlock(&program->sim_lock);
		free_program(program);
		return (true);
	}
	return (false);
}

// Frees the allocated memory for philosophers and destroys mutexes
void	free_program(t_program *program)
{
	int	i;

	i = 0;
	if (!program)
		return ;
	if (program->forks)
	{
		while (i < program->num_philos)
		{
			pthread_mutex_destroy(&program->forks[i]);
			i++;
		}
		free(program->forks);
		program->forks = NULL;
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->sim_lock);
	if (program->philos)
		free(program->philos);
	free(program);
}
