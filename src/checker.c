/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:34:02 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/22 17:28:43 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_check_meals(t_philo *philos, int nb_philo, int max_meal)
{
	int	i;

	if (max_meal == -1)
		return (0);
	i = -1;
	while (++i < nb_philo)
	{
		if (get_mutex_int(&philos[i].m_meal, &philos[i].nb_meal) < max_meal)
			return (0);
	}
	return (1);
}

void	*ft_checker(void *la_data)
{
	t_main	*super;
	int		i;

	super = (t_main *)la_data;
	while (1)
	{
		i = -1;
		while (++i < super->nb_philo)
		{
			if (get_time() - get_mutex_uint(&super->philos[i].m_meal, \
						&super->philos[i].last_meal_time) > super->tt_die)
			{
				set_mutex_uint(&super->mutex_is_dead, &super->is_dead, 1);
				narrate("died", &super->philos[i], 1);
				return (NULL);
			}
		}
		if (ft_check_meals(super->philos, super->nb_philo, super->max_meal))
		{
			set_mutex_uint(&super->mutex_is_dead, &super->is_dead, 1);
			return (NULL);
		}
	}
	return (NULL);
}
