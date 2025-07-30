/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:54 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/30 14:45:48 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"




int	main(int ac, char **av)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (ac == 6 || ac == 5)
	{
		if (!check_parameter(ac, av, param))
			return (0);
		initialize_all_variables(param, ac, av);
		create_threads(param);
	}
}
