/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:55:24 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/23 17:31:23 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	dead(t_philo philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

int  philo(char **arg)
{
	t_data	data;
	int	i;

	if (set_data(&data, arg))
		return (1);
	create_philo(&data);
	i = -1;
	while (++i < data.n_philo)
		if (pthread_create(&data.philo[i].philo, NULL, &philo_daily_routine, &(data.philo[i])))
			return (1);
	i = -1;
	while (++i < data.n_philo)
		if (pthread_join(data.philo[i].philo, NULL) != 0)
			return (1);
	clear_data(&data);
	return (0);
}
