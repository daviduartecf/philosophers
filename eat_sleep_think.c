/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:55:51 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/11 12:41:52 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(int id)
{
	ft_printf("-> Philosopher %d is sleeping.\n", id + 1);
	//sleep(5);
}

void	eat(int id)
{
	ft_printf("-> Philosopher %d is eating.\n", id + 1);
	//sleep(5);
}

void	thinking(int id)
{
	ft_printf("-> Philosopher %d is thinking.\n", id + 1);
	//sleep(5);
}

void	picks_fork(int id)
{
	ft_printf("-> Philosopher %d has taken a fork.\n", id + 1);
}

void	puts_down_fork(int id)
{
	ft_printf("-> Philosopher %d puts down a fork.\n", id + 1);
}
