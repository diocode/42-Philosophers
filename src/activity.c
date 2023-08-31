/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:39:24 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/31 12:56:08 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	logs(t_philo *p, int status)
{
	pthread_mutex_lock(&p->data->finish_lock);
	pthread_mutex_lock(&p->data->log);
	p->status = status;
	if ((status == DEATH || status == FULL) && !p->data->finish)
	{
		if (status == DEATH)
			printf("%lu %lu died\n", get_time() - p->data->start_t, p->id);
		p->data->finish = true;
		pthread_mutex_unlock(p->r_fork);
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

static bool	get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->finish_lock);
	if (philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->finish_lock);
	logs(philo, FORK);
	if (philo->data->n_philos == 1)
		return (false);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->finish_lock);
	if (philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		pthread_mutex_unlock(philo->l_fork);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->finish_lock);
	logs(philo, FORK);
	return (true);
}

static void	sleeping(t_philo *philo)
{
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
	pthread_mutex_lock(&philo->data->finish_lock);
	if (philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->finish_lock);
	if (!get_forks(philo))
		return ;
	pthread_mutex_lock(&philo->data->finish_lock);
	if (philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->data->finish_lock);
	pthread_mutex_lock(&philo->lock);
	philo->status = EATING;
	logs(philo, EATING);
	philo->death_t = get_time() + philo->data->death_t;
	wait_time(philo, philo->data->eat_t);
	philo->status = 0;
	philo->meals++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->lock);
	sleeping(philo);
}
