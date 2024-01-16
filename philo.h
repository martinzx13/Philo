#ifndef PHILO_H 
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// Constants. 
#define RED  "\033[31m" //  - Red 
#define G    "\033[32m" //  - Green 
#define YELL  "\033[33m" //  - Yellow 
#define B    "\033[34m" //  - Blue 
#define MAGE "\033[35m" //  - Magenta 
#define CYAN "\033[36m" //  - Cyan 
#define WHIT "\033[37m" //  - White 
// We will create 3 structs
//  1. Folk. 
//  2. Philosopher.
//  3. Mutex.

// This is the mutex struct, that will be for the control of the forks access.
typedef struct s_mutex
{
    pthread_mutex_t mutex;
} t_muetex;

typedef struct s_table t_table;

typedef struct s_fork
{
    int num_fork;
    t_muetex mutex;
} t_fork;

typedef struct s_philo
{
    int     philo_id;
    long    num_meals;
    int     full;
    long    t_last_meal;
    t_fork  *left_fork;
    t_fork  *right_fork;
    pthread_t thread_id;
    t_table   *table;
} t_philo;

// we will create a table struct

struct s_table
{
    long    nbr_philo;
    long    time_die;
    long    time_sleep;
    long    time_eat;
    int     time_must_eat;
    long    time_sim_start;
    int     end_simulation;
    t_fork *forks;
    t_philo *philosophers;

};


#endif