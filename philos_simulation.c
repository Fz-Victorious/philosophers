/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:43:57 by fabou-za          #+#    #+#             */
/*   Updated: 2022/09/16 15:49:19 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	is_dead(t_info *info, int ac)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < info->num_philo)
		{
			if (ac == 5 && (info->num_of_meals >= \
						(info->max_meals * info->num_philo)))
			{
				pthread_mutex_lock(&info->action);
				return ;
			}
			if ((getime_in_ms() - info->philos[i].last_meal) \
					> info->time_to_die)
			{
				pthread_mutex_lock(&info->action);
				printf("%ld  ms  %d died\n", (getime_in_ms() - \
							info->start_time), info->philos[i].id + 1);
				return ;
			}
			usleep(50);
		}
	}
}

void	print_action(t_info *info, char *action, int id)
{
	pthread_mutex_lock(&info->action);
	printf("%ld  ms  %d %s\n", (getime_in_ms() - info->start_time), id, action);
	pthread_mutex_unlock(&info->action);
}

void	*simulation(void *param)
{
	t_phil	*philo;
	t_info	*info;

	philo = (t_phil *)param;
	info = philo->param;
	info->num_of_meals = 0;
	if (philo->id % 2)
		ft_usleep(100);
	while (1)
	{
		pthread_mutex_lock(&info->fork_mutex[philo->l_frk]);
		print_action(info, "has taken a fork", philo->id + 1);
		pthread_mutex_lock(&info->fork_mutex[philo->r_frk]);
		print_action(info, "has taken a fork", philo->id + 1);
		print_action(info, "is eating", philo->id + 1);
		philo->last_meal = getime_in_ms();
		ft_usleep(info->time_to_eat);
		pthread_mutex_unlock(&info->fork_mutex[philo->l_frk]);
		pthread_mutex_unlock(&info->fork_mutex[philo->r_frk]);
		info->num_of_meals++;
		print_action(info, "is sleeping", philo->id + 1);
		ft_usleep(info->time_to_sleep);
		print_action(info, "is thinking", philo->id + 1);
	}
	return (NULL);
}
