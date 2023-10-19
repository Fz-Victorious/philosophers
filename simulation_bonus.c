/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:09:39 by fabou-za          #+#    #+#             */
/*   Updated: 2022/09/16 17:22:13 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_info *info, char *action, int id)
{
	sem_wait(info->action);
	printf("%ld %d %s\n", (getime_in_ms() - info->start_time), id, action);
	sem_post(info->action);
}

int	process_fk(t_info *info)
{
	static int	i;
	int			pid;

	pid = fork();
	if (!pid)
	{
		info->philos[i].last_meal = getime_in_ms();
		if (pthread_create(&(info->philos[i].philo_thread), \
					NULL, &is_dead, &info->philos[i]))
			exit(0);
		simulation(&info->philos[i]);
	}
	i++;
	return (pid);
}

void	kill_procs(t_info *info, int i)
{
	i--;
	while (i >= 0)
	{
		kill(info->pid_arr[i], SIGINT);
		i--;
	}
	exit(0);
}

void	actions(t_phil *philo, t_info *info)
{
	sem_wait(info->fork_sem);
	print_action(info, "has taken a fork", philo->id + 1);
	sem_wait(info->fork_sem);
	print_action(info, "has taken a fork", philo->id + 1);
	print_action(info, "is eating", philo->id + 1);
	philo->last_meal = getime_in_ms();
	ft_usleep(info->time_to_eat);
	sem_post(info->fork_sem);
	sem_post(info->fork_sem);
	info->num_of_meals++;
	print_action(info, "is sleeping", philo->id + 1);
	ft_usleep(info->time_to_sleep);
	print_action(info, "is thinking", philo->id + 1);
}

void	*simulation(t_phil *philo)
{
	t_info	*info;
	int		i;

	info = philo->param;
	if (philo->id % 2)
		ft_usleep(100);
	if (info->max_meals != 0)
	{
		i = 0;
		while (i < info->max_meals)
		{
			actions(philo, info);
			i++;
		}
	}
	else
	{
		while (1)
		{
			actions(philo, info);
		}
	}
	return (NULL);
}
