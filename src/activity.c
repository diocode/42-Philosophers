/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:39:24 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/17 16:47:49 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	logs(void *philo_ptr, int status)
{
	t_philo	*p;

	p = (t_philo *) philo_ptr;
	pthread_mutex_lock(&p->data->log);
	if ((status == DEATH || status == FULL) && p->data->death != DEATH)
	{
		if (status == DEATH)
			printf("%lu %lu died\n", get_time() - p->data->start_t, p->id);
		p->data->death = DEATH;
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
	}
	else if (status == EATING && p->data->death != DEATH)
		printf("%lu %lu is eating\n", get_time() - p->data->start_t, p->id);
	else if (status == SLEEPING && p->data->death != DEATH)
		printf("%lu %lu is sleeping\n", get_time() - p->data->start_t, p->id);
	else if (status == THINKING && p->data->death != DEATH)
		printf("%lu %lu is thinking\n", get_time() - p->data->start_t, p->id);
	else if (status == FORK && p->data->death != DEATH)
		printf("%lu %lu has taken a fork\n",
			get_time() - p->data->start_t, p->id);
	pthread_mutex_unlock(&p->data->log);
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
	pthread_mutex_lock(philo->r_fork);
	logs(philo, FORK);
	if (philo->r_fork != philo->l_fork)
	{
		pthread_mutex_lock(philo->l_fork);
		logs(philo, FORK);
	}
	else
		return ;
	pthread_mutex_lock(&philo->lock);
	logs(philo, EATING);
	philo->meals++;
	philo->status = EATING;
	usleep(philo->data->eat_t);
	philo->status = 0;
	pthread_mutex_unlock(&philo->lock);
	sleeping(philo);
}
