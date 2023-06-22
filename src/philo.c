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

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead);
	if (philo->data.died)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

void	*check_death(t_philo *philo)
{
	my_usleep(philo->info->time_to_die + 1);
	pthread_mutex_lock(&philo->info->eating);
	pthread_mutex_lock(&philo->info->dead);
	if (!is_dead(philo) && timestamp() - philo->last_meal >= (long)(philo->info->time_to_die))
	{
		pthread_mutex_unlock(&philo->info->eating);
		pthread_mutex_unlock(&philo->info->dead);
		print_mutex(philo, " died\n");
		pthread_mutex_lock(&philo->info->dead);
		philo->data.died = 1;
		pthread_mutex_unlock(&philo->info->dead);
	}
	pthread_mutex_unlock(&philo->info->eating);
	pthread_mutex_unlock(&philo->info->dead);
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork));
	print(philo, " has taken a fork\n");
	pthread_mutex_lock((philo->left_fork));
	print_mutex(philo, " has taken a fork\n");
	print_mutex(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->eating));
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(philo->info->eating));
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock((philo->left_fork));
	pthread_mutex_unlock(&(philo->right_fork));
}

int  philo_daily_routine(t_philo *philo)
{
	pthread_t	death;

	if (philo->seat % 2 == 0)
		my_usleep(philo->info->time_to_eat / 10);
	else if (philo->seat == philo->data.n_philo)
		my_usleep(philo->info->time_to_eat / 5);
	while (!is_dead(philo) && !(philo->data.n_eat != -1 && philo.day < philo.data.n_eat))
	{
		pthread_create(&death, NULL, check_death, philo);
		philo_eat(philo);
		print_mutex(philo, " is sleeping\n");
		usleep(philo->info->time_to_sleep);
		print_mutex(philo, " is thinking\n");
		if (philo->data.n_eat != -1)
			philo->day++;
		pthread_detach(death);
	}
}

int  philo(char **arg)
{
	t_data	data;
	int	i:

	if (set_data(data, arg))
		return (1);
	create_philo(data);
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data.philo[i].thread, NULL, &philo_daily_routine, &(data.philo[i])))
			return (1);
		else if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (1);
	}
}
