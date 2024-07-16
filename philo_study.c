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
		continue;
	}
}

void	destroy_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->philos[i].l_fork);
		i ++;
	}
	pthread_mutex_destroy(&info->write_mutex);
	pthread_mutex_destroy(&info->sync_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
	pthread_mutex_destroy(&info->dead_mutex);
}

void	write_action(t_philo *philo, void (*action)(int id, long long time))
{
	pthread_mutex_lock(&philo->info->write_mutex);
	if (!philo->info->someone_died && !philo->info->all_full)
		action(philo->id, ft_get_time() - philo->info->start_time);
	pthread_mutex_unlock(&philo->info->write_mutex);
}

void pick_up_forks(t_philo *philos)
{
	if (philos->id % 2 == 0 && !philos->info->someone_died && !philos->info->all_full)
	{
		pthread_mutex_lock(philos->r_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(&philos->l_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(&philos->lock);
		write_action(philos, eat);
		philos->last_meal = ft_get_time();
		philos->eat_count += 1;
		pthread_mutex_unlock(&philos->lock);
		my_sleep(philos->info->time_to_eat, philos->info);
	}
	else if (philos->id % 2 != 0 && !philos->info->someone_died && !philos->info->all_full)
	{
		pthread_mutex_lock(&philos->l_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(philos->r_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(&philos->lock);
		write_action(philos, eat);
		philos->last_meal = ft_get_time();
		philos->eat_count += 1;
		pthread_mutex_unlock(&philos->lock);
		my_sleep(philos->info->time_to_eat, philos->info);
	}
}

void	put_down_forks(t_philo *philos)
{
	pthread_mutex_unlock(&philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}

/* void	*philosophers_are_full(void *infos)
{
	int	i;
	int	count;
	t_info	*info;

	info = (t_info *)infos;
	i = 0;
	count = 0;
	if (info->n_times_to_eat == 0)
		return (NULL);
	while (i < info->n_philo)
	{
		if (info->philos[i].eat_count >= info->n_times_to_eat)
			count ++;
		i ++;
	}
	if (count == info->n_philo)
	{
		pthread_mutex_lock(&info->philos[0].lock);
		info->all_full = 1;
		info->someone_died = 1;
		pthread_mutex_unlock(&info->philos[0].lock);
		printf("ENTERED!\n");
		return (NULL);
	}
	return (NULL);
}

void	*check_for_death(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (!philo->info->someone_died)
	{
		pthread_mutex_lock(&philo->info->dead_mutex);
		if (ft_get_time() - philo->last_meal > philo->info->time_to_die)
		{
			philo->info->someone_died = 1;
			printf("%llu %d has died\n", ft_get_time() - philo->info->start_time, philo->id + 1);
			pthread_mutex_unlock(&philo->info->eat_mutex);
			return NULL;
		}
		pthread_mutex_unlock(&philo->info->dead_mutex);
		usleep(100);
	}
	return NULL;
} */

void *check_for_death_and_fullness(void *infos)
{
	t_info *info = (t_info *)infos;
	int i;

	while (!info->someone_died && !info->all_full)
	{
		int full_count = 0;
		for (i = 0; i < info->n_philo; i++)
		{
			pthread_mutex_lock(&info->philos[i].lock);
			if (ft_get_time() - info->philos[i].last_meal > info->time_to_die)
			{
				info->someone_died = 1;
				printf("%llu %d has died\n", ft_get_time() - info->start_time, info->philos[i].id + 1);
				pthread_mutex_unlock(&info->philos[i].lock);
				return (NULL);
			}
			if (info->philos[i].eat_count >= info->n_times_to_eat && info->n_times_to_eat != 0)
				full_count++;
			pthread_mutex_unlock(&info->philos[i].lock);
		}
		if (full_count == info->n_philo)
			info->all_full = 1;
		usleep(100); // Adding a small sleep to reduce CPU usage
	}
	return NULL;
}

/* void	*philosophers(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int	id;

	id = philo->id;
	pthread_create(&philo->info->death_thread, NULL, &check_for_death, &philo);
	pthread_join(philo->info->death_thread, NULL);
	while (!philo->info->someone_died)
	{
		pick_up_forks(philo);
		if (philosophers_are_full(philo->info))
			return (NULL);
		put_down_forks(philo);
		write_action(philo, sleeping);
		my_sleep(philo->info->time_to_sleep, philo->info);
		pthread_mutex_lock(&philo->info->sync_mutex);
		if (!philo->info->someone_died)
			write_action(philo, thinking);
		pthread_mutex_unlock(&philo->info->sync_mutex);
	}
	return (NULL);
} */

void *philosophers(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (!philo->info->someone_died && !philo->info->all_full)
	{
		pick_up_forks(philo);
		put_down_forks(philo);
		write_action(philo, sleeping);
		my_sleep(philo->info->time_to_sleep, philo->info);
		if (!philo->info->someone_died)
			write_action(philo, thinking);
	}
	return NULL;
}

void	get_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		info->philos[i].last_meal = ft_get_time();
		info->philos[i].id = i;
		info->philos[i].eat_count = 0;
		pthread_mutex_init(&info->philos[i].lock, NULL);
		pthread_mutex_init(&info->philos[i].l_fork, NULL);
		if (i + 1 == info->n_philo)
			info->philos[i].r_fork = &info->philos[0].l_fork;
		else
			info->philos[i].r_fork = &info->philos[i + 1].l_fork;
		info->philos[i].info = info;
		i ++;
	}
}

int	my_error(char *error_msg, t_info *info)
{
	printf("%s", error_msg);
	free(info->philos);
	return (1);
}

/* int	philo_routine(t_info *info)
{
	int	i;

	i = -1;
	if (info->time_to_eat > 0)
		pthread_create(&info->full_thread, NULL, &philosophers_are_full, &info);
	pthread_create(&info->death_thread, NULL, &check_for_death, &info);
	while (++i < info->n_philo)
	{
		if (pthread_create(&info->philos[i].thread, NULL, &philosophers, &info->philos[i]))
			return (my_error("Error creating threads\n", info));
	}
	i = -1;
	while (++i < info->n_philo)
		pthread_join(info->philos[i].thread, NULL);
	pthread_join(info->death_thread, NULL);
	pthread_join(info->full_thread, NULL);
	return (1);
} */

int philo_routine(t_info *info)
{
	int i;

	pthread_t check_thread;
	pthread_create(&check_thread, NULL, &check_for_death_and_fullness, info);

	for (i = 0; i < info->n_philo; i++)
	{
		if (pthread_create(&info->philos[i].thread, NULL, &philosophers, &info->philos[i]))
			return my_error("Error creating threads\n", info);
	}

	for (i = 0; i < info->n_philo; i++)
		pthread_join(info->philos[i].thread, NULL);

	pthread_join(check_thread, NULL);
	return (1);
}

int	one_philo_routine(t_info *info)
{
	if (pthread_create(&info->philos[0].thread, NULL, &philosophers, &info->philos[0]))
		return (my_error("Error creating threads\n", info));
	pthread_detach(info->philos[0].thread);
	//while (!info->someone_died)
	//	check_for_death(info);
	destroy_forks(info);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	int	i;

	i = -1;
	memset(&info, 0, sizeof(t_info));
	if (argc != 5 && argc != 6)
	{
		ft_printf("Wrong use. ./philo N N N N (N)\n");
		exit(1);
	}
	else
		parse_input(argv, argc, &info);
	get_philos(&info);
	if (info.n_philo == 1)
		return (one_philo_routine(&info));
	else
		philo_routine(&info);
	destroy_forks(&info);
	return (0);
}

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

void	parse_input(char *argv[], int argc, t_info *info)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!valid_args(argv[i]))
		{
			printf("One or more invalid arguments.\n");
			exit(1);
		}
	info->someone_died = 0;
	info->all_full = 0;
	info->n_philo = ft_atoi(argv[1]);
	if (info->n_philo > 200)
		exit(1);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->n_times_to_eat = ft_atoi(argv[5]);
	else
		info->n_times_to_eat = 0;
	info->start_time = ft_get_time();
	pthread_mutex_init(&info->sync_mutex, NULL);
	pthread_mutex_init(&info->dead_mutex, NULL);
	pthread_mutex_init(&info->eat_mutex, NULL);
	pthread_mutex_init(&info->write_mutex, NULL);
	memset(info->philos, 0, sizeof(t_philo) * info->n_philo);
}
