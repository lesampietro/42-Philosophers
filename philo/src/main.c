#include "../includes/philo.h"

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