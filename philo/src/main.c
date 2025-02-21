#include "../includes/philo.h"

void	init_table(int argc, char **argv, t_data *data)
{
	if (!data)
		error_n_exit(NULL, -1);
	data->philo_nbr = ft_atol(argv[1]);
	if (data->philo_nbr > 200 || data->philo_nbr < 1)
		error_n_exit("Error: Number of philosophers must be between 1 and 200\n", 0);
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4 \
		|| data->time_to_sleep < 6e4)
		error_n_exit("Error: Time to die, eat and sleep must be over 60ms\n", 0);
	if (argc == 6)
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
	data->end_simulation = false;
	data->philos = NULL;
	data->forks = NULL;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		error_n_exit(NULL, 1);
		return (1);
	}
	else
	{
		if (is_valid_input(argv))
			error_n_exit("Error: Invalid arguments. All inputs must be positive integers\n", 0);
		init_table(argc, argv, data);
		init_philo(data);
	}
}