/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:33:42 by daduarte          #+#    #+#             */
/*   Updated: 2024/09/03 15:36:11 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int		i;
	t_info	info;

	i = -1;
	memset(&info, 0, sizeof(t_info));
	if (argc != 5 && argc != 6)
	{
		ft_printf("Wrong use. ./philo N N N N (N)\n");
		return (1);
	}
	parse_input(argv, argc, &info);
	info.philos = malloc(sizeof(t_philo) * info.n_philo);
	if (!info.philos)
	{
		perror("Failed to allocate memory for philosophers");
		return (2);
	}
	get_philos(&info);
	if (info.n_philo == 1)
		one_philo_routine(&info);
	else
		philo_routine(&info);
	destroy_forks(&info);
	return (0);
}
