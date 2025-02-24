#include "../includes/philo.h"

void	init_table(int argc, char **argv, t_data *data)
{
	data->philo_nbr = ft_atol(argv[1]);
	if (data->philo_nbr > 200 || data->philo_nbr < 1)
		error_n_exit("Error: Number of philosophers must be between 1 and 200\n", 0, data);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60 \
		|| data->time_to_sleep < 60)
		error_n_exit("Error: Time to die, eat and sleep must be over 60ms\n", 0, data);
	if (argc == 6)
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
	data->end_simulation = false;
	data->all_full = 0;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc < 5 || argc > 6)
		error_n_exit(NULL, 1, data);
	if (is_valid_input(argv))
		error_n_exit("Error: Invalid arguments. All inputs must be in the positive integer scope\n", 0, data);
	init_table(argc, argv, data);
	init_philos(data);
	init_monitor(data);
	cleanup_routine(data);
	return (0);
}
