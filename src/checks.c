/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:07:18 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/03 14:07:18 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	is_full(t_philo	*philo)
{
	if (philo->meals >= philo->data->n_meals
		&& philo->data->n_meals != 0 && !philo->full)
	{
		philo->data->philos_full++;
		philo->full = true;
	}
}

bool	is_dead(t_philo *philo)
{
	bool	dead;

	dead = false;
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->finish_lock);
	if (get_time() >= philo->death_t || philo->data->finish)
	{
		if (!philo->data->finish)
			logs(philo, DEATH);
		philo->data->finish = true;
	}
	pthread_mutex_lock(&philo->data->lock);
	is_full(philo);
	if (philo->data->philos_full == philo->data->n_philos)
		philo->data->finish = true;
	dead = philo->data->finish;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->finish_lock);
	pthread_mutex_unlock(&philo->lock);
	return (dead);
}

bool	is_solo(t_philo *philo)
{
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_lock(philo->fork[RIGHT]);
		logs(philo, FORK);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		logs(philo, THINKING);
		while (!is_dead(philo))
			;
		return (true);
	}
	return (false);
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
	if (av[2][0] == '0' && !av[2][1])
		return (1);
	return (0);
}
