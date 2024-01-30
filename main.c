#include "philo.h"


int main(int argc, char *argv[])
{
    t_table table;

    if (argc == 5 || argc == 6)
    {
        philo_put_the_table(&table, argv);
        // initializa all the other values.
        philo_table_data_init(&table);
        philo_simu_start(&table);
        philo_wash_dishes(&table);
    }
    else 
    {
        ft_error(RED"Incorrect Number of Parameters, please try:\n\t" 
        "./philo philo t_die t_eat t_sleep max_meals");
    }

}
