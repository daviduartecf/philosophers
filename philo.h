/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:31:17 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/06 22:34:20 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include "ft_printf/includes/ft_printf.h"
# include "ft_printf/includes/libft.h"

typedef struct s_info	t_info;

typedef struct s_philo
{
	int				id;
	int				n_philo;
	int				eat_count;
	int				fork[2];
	t_info			*info;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	eat_mutex;
}	t_philo;

struct s_info
{
	int				n_philo;
	int				time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				n_times_to_eat;
	int				someone_died;
	long long		start_time;
	t_philo			**philos;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_t		monitor;
};

/* NEW */
void	eat_sleep_routine(t_philo *philo);
void	think_routine(t_philo *philo, int silent);
void	sim_start_delay(time_t start_time);
void	philo_sleep(t_info *info, time_t sleep_time);
void	write_status(t_philo *philo, bool reaper_report, char *status);
void	print_status(t_philo *philo, char *str);
int	kill_philo(t_philo *philo);
int	has_simulation_stopped(t_info *info);
void	set_sim_stop_flag(t_info *info, int state);
int	check_for_death_or_fullness(t_info *info);
void	*free_info(t_info *info);
t_info	*parse_input(char *argv[], int argc, t_info *info);
int	lone_philo_routine(t_philo *philo);

/* INIT */
int	init_global_mutexes(t_info *info);
t_philo	**get_philos(t_info *info);
void	give_forks(t_philo *philo);
pthread_mutex_t	*init_forks(t_info *info);

/* PARSING UTILS */
//void		parse_input(char *argv[], int argc, t_info *info);
int			valid_args(char *str);
t_philo		**get_philos(t_info *info);

/* COMMON UTILS */
long long	ft_get_time(void);
void		my_sleep(long long time, t_info *info);
//void		write_action(t_philo *philo,
//				void (*action)(int id, long long time));
void	*my_error(char *str, t_info *info);

/* ROUTINES */
void		pick_up_forks(t_philo *philos);
void		eat(int id, long long time);
void		destroy_forks(t_info *info);
void		pair_forks(t_philo *philos);
void		thinking(int id, long long time);
void		sleeping(int id, long long time);
void		picks_fork(int id, long long time);
void		put_down_forks(t_philo *philos);

/* PHILOSOPHER FUNCTION */
void		*philosophers(void *arg);
int			philo_routine(t_info *info);
int			one_philo_routine(t_info *info);
void		*check_for_death_and_fullness(void *infos);
#endif
