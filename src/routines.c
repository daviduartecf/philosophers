/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:38:08 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:32:56 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	end_program(t_info *info)
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
	if ((time - philo->last_meal)
		> philo->info->time_to_die && philo->is_eating != 1)
	{
		check_state(philo->info, true);
		write_status(philo, 1, "died");
		pthread_mutex_unlock(&philo->eat_mutex);
		return (1);
	}
	return (0);
}

void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks_mutex[philo->fork[0]]);
	write_status(philo, false, "has taken a fork");
	pthread_mutex_lock(&philo->info->forks_mutex[philo->fork[1]]);
	write_status(philo, false, "has taken a fork");
	write_status(philo, false, "is eating");
	pthread_mutex_lock(&philo->eat_mutex);
	philo->is_eating = 1;
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	philo_sleep(philo->info, philo->info->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->fork[1]]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->fork[0]]);
	if (end_program(philo->info) == 0)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->eat_count += 1;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	write_status(philo, 0, "is sleeping");
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
	pthread_mutex_lock(&philo->info->start_mutex);
	philo->info->all_started += 1;
	pthread_mutex_unlock(&philo->info->start_mutex);
	start_delay(philo->info->start_time);
	if (philo->info->time_to_die == 0)
		return (NULL);
	while (end_program(philo->info) == 0)
	{
		eat_sleep_routine(philo);
		write_status(philo, 0, "is thinking");
	}
	return (NULL);
}

int	one_philo_routine(t_philo *philo)
{
	philo->info->start_time = ft_get_time();
	pthread_mutex_lock(&philo->info->forks_mutex[philo->fork[0]]);
	write_status(philo, 0, "has taken a fork");
	philo_sleep(philo->info, philo->info->time_to_die);
	write_status(philo, 0, "died");
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->fork[0]]);
	destroy_forks(philo->info);
	free_info(philo->info);
	return (0);
}
