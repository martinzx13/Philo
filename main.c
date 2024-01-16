#include "philo.h"

void ft_error()
{
    printf(YELL"Socrates: " RED"Wrong input \n"
        YELL"Platon:" G"Correct format is : ./philo t_die t_eat t_sleep t_philo_eat\n");
}

int main(int argc, char *argv[])
{
    if (argc != 4 || argc != 5)
    {
        ft_error();
    }
}
