#include "../includes/philo.h"

void	error_n_exit(char *msg, int msg_type)
{
	if (msg == NULL && msg_type == 1)
	{
		printf(MAG"Error: Wrong number of arguments\n"RST);
		printf(CYN"Usage example: ./philo <nbr_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> <nbr_of_meals>\n"RST);
	}
	else if (!msg_type)
		printf(MAG"%s"RST, msg);
	else
		printf(MAG"Unknown Error\n"RST);
	exit(1);
}

void	safe_print(t_data *data, int philo_id, char *msg)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!is_simulation_end(data))
		printf("%ld %d %s\n", get_elapsed_time(data) / 1000, philo_id, msg);
	pthread_mutex_unlock(&data->print_mutex);
}