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
#define BLU    "\033[34m" //  - Blue 
# define RST    "\033[0m"      /* Reset to default color */

// Mutex constants.
#define MUTEX_INIT 1
#define MUTEX_LOCK 2
#define MUTEX_UNLOCK 3
#define MUTEX_DESTROY 4

// pthreads Operations.
#define CREATE 1
#define JOIN 2
#define DETACH 3

// time units.
#define MICRO_S 1
#define MILI_S 2

// States.
#define THINK 1   
#define SLEEP 2
#define EAT 3
#define DIE 4 
#define TAKE_F_FORK 5
#define TAKE_S_FORK 6

/* We will create 4 structs

  1. Fork. 
  2. Philosopher.
  3. Mutex.
  4. Table.

*/


typedef pthread_mutex_t t_mutex;

typedef struct s_table t_table;
typedef struct s_fork
{
    int     fork_id;
    t_mutex fork;
} t_fork;
typedef struct s_philosopher
{
     int    philo_id ; // Position in the table.
     long   philo_num_meals; // this variable, will be to count how many meals the philosopher can eat.
     // 0 is false. 
     // 1 is true.
     int    philo_full; // we will need to check if the philospher is full, that means that He has eat all the meals.
     long   philo_last_meal_t; // is the time of the last meal that need to be less that time to die.
    t_fork  *philo_first_fork;
    t_fork  *philo_second_fork;
    t_mutex philo_mutex;
    t_table *table;
    pthread_t philo_thread_id;

}   t_philo;
// This is the mutex struct, that will be for the control of the forks access.

// table = num philo time_die time_eat thime_sleep.
struct s_table
{
    long table_philo_num;
    long table_time_die;
    long table_time_eat;
    long table_time_sleep;
    long table_max_meals;
    long table_sim_start;
    int  table_sim_end; // this will happend if one philo die, or all are full.
    int  pthreads_done;
    long pthread_count_r; // will count that the num of process == num of philo.
    pthread_t   table_monitor;
    t_mutex table_mutex;
    t_mutex table_write_mutex;
    t_philo *philos;
    t_fork  *forks;

};

// Error handler.
void ft_error(const char *str);

// Parse the data, and put the table. 
void philo_put_the_table (t_table *table, char **argv);

// Initialize the data for the simulation. 
void philo_table_data_init(t_table *table);

// malloc handler. 
void *ft_malloc(int num);

// pthreads handler.
int pthread_handler(pthread_t *pthread, void *(*start_routine)(void *), void *restrict arg, int ops);

// mutex handler 
void mutex_handle(t_mutex *mutex, int ops);

// Value manipulation. 
void ft_set_bool(t_mutex *mutex, int *dest, int value);
int ft_get_bool(t_mutex *mutex, int *val );
void ft_set_long(t_mutex *mutex, long *dest, long value);
long ft_get_long(t_mutex *mutex, long *val );
int ft_simulation_finish(t_table *table);

// Simulation starts.
void philo_simu_start(t_table *table);

// check all threads ready.
void ft_pthreads_init_check(t_table *table);

// get time of the day.
long ft_get_time(int unit);
// sleep. 
void ft_usleep(long usec, t_table *table);
// write status. 
void ft_write(int status, t_philo *philo);
void ft_philo_eat(t_philo *philo);
void ft_philo_think(t_philo *philo, int init);
// check if all pthtreads where created.
int ft_all_philo_run(t_mutex *mutex, long *threads, long philo_nbr);
void ft_increase_pthreads(t_mutex *mutex, long *value);
void *monitor_dinner(void *data);

// clean the data. 
void philo_wash_dishes(t_table *table);
// sinc philo.
void    ft_unsync_philo(t_philo *philo);

#endif