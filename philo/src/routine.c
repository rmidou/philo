/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:15:02 by rmidou            #+#    #+#             */
/*   Updated: 2024/04/14 14:23:33 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	take_forks(t_philo *philo)
{
	if (!philo->main->dead && !philo->main->eat)
	{
		pthread_mutex_lock(philo->fork1);
		if (philo->main->dead || philo->main->eat)
			return (1);
		printf("%lu %d %s\n", get_time2(philo->main), philo->id,
			"has taken a fork");
		pthread_mutex_lock(philo->fork2);
		if (philo->main->dead || philo->main->eat)
			return (1);
		printf("%lu %d %s\n", get_time2(philo->main), philo->id,
			"has taken a fork");
		return (0);
	}
	return (1);
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
	if (take_forks(philo))
		return ;
	philo->eatt = 1;
	philo->leat = get_time2(philo->main) + philo->tte;
	printf("%lu %d %s\n", philo->leat - philo->tte, philo->id, "is eating");
	philo->eat++;
	ft_usleep(philo->main->tte);
	philo->eatt = 0;
	if (!philo->main->dead && !philo->main->eat)
		drop_forks(philo);
	else
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
	}
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
		if (!philo->main->dead && !philo->main->eat)
			printf("%lu %d %s\n", get_time2(philo->main), philo->id,
				"is thinking");
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
				>= (uint64_t)main->philos[i].ttd && main->philos[i].eatt == 0)
			{
				main->dead = 1;
				printf("%lu %d %s\n", get_time() - main->time_of_start,
					i + 1, "died");
				break ;
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
