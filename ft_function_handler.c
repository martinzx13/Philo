#include "philo.h"

/*
    Malloc handler.
this will contain the malloc handler function, that is 
usesfull to allocate any type of data, and also protect 
it to avoid any further problem with the memory.

    Mutex handler
we will create a function to handle the mutex.
as we need to protected. 

*/

void *ft_malloc(int num)
{
    void *args;
    
    args = malloc(num);
    if (!args)
        ft_error(RED"Problem with malloc");
}

void mutex_handle(t_mutex *mutex, int ops)
{
    // init.
    if (ops == MUTEX_LOCK)
    {
        if (pthread_mutex_lock(mutex) != 0)
            ft_error(RED"Problem with the mutex join");
    }
    else if (ops == MUTEX_UNLOCK)
    {
        if (pthread_mutex_unlock(mutex) != 0)
            ft_error(RED"Problem with the mutex unlock");
    }
    else if (ops == MUTEX_INIT)
    {
        if (pthread_mutex_init(mutex, NULL) != 0)
            ft_error(RED"Problem with the mutex initialization");
    }
    else if (ops == MUTEX_DESTROY)
    {
        if (pthread_mutex_destroy(mutex) != 0)
            ft_error(RED"Problem with mutex destruction");
    }
    else 
        ft_error("Wrong code.");
}

int pthread_handler(pthread_t *thread_id, void *(*start_routine)(void *), void *arg, int ops)
{
    if (ops == CREATE)
    {
        if (pthread_create(thread_id, NULL, start_routine, arg) != 0)
            ft_error("Error with the pthread creation");
    }
    else if (ops == JOIN)
    {
        if (pthread_join(*thread_id, NULL) != 0)
            ft_error(RED"Problem with the pthread join function");
    }
    else if (ops == DETACH)
    {
        if (pthread_detach(*thread_id) != 0)
            ft_error(RED"Problem with the phtread detach function");
    }
    else
        ft_error("Wrong code.");

}

void ft_set_bool(t_mutex *mutex, int *dest, int value)
{
    mutex_handle(mutex, MUTEX_LOCK);
    *dest = value;
    mutex_handle(mutex, MUTEX_UNLOCK);
}

int ft_get_bool(t_mutex *mutex, int *val )
{
    int res;
    
    mutex_handle(mutex, MUTEX_LOCK);
    res = *val;
    mutex_handle(mutex, MUTEX_UNLOCK);
    return (res);
}

void ft_set_long(t_mutex *mutex, long *dest, long value)
{
    mutex_handle(mutex, MUTEX_LOCK);
    *dest = value;
    mutex_handle(mutex, MUTEX_UNLOCK);
}

long ft_get_long(t_mutex *mutex, long *val )
{
    long res;
    
    mutex_handle(mutex, MUTEX_LOCK);
    res = *val;
    mutex_handle(mutex, MUTEX_UNLOCK);
    return (res);
}


int ft_simulation_finish(t_table *table)
{
    return(ft_get_bool(&table->table_mutex, &table->table_sim_end));
}

void ft_increase_pthreads(t_mutex *mutex, long *value)
{
    mutex_handle(mutex, MUTEX_LOCK);
    (*value)++;
    mutex_handle(mutex, MUTEX_UNLOCK);
}
int ft_all_philo_run(t_mutex *mutex, long *threads, long philo_nbr)
{
    int ret;

    ret = 0;
    mutex_handle(mutex, MUTEX_LOCK);
    if (*threads == philo_nbr)
        ret = 1;
    mutex_handle(mutex, MUTEX_UNLOCK);
    return (ret);
}


void philo_wash_dishes(t_table *table)
{
    t_philo *philo;
    int i;

    i = -1;
    while (++i < table->table_philo_num)
    {
        philo = table->philos + i;
        mutex_handle(&philo->philo_mutex,MUTEX_DESTROY);
    }
    mutex_handle(&table->table_write_mutex, MUTEX_DESTROY);
    mutex_handle(&table->table_write_mutex, MUTEX_DESTROY);
    free(table->forks);
    free(table->philos);

    
}

/// make system fair. 
void    ft_unsync_philo(t_philo *philo)
{
    if (philo->table->table_philo_num % 2 == 0)
    {
        if (philo->philo_id % 2 == 0)
        {
            ft_usleep(3e4, philo->table);
        }
    }
    else 
    {
        if (philo->philo_id % 2)
            ft_philo_think(philo, 1);
    }
}
