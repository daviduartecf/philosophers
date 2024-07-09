#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include "../ft_printf/includes/ft_printf.h"
# include "../ft_printf/includes/libft.h"

typedef struct s_philo
{
	pthread_t	thread;
	int	n_philo;
	int	id;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int	n_times_to_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*deal_lock;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*write_lock;
}	t_philo;

typedef struct s_mainstruct
{
	pthread_mutex_t	deal_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
	t_philo	*philos;
}	t_mainstruct;

t_philo	*parse_input(char *argv[], int argc);

void	eat(t_philo philo);
void	thinking(t_philo philo);
void	sleeping(t_philo philo);
#endif
