/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:56:25 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/03 22:16:28 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* routine for if only 1 philosopher exists;
philo can only pick up 1 fork thus cant eat and will die eventually */
static void	*lone_philo_routine(t_philo *philo_struct)
{
	pthread_mutex_lock(&philo_struct->table->fork_locks[philo_struct->fork[0]]);
	write_status(philo_struct, false, GOT_FORK_1);
	philo_sleep(philo_struct->table, philo_struct->table->time_to_die);
	write_status(philo_struct, false, DIED);
	pthread_mutex_unlock(&philo_struct->table->fork_locks[philo_struct->fork[0]]);
	return (NULL);
}

/* calculates time_to_think to determine when the philo needs to eat again */
static void think_routine(t_philo *philo_struct, bool tf)
{
    time_t  time_to_think;

    pthread_mutex_lock(&philo_struct->eat_time_lock);
    time_to_think = (philo_struct->table->time_to_die - (time_in_ms() - philo_struct->last_meal) - philo_struct->table->time_to_eat) / 2;
    pthread_mutex_unlock(&philo_struct->eat_time_lock);
    if (time_to_think < 0)
        time_to_think = 0;
    if (time_to_think == 0 && tf == true)
        time_to_think = 1;
    if (time_to_think > 600)
        time_to_think = 200;
    if (tf == false)
        write_status(philo_struct, false, THINKING);
    philo_sleep(philo_struct->table, time_to_think);
}

/* eating routine in which time of last meal is
recorded at the beginning of the meal */
static void	eat_sleep_routine(t_philo *philo_struct)
{
	pthread_mutex_lock(&philo_struct->table->fork_locks[philo_struct->fork[0]]);
	write_status(philo_struct, false, GOT_FORK_1);
	pthread_mutex_lock(&philo_struct->table->fork_locks[philo_struct->fork[1]]);
	write_status(philo_struct, false, GOT_FORK_2);
	write_status(philo_struct, false, EATING);
	pthread_mutex_lock(&philo_struct->eat_time_lock);
	philo_struct->last_meal = time_in_ms();
	pthread_mutex_unlock(&philo_struct->eat_time_lock);
	philo_sleep(philo_struct->table, philo_struct->table->time_to_eat);
	if (has_simulation_stopped(philo_struct->table) == false)
	{
		pthread_mutex_lock(&philo_struct->eat_time_lock);
		philo_struct->times_ate++;
		pthread_mutex_unlock(&philo_struct->eat_time_lock);
	}
	write_status(philo_struct, false, SLEEPING);
	pthread_mutex_unlock(&philo_struct->table->fork_locks[philo_struct->fork[1]]);
	pthread_mutex_unlock(&philo_struct->table->fork_locks[philo_struct->fork[0]]);
	philo_sleep(philo_struct->table, philo_struct->table->time_to_sleep);
}

/* function for the philo-threads called via pthread_create in start_simulation;
data: is var we put in pthread_create (here: the whole *philo struct);
must be typecasted because void is merely a placeholder for any variable type;
philos with even id-number start with thinking - cause a small delay -of their 
meal time. This way uneven-id philos eat first and deadlock is prevented */
void    *philosopher(void *data)
{
    t_philo *philo_struct;

    philo_struct = (t_philo *)data;
    if (philo_struct->table->must_eat_count == 0)
        return (NULL);
    pthread_mutex_lock(&philo_struct->eat_time_lock);
    philo_struct->last_meal = philo_struct->table->start_time;
    pthread_mutex_unlock(&philo_struct->eat_time_lock);
    sim_start_delay(philo_struct->table->start_time);
    if (philo_struct->table->time_to_die == 0)
        return (NULL);
    if (philo_struct->table->nb_philos == 1)
        return (lone_philo_routine(philo_struct));
    else if (philo_struct->id % 2 == 0)
        think_routine(philo_struct, true);
    while (has_simulation_stopped(philo_struct->table) == false)
    {
        eat_sleep_routine(philo_struct);
        think_routine(philo_struct, false);
    }
    return (NULL);
}
