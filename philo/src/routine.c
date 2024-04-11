/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:15:02 by rmidou            #+#    #+#             */
/*   Updated: 2024/04/10 15:53:24 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	printf("%lu %d %s\n", get_time2(philo->main), philo->id, "has taken a fork");
	pthread_mutex_lock(philo->fork2);
	printf("%lu %d %s\n", get_time2(philo->main), philo->id, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
	printf("%lu %d %s\n", get_time2(philo->main), philo->id, "is sleeping");
	ft_usleep(philo->main->tts);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->leat = get_time2(philo->main);
	printf("%lu %d %s\n", philo->leat, philo->id, "is eating");
	philo->eat++;
	ft_usleep(philo->main->tte);
	drop_forks(philo);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->tte);
	while (!philo->main->dead && !philo->main->eat)
	{
		eat(philo);
		printf("%lu %d %s\n", get_time2(philo->main), philo->id, "is thinking");
	}
	return ((void *)0);
}

void	check_death(t_main *main)
{
	int		i;

	while (!main->eat)
	{
		i = 0;
		while (i < main->nb_philo && !main->dead)
		{
			if (get_time2(main) - main->philos[i].leat
				>= (uint64_t)main->philos[i].ttd)
			{
				printf("%lu %d %s\n", get_time() - main->time_of_start,
					i + 1, "died");
				main->dead = 1;
			}
			i++;
		}
		if (main->dead)
			break ;
		i = 0;
		while (main->philos[i].eat > main->nbr_philo_eat)
			i++;
		if (i == main->nb_philo)
			main->eat = 1;
	}
}
