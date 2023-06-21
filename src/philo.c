/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:55:24 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/21 19:41:57 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
/*
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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork));
	print(philo, " has taken a fork\n");
	pthread_mutex_lock((philo->left_fork));
	print(philo, " has taken a fork\n");
	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&(philo->info->m_eat));
	usleep(philo->info->t_eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	print(philo, " is sleeping\n");
	usleep(philo->info->t_sleep);
	print(philo, " is thinking\n");
}

int  philo_daily_routine(t_philo philo)
{
	pthread_t	death;

	if (philo.seat % 2)
		my_usleep(1000);
	while (!is_dead(philo) && philo.day < philo.data.day)
	{
		pthread_create(&death, NULL, check_death, philo);
		philo_eat(philo);
		pthread_detach(death);
	}
}
*/
int  philo(char **arg)
{
	t_data	data;
//	int	i:

	if (set_data(data, arg))
		return (1);
	create_philo(data);
/*	i = -1;
	while (++i < data->n_philo)
		if (pthread_create(&data.philo[i].thread, NULL, &philo_daily_routine, &(data.philo[i])))
			return (1);*/
}
