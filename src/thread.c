#include "philo.h"

void	*check_death(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo*)philosophers;
	usleep(philo->data->time_to_die + 1);
	pthread_mutex_lock(&philo->data->eating);
	pthread_mutex_lock(&philo->data->end);
	if (!end(philo) && timestamp() - philo->last_meal >= (long)(philo->data->time_to_die))
	{
		pthread_mutex_unlock(&philo->data->eating);
		pthread_mutex_unlock(&philo->data->end);
		print_mutex(philo, " died\n");
		pthread_mutex_lock(&philo->data->dead);
		philo->data->died = 1;
		pthread_mutex_unlock(&philo->data->dead);
	}
	pthread_mutex_unlock(&philo->data->eating);
	pthread_mutex_unlock(&philo->data->end);
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
	while (!end(philo))
	{
		pthread_create(&death, NULL, check_death, philo);
		philo_eat(philo);
		print_mutex(philo, " is sleeping\n");
		usleep(philo->data->time_to_sleep);
		print_mutex(philo, " is thinking\n");
		if (philo->data->n_eat != -1)
		{
			if (++philo->day >= philo->data->n_eat)
			{
				pthread_mutex_lock(&philo->data->end);
				philo->data->ended = 1;
				pthread_mutex_unlock(&philo->data->end);
			}
		}
		pthread_detach(death);
	}
	return (NULL);
}
