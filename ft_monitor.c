#include "philo.h"

static int philo_died(t_philo *philo)
{
    long elapsed;
    long t_die;

    if (ft_get_bool(&philo->philo_mutex, &philo->philo_full))
        return (0);
    elapsed = ft_get_time(MILI_S) - ft_get_long(&philo->philo_mutex, &philo->philo_last_meal_t);
    t_die = philo->table->table_time_die /1e3;
    if (elapsed > t_die)
        return (1);
    return (0);
}

void *monitor_dinner(void *data)
{
    t_table *table;
    int i;

    table = (t_table *) data;
    // I need to make sure that all philos rining
    // Spinlock until threads run.
    while (!ft_all_philo_run(&table->table_mutex, 
        &table->pthread_count_r, table->table_philo_num))
        ;
    while (!ft_simulation_finish(table))
    {
        i = -1;
        while (++i < table->table_philo_num && !ft_simulation_finish(table))
        {
            if(philo_died(table->philos + i))
            {
                ft_set_bool(&table->table_mutex, &table->table_sim_end, 1);
                ft_write(DIE, table->philos + i);
            }
        }
        
    }
    
}