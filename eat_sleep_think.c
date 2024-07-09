/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:55:51 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/09 14:57:43 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo philo)
{
	ft_printf("Philosopher %d is sleeping.\n", philo.id);
	sleep(2);
}

void	eat(t_philo philo)
{
	ft_printf("Philosopher %d is eating.\n", philo.id);
	sleep(2);
}

void	thinking(t_philo philo)
{
	ft_printf("Philosopher %d is thinking.\n", philo.id);
	sleep(2);
}
