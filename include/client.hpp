/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:55:22 by root              #+#    #+#             */
/*   Updated: 2021/10/19 14:30:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CLIENT_HPP
# define IRC_CLIENT_HPP

# define MAX_COMMAND_SIZE 512
# define CRLF "\n"
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include <unistd.h>
# include <string>
# include <sys/time.h>
# include <stdexcept>
# include <poll.h>
# include <iostream>

namespace ft_irc
{
	class IRCClient
	{
	private:
		std::string			nick;
		std::string			realname;
		std::string			username;
		std::string			mode;
		std::string			joined_channels;
		std::string			password;
		struct sockaddr_in	address;			//IPv4 address		
		socklen_t 			address_size;		//IPv4 address size
		std::string			address_str;		//IPv4 address as string
		struct timeval		timeout;			//timeout for select()
		int					socket_fd;			//socket file descriptor
		bool				connected;		//is the client connected to the server?
		std::string			in_buffer;			//buffer for incoming data
		std::string			out_buffer;		//buffer for outgoing data
		size_t				max_cmd_length;	//max length of a command
		bool				alive;
	public:
							IRCClient(struct sockaddr_in address=(struct sockaddr_in){0,0,{0},{0}},
		std::string nick="", std::string realname="", std::string username="", std::string password="");
							IRCClient(const IRCClient &other);
		IRCClient 			&operator=(const IRCClient &other);
							~IRCClient();
		//IRCClient ge/tters
		std::string			getNick() const;
		std::string			getRealName() const;
		std::string			getJoinedChannels() const;
		std::string			getPassword() const;
		std::string			getIpAddressStr() const;
		int 				getSocketFd() const;
		struct sockaddr_in	&getAddress();
		socklen_t 			&getAddressSize();
		//get username
		std::string			getUsername() const;
		//set
		void				setUsername(std::string username);
		//IRCClient se/tters
		void				setNick(std::string nick);
		void				setRealName(std::string realname);
		void				setJoinedChannels(std::string joined_channels);
		void				setPassword(std::string password);
		void				setSocketFd(int socket_fd);
		bool				isRegistered() const;
		bool				isConnected() const;
		void				setConnected(bool connected);
		int					awaitConnection(int socket_fd);
		bool				hasNewEvents();
		bool				hasUnprocessedCommands();
		std::string			popUnprocessedCommand();
		int					updateInBuffer();
		int					updateOutBuffer();
		//add response to the output buffer
		void				sendCommand(std::string response);
		bool				isAlive() const;
		void				setAlive(bool alive);
		//operator==
		friend bool			operator==(const IRCClient &lhs, const IRCClient &rhs);
	};
}

#endif // !IRC_CLIENT
