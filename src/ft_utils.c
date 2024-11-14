/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:24:58 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/26 16:57:04 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	is_not_number(const char *s)
{
	int	i;
	int	len;

	len = 0;
	while (s[len])
		len++;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	while (ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (0);
	return (1);
}

int	ft_atoi(const char *s, int *err)
{
	long long	res;
	int			neg;
	int			i;

	res = 0;
	neg = 1;
	i = 0;
	*err = is_not_number(s);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			neg = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		if (res * neg > 2147483647 || res * neg < -2147483648)
			*err = 1;
		i++;
	}
	res *= neg;
	return ((int)res);
}

unsigned int	ft_atoui(const char *s, int *err)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	*err = is_not_number(s);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			*err = 1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		if (res > 4294967295)
			*err = 1;
		i++;
	}
	return ((unsigned int)res);
}
