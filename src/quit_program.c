/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:34:10 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:32:55 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
}

void	end_all(t_info	*info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_join(info->philos[i]->thread, NULL);
		i++;
	}
	if (info->n_philo > 1)
		pthread_join(info->monitor, NULL);
	destroy_forks(info);
	free_info(info);
}
