/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:33:42 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/06 22:51:54 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_death_or_fullness(t_info *info)
{
	int	i;
	int			all_ate_enough;

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
		set_sim_stop_flag(info, 1);
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
	set_sim_stop_flag(info, 0);
	sim_start_delay(info->start_time);
	while (true)
	{
		if (check_for_death_or_fullness(info) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

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
	if (info->n_philo > 1)
	{
		if (pthread_create(&info->monitor, NULL,
				&monitoring, info) != 0)
			return (0);
	}
	return (1);
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
	//if (DEBUG_FORMATTING == true && info->must_eat_count != -1)
	//	write_outcome(info);
	destroy_forks(info);
	free_info(info);
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
		return (lone_philo_routine(info->philos[0]));
	else
		if (start_threads(info) == 0)
			return (0);
	end_all(info);
	//destroy_forks(&info);
	return (0);
}
