#include "../includes/philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_n_exit(NULL, -1);
	return ((tv.tv_sec * 1e6) + tv.tv_usec);
}

long	get_elapsed_time(t_data *data)
{
	return (get_current_time() - data->start_time);
}

long	get_time_since_last_meal(t_philo *philo)
{
	return (get_current_time() - philo->last_meal_time);
}

void	precise_sleep(long duration)
{
	long	start_time;
	long	current_time;

	start_time = get_current_time();
	while (1)
	{
		current_time = get_current_time();
		if ((current_time - start_time) >= duration)
			break ;
		usleep(100);
	}
}