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
			if (av[i][j] && !ft_isdigit(av[i][j]))
				return (1);
		}
		tmp = ft_atol(av[i]);
		if (tmp < 0 || tmp > 4294967295)
			return (1);
	}
	return (0);
}
