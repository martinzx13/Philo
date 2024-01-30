#include "philo.h"

void *lone_philo(void *args)
{
    t_philo *philo;

    philo = (t_philo *) args;
    ft_set_long(&philo->philo_mutex, &philo->philo_last_meal_t, ft_get_time(MILI_S));
    ft_increase_pthreads(&philo->table->table_mutex, &philo->table->pthread_count_r);
    ft_write(TAKE_F_FORK, philo);
    while (!ft_simulation_finish(philo->table))
        ft_usleep(200, philo->table);
    return NULL;
    
}

/*

    if !meals return 
    create all threads for all the philos.
    create a monitor thread.
    sync the beginning and the end.
    we want all the philo start at same time.
    join.
*/

void ft_philo_think(t_philo *philo, int init)
{
    long t_think;

    if (!init)
        ft_write(THINK, philo);
    if (philo->table->table_philo_num % 2 == 0)
        return;
    t_think = philo->table->table_time_eat * 2 - philo->table->table_time_sleep;
    if (t_think < 0 )
        t_think = 0;
    ft_usleep(t_think * 0.42, philo->table);
}

void ft_philo_eat(t_philo *philo)
{
    mutex_handle(&philo->philo_first_fork->fork, MUTEX_LOCK);
    ft_write(TAKE_F_FORK, philo);
    mutex_handle(&philo->philo_second_fork->fork, MUTEX_LOCK);
    ft_write(TAKE_S_FORK, philo);
    ft_set_long(&philo->philo_mutex, 
        &philo->philo_last_meal_t, ft_get_time(MILI_S));
    philo->philo_num_meals++;
    ft_write(EAT, philo);
    ft_usleep(philo->table->table_time_eat, philo->table);
    if (philo->table->table_max_meals > 0 
        && philo->philo_num_meals == philo->table->table_max_meals)
            ft_set_bool(&philo->philo_mutex, &philo->philo_full, 1);
    mutex_handle(&philo->philo_first_fork->fork, MUTEX_UNLOCK);
    mutex_handle(&philo->philo_second_fork->fork, MUTEX_UNLOCK);

}

void ft_pthreads_init_check(t_table *table)
{
    while (ft_get_bool(&table->table_mutex, &table->pthreads_done) == 0)
        ;
    
}
static void *ft_simutation_process (void *data)
{
    t_philo *philo;
    
	// printf("ft_simutation_process: %d\n", TAKE_F_FORK);
    philo = (t_philo *) data;
    ft_pthreads_init_check(philo->table);
   
    ft_set_long(&philo->philo_mutex, &philo->philo_last_meal_t, ft_get_time(MILI_S));
    ft_increase_pthreads(&philo->table->table_mutex, &philo->table->pthread_count_r);

    ft_unsync_philo(philo);
    while (!ft_simulation_finish(philo->table))
    {
        if (ft_get_bool(&philo->philo_mutex, &philo->philo_full))
            break;
        // eat.
        ft_philo_eat(philo);
        //sleep.---> write status.
        ft_write(SLEEP, philo);
        ft_usleep(philo->table->table_time_sleep, philo->table);
        //think.

        ft_philo_think(philo, 0);


    }
    
}

void philo_simu_start(t_table *table)
{
    int i;
    i = -1;
    if (table->table_max_meals == 0)
        return ;
    else if (table->table_philo_num == 1)
        pthread_handler(&table->philos[0].philo_thread_id, lone_philo, &table->philos[0], CREATE);
    else
    {
        while (++i < table->table_philo_num)
        {
            pthread_handler(&table->philos[i].philo_thread_id, 
                ft_simutation_process,&table->philos[i], CREATE);
        }
    }
    // monitor.
    pthread_handler(&table->table_monitor, monitor_dinner, table, CREATE);
    table->table_sim_start = ft_get_time(MILI_S);
    ft_set_bool(&table->table_mutex, &table->pthreads_done, 1);

    i = -1;
    while(++i < table->table_philo_num)
        pthread_handler(&table->philos[i].philo_thread_id, NULL, NULL, JOIN);

    ft_set_bool(&table->table_mutex, &table->table_sim_end, 1);
    pthread_handler(&table->table_monitor, NULL, NULL, JOIN);
}