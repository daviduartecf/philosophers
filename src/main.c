/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:33:42 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:32:51 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_threads(t_info *info)
{
	int	i;

	info->start_time = ft_get_time() + (info->n_philo * 2 * 10);
	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_create(&info->philos[i]->thread, NULL,
				&philosophers, info->philos[i]) != 0)
			return (0);
		i++;
	}
	all_initialized_check(info);
	if (info->n_philo > 1)
	{
		if (pthread_create(&info->monitor, NULL,
				&monitoring, info) != 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info	*info;

	info = NULL;
	if (argc != 5 && argc != 6)
	{
		ft_printf("Wrong use. ./philo N N N N (N)\n");
		return (1);
	}
	info = parse_input(argv, argc, info);
	if (!info)
		return (0);
	info->philos = get_philos(info);
	if (info->n_philo == 1)
		return (one_philo_routine(info->philos[0]));
	else
		if (start_threads(info) == 0)
			return (0);
	end_all(info);
	return (0);
}
