#include "../includes/philo.h"

// int is_empty(char **str)
// {
// 	int i;

// 	i = 0;
// 	if (str[0] == NULL)
// 		return (1);
// 	while (str[i])
// 	{
// 		if (str[i][0] == '\0')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int is_integer(char **args)
{
	int i;
	long nbr;

	i = 0;
	while (args[i])
	{
		nbr = ft_atol(args[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

int check_ascii(t_data *data)
{
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '-' || args[i][j] == '+')
			{
				j++;
				if (!args[i][j])
					return (1);
			}
			while (ft_isdigit(args[i][j]))
				j++;
			if (args[i][j])
				return (1);
		}
		i++;
	}
	return (0);
}

int	parse_input(t_data *data)
{
	if (check_ascii(data))
		return (1);
	else if (is_integer(data))
		return (1);
	return (0);
}