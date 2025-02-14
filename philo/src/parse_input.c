#include "../includes/philo.h"

static bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' \
			|| c == '\v' || c == '\f' || c == '\r');
}

static bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long int	ft_atol(char *str)
{
	long int	res;
	int			sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * sign);
}

static int	is_integer(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str[i])
		return (1);
	while (str[i] && ft_isspace(str[i]))
			i++;
	if (!str[i])
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (1);
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]))
	{
		i++;
		len++;
	}
	if (str[i] || len > 10)
		return (1);
	return (0);
}

int	is_valid_input(char **argv)
{
	char	**tmp;
	long	value;

	value = 0;
	tmp = argv + 1;
	while (*tmp)
	{
		if (is_integer(*tmp))
			return (1);
		value = ft_atol(*tmp);
		if (value < 0 || value > INT_MAX)
			return (1);
		tmp++;
	}
	return (0);
}