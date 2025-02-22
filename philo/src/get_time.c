#include "../includes/philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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