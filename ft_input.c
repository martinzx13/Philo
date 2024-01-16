#include "philo.h"

static int is_space(const char c)
{
    if (c == ' ' || c == '\n' || c == '\t')
        return (1);
    return (0);
}

static int is_digit(const char c)
{
    if(c >= '0'  && c <= '9')
        return (1);
    return (0);
}

static int ft_check(char *str)
{
    int i;
    
    while (is_space(*str))
        str++;
    if (*str == '+')
        str++;
    if (*str == '-')
        ft_error(RED "Error can not get negative values");
    while (*str)
    {
        if (!is_digit(*str))
            ft_error(RED "Incorrect parameter, only integers");
        str++;
    }
    return (0);
        
    
}

int ft_atoi(char *str)
{
    int num;
    int i;

    i = 0;
    num = 0;
    if (!ft_check(str))
    {
        while (str[i])
            num = num * 10 + (str[i++] - '0');
    }
    return (num);
}

int put_the_table( t_table *table, char **args)
{
    table->nbr_philo = ft_atoi(args[1]);
    printf("Philosopher : %ld\n", table->nbr_philo);
    table->time_eat  = ft_atoi(args[2]);
    table->time_die = ft_atoi(args[3]);
    table->time_sleep = ft_atoi(args[4]);
    if (args[5])
        table->time_must_eat = ft_atoi(args[5]);
    else
        table->time_must_eat = -1;
}