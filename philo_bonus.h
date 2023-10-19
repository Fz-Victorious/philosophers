/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 10:18:31 by fabou-za          #+#    #+#             */
/*   Updated: 2022/09/16 14:17:48 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

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
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals;
	int		num_of_meals;
	long	start_time;
	t_phil	*philos;
	sem_t	*fork_sem;
	int		*pid_arr;
	sem_t	*action;
}				t_info;
void	init_args(int ac, char **av, t_info *info);
//check for args
void	help_message(void );
long	ft_atolg(const char *str);
int		is_integer(long long int n);
int		is_num(char *av);
int		check_args(char **av);
void	*simulation(t_phil *philo);
void	print_action(t_info *info, char *message, int id);
void	*is_dead(void *info);
long	getime_in_ms(void);
void	create_processes(t_info *info);
int		process_fk(t_info *info);
void	kill_procs(t_info *info, int i);
void	ft_usleep(int tm);
void	actions(t_phil *philo, t_info *info);
void	init_philos_and_sem(t_info *info);
void	freeing_mem(t_info *info, int status);

#endif
