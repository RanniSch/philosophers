/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:56:25 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/03 16:43:51 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
    pthread_mutex_lock(&philo_struct->meal_time_lock);
    philo_struct->last_meal = philo_struct->table->start_time;
    pthread_mutex_unlock(&philo_struct->meal_time_lock);
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