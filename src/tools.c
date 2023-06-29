/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:14:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/23 14:21:06 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - 48);
	return (nb * sign);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_usleep(int t)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < t)
		usleep(t / 10);
}

void	print_mutex(t_philo *philo, char *str)
{
	long long int	time;

	pthread_mutex_lock(&(philo->data->print_m));
	time = timestamp() - philo->data->start_time;
	if (!dead(philo))
		printf("%05lld %d %s", time, philo->seat, str);
	pthread_mutex_unlock(&(philo->data->print_m));
}
