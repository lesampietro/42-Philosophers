#include "../includes/philo.h"

void	error_n_exit(int msg)
{
	if (msg == 1)
	{
		printf(RED"Error: Wrong number of arguments\n"RST);
		printf(YEL"Usage example: ./philo <nbr_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> <nbr_of_meals>\n"RST);
	}
	else if (msg == 2)
		printf(RED "Error: Invalid arguments. All inputs must be positive integers\n" RST);
	else if (msg == 3)
		printf(RED"Error: Time to die, eat and sleep must be over 60ms\n" RST);
	else
		printf(RED "Unknown Error\n" RST);
	exit(1);
}

void	init_table(int argc, char **argv, t_data *data)
{
	if (!data)
		error_n_exit(-1);
	data->philo_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4 \
		|| data->time_to_sleep < 6e4)
		error_n_exit(3);
	if (argc == 6)
		data->limit_nbr_meals = ft_atol(argv[5]);
	else
		data->limit_nbr_meals = -1;
	// data->start_time = get_time();
	data->end_simulation = false;
	data->philos = NULL;
	data->forks = NULL;
	// data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	// data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	// if (!data->philos || !data->forks)
	// 	error_n_exit(3);
}