/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:55:24 by gpouzet           #+#    #+#             */
/*   Updated: 2023/07/06 17:59:41 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	end(t_philo *philo, int stop)
{
	pthread_mutex_lock(&philo->data->end);
	if (stop)
		philo->data->philo_end = 1;
	if (philo->data->philo_end)
	{
		pthread_mutex_unlock(&philo->data->end);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end);
	return (0);
}

void	*check_death(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo*)philosophers;
	pthread_mutex_lock(&philo->data->eating);
	if (!end(philo, 0) && timestamp() - philo->last_meal >= (long)(philo->data->time_to_die))
	{
		pthread_mutex_unlock(&philo->data->eating);
		print_mutex(philo, " died\n");
		end(philo, 1);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->eating);
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork));
	print_mutex(philo, " has taken a fork\n");
	pthread_mutex_lock((philo->left_fork));
	print_mutex(philo, " has taken a fork\n");
	print_mutex(philo, " is eating\n");
	pthread_mutex_lock(&(philo->data->eating));
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(philo->data->eating));
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock((philo->left_fork));
	pthread_mutex_unlock(&(philo->right_fork));
	print_mutex(philo, " is sleeping\n");
	usleep(philo->data->time_to_sleep * 1000);
	print_mutex(philo, " is thinking\n");
}

void  *philo_daily_routine(void *philosophers)
{
	t_philo		*philo;

	philo = (t_philo*)philosophers;
	if (philo->seat % 2 == 0)
		usleep(1000);
	else if (philo->seat == philo->data->n_philo)
		usleep(2000);
	while (!end(philo, 0))
	{
		if (philo->data->n_philo > 1)
			philo_eat(philo);
		else
			usleep(philo->data->time_to_die * 1000 + 1);
		if (philo->data->n_eat != -1)
			if (++philo->day >= philo->data->n_eat)
				if (++philo->data->n_day_end >= philo->data->n_philo)
					end(philo, 1);
	}
	return (NULL);
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
	while (!end(&data.philo[0], 0))
	{
		usleep(1000);
		i = -1;
		while (++i < data.n_philo)
			check_death(&data.philo[i]);
	}
	i = -1;
	while (++i < data.n_philo)
		if (pthread_join(data.philo[i].philo, NULL) != 0)
			return (1);
//	usleep((data.time_to_die - data.time_to_eat - data.time_to_sleep) * 1000);
	clear_data(&data);
	return (0);
}
