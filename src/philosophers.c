/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:28:11 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/26 13:49:36 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->not_my_fork);
	pthread_mutex_lock(&philo->my_fork);
	narrate("has taken a fork", philo, 0);
	narrate("has taken a fork", philo, 0);
	narrate("is eating", philo, 0);
	pthread_mutex_lock(&philo->m_meal);
	philo->last_meal_time = get_time();
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->m_meal);
	usleep(philo->main->tt_eat * 1000);
	pthread_mutex_unlock(&philo->my_fork);
	pthread_mutex_unlock(philo->not_my_fork);
}

static void	*philone(void *the_data)
{
	t_philo	*philo;

	philo = (t_philo *) the_data;
	pthread_mutex_lock(&philo->my_fork);
	narrate("has taken a fork", philo, 0);
	usleep(philo->main->tt_die * 1000);
	pthread_mutex_unlock(&philo->my_fork);
	return (NULL);
}

static void	*eat_sleep_think(void *the_data)
{
	t_philo	*philo;

	philo = (t_philo *) the_data;
	if (philo->num % 2)
		usleep(50);
	while (!get_mutex_uint(&philo->main->mutex_is_dead, &philo->main->is_dead))
	{
		ft_philo_eat(philo);
		narrate("is sleeping", philo, 0);
		usleep(philo->main->tt_sleep * 1000);
		narrate("is thinking", philo, 0);
	}
	return (NULL);
}

static void	create_philo_threads(t_philo *philos, int nb_philo)
{
	int	i;

	if (nb_philo == 1)
		pthread_create(&philos[0].thread, NULL, &philone, (void *)&philos[0]);
	else
	{
		i = -1;
		while (++i < nb_philo)
			pthread_create(&philos[i].thread, NULL, &eat_sleep_think,
				(void *)&philos[i]);
	}
}

t_philo	*get_philos(t_philo *philos, int nb_philo, t_main *super)
{
	int	i;

	philos = malloc((nb_philo + 1) * sizeof(t_philo));
	i = -1;
	philos[nb_philo - 1].not_my_fork = &philos[0].my_fork;
	while (++i < nb_philo - 1)
		philos[i].not_my_fork = &philos[i + 1].my_fork;
	i = -1;
	while (++i < nb_philo)
	{
		philos[i].num = i + 1;
		philos[i].last_meal_time = get_time();
		philos[i].nb_meal = 0;
		philos[i].main = super;
		pthread_mutex_init(&philos[i].my_fork, NULL);
		pthread_mutex_init(&philos[i].m_meal, NULL);
	}
	create_philo_threads(philos, nb_philo);
	return (philos);
}
