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

static int ft_atoi(char *str)
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

void philo_put_the_table (t_table *table, char **argv)
{
    table->table_philo_num = ft_atoi(argv[1]);
    table->table_time_die = ft_atoi(argv[2]) * 1e3;
    table->table_time_eat = ft_atoi(argv[3]) * 1e3;
    table->table_time_sleep = ft_atoi(argv[4]) * 1e3;
    if (argv[5])
        table->table_max_meals = ft_atoi(argv[5]);
    else 
        table->table_max_meals = -1;
}