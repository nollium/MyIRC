/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CLIParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboivin <mboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:34:20 by root              #+#    #+#             */
/*   Updated: 2021/11/28 16:54:12 by mboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <cstring>
#include <string>
#include "ft_irc.hpp"
#include "CLIParser.hpp"

namespace ft_irc
{
	/* Default constructor */
	CLIParser::CLIParser()
	: _argc(0), _argv(), _bind_address(""), _port(""), _password("")
	{
		this->_argv = nullptr;
	}

	/* Arguments constructor */
	CLIParser::CLIParser(int argc, char** argv)
	{
		if (argc == 2 && std::strcmp(argv[1], "--help") == 0)
		{
			displayUsage(argv[0]);
			exit(EXIT_SUCCESS);
		}
		if (argc < 4)
			throw std::runtime_error("Not enough arguments");
		if (argc > 4)
			throw std::runtime_error("Too many arguments");
		parse(argv[1], argv[2], argv[3]);
	}

	/* Copy constructor */
	CLIParser::CLIParser(const CLIParser& other)
	: _argc(other._argc),
	  _argv(other._argv),
	  _bind_address(other._bind_address),
	  _port(other._port),
	  _password(other._password)
	{
		this->_argv = nullptr;
	}

	/* Copy assignment operator */
	CLIParser&	CLIParser::operator=(const CLIParser& other)
	{
		if (this != &other)
		{
			this->_argc = other._argc;
			this->_argv = other._argv;
			this->_bind_address = other._bind_address;
			this->_port = other._port;
			this->_password = other._password;
		}
		return (*this);
	}

	/* Destructor */
	CLIParser::~CLIParser()
	{
	}

	/* Getters ****************************************************************** */

	std::string	CLIParser::getBindAddress() const
	{
		return (this->_bind_address);
	}

	std::string	CLIParser::getPort() const
	{
		return (this->_port);
	}

	std::string	CLIParser::getPassword() const
	{
		return (this->_password);
	}

	/* Parsing ************************************************************** */

	/* Parses the command line arguments */
	void	CLIParser::parse(const char* bind_address, const char* port, const char* password)
	{
		this->_bind_address = bind_address;
		this->_port = port;
		this->_password = password;
	}
}
