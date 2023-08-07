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

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philos = ft_atol(av[1]);
	data->death_t = ft_atol(av[2]);
	data->eat_t = ft_atol(av[3]);
	data->sleep_t = ft_atol(av[4]);
	if (ac == 6)
		data->nbr_meals = ft_atol(av[5]);
	else
		data->nbr_meals = -1;
	return (data);
}
