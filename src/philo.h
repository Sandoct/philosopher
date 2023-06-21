/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:56:28 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/21 19:41:54 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>


typedef struct s_philo
{
	pthread_t			philo;
	int					seat;
 	long int			last_meal;
	long int			day;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	struct s_data		data;

}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat;
	t_philo			*philo;
	pthread_mutex_t	print_m;
}		t_data;

int		parser(char **arg);
/*		tools		*/
void	my_usleep(unsigned int t);
/*		philo		*/
int 	 philo(char **arg);
#endif
