/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:54:24 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/15 16:01:26 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_mutex_int(pthread_mutex_t *mutex, int *n, int val)
{
	pthread_mutex_lock(mutex);
	*n = val;
	pthread_mutex_unlock(mutex);
}

void	set_mutex_uint(pthread_mutex_t *mutex, unsigned int *n,
			unsigned int val)
{
	pthread_mutex_lock(mutex);
	*n = val;
	pthread_mutex_unlock(mutex);
}

void	add_to_locked_int(pthread_mutex_t *mutex, int *n, int val)
{
	pthread_mutex_lock(mutex);
	*n += val;
	pthread_mutex_unlock(mutex);
}

unsigned int	get_mutex_uint(pthread_mutex_t *mutex, unsigned int *n)
{
	unsigned int	res;

	pthread_mutex_lock(mutex);
	res = *n;
	pthread_mutex_unlock(mutex);
	return (res);
}

int	get_mutex_int(pthread_mutex_t *mutex, int *n)
{
	int	res;

	pthread_mutex_lock(mutex);
	res = *n;
	pthread_mutex_unlock(mutex);
	return (res);
}
