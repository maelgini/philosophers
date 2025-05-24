/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:21:04 by maelgini          #+#    #+#             */
/*   Updated: 2025/05/24 17:47:24 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

#define ARG_NB_PHILO		"number_of_philosophers"
#define ARG_TIME_DIE		"time_to_die"
#define ARG_TIME_EAT		"time_to_eat"
#define ARG_TIME_SLEEP		"time_to_sleep"
#define ARG_NB_EAT_OPTIONAL	"number_of_times_each_philosopher_must_eat"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

bool		check_args(int ac, char **av);
void		*routine(void *arg);
void		p_eat(t_philo *philo);
void		init_struct(int ac, char **av, t_philo *philo);
void		create_threads(t_program *program);
void		my_usleep(long long time_in_ms);
long long	get_time(void);