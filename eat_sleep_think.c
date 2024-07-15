/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:55:51 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/11 16:42:33 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(int id, long long time)
{
	printf("%llu %d is sleeping\n", time, id + 1);
}

void	eat(int id, long long time)
{
	printf("%llu %d is eating\n", time, id + 1);
}

void	thinking(int id, long long time)
{
	printf("%llu %d is thinking\n", time, id + 1);
}

void	picks_fork(int id, long long time)
{
	printf("%llu %d has taken a fork\n", time, id + 1);
}

void	puts_down_fork(int id, long long time)
{
	printf("%llu %d puts down a fork\n", time, id + 1);
}
