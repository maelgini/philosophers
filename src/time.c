/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelgini <maelgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:37:41 by maelgini          #+#    #+#             */
/*   Updated: 2025/07/25 18:57:41 by maelgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// Get the current time in milliseconds
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

// Sleep for a specified time in milliseconds
void	my_usleep(long long time_in_ms)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(50);
}
