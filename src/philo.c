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

int  philo()
{
  create philo;
  creat thread;
  philo daily;
}

void  clear()
{
  
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
