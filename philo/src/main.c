#include "../includes/philo.h"

int main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		// printf("Error: Wrong number of arguments\n");
		error_n_exit(1);
		return (1);
	}
	else
	{
		if (is_valid_input(argv))
			error_n_exit(2);
		init_table(argc, argv, data);
		printf(GRN"RUN PHILO\n"RST);
		init_philo(argc, argv);
	}
}