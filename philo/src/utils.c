#include "../includes/philo.h"

void	error_n_exit(char *msg, int msg_type, t_data *data)
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
	free_memory(data);
	exit(1);
}

void	safe_print(t_data *data, int id, char *msg)
{
	long	current_time;

	if(is_philo_dead(data->philos))
		return ;
	pthread_mutex_lock(&data->print_mutex);
	current_time = get_current_time() - data->philos->start_time;
	if (!is_philo_dead(data->philos))
	{
		printf("%ld ", current_time);
		printf(MAG"%d "RST, id);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&data->print_mutex);
}