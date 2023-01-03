/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:48:19 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/03 16:38:16 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* int gettimeofday(struct timeval *tv, struct timezone *tz);
timeval tv: is a struct containing time variables;
struct timeval {
time_t      tv_sec;     //seconds
suseconds_t tv_usec;    //microseconds
}
gettimeofday computes the current time and saves it in tv;
to get the current time in ms tv_sec * 1000 and tv_usec / 1000;
1 sec = 1000 millisec; 1 millisec = 1000 microsec 
The tz argument should normally be specified as NULL.
gettimeofday() return 0 for success, or -1 for failure */
time_t  time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* causes a short delay at start of each threads execution,
based on the individual start_time in start_simulation */
void    sim_start_delay(time_t start_time)
{
    while (time_in_ms() < start_time)
        continue ;
}
