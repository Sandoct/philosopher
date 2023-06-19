/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:56:28 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/08 17:54:39 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>


struct s_philo
{
	pthread_t	philo;
 	long int		last_eat;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;

}	t_philo

typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
}		t_data;

int	parser(char **arg);
#endif
