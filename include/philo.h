/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:31:17 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:33:52 by daduarte         ###   ########.fr       */
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
# include "../ft_printf/includes/ft_printf.h"
# include "../ft_printf/includes/libft.h"

typedef struct s_info	t_info;

typedef struct s_philo
{
	int				id;
	int				n_philo;
	int				eat_count;
	int				fork[2];
	int				is_eating;
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
	int				all_started;
	long long		start_time;
	t_philo			**philos;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_t		monitor;
};

/* INIT */
void			all_initialized_check(t_info *info);
int				init_global_mutexes(t_info *info);
t_philo			**get_philos(t_info *info);
void			give_forks(t_philo *philo);
pthread_mutex_t	*init_forks(t_info *info);

/* PARSING UTILS */
int				valid_args(char *str);
t_philo			**get_philos(t_info *info);
t_info			*parse_input(char *argv[], int argc, t_info *info);

/* COMMON UTILS */
long long		ft_get_time(void);
void			start_delay(time_t start_time);
void			*my_error(char *str, t_info *info);
void			my_sleep(long long time, t_info *info);
void			print_status(t_philo *philo, char *str);
void			write_status(t_philo *philo, int is_a_death, char *status);

/* ROUTINES */
void			*monitoring(void *data);
void			destroy_forks(t_info *info);
void			eat_sleep_routine(t_philo *philo);
int				one_philo_routine(t_philo *philo);
int				check_for_death_or_fullness(t_info *info);
void			philo_sleep(t_info *info, time_t sleep_time);

/* PHILOSOPHER FUNCTION */
void			end_all(t_info	*info);
void			*philosophers(void *arg);
void			*free_info(t_info *info);
int				end_program(t_info *info);
int				kill_philo(t_philo *philo);
void			check_state(t_info *info, int state);
#endif
