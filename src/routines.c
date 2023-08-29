/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:11:44 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/18 12:44:41 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	thinking(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		logs(philo, THINKING);
		usleep(100);
	}
}

static void	philo_full(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->lock);
	philo->meals++;
	philo->data->philos_full++;
	pthread_mutex_unlock(&philo->data->lock);
}

static void	*check_status(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->data->log);
	while (!philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->log);
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->death_t && philo->status != EATING)
			logs(philo, DEATH);
		if (philo->meals == philo->data->n_meals && philo->meals != 0)
			philo_full(philo);
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->data->lock);
		pthread_mutex_lock(&philo->lock);
		if (philo->data->philos_full == philo->data->n_philos)
			logs(philo, FULL);
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->data->log);
	}
	pthread_mutex_unlock(&philo->data->log);
	return (NULL);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->lock);
	philo->death_t = get_time() + philo->data->death_t;
	thinking(philo);
	if (pthread_create(&philo->thread, NULL, &check_status, philo_ptr))
		return (NULL);
	pthread_mutex_unlock(&philo->lock);
	while (!philo->data->finish)
	{
		eating(philo);
		logs(philo, THINKING);
	}
	if (pthread_join(philo->thread, NULL))
		return (NULL);
	return (NULL);
}
