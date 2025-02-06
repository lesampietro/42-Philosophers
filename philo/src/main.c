#include "../includes/philo.h"

int main(int argc, char **argv)
{
	t_data	*data;
	if (argc != 5 && argc != 6)
	{
		// printf("Error: Wrong number of arguments\n");
		error_n_exit(1);
		return (1);
	}
	else
	{
		init_table(argc, argv, data);
		if (parse_input(argc, argv))
			error_n_exit(2);
		printf(GRN"RUN PHILO\n"RST);
		// init_philo(argc, argv);
	}
}