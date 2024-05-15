/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:18:21 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/15 16:09:54 by rmidou           ###   ########.fr       */
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
	brindf(philo->main, philo->id, "has taken a fork");
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
	brindf(philo->main, philo->id, "has taken a fork");
	return (0);
}

int	take_forks2(t_philo *philo)
{
	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(&philo->main->lock);
	if (philo->main->eat)
	{
		pthread_mutex_unlock(&philo->main->lock);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->lock);
	brindf(philo->main, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->fork1);
	pthread_mutex_lock(&philo->main->lock);
	if (philo->main->eat)
	{
		pthread_mutex_unlock(&philo->main->lock);
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->lock);
	brindf(philo->main, philo->id, "has taken a fork");
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
	brindf(philo->main, philo->id, "is sleeping");
	ft_usleep(philo->main->tts);
}

int	forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (take_forks(philo))
			return (1);
	}
	else
	{
		if (take_forks2(philo))
			return (1);
	}
	return (0);
}
