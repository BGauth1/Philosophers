/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:32:59 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/26 16:56:44 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILO 256

typedef struct s_philo
{
	int				num;
	int				nb_meal;
	pthread_t		thread;
	pthread_mutex_t	my_fork;
	pthread_mutex_t	*not_my_fork;
	pthread_mutex_t	m_meal;
	unsigned int	last_meal_time;
	struct s_main	*main;
}				t_philo;

typedef struct s_main
{
	pthread_t		checker;
	pthread_mutex_t	can_print;
	pthread_mutex_t	mutex_is_dead;
	t_philo			*philos;
	unsigned int	curr_time;
	int				nb_philo;
	unsigned int	is_dead;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	unsigned int	tt_die;
	int				max_meal;
}				t_main;

unsigned int	get_time(void);
void			narrate(char *txt, t_philo *philo, int force_print);
void			*ft_checker(void *la_data);
t_philo			*get_philos(t_philo *philos, int nb_philo, t_main *super);

void			set_mutex_int(pthread_mutex_t *mutex, int *n, int val);
void			set_mutex_uint(pthread_mutex_t *mutex, unsigned int *n,
					unsigned int val);
void			add_to_locked_int(pthread_mutex_t *mutex, int *n, int val);
unsigned int	get_mutex_uint(pthread_mutex_t *mutex, unsigned int *n);
int				get_mutex_int(pthread_mutex_t *mutex, int *n);

int				ft_atoi(const char *s, int *err);
unsigned int	ft_atoui(const char *s, int *err);

#endif