#include "../includes/philo.h"

static void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}

void	free_memory(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	free(data);
}

void	cleanup_routine(t_data *data)
{
	if (!data)
		return;
	check_simulation_end(data); // make sure simulation has ended
	usleep(1000); // wait for all threads to finish
	destroy_mutexes(data);
	free_memory(data);
}
