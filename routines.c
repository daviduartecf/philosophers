/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:38:08 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/03 14:54:17 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *arg)
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
}

int	philo_routine(t_info *info)
{
	int			i;
	pthread_t	check_thread;

	pthread_create(&check_thread, NULL, &check_for_death_and_fullness, info);
	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_create(&info->philos[i].thread, NULL,
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
	write_action(&info->philos[0], picks_fork);
	my_sleep(info->time_to_die, info);
	//UNLOCK
	printf("%llu %d has died\n", ft_get_time() - info->start_time,
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
				printf("%llu %d has died\n", ft_get_time() - info->start_time, info->philos[i].id + 1);
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
}
