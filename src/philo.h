/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:56:28 by gpouzet           #+#    #+#             */
/*   Updated: 2023/07/06 16:35:36 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo
{
	pthread_t			philo;
	int					seat;
 	long int			last_meal;
	long int			day;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	struct s_data		*data;

}	t_philo;

typedef struct s_data
{
	int					n_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_eat;
	int					philo_end;
	long long int		start_time;
	t_philo				*philo;
	pthread_mutex_t		print_m;
	pthread_mutex_t		eating;
	pthread_mutex_t		end;

}		t_data;

int		parser(char **arg);
/*		tools		*/
int		ft_atoi(const char *str);
long long	timestamp(void);
void		my_usleep(int t);
void		print_mutex(t_philo *philo, char *str);
/*		set_data	*/
void		create_philo (t_data *data);
int  		set_data (t_data *data, char **arg);
void		clear_data(t_data *data);
/*		philo		*/
int 		philo(char **arg);
int			end(t_philo *philo, int stop);
#endif
