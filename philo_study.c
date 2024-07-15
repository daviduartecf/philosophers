#include "philo.h"

long long	ft_get_time(void)
{
	struct	timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) * 1000) + ((long long)(tv.tv_usec) / 1000);
}

void		my_sleep(long long time)
{
	long long i;

	i = ft_get_time();
	//while (!(info->someone_dead))
	//{
	while (1)
	{
		if ((ft_get_time() - i) >= time)
			break ;
		//usleep(25);
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
	pthread_mutex_destroy(&info->sync_mutex);
	pthread_mutex_destroy(&info->eat_mutex);
}

void	write_action(t_philo *philo, void (*action)(int id, long long time))
{
	if (!philo->info->someone_died)
	{
		pthread_mutex_lock(&philo->info->sync_mutex);
		action(philo->id, ft_get_time() - philo->info->start_time);
		pthread_mutex_unlock(&philo->info->sync_mutex);
	}
}

void pick_up_forks(t_philo *philos)
{
	if (philos->id % 2 == 0 && !philos->info->someone_died)
	{
		pthread_mutex_lock(philos->r_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(&philos->l_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(&philos->info->eat_mutex);
		write_action(philos, eat);
		philos->last_meal = ft_get_time();
		pthread_mutex_unlock(&philos->info->eat_mutex);
		my_sleep(philos->info->time_to_eat);
	}
	else if (philos->id % 2 != 0 && !philos->info->someone_died)
	{
		pthread_mutex_lock(&philos->l_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(philos->r_fork);
		write_action(philos, picks_fork);
		pthread_mutex_lock(&philos->info->eat_mutex);
		write_action(philos, eat);
		philos->last_meal = ft_get_time();
		pthread_mutex_unlock(&philos->info->eat_mutex);
		my_sleep(philos->info->time_to_eat);
	}
}

void	put_down_forks(t_philo *philos)
{
	pthread_mutex_unlock(&philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}

void	*philosophers(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int	id;

	id = philo->id;
	while (!philo->info->someone_died)
	{
		pick_up_forks(philo);
		put_down_forks(philo);
		write_action(philo, sleeping);
		my_sleep(philo->info->time_to_sleep);
		write_action(philo, thinking);
	}
	return (NULL);
}

void	get_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		info->philos[i].last_meal = ft_get_time();
		info->philos[i].id = i;
		pthread_mutex_init(&info->philos[i].l_fork, NULL);
		if (i + 1 == info->n_philo)
			info->philos[i].r_fork = &info->philos[0].l_fork;
		else
			info->philos[i].r_fork = &info->philos[i + 1].l_fork;
		info->philos[i].info = info;
		i ++;
	}
}

void	check_for_death(t_info	*info, t_philo *philos)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (i < info->n_philo && !info->someone_died)
	{
		pthread_mutex_lock(&info->sync_mutex);
		if (ft_get_time() - philos[i].last_meal > info->time_to_die)
		{
			info->someone_died = 1;
			printf("%llu %d has died\n", ft_get_time() - philos->info->start_time, info->philos[i].id + 1);
			pthread_mutex_unlock(&info->sync_mutex);
			return ;
		}
		pthread_mutex_unlock(&info->sync_mutex);
		i ++;
	}
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
	while (++i < info.n_philo)
		pthread_create(&info.philos[i].thread, NULL, philosophers, &info.philos[i]);
	while (!info.someone_died)
		check_for_death(&info, info.philos);
	if (info.someone_died == 1)
		pthread_mutex_unlock(&info.sync_mutex);
	i = -1;
	while (++i < info.n_philo)
		pthread_join(info.philos[i].thread, NULL);
	destroy_forks(&info);
	return 0;
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
	pthread_mutex_init(&info->eat_mutex, NULL);
	memset(info->philos, 0, sizeof(t_philo) * info->n_philo);
}
