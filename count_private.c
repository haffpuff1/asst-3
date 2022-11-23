#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int count1s();
int Threads();
int arr[] = {0, 1, 2, 3, 4, 5};
int *array = &arr[0];
int length = 6;
int count;


// requires : an array of integers with a certain length
// effects : counts the number of 1s in the array
int count1s()
{
    int i;
    count = 0;
    for (i = 0; i < length; i++)
    {
        if (array[i] == 1)
        {
            count++;
        }
    }
    return count;
}
//requires : an array of integers with a certain length and a count1s function and a mutex function and a number of threads and a private variable
// effects : counts the number of 1s in the array

int Threads(int nb_of_threads)
{
    int i;
    pthread_t *threads;
    int index = nb_of_threads;
    int array_private [nb_of_threads];
    threads = (pthread_t *)malloc(nb_of_threads * sizeof(pthread_t));
    for (i = 0; i < nb_of_threads; i++)
    {
        pthread_create(&threads[i], NULL, (void *)count1s, NULL);
        
    }
    for (i = 0; i < nb_of_threads; i++)
    {
        array_private[i] = count1s();
        pthread_join(threads[i], NULL);
    }
    int sum = 0;
    for(i = 0; i < nb_of_threads; i++){
    sum += array_private[i];
    }
    return sum;
}
int main()
{
    
    clock_t start, end;
    /* Store time before function call */
    start = clock();
    
    printf("The number of 1s in the array is %d", Threads(2));

    end = clock();
    /* Get the time taken by program to execute in seconds */
    double duration = ((double)end - start)/CLOCKS_PER_SEC;
     
    printf("Time taken to execute in seconds : %f", duration);  
    int array_with_no_1 [] = {0,0,0,0,0,0,0,0,5};
array = &array_with_no_1;
printf("\nNumber of 1's is %d", count1s());
printf("\nThe number of 1s in the array is %d", Threads_mutex(4));
// test 2 
int array_with_only_1 [] = {1,1,1,1,1,1,1,1,1};
array = &array_with_no_1;
printf("\nNumber of 1's is %d", count1s());
printf("\nThe number of 1s in the array is %d", Threads_mutex(4));
// test 3
int array_with_1 [] = {1,0,0,0,0,0,0,0,0};
array = &array_with_no_1;
printf("\nNumber of 1's is %d", count1s());
printf("\nThe number of 1s in the array is %d", Threads_mutex(4));
return 0;
}