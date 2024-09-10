/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:57:37 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/10 13:32:59 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_state(t_info *info, int state)
{
	pthread_mutex_lock(&info->dead_mutex);
	info->someone_died = state;
	pthread_mutex_unlock(&info->dead_mutex);
}

void	print_status(t_philo *philo, char *str)
{
	printf("%lld %d %s\n", ft_get_time() - philo->info->start_time,
		philo->id + 1, str);
}

void	write_status(t_philo *philo, int is_a_death, char *status)
{
	pthread_mutex_lock(&philo->info->write_mutex);
	if (end_program(philo->info) == 1 && is_a_death == false)
	{
		pthread_mutex_unlock(&philo->info->write_mutex);
		return ;
	}
	print_status(philo, status);
	pthread_mutex_unlock(&philo->info->write_mutex);
}

void	*my_error(char *str, t_info *info)
{
	if (info != NULL)
		free_info(info);
	printf("%s \n", str);
	return (NULL);
}
