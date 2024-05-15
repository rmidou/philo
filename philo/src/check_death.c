/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:14:12 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/15 14:23:15 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_death3(t_main *main, int i)
{
	pthread_mutex_unlock(&main->lock);
	brindf(main, i + 1, "died");
	pthread_mutex_lock(&main->lock);
	main->dead = 1;
	pthread_mutex_unlock(&main->lock);
}

int	check_death2(t_main *main)
{
	pthread_mutex_lock(&main->lock);
	if (main->dead || main->eatt == main->nb_philo)
	{
		main->eat = 1;
		pthread_mutex_unlock(&main->lock);
		return (1);
	}
	pthread_mutex_unlock(&main->lock);
	return (0);
}

void	check_death(t_main *main)
{
	int			i;
	uint64_t	leat;
	uint64_t	ttd;

	while (1)
	{
		i = 0;
		while (i < main->nb_philo && !main->dead)
		{
			pthread_mutex_lock(&main->philos[i].lock);
			leat = main->philos[i].leat;
			ttd = main->philos[i].ttd;
			pthread_mutex_unlock(&main->philos[i].lock);
			pthread_mutex_lock(&main->lock);
			if (get_time2(main) - leat >= ttd)
			{
				check_death3(main, i);
				return ;
			}
			pthread_mutex_unlock(&main->lock);
			i++;
		}
		if (check_death2(main))
			return ;
	}
}

void	brindf(t_main *main, int i, char *todo)
{
	pthread_mutex_lock(&main->lock);
	if (!main->dead && !main->eat)
		printf("%lu %d %s\n", get_time2(main), i,
			todo);
	pthread_mutex_unlock(&main->lock);
}