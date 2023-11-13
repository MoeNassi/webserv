/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnassi <mnassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:26:57 by mnassi            #+#    #+#             */
/*   Updated: 2023/10/20 23:26:57 by mnassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define BOLD_BLACK "\033[1;30m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_PURPLE "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"
#define DEF "\033[0m"

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <map>
#include <vector>

#define st_ std::string

class webserv {
	private :
		st_	Method_;
		st_	UniformRI;
		st_	HTTPVersion_;
		st_	buffer;
		st_	body;
		std::vector < std::pair < st_, st_ > > headers;
	public :
		webserv( void );
		void	setMethod_( std::string Method_ );
		void	setBuffer( std::string buffer );
		void	setURI( std::string URI );
		void	setVersion( std::string version );
		void	setBody( std::string body );
		std::string	&getBody( void );
		std::string	&getVersion( void );
		std::string	&getURI( void );
		std::string	&getBuffer( void );
		std::string	&getMethod_( void );
		void	printVec(void);
		void	set_up( void );
		void	HTTPRequest( void );
		void	FillHeaders_( st_ request_ );
		int	CheckForBody( st_ request_ );
		~webserv( void );
};

bool	checkURI( st_ URI );

#endif