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
#include <map>

#define st_ std::string
# define STACK_MAX 8000000

class webserv {
	private :
		std::multimap < st_, st_ > cont_;
		std::string	buffer;
	public :
		webserv( void );
		void	setBuffer( std::string buffer );
		std::string	getBuffer( void );
		void	set_up( void );
		void	request( void );
		~webserv( void );
};

#endif