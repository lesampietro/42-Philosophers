#include <stdio.h>
#include <stdlib.h> //malloc, free
#include <unistd.h> //write, usleep
#include <stdbool.h>
#include <pthread.h> // mutex: init, lock, unlock, destroy && threads: create, join, detach
#include <sys/time.h> //gettimeofday
#include <limits.h> //INT_MAX

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
# define RST "\e[0m"

//STRUCTURES
typedef pthread_mutex_t	t_mutex;
typedef struct			s_fork t_fork;
typedef struct			s_philo t_philo;
typedef struct			s_data t_data;

//Fork structure
struct s_fork
{
	t_mutex		fork;
	int			fork_id;
};

//Philosopher structure
struct s_philo
{
	int			philo_id;
	long		last_meal_time;
	long		meal_count;
	bool		is_full;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
};

//Data table structure to hold important info
struct s_data
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		max_meals;
	long		start_time;
	bool		end_simulation; //true either by philo death or by meal limit
	t_mutex		print_mutex; // ensures atomic printing
	t_mutex		end_mutex; //protects end_simulation flag
	t_mutex		meal_mutex; // protects meal-related variables
	t_philo		*philos;
	t_fork		*forks;
};

//PARSE FUNCTIONS
int				is_valid_input(char **argv);
long int		ft_atol(char *str);

//INIT and ROUTINE FUNCTIONS
void			init_table(int argc, char **argv, t_data *data);
void			init_philo(t_data *data);
void			init_simulation(t_data *data);
void			*philosopher_routine(void *arg);
void			*monitor_routine(void *arg);
void			start_dinner(t_data *data);

//TIME UTILITY FUNCTIONS
long			get_current_time(void);
long			get_elapsed_time(t_data *data);
long			get_time_since_last_meal(t_philo *philo);
void			precise_sleep(long duration);

//GENERAL UTILITY FUNCTIONS
void			error_n_exit(char *msg, int msg_type);