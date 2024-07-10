#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
#include <time.h>
# include <sys/time.h>
# include "../ft_printf/includes/ft_printf.h"
# include "../ft_printf/includes/libft.h"

typedef struct s_info t_info;

typedef struct s_philo
{
	pthread_t	thread;
	int	n_philo;
	int	id;
	uint64_t	last_meal;
	int	n_times_to_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	t_info	*info;
}	t_philo;

struct s_info
{
	int	n_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int	n_times_to_eat;
	int	death;
	uint64_t	start_time;
	struct s_philo	philos[200];
	pthread_mutex_t	sync_mutex;
	pthread_mutex_t	eat_mutex;
};


typedef struct s_mainstruct
{
	t_philo	*philos;
}	t_mainstruct;

int	parse_input(char *argv[], int argc, t_info *info);

void	eat(int id);
void	thinking(int id);
void	sleeping(int id);
void	picks_fork(int id);
#endif
