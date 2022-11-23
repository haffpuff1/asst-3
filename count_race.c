#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


int *array;
int length = 100;
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

// requires : an array of integers with a certain length and a certain nb of threads
// effects : creates nb of threads and counts the number of 1s in the array
int Threads_race(int nb_of_threads)
{
    int i;
    pthread_t *threads;
    int index = nb_of_threads;
    threads = (pthread_t *)malloc(nb_of_threads * sizeof(pthread_t));
    for (i = 0; i < nb_of_threads; i++)
    {
        pthread_create(&threads[i], NULL, (void *)count1s, NULL);
        
    }
    for (i = 0; i < nb_of_threads; i++)
    {

        pthread_join(threads[i], NULL);
    }
    return count;
}
// effects : tests the function we created and returns the result
int main()
{
    
    clock_t start, end;
    /* Store time before function call */
    start = clock();
    
    int randArray[length],i;
    for(i=0;i<length;i++)
        randArray[i]=rand()%6;   //Generate number between 0 and 5

    printf("\nElements of the array::");
    for(i=0;i<length;i++)
    {
        printf("\nElement number %d::%d",i+1,randArray[i]);
    }


    array = &randArray;
    printf("\nNumber of 1's is %d", count1s());
    printf("\nThe number of 1s in the array is %d", Threads_race(10));

    end = clock();
    /* Get the time taken by program to execute in seconds */
    double duration = ((double)end - start)/CLOCKS_PER_SEC;
     
    printf("Time taken to execute in seconds : %f", duration);   
// test cases if we have an array of zero ones this is test 1 
// test 2 if we have an array of only ones
// test 3 if we have an array of 1s only

// test 1
int array_with_no_1 [] = {0,0,0,0,0,0,0,0,5};
array = &array_with_no_1;
printf("\nNumber of 1's is %d", count1s());
printf("\nThe number of 1s in the array is %d", Threads_race(10));
// test 2 
int array_with_only_1 [] = {1,1,1,1,1,1,1,1,1};
array = &array_with_no_1;
printf("\nNumber of 1's is %d", count1s());
printf("\nThe number of 1s in the array is %d", Threads_race(10));
// test 3
int array_with_1 [] = {1,0,0,0,0,0,0,0,0};
array = &array_with_no_1;
printf("\nNumber of 1's is %d", count1s());
printf("\nThe number of 1s in the array is %d", Threads_race(10));
return 0;
}