#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int i;

void *routine()
{
	int j;

	j = 0;
	while(j < 1000000000)
	{
		pthread_mutex_lock(&mutex);
		i++;
		j++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main()
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_mutex_init(&mutex, NULL);


	printf("%d\n", i);
	pthread_create(&thread1, NULL, routine, NULL);
	pthread_create(&thread2, NULL, routine, NULL);


	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("%d\n", i);
}
