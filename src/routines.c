/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:11:44 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/30 22:40:23 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	logs(t_philo *p, int status)
{
	pthread_mutex_lock(&p->data->log);
	if (status == DEATH)
		printf("%lu %lu died\n", get_time() - p->data->start_t, p->id);
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

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->lock);
	philo->death_t = philo->data->start_t + philo->data->death_t;
	pthread_mutex_unlock(&philo->lock);
	if (philo->id % 2 == 0 || philo->id == philo->data->n_philos)
		thinking(philo);
	if (is_solo(philo))
		return (NULL);
	while (!is_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
