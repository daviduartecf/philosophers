#include "philo.h"

uint64_t	ft_get_time(void)
{
	uint64_t	time;
	struct	timeval	tv;
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
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
}

/* void pick_up_forks(t_philo *philos, pthread_mutex_t l_fork, pthread_mutex_t r_fork, int id)
{
	if (id == philos[1].n_philo - 1)
	{
		pthread_mutex_lock(&r_fork);
		pthread_mutex_lock(&l_fork);
	}
	else
	{
		pthread_mutex_lock(&l_fork);
		pthread_mutex_lock(&r_fork);
	}
	pthread_mutex_lock(&philos->info->sync_mutex);
} */

void	put_down_forks(t_philo *philos, pthread_mutex_t l_fork, pthread_mutex_t r_fork)
{
	pthread_mutex_unlock(&l_fork);
	pthread_mutex_unlock(&r_fork);
	pthread_mutex_unlock(&philos->info->sync_mutex);
}

void	write_action(t_philo *philo, void (*action)(int id))
{
	uint64_t	times;

	times = (int)time(NULL);
	pthread_mutex_lock(&philo->info->sync_mutex);
	ft_printf("%d ", times);
	action(philo->id);
	pthread_mutex_unlock(&philo->info->sync_mutex);
}

void	*philosophers(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int	id;

	id = philo->id;
	while (1)
	{
		pthread_mutex_lock(&philo->l_fork);
		//write_action(philo, picks_fork);
		pthread_mutex_lock(&*(philo)->r_fork);
		//write_action(philo, picks_fork);
		pthread_mutex_lock(&(philo->info->eat_mutex));
		write_action(philo, eat);
		pthread_mutex_unlock(&(philo->info->eat_mutex));
		usleep(philo->info->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&*(philo)->r_fork);
		write_action(philo, sleeping);
		usleep(philo->info->time_to_sleep * 1000);
		write_action(philo, thinking);
	}
}

void	get_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		info->philos[i].id = i + 1;
		pthread_mutex_init(&info->philos[i].l_fork, NULL);
		if (i + 1 == info->n_philo)
			info->philos[i].r_fork = &info->philos[0].l_fork;
		else
			info->philos[i].r_fork = &info->philos[i + 1].l_fork;
		info->philos[i].info = info;
		i ++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo	*philos;
	t_info	info;
	int	i;

	i = -1;
	philos = NULL;
	memset(&info, 0, sizeof(t_info));
	if (argc == 5 || argc == 6)
	{
		if (!parse_input(argv, argc, &info))
			return (0);
	}
	else
		ft_printf("Wrong use. ./philo N N N N (N)");
	get_philos(&info);
	while (++i < info.n_philo)
		pthread_create(&info.philos[i].thread, NULL, philosophers, &info.philos[i]);
	i = 0;
	while (i < info.n_philo)
	{
		pthread_join(info.philos[i].thread, NULL);
		i ++;
	}
	destroy_forks(&info);
}

int	parse_input(char *argv[], int argc, t_info *info)
{
	int	i;

	i = 0;
	//while (argv[++i])
	//	if (!valid_args(argv[i]))
	//		return (0);
	info->start_time = ft_get_time();
	info->n_philo = ft_atoi(argv[1]);
	if (info->n_philo > 200)
		return (0);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->n_times_to_eat = ft_atoi(argv[5]);
	else
		info->n_times_to_eat = 0;
	pthread_mutex_init(&info->sync_mutex, NULL);
	return (1);
}
