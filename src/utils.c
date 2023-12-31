/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:55:53 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/17 17:11:48 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_time(t_philo *philo, u_int64_t time)
{
	if ((get_time() + time) >= philo->death_t)
		usleep((philo->death_t - get_time()) * 1000);
	else
		usleep(time * 1000);
}

u_int64_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
	{
		printf("ERROR: gettimeofday()");
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
	pthread_mutex_destroy(&data->log);
	pthread_mutex_destroy(&data->finish_lock);
	if (data->table)
		free(data->table);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	free(data);
}
