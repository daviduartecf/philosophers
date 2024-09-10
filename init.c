/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:33:42 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/06 22:22:25 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(t_info *info)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if(!forks)
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
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->info->n_philo;
	if (philo->id % 2)
	{
		philo->fork[1] = (philo->id + 1) % philo->info->n_philo;
		philo->fork[0] = philo->id;
	}
}

t_philo	**get_philos(t_info *info)
{
	t_philo	**philos;
	int	i;

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
	return (1);
}
