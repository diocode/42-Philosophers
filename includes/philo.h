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

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

/* ---------- MACROS ---------- */

enum e_actions{
	DEATH,
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	FULL
};

/*------------- STRUCTURES ---------------*/

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	u_int64_t		id;
	int				status;
	u_int64_t		meals;
	u_int64_t		death_t;
	bool			full;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	pthread_t		*table;
	t_philo			*philos;
	u_int64_t		n_philos;
	u_int64_t		death_t;
	u_int64_t		eat_t;
	u_int64_t		sleep_t;
	u_int64_t		n_meals;
	u_int64_t		start_t;
	u_int64_t		philos_full;
	bool			finish;
	bool			solo_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	log;
	pthread_mutex_t	finish_lock;
}					t_data;

/*---------- FUNCTIONS ----------*/

//activity
void		logs(t_philo *p, int status);
void		eating(t_philo *philo);

//routines
void		*routine(void *philo_ptr);

//utils
int			check_input(char **av);
void		free_data(t_data *data);
long		ft_atol(const char *nptr);
u_int64_t	get_time(void);
void		wait_time(t_philo *philo, u_int64_t time);

//init
t_data		*init_data(int ac, char **av);

#endif