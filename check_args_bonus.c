/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:35:30 by fabou-za          #+#    #+#             */
/*   Updated: 2022/09/10 11:34:45 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	help_message(void )
{
	printf("The program takes the following arguments\n");
	printf("./philo <number_of_philosophers> <time_to_die> <time_to_eat> ");
	printf("<time_to_sleep> and an optional arg <number_of_max_meals>\n");
}

long	ft_atolg(const char *str)
{
	int		i;
	int		n;
	int		negtv;
	long	sum;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	negtv = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negtv = -1;
		i++;
	}
	sum = 0;
	n = 0;
	while ((str[i] >= 48 && str[i] <= 57) && str[i])
	{
		n = (str[i] - 48);
		sum = ((sum * 10) + n * negtv);
		i++;
	}
	return (sum);
}

int	is_integer(long long int n)
{
	if (n < 0 || n > 2147483647)
		return (0);
	return (1);
}

int	is_num(char *av)
{
	int	i;

	i = 0;
	if ((av[i] == '+') && \
			((av[i + 1]) >= '0' && av[i + 1] <= '9'))
		i++;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **av)
{
	int		i;
	long	data;

	i = 0;
	if (ft_atolg(av[0]) == 0)
		return (0);
	while (av[i])
	{
		if (!(is_num(av[i])))
			return (0);
		data = ft_atolg(av[i]);
		if (data < 0)
			return (0);
		if (!is_integer(data))
			return (0);
		i++;
	}
	return (1);
}
