/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:45:02 by fabou-za          #+#    #+#             */
/*   Updated: 2022/09/16 16:37:34 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	freeing_mem(t_info *info, int status)
{
	free(info->philos);
	free(info->pid_arr);
	sem_close(info->action);
	sem_close(info->fork_sem);
	sem_unlink("forks");
	sem_unlink("action");
	exit(status);
}

void	init_args(int ac, char **av, t_info	*info)
{
	info->num_philo = ft_atolg(av[0]);
	info->time_to_die = ft_atolg(av[1]);
	info->time_to_eat = ft_atolg(av[2]);
	info->time_to_sleep = ft_atolg(av[3]);
	if (ac == 5)
		info->max_meals = ft_atolg(av[4]);
	else
		info->max_meals = 0;
}

void	create_processes(t_info *info)
{
	int	i;
	int	status;

	info->start_time = getime_in_ms();
	i = -1;
	while (++i < info->num_philo)
	{
		info->pid_arr[i] = process_fk(info);
		if (!(info->pid_arr[i]))
			kill_procs(info, i);
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (status == 256)
			kill_procs(info, i);
	}
}

void	init_philos_and_sem(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_phil) * info->num_philo);
	if (info->philos == NULL)
		return ;
	info->pid_arr = malloc(sizeof(int) * info->num_philo);
	if (info->pid_arr == NULL)
		return ;
	i = 0;
	while (i < info->num_philo)
	{
		info->philos[i].id = i;
		info->philos[i].l_frk = i;
		info->philos[i].r_frk = (i + 1) % info->num_philo;
		info->philos[i].param = info;
		i++;
	}
	sem_unlink("forks");
	sem_unlink("action");
	info->fork_sem = sem_open("forks", O_CREAT, S_IRWXU, info->num_philo);
	info->action = sem_open("action", O_CREAT, S_IRWXU, 1);
	if (info->fork_sem == SEM_FAILED || info->action == SEM_FAILED)
		freeing_mem(info, 1);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
	{
		help_message();
		return (0);
	}
	if (!check_args(&av[1]))
	{
		printf("Invalid Arguments\n");
		return (0);
	}
	init_args(ac - 1, &av[1], &info);
	init_philos_and_sem(&info);
	create_processes(&info);
	freeing_mem(&info, 0);
	return (0);
}
