/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboivin <mboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:48:18 by mboivin           #+#    #+#             */
/*   Updated: 2021/10/08 17:02:26 by mboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <string>
#include "Client.hpp"
#include "Message.hpp"

namespace ft_irc
{
	// default constructor
	Message::Message(Client& sender)
	: _sender(sender), _serv_hostname("irc.42.fr"),
	  _response(), _command(), _params(), _recipients()
	{
	}

	// server hostname constructor
	Message::Message(Client& sender, const std::string& serv_hostname)
	: _sender(sender), _serv_hostname(serv_hostname),
	  _response(), _command(), _params(), _recipients()
	{
	}

	// copy constructor
	Message::Message(const Message& other)
	: _sender(other._sender), _serv_hostname(other._serv_hostname),
	  _response(other._response), _command(other._command), _params(other._params),
	  _recipients(other._recipients)
	{
	}

	// assignment operator
	Message&	Message::operator=(const Message& other)
	{
		if (this != &other)
		{
			_sender = other.getSender();
			_serv_hostname = other.getServHostname();
			_response = other.getResponse();
			_command = other.getCommand();
			_params = other.getParams();
			_recipients = other.getRecipients();
		}
		return (*this);
	}

	// destructor
	Message::~Message() {}

	// getters
	Client&	Message::getSender() const
	{
		return (this->_sender);
	}

	std::string	Message::getServHostname() const
	{
		return (this->_serv_hostname);
	}

	std::string	Message::getResponse() const
	{
		return (this->_response);
	}

	std::string	Message::getCommand() const
	{
		return (this->_command);
	}

	const std::list<std::string>&	Message::getParams() const
	{
		return (this->_params);
	}

	const std::list<Client*>&	Message::getRecipients() const
	{
		return (this->_recipients);
	}

	// setters

	void	Message::setSender(const Client& sender)
	{
		this->_sender = sender;
	}

	void	Message::setServHostname(const std::string& serv_hostname)
	{
		this->_serv_hostname = serv_hostname;
	}

	void	Message::setResponse(const std::string& response)
	{
		this->_response = response;
	}

	void	Message::setCommand(const std::string& command)
	{
		this->_command = command;
	}

	void	Message::setParam(const std::string& param)
	{
		if (!param.empty() && (this->_params.size() < MSG_MAX_PARAMS))
			this->_params.push_back(param);
	}

	void	Message::setRecipients(const std::list<Client*>& recipients)
	{
		this->_recipients = recipients;
	}

	void	Message::setRecipient(Client& recipient)
	{
		this->_recipients.push_back(&recipient);
	}

	void	Message::addRecipients(const std::list<Client*>& recipients)
	{
		this->_recipients.insert(this->_recipients.end(), recipients.begin(), recipients.end());
	}

	// end message with CRLF
	void	Message::appendSeparator()
	{
		this->_response.append("\r\n");
	}

	// debug
	void	Message::displayMessage() const
	{
		std::cout << "command:  " << getCommand() << '\n'
				  << "params:   ";

		for (std::list<std::string>::const_iterator it = this->_params.begin();
			 it != this->_params.end();
			 ++it)
		{
			std::cout << "'" << *it << "' ";
		}
		std::cout << "\nresponse: " << this->_response << std::endl;
	}
} // !namespace ft_irc
