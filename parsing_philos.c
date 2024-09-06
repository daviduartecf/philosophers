/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:32:38 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/06 22:24:39 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void	get_philos(t_info *info)
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
}*/

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

void	*my_error(char *str, t_info *info)
{
	if (info != NULL)
		free_info(info);
	printf("%s \n", str);
	return (NULL);
}

t_info	*parse_input(char *argv[], int argc, t_info *info)
{
	int	i;

	info = malloc(sizeof(t_info) * 1);
	i = 0;
	while (argv[++i])
		if (!valid_args(argv[i]))
			return (my_error("invalid args", info));
	info->someone_died = 0;
	info->n_philo = ft_atoi(argv[1]);
	if (info->n_philo > 200)
		return (my_error("Too many philo", info));
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->n_times_to_eat = ft_atoi(argv[5]);
	else
		info->n_times_to_eat = -1;
	if (!init_global_mutexes(info))
		return (my_error("Mutex init error", info));
	return (info);
}
