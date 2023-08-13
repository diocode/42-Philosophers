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

static int	reunion(t_data *data)
{
	u_int64_t	n;


	data->start_t = get_time();
	if (data->start_t == 0)
		return (1);
	n = 0;
	while (n < data->n_philos)
	{
		if (pthread_create(&data->table[n], NULL, &routine, &data->philos[n]))
			return (1);
		n++;
	}
	n = 0;
	while (n < data->n_philos)
	{
		if (pthread_join(data->table[n], NULL))
			return (1);
		n++;
	}
	return (0);
}

static int	lonely_philo(t_data *data)
{
	data->start_t = get_time();
	if (data->start_t == 0)
		return (1);
	if (pthread_create(&data->table[0], NULL, &routine, &data->philos[0]))
		return (1);
	pthread_detach(data->table[0]);
	while (data->death != DEATH)
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
	else
		reunion(data);
	free_data(data);
}

/*
 * NOTES:
 * - Check valgrind and leaks;
 * - Check unusual arguments;
 * - Check if my time output is in the correct format;
 * - Check if it's ok for the inputs to show up after the died or full message
 * 	 (it should be oh because the threads are running at the same time);
 * - Check if the program is working when: none die | philo dies | meals completed
 * */