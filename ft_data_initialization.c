#include "philo.h"

static void ft_forks_handler(t_philo *philo, t_fork *forks, int position)
{
    int num_philo;

    num_philo = philo->table->table_philo_num;
    philo->philo_first_fork = &forks[(position + 1) % num_philo];
    philo->philo_second_fork = &forks[position];
    if (philo->philo_id % 2 == 0)
    {
        philo->philo_first_fork = &forks[position];
        philo->philo_second_fork= &forks[(position + 1) % num_philo];
    }
}

static void ft_philo_starts(t_table *table)
{
    int i;
    t_philo *philo;
    
    i = -1;
    while (++i < table->table_philo_num)
    {
        philo = table->philos + i;
        philo->philo_id = i + 1;
        philo->philo_full = 0; // this means that the philo is still hungry
        philo->philo_num_meals = 0; // this means the philo meals counter.
        mutex_handle(&philo->philo_mutex, MUTEX_INIT);
        philo->table = table;
        ft_forks_handler(philo, table->forks, i);
    }
    
}

void philo_table_data_init(t_table *table)
{
    int i; 

    i = -1;
    table->table_sim_end = 0; 
    table->pthreads_done = 0;
    table->pthread_count_r = 0;
    table->philos = ft_malloc((sizeof(t_philo) * table->table_philo_num)); 
    table->forks = ft_malloc((sizeof(t_fork) * table->table_philo_num));
    mutex_handle(&table->table_mutex, MUTEX_INIT);
    mutex_handle(&table->table_write_mutex, MUTEX_INIT);
    while(++i < table->table_philo_num)
    {
        mutex_handle(&table->forks[i].fork, MUTEX_INIT);
        table->forks[i].fork_id = i;
    }
    ft_philo_starts(table);
}