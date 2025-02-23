#include "../includes/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		// printf("philo %d has taken a fork\n", philo->id);
		safe_print(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
		safe_print(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		safe_print(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork);
		safe_print(philo->data, philo->id, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

static void	eat(t_philo *philo)
{
	if (philo->data->max_meals != -1)
		philo->meal_count++;
	pthread_mutex_lock(&philo->meal_mutex); //the thread that locks the mutex is the only one that can unlock it, and access any line of code between the lock and unlock lines;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo->data, philo->id, "is eating");
	// if (philo->data->max_meals != -1 && philo->meal_count >= philo->data->max_meals)
	// 	philo->is_full = true;
	precise_sleep(philo->data->time_to_eat);
	drop_forks(philo);
}

static void sleep_n_think(t_philo *philo)
{
	safe_print(philo->data, philo->id, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
	safe_print(philo->data, philo->id, "is thinking");
	usleep(100);
}

void	*philosopher_routine(void *arg)
{
	int			i;
	t_philo		*philo;
	static void	(*f[3])(t_philo *) = {take_forks, eat, sleep_n_think};

	i = 0;
	philo = (t_philo *)arg; //just a type casting, because the argument passed is void pointer
	while (!check_philos(philo))
	{
		f[i++](philo);
		if (i == 3)
			i = 0;
		// take_forks(philo);
		// eat(philo);
		// sleep_n_think(philo);
		// i++;
	}
	if (i == 1)
		drop_forks(philo);
	return (NULL);
}

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->left_fork->fork);
	safe_print(philo->data, philo->id, "has taken a fork");
	precise_sleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (NULL);
}
