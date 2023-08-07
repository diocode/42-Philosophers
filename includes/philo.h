/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:39:00 by digoncal          #+#    #+#             */
/*   Updated: 2023/08/07 15:56:32 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ---------- LIBRARIES ---------- */

# include "libft.h"
# include <stdio.h>
# include <pthread.h>

/*------------- Structures ---------------*/

typedef struct s_data
{
	long	philos;
	long	death_t;
	long	eat_t;
	long	sleep_t;
	long	nbr_meals;
}		t_data;

/*---------- FUNCTIONS ----------*/

//utils
int		check_input(char **av);

//init
t_data	*init_data(int ac, char **av);

//free
void	free_data(t_data *data);

#endif