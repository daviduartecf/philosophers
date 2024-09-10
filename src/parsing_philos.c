/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:32:38 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:32:53 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

t_info	*parse_input(char *argv[], int argc, t_info *info)
{
	int	i;

	info = malloc(sizeof(t_info) * 1);
	ft_memset(info, 0, sizeof(t_info));
	i = 0;
	while (argv[++i])
		if (!valid_args(argv[i]))
			return (my_error("Invalid args", info));
	info->someone_died = 0;
	info->all_started = 0;
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
