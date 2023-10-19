/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:35:45 by fabou-za          #+#    #+#             */
/*   Updated: 2022/09/16 16:38:25 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	getime_in_ms(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	ft_usleep(int duration)
{
	long	time_to_stop;

	time_to_stop = getime_in_ms() + duration;
	while (getime_in_ms() < time_to_stop)
		usleep(50);
	return ;
}

void	*is_dead(void *params)
{
	t_phil	*philo;
	t_info	*info;

	philo = (t_phil *)params;
	info = philo->param;
	while (1)
	{
		if ((getime_in_ms() - philo->last_meal) > info->time_to_die)
		{
			sem_wait(info->action);
			printf("%ld %d died\n", getime_in_ms() - info->start_time, \
					philo->id + 1);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}
