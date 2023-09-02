/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:50:07 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/02 00:50:58 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	logs(t_philo *p, int status)
{
	pthread_mutex_lock(&p->data->finish_lock);
	pthread_mutex_lock(&p->data->log);
	if ((status == DEATH || status == FULL) && !p->data->finish)
	{
		if (status == DEATH)
			printf("%lu %lu died\n", get_time() - p->data->start_t, p->id);
		p->data->finish = true;
	}
	else if (status == EATING && !p->data->finish)
		printf("%lu %lu is eating\n", get_time() - p->data->start_t, p->id);
	else if (status == SLEEPING && !p->data->finish)
		printf("%lu %lu is sleeping\n", get_time() - p->data->start_t, p->id);
	else if (status == THINKING && !p->data->finish)
		printf("%lu %lu is thinking\n", get_time() - p->data->start_t, p->id);
	else if (status == FORK && !p->data->finish)
		printf("%lu %lu has taken a fork\n",
			get_time() - p->data->start_t, p->id);
	pthread_mutex_unlock(&p->data->log);
	pthread_mutex_unlock(&p->data->finish_lock);
}

static int	reunion(t_data *data)
{
	u_int64_t	n;

	data->start_t = get_time();
	if (data->start_t == 0)
		return (1);
	pthread_mutex_lock(&data->lock);
	n = 0;
	while (n < data->n_philos)
	{
		if (pthread_create(&data->table[n], NULL, &routine, &data->philos[n]))
			return (1);
		n++;
	}
	pthread_mutex_unlock(&data->lock);
	n = 0;
	while (n < data->n_philos)
	{
		if (pthread_join(data->table[n], NULL))
			return (1);
		n++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;

	if ((ac != 5 && ac != 6) || check_input(av))
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	data = init_data(ac, av);
	if (!data)
	{
		free_data(data);
		return (1);
	}
	reunion(data);
	free_data(data);
}
