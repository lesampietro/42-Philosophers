#include "../includes/philo.h"

void	init_table(int argc, char **argv, t_data *data)
{
	if (!data)
	{
		free_memory(data);
		error_n_exit(NULL, -1);
	}
	data->philo_nbr = ft_atol(argv[1]);
	if (data->philo_nbr > 200 || data->philo_nbr < 1)
	{
		free_memory(data);
		error_n_exit("Error: Number of philosophers must be between 1 and 200\n", 0);
	}
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4 \
		|| data->time_to_sleep < 6e4)
	{
		free_memory(data);
		error_n_exit("Error: Time to die, eat and sleep must be > 60ms\n", 0);
	}
	if (argc == 6)
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
	data->end_simulation = false;
	data->philos = NULL;
	data->forks = NULL;
}

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	safe_print(philo->data, philo->philo_id, "has taken a fork");
	// Wait until death with just one fork
	while (!is_simulation_end(philo->data))
		usleep(100);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		free_memory(data);
		error_n_exit(NULL, 1);
		return (1);
	}
	else
	{
		if (is_valid_input(argv))
		{
			free_memory(data);
			error_n_exit("Error: Invalid arguments. All inputs must be in the positive integer scope\n", 0);
		}
		init_table(argc, argv, data);
		init_philo(data);
		if (data->philo_nbr == 1)
			handle_single_philo(&data->philos[0]);
		else
			start_dinner(data);
		cleanup_routine(data);
	}
	return (0);
}
