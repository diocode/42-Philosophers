/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:04:18 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/08 18:05:31 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	printf("PING[%ld]\n", philo->id);
	philo->data->death = DEATH;
	return (NULL);
}

static int	lonely_philo(t_data *data)
{
	data->start_t = get_time();
	if (data->start_t == 0)
		return (1);
	if (pthread_create(&data->table[0], NULL, &routine, &data->philos[0]))
		return (1);
	pthread_detach(data->table[0]);
	while (data->death == 0)
		usleep(0);
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
	if (data->n_philos == 1)
		lonely_philo(data);
	free_data(data);
}
