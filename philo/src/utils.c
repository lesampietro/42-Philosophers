#include "../includes/philo.h"

void	error_n_exit(char *msg, int msg_type)
{
	if (msg == NULL && msg_type == 1)
	{
		printf(RED"Error: Wrong number of arguments\n"RST);
		printf(YEL"Usage example: ./philo <nbr_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> <nbr_of_meals>\n"RST);
	}
	else if (!msg_type)
		printf(RED"%s"RST, msg);
	else if (msg_type == 3)
		printf(RED"Error: Time to die, eat and sleep must be over 60ms\n" RST);
	else if (msg_type == 4)
		printf(RED"Error: Number of philosophers must be between 1 and 200\n" RST);
	else
		printf(RED "Unknown Error\n" RST);
	exit(1);
}

void	init_table(int argc, char **argv, t_data *data)
{
	if (!data)
		error_n_exit(NULL, -1);
	data->philo_nbr = ft_atol(argv[1]);
	if (data->philo_nbr > 200 || data->philo_nbr < 1)
		error_n_exit(NULL, 4);
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4 \
		|| data->time_to_sleep < 6e4)
		error_n_exit(NULL, 3);
	if (argc == 6)
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
	data->start_time = 0;
	data->end_simulation = false;
	data->philos = NULL;
	data->forks = NULL;
}
