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

void	logs(void *philo_ptr, int status)
{
	t_philo	*p;

	p = (t_philo *) philo_ptr;
	pthread_mutex_lock(&p->data->log);
	if ((status == DEATH || status == FULL) && !p->data->finish)
	{
		if (status == DEATH)
			printf("%lu %lu died\n", get_time() - p->data->start_t, p->id);
		p->data->finish = true;
		pthread_mutex_unlock(p->l_fork);
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
}

static void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	logs(philo, FORK);
	if (philo->data->n_philos == 1)
		return ;
	pthread_mutex_lock(philo->l_fork);
	logs(philo, FORK);
}

void	eating(t_philo *philo)
{
	get_forks(philo);
	pthread_mutex_lock(&philo->lock);
	logs(philo, EATING);
	philo->status = EATING;
	philo->death_t = get_time() + philo->data->death_t;
	usleep(philo->data->eat_t * 1000);
	philo->status = 0;
	philo->meals++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	logs(philo, SLEEPING);
	pthread_mutex_unlock(&philo->lock);
	usleep(philo->data->sleep_t * 1000);
}
