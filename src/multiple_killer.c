/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_killer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:38:31 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/03 22:21:44 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* checks if the simulation is at the end by checking the
sim_stop_flag in table, which can be modiefied only by grimreaper */
bool    has_simulation_stopped(t_table *table)
{
    bool    tf;

    tf = false;
    pthread_mutex_lock(&table->sim_stop_lock);
    if (table->sim_stop == true)
        tf = true;
    pthread_mutex_unlock(&table->sim_stop_lock);
    return (tf);
}

/* function to set the stop_flag for the simulation;
becomes true if an end condition has been met */
static void	set_sim_stop_flag(t_table *table, bool tf)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = tf;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

/* checks if the philo should die by comparing if the
time since philos last meal is greater than the time_to_die;
in case of death the stop_sim_flag is set to true */
static bool	kill_philo(t_philo *philo_struct)
{
	time_t	time;

	time = time_in_ms();
	if ((time - philo_struct->last_meal) >= philo_struct->table->time_to_die)
	{
		set_sim_stop_flag(philo_struct->table, true);
		write_status(philo_struct, true, DIED);
		pthread_mutex_unlock(&philo_struct->eat_time_lock);
		return (true);
	}
	return (false);
}

/* checks for each philosopher if he is dead and/or checks if all
philos ate sufficient times; 
if one of these conditions is met, true is returned otherwise false */
static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->eat_time_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->must_eat_count != -1)
			if (table->philos[i]->times_ate \
				< (unsigned int)table->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->eat_time_lock);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(table, true);
		return (true);
	}
	return (false);
}

/* is called in start_simulation (main.c) via pthread_create;
data is table which is put in pthread_create function;
continously checks for validity of an end condition and sets
the flag accordingly via end_condition_reached;
*table new declared cause it is not passed through function */
void	*multiple_killer(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	set_sim_stop_flag(table, false);
	sim_start_delay(table->start_time);
	while (true)
	{
		if (end_condition_reached(table) == true)
		{
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
