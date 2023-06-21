/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:55:24 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/08 17:55:27 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int  philo(char **arg)
{
	t_data	data;
	int	i:

	if (set_data(data, arg))
		return (1);
	create_philo(data);
	i = -1;
	while (++i < data->n_philo)
		if (pthread_create(&data->philo[i].thread, NULL, &philo_daily_routine, &(data->philo[i])))
			return (1);
}

void	clear_data(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->print);
}

int  philo_daily_routine(t_philo philo)
{
pthread_t	death;

  while (!is_dead(philo) && philo.day < philo.data.day)
	{
		pthread_create(&death, NULL, check_death, philo);
    take_forks(philo);
		philo_eat(philo);
		pthread_detach(death);
}
