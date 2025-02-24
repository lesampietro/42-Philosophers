#include "../includes/philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
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
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex); //the thread that locks the mutex is the only one that can unlock it, and access any line of code between the lock and unlock lines;
	philo->meal_count++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo->data, philo->id, "is eating");
	precise_sleep(philo->data->time_to_eat, philo->data);
	drop_forks(philo);
}

static void philo_sleep(t_philo *philo)
{
	safe_print(philo->data, philo->id, "is sleeping");
	precise_sleep(philo->data->time_to_sleep, philo->data);
}

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg; //just a type casting, because the argument passed is void pointer
	while (!check_philos(philo))
	{
		if (is_philo_full(philo))
			break ;
		take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		safe_print(philo->data, philo->id, "is thinking");
		usleep(1000);
	}
	return (NULL);
}

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->left_fork->fork);
	safe_print(philo->data, philo->id, "has taken a fork");
	precise_sleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (NULL);
}
