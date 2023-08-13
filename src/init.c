/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:36:21 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/03 15:36:21 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philos(t_data *data)
{
	u_int64_t	i;

	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].status = 0;
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].status = 0;
		data->philos[i].death_t = data->death_t;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->n_philos - 1];
	i = 0;
	while (++i < data->n_philos)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
	}
}

static t_data	*init_threads(t_data *data)
{
	u_int64_t	i;

	data->death = 0;
	data->philos_full = 0;
	data->table = malloc(data->n_philos * sizeof(pthread_t));
	data->forks = malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!data->table || !data->forks)
		return (NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->log, NULL);
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (data);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_philos = ft_atol(av[1]);
	data->death_t = ft_atol(av[2]);
	data->eat_t = ft_atol(av[3]);
	data->sleep_t = ft_atol(av[4]);
	if (ac == 6)
		data->n_meals = ft_atol(av[5]);
	else
		data->n_meals = 0;
	if (!data->n_philos || !data->death_t || !data->eat_t || !data->sleep_t)
	{
		free(data);
		return (NULL);
	}
	data->start_t = 0;
	data->philos = malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (NULL);
	data = init_threads(data);
	init_philos(data);
	return (data);
}
