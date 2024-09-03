/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:34:10 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/03 15:40:36 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philos)
{
	if (philos->id % 2 == 0 && !philos->info->someone_died && !philos->info->all_full)
		pair_forks(philos);
	else if (philos->id % 2 != 0 && !philos->info->someone_died && !philos->info->all_full)
	{
		pthread_mutex_lock(&philos->l_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(philos->r_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(&philos->lock);
		write_action(philos, eat);
		philos->last_meal = ft_get_time();
		philos->eat_count += 1;
		pthread_mutex_unlock(&philos->lock);
	}
	my_sleep(philos->info->time_to_eat, philos->info);
}

void	pair_forks(t_philo *philos)
{
	pthread_mutex_lock(philos->r_fork);
	write_action(philos, picks_fork);
	pthread_mutex_lock(&philos->l_fork);
	write_action(philos, picks_fork);
	pthread_mutex_lock(&philos->lock);
	write_action(philos, eat);
	philos->last_meal = ft_get_time();
	philos->eat_count += 1;
	pthread_mutex_unlock(&philos->lock);
}

void	destroy_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->philos[i].l_fork);
		i ++;
	}
	pthread_mutex_destroy(&info->write_mutex);
	pthread_mutex_destroy(&info->sync_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
	pthread_mutex_destroy(&info->dead_mutex);
	free(info->philos);
}

void	put_down_forks(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_unlock(philos->r_fork);
		pthread_mutex_unlock(&philos->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&philos->l_fork);
		pthread_mutex_unlock(philos->r_fork);
	}
}
