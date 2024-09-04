/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:57:37 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/03 15:08:41 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct	timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000) + ((long long)(tv.tv_usec) / 1000);
}

void		my_sleep(long long time, t_info *info)
{
	long long i;

	i = ft_get_time();

	while (!(info->someone_died))
	{
		if ((ft_get_time() - i) >= time)
			break ;
		usleep(100);
		//continue;
	}
}

void	write_action(t_philo *philo, void (*action)(int id, long long time))
{
	pthread_mutex_lock(&philo->info->write_mutex);
	if (!philo->info->someone_died && !philo->info->all_full)
		action(philo->id, ft_get_time() - philo->info->start_time);
	pthread_mutex_unlock(&philo->info->write_mutex);
}

int	my_error(char *error_msg, t_info *info)
{
	printf("%s", error_msg);
	free(info->philos);
	return (1);
}


