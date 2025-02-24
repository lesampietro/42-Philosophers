#include "../includes/philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_sleep(long duration, t_data *data)
{
	long	start_time;
	int		is_dead;

	start_time = get_current_time();
	is_dead = 0;
	while (1)
	{
		pthread_mutex_lock(&data->end_mutex);
		is_dead = data->end_simulation;
		pthread_mutex_unlock(&data->end_mutex);
		if (is_dead)
			break ;
		if (((get_current_time()) - start_time) >= duration)
			break ;
		usleep(100);
	}
}

// https://github.com/SeijiUeno/42_philosophers/blob/main/time.c#L28