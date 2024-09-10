/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:33:42 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:32:49 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	*init_forks(t_info *info)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i ++;
	}
	return (forks);
}

void	give_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->info->n_philo;
		philo->fork[1] = philo->id;
	}
	else
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % philo->info->n_philo;
	}
}

t_philo	**get_philos(t_info *info)
{
	int		i;
	t_philo	**philos;

	philos = malloc(sizeof(t_philo) * info->n_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < info->n_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		if (pthread_mutex_init(&philos[i]->eat_mutex, 0) != 0)
			return (NULL);
		philos[i]->info = info;
		philos[i]->id = i;
		philos[i]->eat_count = 0;
		philos[i]->is_eating = 0;
		give_forks(philos[i]);
		i ++;
	}
	return (philos);
}

int	init_global_mutexes(t_info *info)
{
	info->forks_mutex = init_forks(info);
	if (!info->forks_mutex)
		return (0);
	if (pthread_mutex_init(&info->dead_mutex, 0) != 0)
		return (0);
	if (pthread_mutex_init(&info->write_mutex, 0) != 0)
		return (0);
	if (pthread_mutex_init(&info->start_mutex, 0) != 0)
		return (0);
	return (1);
}
