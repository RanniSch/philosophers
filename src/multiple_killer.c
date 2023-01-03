/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_killer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:38:31 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/03 16:49:22 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void    multiple_killer(void *data)
{
    return (NULL);
}