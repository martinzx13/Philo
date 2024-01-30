#include "philo.h"

void ft_error(const char *str)
{
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

long ft_get_time(int unit)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == 0)
    {
        if (unit  == MICRO_S)
            return (tv.tv_sec * 1e6 + tv.tv_usec);
        else if (unit == MILI_S)
            return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
    }
    else 
        ft_error(RED"gettingtimeof() failed");
    return (-1);
}

// Precise Usleep funcion.

void ft_usleep(long usec, t_table *table)
{
    long start;
    long elapsed;
    long rem;

    start = ft_get_time(MICRO_S);
    while (ft_get_time(MICRO_S) - start < usec)
    {
        if (ft_simulation_finish(table))
            break;
        elapsed = ft_get_time(MICRO_S) - start;
        rem = usec - elapsed;
        if (rem > 1e4)
            usleep(rem / 2);
        else
            while (ft_get_time(MICRO_S) - start < usec)
                ;
            
    }
}


void ft_write(int status, t_philo *philo)
{

    long elapsed;
    elapsed = ft_get_time(MILI_S) - philo->table->table_sim_start;
    if (ft_get_bool(&philo->philo_mutex, &philo->philo_full))
		return ;
    mutex_handle(&philo->table->table_write_mutex, MUTEX_LOCK);
    if (status == TAKE_F_FORK && (!ft_simulation_finish(philo->table)))
        printf("%-4ld Philo %d Has taken the first fork\n", elapsed, philo->philo_id);
    else if (status == TAKE_S_FORK && (!ft_simulation_finish(philo->table)))
        printf("%-4ld Philo %d Has taken the second fork\n", elapsed, philo->philo_id);
    else if (status == THINK && !ft_simulation_finish(philo->table))
        printf("%-4ld Philo %d is thinking \n", elapsed, philo->philo_id);
    else if (status == SLEEP && !ft_simulation_finish(philo->table))
        printf("%-4ld Philo %d is sleeping\n", elapsed, philo->philo_id);
    else if (status == EAT && !ft_simulation_finish(philo->table))
        printf("%-4ld "YELL"Philo %d is eating \n"RST, elapsed, philo->philo_id);
    else if (status == DIE )
        printf("%-4ld Philo %d has died\n", elapsed, philo->philo_id);
    mutex_handle(&philo->table->table_write_mutex, MUTEX_UNLOCK);

}
