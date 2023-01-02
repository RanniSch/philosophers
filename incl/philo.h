/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:32:48 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/02 12:35:41 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* Macros */

# define MAX_PHILOS 250
# define STR_MAX_PHILOS "250"

# define STR_PROG_NAME "philo:"
# define STR_INPUT_FORMAT "input format: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT "invalid input: Type in digits \
between 0 and 2147483647\n"
# define STR_ERR_INPUT_PHILO "%s invalid input: \
First digit needs to be between 1 and %s philosophers\n"
# define STR_ERR_MALLOC "%s error: Memory allocation failed\n"
# define STR_ERR_MUTEX "%s error: Mutex not created\n"

/* Structs */
typedef struct s_philo	t_philo;

/* stores input values; time_t defined in gettimeofday; 
pthread_t is thread variable stores info about the thread;
pthread_mutex_t is data type of pthread_mutex_init function (is pointer) */
typedef struct s_table
{
	//time_t				start_time;
	unsigned int		nb_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					must_eat_count;
	bool				sim_stop;
	pthread_mutex_t		*fork_locks;
	pthread_mutex_t		sim_stop_lock;
	pthread_mutex_t		do_lock;
	t_philo				**philos;

}						t_table;

/* struct for for a philosopher;
id = identification;
pthread_mutex_t is data type of pthread_mutex_init function and a pointer */
typedef struct s_philo
{
	t_table				*table;
	pthread_mutex_t		eat_time_lock;
	unsigned int		id;
	unsigned int		fork[2];
	unsigned int		times_ate;
}						t_philo;

/* static functions are not declared in the headerfile because
a static function is only visible in the file where its declared in
and thus can only be used there */
void					destroy_mutexes(t_table *table);
void					*free_table(t_table *table);
int						input_error_msg(char *str, char *infos, int exit_no);
void					*error_null(char *str, char *infos, t_table *table);
int						error_failure(char *str, char *details, t_table *table);
int						ft_atoi(const char *str);
bool					is_valid_input(int argc, char **argv);
t_table					*init_process(int argc, char **argv);
int						main(int argc, char **argv);

#endif