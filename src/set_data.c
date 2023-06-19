#include "philo.h"

t_philo *create_philo ()
{
  int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].left_fork = NULL;
		pthread_mutex_init(&(data->philo[i].right_fork), NULL);
		if (i == data->n_philo - 1)
			&data->philo[0].left_fork = data->philo[i].right_fork;
		else
			data->philo[i].left_fork = &data->philo[i - 1].right_fork;
	}
	return (0);

}

int  set_data (char **arg)
{
  pthread_mutex_init(&data->print, NULL);
  data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (data->philo == NULL)
		return (1);
	data->n_philo = ft_atoi(arg[1]);
	data->time_to_die = ft_atoi(arg[2]);
	data->time_to_eat = ft_atoi(arg[3]);
	data->time_to_sleep = ft_atoi(arg[4]);
  if (arg[5])
		data->n_eat = ft_atoi(arg[5]);
	if (arg[5] && data->n_eat == 0)
		return (1);
	return (0);
}
