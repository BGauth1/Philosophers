/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:16:14 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/26 16:57:37 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	narrate(char *txt, t_philo *philo, int force_print)
{
	pthread_mutex_lock(&philo->main->can_print);
	if (!get_mutex_uint(&philo->main->mutex_is_dead, &philo->main->is_dead)
		|| force_print)
		printf("%u %d %s\n", get_time() - philo->main->curr_time,
			philo->num, txt);
	pthread_mutex_unlock(&philo->main->can_print);
}

static void	print_error(int n_error)
{
	if (n_error == 1)
		printf("Incorrect number of arguments. Example of usage : \n./philo nb\
_of_philos time_to_die_in_ms time_to_eat_in_ms time_to sleep_in_ms [nb_of_meal\
s_requiered]\n");
	else if (n_error == 2)
		printf("Incorrect number of philosophers.\n");
	else if (n_error == 3)
		printf("Invalid time length.\n");
	else
		printf("Invalid number of times philosophers must eat.\n");
}

static int	parse_args(t_main *super, int ac, char **av)
{
	int	err;

	if (!(ac == 5 || ac == 6))
		return (1);
	super->nb_philo = ft_atoi(av[1], &err);
	if (err || super->nb_philo > MAX_PHILO || super->nb_philo < 1)
		return (2);
	super->tt_die = ft_atoui(av[2], &err);
	if (err || super->tt_die < 1)
		return (3);
	super->tt_eat = ft_atoui(av[3], &err);
	if (err || super->tt_eat < 1)
		return (3);
	super->tt_sleep = ft_atoui(av[4], &err);
	if (err || super->tt_sleep < 1)
		return (3);
	if (ac == 6)
	{
		super->max_meal = ft_atoi(av[5], &err);
		if (err || super->max_meal < 1)
			return (4);
	}
	else
		super->max_meal = -1;
	return (0);
}

static void	free_philos(t_philo *philos, int nb_philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		pthread_mutex_destroy(&philos[i].my_fork);
		pthread_mutex_destroy(&philos[i].m_meal);
	}
	free(philos);
}

int	main(int ac, char **av)
{
	t_main	super;
	int		i;

	i = parse_args(&super, ac, av);
	if (i)
	{
		print_error(i);
		return (1);
	}
	super.curr_time = get_time();
	super.is_dead = 0;
	pthread_mutex_init(&super.can_print, NULL);
	pthread_mutex_init(&super.mutex_is_dead, NULL);
	super.philos = get_philos(super.philos, super.nb_philo, &super);
	i = -1;
	pthread_create(&super.checker, NULL, &ft_checker, (void *)&super);
	while (++i < super.nb_philo)
		pthread_join(super.philos[i].thread, NULL);
	pthread_join(super.checker, NULL);
	pthread_mutex_destroy(&super.can_print);
	pthread_mutex_destroy(&super.mutex_is_dead);
	free_philos(super.philos, super.nb_philo);
	return (0);
}
