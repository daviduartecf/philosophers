/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:38:08 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/06 22:47:07 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->info->someone_died && !philo->info->all_full)
	{
		pick_up_forks(philo);
		put_down_forks(philo);
		write_action(philo, sleeping);
		my_sleep(philo->info->time_to_sleep, philo->info);
		if (!philo->info->someone_died)
			write_action(philo, thinking);
	}
	return (NULL);
}*/

void	set_sim_stop_flag(t_info *info, int state)
{
	pthread_mutex_lock(&info->dead_mutex);
		info->someone_died = state;
	pthread_mutex_unlock(&info->dead_mutex);
}

int	has_simulation_stopped(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&info->dead_mutex);
	if (info->someone_died == 1)
		i = 1;
	pthread_mutex_unlock(&info->dead_mutex);
	return (i);
}

int	kill_philo(t_philo *philo)
{
	time_t	time;

	time = ft_get_time();
	if ((time - philo->last_meal) >= philo->info->time_to_die)
	{
		set_sim_stop_flag(philo->info, true);
		write_status(philo, true, "died");
		pthread_mutex_unlock(&philo->eat_mutex);
		return (1);
	}
	return (0);
}

void	print_status(t_philo *philo, char *str)
{
	printf("%lld %d %s\n", ft_get_time() - philo->info->start_time,
		philo->id + 1, str);
}

void	write_status(t_philo *philo, bool reaper_report, char *status)
{
	pthread_mutex_lock(&philo->info->write_mutex);
	if (has_simulation_stopped(philo->info) == true && reaper_report == false)
	{
		pthread_mutex_unlock(&philo->info->write_mutex);
		return ;
	}
	print_status(philo, status);
	pthread_mutex_unlock(&philo->info->write_mutex);
}

void	philo_sleep(t_info *info, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = ft_get_time() + sleep_time;
	while (ft_get_time() < wake_up)
	{
		if (has_simulation_stopped(info))
			break ;
		usleep(100);
	}
}

void	sim_start_delay(time_t start_time)
{
	while (ft_get_time() < start_time)
		continue ;
}

void	think_routine(t_philo *philo, int silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->eat_mutex);
	time_to_think = (philo->info->time_to_die
			- (ft_get_time() - philo->last_meal)
			- philo->info->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->eat_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == 0)
		write_status(philo, false, "is thinking");
	philo_sleep(philo->info, time_to_think);
}

void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks_mutex[philo->fork[0]]);
	write_status(philo, false, "has taken a fork");
	pthread_mutex_lock(&philo->info->forks_mutex[philo->fork[1]]);
	write_status(philo, false, "has taken a fork");
	write_status(philo, false, "is eating");
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	philo_sleep(philo->info, philo->info->time_to_eat);
	if (has_simulation_stopped(philo->info) == false)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->eat_count += 1;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	write_status(philo, false, "is sleeping");
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->fork[1]]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->fork[0]]);
	philo_sleep(philo->info, philo->info->time_to_sleep);
}

void	*philosophers(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->info->n_times_to_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal = philo->info->start_time;
	pthread_mutex_unlock(&philo->eat_mutex);
	sim_start_delay(philo->info->start_time);
	if (philo->info->time_to_die == 0)
		return (NULL);
	//if (philo->info->n_philo == 1)
	//	one_philo_routine(philo->info);
	else if (philo->id % 2)
		think_routine(philo, 1);
	while (has_simulation_stopped(philo->info) == false)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
	return (NULL);
}

int	lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks_mutex[philo->fork[0]]);
	write_status(philo, false, "GOT_FORK_1");
	philo_sleep(philo->info, philo->info->time_to_die);
	write_status(philo, false, "DIED");
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->fork[0]]);
	return (0);
}
/*
int	philo_routine(t_info *info)
{
	int			i;
	pthread_t	check_thread;

	pthread_create(&check_thread, NULL, &check_for_death_and_fullness, info);
	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_create(&info->philos[i]->thread, NULL,
				&philosophers, &info->philos[i]))
			return (my_error("Error creating threads\n", info));
		i ++;
	}
	i = -1;
	while (++i < info->n_philo)
		pthread_join(info->philos[i].thread, NULL);
	pthread_join(check_thread, NULL);
	return (1);
}

int	one_philo_routine(t_info *info)
{
	//LOCK
	//write_action(&info->philos[0], picks_fork);
	my_sleep(info->time_to_die, info);
	//UNLOCK
	printf("%llu %d died\n", ft_get_time() - info->start_time,
		info->philos[0].id + 1);
	return (1);
}

void	*check_for_death_and_fullness(void *infos)
{
	int		i;
	t_info	*info;
	int		full_count;

	info = (t_info *)infos;
	while (!info->someone_died && !info->all_full)
	{
		full_count = 0;
		i = 0;
		while (i < info->n_philo)
		{
			pthread_mutex_lock(&info->philos[i].lock);
			if (ft_get_time() - info->philos[i].last_meal > info->time_to_die)
			{
				info->someone_died = 1;
				printf("%llu %d died\n", ft_get_time() - info->start_time, info->philos[i].id + 1);
				pthread_mutex_unlock(&info->philos[i].lock);
				return (NULL);
			}
			if (info->philos[i].eat_count >= info->n_times_to_eat && info->n_times_to_eat != 0)
				full_count++;
			pthread_mutex_unlock(&info->philos[i].lock);
			i ++;
		}
		if (full_count == info->n_philo)
			info->all_full = 1;
		usleep(100);
	}
	return (NULL);
}*/
