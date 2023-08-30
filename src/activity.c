/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:39:24 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/21 14:04:55 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	logs(t_philo *p, int status)
{
	pthread_mutex_lock(&p->data->finish_lock);
	if (p->data->finish)
		return ;
	pthread_mutex_unlock(&p->data->finish_lock);
	pthread_mutex_lock(&p->data->log);
	if ((status == DEATH || status == FULL))
	{
		if (status == DEATH)
			printf("%lu %lu died\n", get_time() - p->data->start_t, p->id);
		pthread_mutex_lock(&p->data->finish_lock);
		p->data->finish = true;
		pthread_mutex_unlock(&p->data->finish_lock);
	}
	else if (status == EATING)
		printf("%lu %lu is eating\n", get_time() - p->data->start_t, p->id);
	else if (status == SLEEPING)
		printf("%lu %lu is sleeping\n", get_time() - p->data->start_t, p->id);
	else if (status == THINKING)
		printf("%lu %lu is thinking\n", get_time() - p->data->start_t, p->id);
	else if (status == FORK)
		printf("%lu %lu has taken a fork\n",
			get_time() - p->data->start_t, p->id);
	pthread_mutex_unlock(&p->data->log);
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
	if (philo->data->finish)
		printf("==== PHILO[%lu]====\n", philo->id);
	pthread_mutex_lock(&philo->data->finish_lock);
	if (philo->data->finish)
		return ;
	pthread_mutex_unlock(&philo->data->finish_lock);
	logs(philo, SLEEPING);
	usleep(philo->data->sleep_t * 1000);
}

void	eating(t_philo *philo)
{
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
	usleep(philo->data->eat_t * 1000);
	philo->status = 0;
	philo->meals++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->lock);
	sleeping(philo);
}
