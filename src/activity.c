/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:39:24 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/02 01:15:53 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	solo(t_philo *philo)
{
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_lock(philo->fork[0]);
		logs(philo, FORK);
		pthread_mutex_unlock(philo->fork[0]);
		pthread_mutex_lock(&philo->data->finish_lock);
		philo->data->solo = true;
		pthread_mutex_unlock(&philo->data->finish_lock);
		return (true);
	}
	return (false);
}

static bool	get_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(philo->fork[fork]);
	pthread_mutex_lock(&philo->data->finish_lock);
	if (philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		pthread_mutex_unlock(philo->fork[fork]);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->finish_lock);
	logs(philo, FORK);
	return (true);
}

//right_fork = 0 | left_fork = 1
static bool	get_forks(t_philo *philo)
{
	int	fork1;
	int	fork2;

	fork1 = 1;
	fork2 = 0;
	if (solo(philo))
		return (false);
	if (philo->id % 2 == 0)
	{
		fork1 = 0;
		fork2 = 1;
	}
	if (!get_fork(philo, fork1))
		return (false);
	if (!get_fork(philo, fork2))
	{
		pthread_mutex_unlock(philo->fork[fork1]);
		return (false);
	}
	return (true);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork[1]);
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_lock(&philo->data->finish_lock);
	if (philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->finish_lock);
	logs(philo, SLEEPING);
	wait_time(philo, philo->data->sleep_t);
}

void	eating(t_philo *philo)
{
	if (!get_forks(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->status = EATING;
	logs(philo, EATING);
	philo->death_t = get_time() + philo->data->death_t;
	wait_time(philo, philo->data->eat_t);
	philo->status = 0;
	philo->meals++;
	pthread_mutex_unlock(&philo->lock);
	sleeping(philo);
}
