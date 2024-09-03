/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:32:38 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/03 15:04:27 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		info->philos[i].info = info;
		info->philos[i].last_meal = ft_get_time();
		info->philos[i].id = i;
		info->philos[i].eat_count = 0;
		pthread_mutex_init(&info->philos[i].lock, NULL);
		pthread_mutex_init(&info->philos[i].l_fork, NULL);
		if (i + 1 == info->n_philo)
			info->philos[i].r_fork = &info->philos[0].l_fork;
		else
			info->philos[i].r_fork = &info->philos[i + 1].l_fork;
		info->philos[i].info = info;
		i ++;
	}
}

int	valid_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

void	parse_input(char *argv[], int argc, t_info *info)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!valid_args(argv[i]))
		{
			printf("One or more invalid arguments.\n");
			exit(1);
		}
	info->someone_died = 0;
	info->all_full = 0;
	info->n_philo = ft_atoi(argv[1]);
	if (info->n_philo > 200)
		exit(1);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->n_times_to_eat = ft_atoi(argv[5]);
	else
		info->n_times_to_eat = 0;
	info->start_time = ft_get_time();
	pthread_mutex_init(&info->sync_mutex, NULL);
	pthread_mutex_init(&info->dead_mutex, NULL);
	pthread_mutex_init(&info->eat_mutex, NULL);
	pthread_mutex_init(&info->write_mutex, NULL);
}
