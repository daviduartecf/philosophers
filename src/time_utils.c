/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:48:51 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:32:57 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_delay(time_t start_time)
{
	while (ft_get_time() < start_time)
		continue ;
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)(tv.tv_sec)*1000) + ((long long)(tv.tv_usec) / 1000));
}

void	my_sleep(long long time, t_info *info)
{
	long long	i;

	i = ft_get_time();
	while (!(info->someone_died))
	{
		if ((ft_get_time() - i) >= time)
			break ;
		usleep(100);
	}
}

void	philo_sleep(t_info *info, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = ft_get_time() + sleep_time;
	while (ft_get_time() < wake_up)
	{
		if (end_program(info))
			break ;
		usleep(100);
	}
}
