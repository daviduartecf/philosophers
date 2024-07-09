#include "philo.h"

pthread_mutex_t	*initialize_forks(pthread_mutex_t *forks, int len)
{
	int	i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * len);
	while (i < len)
	{}
}

void	pick_up_forks(t_philo *philos)
{
	if (philos->id == -1)
	{

	}
}

void	philosophers(t_philo *philos)
{

}

int	main(int argc, char *argv[])
{
	pthread_mutex_t	*forks;
	t_philo	*philos;
	int	i;

	i = 0;
	philos = NULL;
	if (argc == 5 || argc == 6)
		philos = parse_input(argv, argc);
	else
		ft_printf("Wrong use. ./philo N N N N (N)");
	forks = initialize_forks(forks, ft_atoi(argv[1]));
	while (i < philos[0].n_philo)
	{
		philos[i].thread = i;
		pthread_create(&philos[i].thread, NULL, philosophers, (void *)&philos);
		i ++;
	}
	i = 0;
	while (i < philos[0].n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i ++;
	}
}
t_philo	get_philo(char *argv[], int argc, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.n_philo = ft_atoi(argv[1]);
	philo.time_to_die = ft_atoi(argv[2]);
	philo.time_to_eat = ft_atoi(argv[3]);
	philo.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.n_times_to_eat = ft_atoi(argv[5]);
	else
		philo.n_times_to_eat = 0;
	return (philo);
}
t_philo	*parse_input(char *argv[], int argc)
{
	t_philo	*philos;
	int	i;
	int	n_philos;

	i = 0;
	n_philos = ft_atoi(argv[1]);
	philos = malloc((n_philos + 1) * sizeof(t_philo));
	if (!philos)
		exit(1);
	while (i < n_philos)
	{
		philos[i] = get_philo(argv, argc, i);
		i ++;
	}
	philos[i].id = -1;
	return (philos);
}
