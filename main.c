#include "philo.h"

int main(int argc, char *argv[])
{
    t_table table;

    if (argc == 4 || argc == 5)
    {
        // Parse the data, and fill the table.
        put_the_table(&table, argv);
        // create the dinner.

        // Clean the data.   
    }
    else 
    {
        ft_error(YELL"Socrates: " RED"Wrong input \n"
        YELL"Platon:" G"Correct format is : ./philo t_die t_eat t_sleep t_philo_eat");
    }
}
