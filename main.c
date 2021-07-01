#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

void	*print_id(void *arg)
{
	int	*id;

	id = arg;
	printf("id = %i\n", *id);
	return (NULL);
}

int	main(void)
{
	int				ret;
	struct timeval	*tp;
	pthread_t		thread;

	ret = gettimeofday(tp, NULL);

	printf("ret = %i\ntv_sec = %li\ntv_usec = %i\n", ret, tp->tv_sec, tp->tv_usec);
	pthread_create(&thread, NULL, print_id, &thread);
	pthread_join(thread, NULL);
	return (0);
}
