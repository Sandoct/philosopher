/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:14:35 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/21 19:42:02 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	create_philo (t_data *data)
{
  int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].seat = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].day = 0;
		data->philo[i].left_fork = NULL;
		pthread_mutex_init(&(data->philo[i].right_fork), NULL);
		if (i == data->n_philo - 1)
			data->philo[0].left_fork = &data->philo[i].right_fork;
		if (i)
			data->philo[i].left_fork = &data->philo[i - 1].right_fork;
	}
}

int  set_data (t_data *data, char **arg)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (data->philo == NULL)
		return (1);
	pthread_mutex_init(&data->print_m, NULL);
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->died = 0;
	data->n_philo = ft_atoi(arg[1]);
	data->time_to_die = ft_atoi(arg[2]);
	data->time_to_eat = ft_atoi(arg[3]);
	data->time_to_sleep = ft_atoi(arg[4]);
	if (arg[5])
		data->n_eat = ft_atoi(arg[5]);
	else
		data->n_eat = -1;
	if (arg[5] && data->n_eat == 0)
		return (1);
	return (0);
}

void	clear_data(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].right_fork);
		pthread_mutex_destroy(data->philo[i].left_forkfork);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->dead);
}
