/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_deaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:13:54 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:32:44 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_for_death_or_fullness(t_info *info)
{
	int	i;
	int	all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_lock(&info->philos[i]->eat_mutex);
		if (kill_philo(info->philos[i]))
			return (1);
		if (info->n_times_to_eat != -1)
			if (info->philos[i]->eat_count
				< info->n_times_to_eat)
				all_ate_enough = 0;
		pthread_mutex_unlock(&info->philos[i]->eat_mutex);
		i++;
	}
	if (info->n_times_to_eat != -1 && all_ate_enough == 1)
	{
		check_state(info, 1);
		return (1);
	}
	return (0);
}

void	*monitoring(void *data)
{
	t_info			*info;

	info = (t_info *)data;
	if (info->n_times_to_eat == 0)
		return (NULL);
	check_state(info, 0);
	start_delay(info->start_time);
	while (true)
	{
		if (check_for_death_or_fullness(info) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	all_initialized_check(t_info *info)
{
	while (1)
	{
		pthread_mutex_lock(&info->start_mutex);
		if (info->all_started == info->n_philo)
		{
			pthread_mutex_unlock(&info->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&info->start_mutex);
		usleep(100);
	}
}
