#include <stdio.h>
#include <pthread.h>

void	*computation(void *add);

int	main()
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_mutex_t mutex;

	long	value1 = 1;
	long	value2 = 2;

	//computation((void *) &value1);
	//computation((void *) &value2);
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread1, NULL, computation, (void *)&value1);
	pthread_create(&thread2, NULL, computation, (void *)&value2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
}

void	*computation(void *add)
{
	long *add_num;
	long sum = 0;

	add_num = (long *)(add);
	for (long i = 0; i < 1000000000; i ++)
		sum += *add_num;
	printf("Well Done: %ld\n", *add_num);
	return (NULL);
}
