/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:15:02 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/13 14:14:26 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(&philo->main->lock);
	if (philo->main->eat)
	{
		pthread_mutex_unlock(&philo->main->lock);
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->lock);
	printf("%lu %d %s\n", get_time2(philo->main), philo->id,
		"has taken a fork");
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(&philo->main->lock);
	if (philo->main->eat)
	{
		pthread_mutex_unlock(&philo->main->lock);
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->lock);
	printf("%lu %d %s\n", get_time2(philo->main), philo->id,
		"has taken a fork");
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
	printf("%lu %d %s\n", get_time2(philo->main), philo->id, "is sleeping");
	ft_usleep(philo->main->tts);
}

void	eat2(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->lock);
	if (!philo->main->dead && !philo->main->eat)
	{
		pthread_mutex_unlock(&philo->main->lock);
		drop_forks(philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->main->lock);
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
	}
}

void	eat(t_philo *philo)
{
	int	nb_eat;

	nb_eat = 0;
	if (take_forks(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->leat = get_time2(philo->main);
	printf("%lu %d %s\n", philo->leat, philo->id, "is eating");
	philo->eat++;
	if (philo->eat >= philo->nbr_philo_eat)
		nb_eat = 1;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->tte);
	if (nb_eat)
	{
		pthread_mutex_lock(&philo->main->lock);
		philo->main->eatt++;
		pthread_mutex_unlock(&philo->main->lock);
	}
	eat2(philo);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	int		end;

	philo = (t_philo *)philo_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(philo->tte);
	end = 0;
	while (1)
	{
		eat(philo);
		pthread_mutex_lock(&philo->lock);
		if (philo->eat >= philo->nbr_philo_eat)
			end = 1;
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->main->lock);
		if (!philo->main->dead && !philo->main->eat)
			printf("%lu %d %s\n", get_time2(philo->main), philo->id,
				"is thinking");
		else
			end = 1;
		pthread_mutex_unlock(&philo->main->lock);
		if (end == 1)
			break ;
	}
	return ((void *)0);
}
