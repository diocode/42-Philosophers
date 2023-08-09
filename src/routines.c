/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*  By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:29:40 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/09 22:29:40 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*check_status(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (!philo->data->death)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->death_t && philo->status != EATING)
			logs(philo, DEATH);
		if (philo->meals == philo->data->n_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->meals++;
			philo->data->philos_full++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->death_t = philo->data->death_t + get_time();
	if (pthread_create(&philo->thread, NULL, &check_status, &philo))
		return (NULL);
	while (philo->data->death != DEATH)
	{
		eating(philo);
		logs(philo, THINKING);
	}
	if (pthread_join(philo->thread, NULL))
		return (NULL);
	return (NULL);
}
