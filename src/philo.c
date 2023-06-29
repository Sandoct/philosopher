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

int	dead(t_philo *philo)
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

void	*check_death(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo*)philosophers;
	usleep(philo->data->time_to_die + 1);
	pthread_mutex_lock(&philo->data->eating);
	if (!dead(philo) && timestamp() - philo->last_meal >= (long)(philo->data->time_to_die))
	{
		pthread_mutex_unlock(&philo->data->eating);
		print_mutex(philo, " died\n");
		pthread_mutex_lock(&philo->data->dead);
		philo->data->died = 1;
		pthread_mutex_unlock(&philo->data->dead);
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
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock((philo->left_fork));
	pthread_mutex_unlock(&(philo->right_fork));
}

void  *philo_daily_routine(void *philosophers)
{
	pthread_t	death;
	t_philo		*philo;

	philo = (t_philo*)philosophers;
	if (philo->seat % 2 == 0)
		usleep(philo->data->time_to_eat / 10);
	else if (philo->seat == philo->data->n_philo)
		usleep(philo->data->time_to_eat + 1);
	while (!dead(philo) && !philo->ended)
	{
		pthread_create(&death, NULL, check_death, philo);
		philo_eat(philo);
		print_mutex(philo, " is sleeping\n");
		usleep(philo->data->time_to_sleep);
		print_mutex(philo, " is thinking\n");
		if (philo->data->n_eat != -1)
			if (++philo->day >= philo->data->n_eat)
				philo->ended = 1;
		pthread_detach(death);
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
	i = -1;
	while (++i < data.n_philo)
		if (pthread_join(data.philo[i].philo, NULL) != 0)
			return (1);
	clear_data(&data);
	return (0);
}
