/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboivin <mboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:07:21 by mboivin           #+#    #+#             */
/*   Updated: 2021/11/01 19:07:35 by mboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>
#include "ft_irc.hpp"

int	main(int argc, char** argv)
{
	try
	{
		ft_irc::CLIParser	CLI_parser(argc, argv);

		try
		{
			ft_irc::Server	server(CLI_parser);

			server.run();
		}
		catch (std::runtime_error &e)
		{
			std::cerr << e.what() << std::endl;
			return (EXIT_FAILURE);
		}
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		displayUsage(argv[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
