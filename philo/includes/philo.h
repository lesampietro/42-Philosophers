#include <stdio.h>
#include <stdlib.h> //malloc, free
#include <unistd.h> //write, usleep
#include <stdbool.h>
#include <pthread.h> // mutex: init, lock, unlock, destroy && threads: create, join, detach
#include <sys/time.h> //gettimeofday
#include <limits.h> //INT_MAX
#include <string.h> //memset

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
# define RST "\e[0m"

	// STRUCTURES
	typedef pthread_mutex_t t_mutex;
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
	pthread_t	tid;
	int			id;
	long		start_time;
	long		last_meal_time;
	long		meal_count;
	t_mutex		meal_mutex;
	t_fork		*left_fork;
	t_fork		*right_fork;
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
	int			all_full;
	bool		end_simulation; //true either by philo death or by meal limit
	t_mutex		print_mutex; // ensures atomic printing
	t_mutex		end_mutex; //protects end_simulation flag
	t_philo		*philos;
	t_fork		*forks;
};

//PARSE FUNCTIONS
int				is_valid_input(char **argv);
long int		ft_atol(char *str);

//INIT and ROUTINE FUNCTIONS
void			init_table(int argc, char **argv, t_data *data);
void			init_philos(t_data *data);
void			init_simulation(t_data *data);
void			*philosopher_routine(void *arg);
void			*monitor_routine(void *arg);
void			start_dinner(t_data *data);
int				is_philo_dead(t_philo *philo);
int				is_philo_full(t_philo *philo);
void			handle_single_philo(t_data *data);
void			*one_philo_routine(void *arg);
int				check_philos(t_philo *philo);
void			init_monitor(t_data *data);
int				check_philo_death(t_data *data);

//TIME UTILITY FUNCTIONS
long			get_current_time(void);
void			precise_sleep(long duration, t_data *data);

//GENERAL UTILITY FUNCTIONS
void			error_n_exit(char *msg, int msg_type, t_data *data);
void			safe_print(t_data *data, int id, char *msg);

//CLEANUP FUNCTIONS
void			free_memory(t_data *data);
void			cleanup_routine(t_data *data);