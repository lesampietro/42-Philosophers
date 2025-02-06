#include "../includes/philo.h"

void	error_n_exit(int msg)
{
	if (msg == 1)
	{
		printf(RED"Error: Wrong number of arguments\n"RST);
		printf("Usage: ./philo  nbr_philosophers  time_to_die  time_to_eat  \
				time_to_sleep  [nbrr_of_meals_each_philosopher_must_eat]\n");
	}
	else if (msg == 2)
		printf(RED "Error: Invalid arguments. Input must be numeric\n" RST);
	else
		printf(RED "Unknown Error\n" RST);
	exit(1);
}

void	*init_table(int argc, char **argv, t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		error_n_exit(3);
	data->philo_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->limit_nbr_meals = ft_atol(argv[5]);
	else
		data->limit_nbr_meals = -1;
	data->start_time = get_time();
	data->end_simulation = false;
	data->philos = NULL;
	data->forks = NULL;
	// data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	// data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	// if (!data->philos || !data->forks)
	// 	error_n_exit(3);
}