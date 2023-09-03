/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:39:24 by digoncal          #+#    #+#             */
/*   Updated: 2023/09/02 13:21:11 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != SLEEPING)
	{
		philo->status = SLEEPING;
		logs(philo, philo->status);
		wait_time(philo, philo->data->sleep_t);
	}
}

void	thinking(t_philo *philo)
{
	if (!is_dead(philo) && philo->status != THINKING)
	{
		philo->status = THINKING;
		logs(philo, philo->status);
		wait_time(philo, 5);
	}
}

static bool	get_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(philo->fork[fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->fork[fork]);
		return (false);
	}
	logs(philo, FORK);
	return (true);
}

static bool	get_forks(t_philo *philo)
{
	if (!get_fork(philo, LEFT))
		return (false);
	if (!get_fork(philo, RIGHT))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		return (false);
	}
	return (true);
}

void	eating(t_philo *philo)
{
	if (!get_forks(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->death_t = get_time() + philo->data->death_t;
	pthread_mutex_unlock(&philo->lock);
	philo->status = EATING;
	logs(philo, philo->status);
	philo->meals++;
	wait_time(philo, philo->data->eat_t);
	pthread_mutex_unlock(philo->fork[LEFT]);
	pthread_mutex_unlock(philo->fork[RIGHT]);
}
