/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:55:53 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/07 15:55:53 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

u_int64_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
	{
		error(NULL, "ERROR: gettimeofday()");
		return (0);
	}
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long	ft_atol(const char *nptr)
{
	long	sign;
	long	res;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return (res * sign);
}

int	check_input(char **av)
{
	int		i;
	int		j;
	long	tmp;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '-')
				return (1);
			if (av[i][j] == '+')
				j++;
			if (av[i][j] && (av[i][j] < '0' || av[i][j] > '9'))
				return (1);
		}
		tmp = ft_atol(av[i]);
		if (tmp < 0 || tmp > 4294967295)
			return (1);
	}
	return (0);
}

void	error(t_data *data, char *str)
{
	printf("%s\n", str);
	if (data)
		free_data(data);
}

void	free_data(t_data *data)
{
	u_int64_t	i;

	if (!data)
		return ;
	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->lock);
	if (data->table)
		free(data->table);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	free(data);
}
