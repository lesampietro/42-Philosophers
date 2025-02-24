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

	(void)data;
	start_time = get_current_time();
	is_dead = 0;
	while (1)
	{
		if (((get_current_time()) - start_time) >= duration)
			break ;
		usleep(42);
	}
}
