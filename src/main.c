/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:30:42 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/03 22:13:25 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* starts the philo simulation; 
start_time: + nb_philos * 8 to get a small delay when calling sim_start_delay;
********************************************************
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
void *(*start_routine) (void *), void *arg);
The function eturns 0 if the creation was successful;
int pthread_create(thread var, NULL, * to thread function to be executed, 
variable used in thread function);
thread: ptr towards pthread_t type var, to store ID of thread we will create.
attr: in general, passing NULL here suffices.
start_routine: function where thread start its execution. When thread reaches 
end of this function, it will be done with its tasks.
arg: ptr towards an argument to pass to thread’s start_routine fct. If we pass
several parameters to this fct, we need to give it a ptr to a data structure.
********************************************************
creates a thread for each philosopher and a multiple_killer thread
and returns true if everything was successful;
from here call philosopher & multiple_killer fct by creating threads for them */
static bool start_simulation(t_table *table)
{
    unsigned int    i;

    i = 0;
    table->start_time = time_in_ms() + (table->nb_philos * 8); // better * 10?
    while (i < table->nb_philos)
    {
        if (pthread_create(&table->philos[i]->thread, NULL, &philosopher, table->philos[i]) != 0)
            return (error_failure(STR_ERR_THREAD, NULL, table));
        i++;
    }
    if (table->nb_philos > 1)
    {
        if (pthread_create(&table->multiple_killer, NULL, &multiple_killer, table) != 0)
           return (error_failure(STR_ERR_THREAD, NULL, table)); 
    }
    return (true);
}

/* waits for all threads to be done;
pthread_join(thread variable, var can save return value of thread function);
pthread_join waits until thread is done & only then program can be finished;
end of a thread is determined via has_simulation_stopped which is
called in each philo's thread individually;
*************************************************
all created mutexes are getting destroyed (forks, eat_time_lock, ...);
all philos are getting freeed and the table pointer */
static void stop_simulation(t_table *table)
{
    unsigned int    i;

    i = 0;
    while (i < table->nb_philos)
    {
        pthread_join(table->philos[i]->thread, NULL);
        i++;
    }
    if (table->nb_philos > 1)
        pthread_join(table->multiple_killer, NULL);
    destroy_mutexes(table);
    free_table(table);
}

/* First check if input is valid;
then the process gets initialized before simulation starts;
after simulation gets stopped; 
EXIT_SUCCESS is defined as 0 and EXIT_FAILURE as 8;
table: data structure that contains the program parameters */
int main(int argc, char **argv)
{
    t_table *table;

    table = NULL;
    (void)argv;
    if (argc != 5 && argc != 6)
        return (input_error_msg(STR_INPUT_FORMAT, NULL, EXIT_FAILURE));
    if (!is_valid_input(argc, argv))
        return (EXIT_FAILURE);
    table = init_process(argc, argv);
    if (!table)
        return (EXIT_FAILURE);
    if (!start_simulation(table))
        return (EXIT_FAILURE);
    stop_simulation(table);
    return (EXIT_SUCCESS);
}
