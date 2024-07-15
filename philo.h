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
	int				id;
	int				n_philo;
	int				n_times_to_eat;
	t_info			*info;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

struct s_info
{
	int				n_philo;
	int			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				n_times_to_eat;
	int				someone_died;
	long long		start_time;
	t_philo			philos[200];
	pthread_mutex_t	sync_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_t	death_thread;
};

void	parse_input(char *argv[], int argc, t_info *info);

void	eat(int id, long long time);
void	thinking(int id, long long time);
void	sleeping(int id, long long time);
void	picks_fork(int id, long long time);
void	puts_down_fork(int id, long long time);
#endif
