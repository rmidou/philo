/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:35:10 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/07 10:34:45 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	clear_main(t_main *main)
{
	if (main->forks)
		free(main->forks);
	if (main->philos)
		free(main->philos);
}

void	ft_exit(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nb_philo)
		pthread_mutex_destroy(&main->forks[i]);
	clear_main(main);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	get_time2(t_main *main)
{
	return (get_time() - main->time_of_start);
}

int	main(int ac, char **av)
{
	t_main		main;

	if (ac < 5)
	{
		printf("philosophers: wrong arguments: <number_of_philosophers>"
			" <time_to_die> <time_to_eat> <time_to_sleep>"
			"[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	ft_bzero(&main, sizeof(t_main));
	if (ac < 4)
		return (0);
	if (args(av, &main) == 0)
		return (0);
	main.time_of_start = get_time();
	init(&main);
	init_philo(&main);
	ft_exit(&main);
	return (0);
}
