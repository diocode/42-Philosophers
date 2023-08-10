/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:39:24 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/09 23:31:26 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	logs(t_philo *p, int status)
{
	pthread_mutex_lock(&p->data->log);
	if (status == DEATH && !p->data->death)
	{
		printf("[%lu] %lu died\n", get_time() - p->data->start_t, p->id);
		p->data->death = DEATH;
	}
	else if (status == EATING)
		printf("[%lu] %lu is eating\n", get_time() - p->data->start_t, p->id);
	else if (status == SLEEPING)
		printf("[%lu] %lu is sleeping\n", get_time() - p->data->start_t, p->id);
	else if (status == THINKING)
		printf("[%lu] %lu is thinking\n", get_time() - p->data->start_t, p->id);
	else if (status == FORK)
		printf("[%lu] %lu has taken a fork\n",
			get_time() - p->data->start_t, p->id);
	pthread_mutex_unlock(&p->data->log);
}

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	logs(philo, FORK);
	if (philo->r_fork != philo->l_fork)
		pthread_mutex_lock(philo->l_fork);
	logs(philo, FORK);
}

void	sleeping(t_philo *philo)
{
	if (philo->r_fork != philo->l_fork)
		pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	logs(philo, SLEEPING);
	usleep(philo->data->sleep_t);
}

void	eating(t_philo *philo)
{
	get_forks(philo);
	pthread_mutex_lock(&philo->lock);
	logs(philo, EATING);
	philo->meals++;
	philo->status = EATING;
	usleep(philo->data->eat_t);
	philo->status = 0;
	pthread_mutex_unlock(&philo->lock);
	sleeping(philo);
}
