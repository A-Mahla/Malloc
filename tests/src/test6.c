# include <stdlib.h>
# include <pthread.h>

void	*routine(void *arg)
{
	arg = malloc(10);
	arg = realloc(arg, 1024);
	free(arg);
	return arg;

}

int main()
{
	pthread_t		threads[50];
	char			str[50];

	for (int i = 0; i < 50; i++)
		pthread_create(threads + i, NULL, &routine, str + i);


	for (int i = 0; i < 50; i++)
		pthread_join(threads[i], NULL);

//	for (int i = 0; i < 100; i++)
//		routine(str + i);


    return (0); 
}
