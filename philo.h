/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:36:18 by fabou-za          #+#    #+#             */
/*   Updated: 2022/09/10 11:30:26 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

//data for each philosopher
typedef struct s_phil
{
	pthread_t		philo_thread;
	int				id;
	long			last_meal;
	int				l_frk;
	int				r_frk;
	struct s_info	*param;
}				t_phil;
//info for philosophers
typedef struct s_info
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				num_of_meals;
	long			start_time;
	t_phil			*philos;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	action;
}				t_info;
void	init_args(int ac, char **av, t_info *info);
//check for args
void	help_message(void );
long	ft_atolg(const char *str);
int		is_integer(long long int n);
int		is_num(char *av);
int		check_args(char **av);
void	*simulation(void *param);
void	print_action(t_info *info, char *message, int id);
void	is_dead(t_info *info, int ac);
long	getime_in_ms(void);
void	create_threads(t_info *info, int ac);
void	ft_usleep(int tm);
void	init_philos_and_mutexes(t_info *info);
void	destroymutex_and_freeingmem(t_info *info);

#endif
