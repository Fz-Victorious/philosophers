/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:14:20 by fabou-za          #+#    #+#             */
/*   Updated: 2022/09/11 13:33:48 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroymutex_and_freeingmem(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&(info->fork_mutex[i]));
		i++;
	}
	free(info->fork_mutex);
	free(info->philos);
}

void	init_args(int ac, char **av, t_info	*info)
{
	info->num_philo = ft_atolg(av[0]);
	info->time_to_die = ft_atolg(av[1]);
	info->time_to_eat = ft_atolg(av[2]);
	info->time_to_sleep = ft_atolg(av[3]);
	if (ac == 5)
		info->max_meals = ft_atolg(av[4]);
}

void	create_threads(t_info *info, int ac)
{
	int	i;

	i = 0;
	info->start_time = getime_in_ms();
	while (i < info->num_philo)
	{
		info->philos[i].last_meal = getime_in_ms();
		pthread_create(&(info->philos[i].philo_thread), NULL, \
				&simulation, &(info->philos[i]));
		i++;
	}
	is_dead(info, ac);
}

void	init_philos_and_mutexes(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_phil) * info->num_philo);
	if (info->philos == NULL)
		return ;
	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (info->fork_mutex == NULL)
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
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_init(&(info->fork_mutex[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(info->action), NULL);
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
	init_philos_and_mutexes(&info);
	create_threads(&info, ac - 1);
	destroymutex_and_freeingmem(&info);
	return (0);
}
