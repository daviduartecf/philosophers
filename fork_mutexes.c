/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:34:10 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/06 22:51:20 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
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
*/
void	*free_info(t_info *info)
{
	int	i;

	if (!info)
		return (NULL);
	if (info->forks_mutex != NULL)
		free(info->forks_mutex);
	if (info->philos != NULL)
	{
		i = 0;
		while (i < info->n_philo)
		{
			if (info->philos[i] != NULL)
				free(info->philos[i]);
			i++;
		}
		free(info->philos);
	}
	free(info);
	return (NULL);
}

void	destroy_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->forks_mutex[i]);
		pthread_mutex_destroy(&info->philos[i]->eat_mutex);
		i ++;
	}
	pthread_mutex_destroy(&info->write_mutex);
	pthread_mutex_destroy(&info->dead_mutex);
	//free(info->philos);
}
/*
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
}*/
