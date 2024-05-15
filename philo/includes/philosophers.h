/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:03:37 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/15 14:17:17 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				ttd;
	int				tte;
	int				tts;
	uint64_t		leat;
	int				eat;
	int				eatt;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	pthread_t		thread;
	struct s_main	*main;
	int				nbr_philo_eat;
}	t_philo;

typedef struct s_main
{
	int				nb_philo;
	int				dead;
	int				ttd;
	int				tte;
	int				tts;
	int				nbr_philo_eat;
	int				eat;
	int				eatt;
	t_philo			*philos;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	uint64_t		time_of_start;
}	t_main;

/*		main.c	*/
uint64_t	get_time(void);
uint64_t	get_time2(t_main *main);

/*		utils.c	*/
size_t		ft_atoi(char *str);
int			ft_usleep(uint64_t time);
int			ft_isdigit(char *c);
void		ft_bzero(void *s, size_t n);
void		brindf(t_main *main, int i, char *todo);

/*		routine.c	*/
void		*routine(void *philo_pointer);
void		*routine(void *philo_pointer);
void		check_death(t_main *main);

/*		init.c		*/
int			args(char **av, t_main *philo);
void		init(t_main *main);
void		init_philo(t_main *main);
void		init_philo1(int ttd);

#endif
