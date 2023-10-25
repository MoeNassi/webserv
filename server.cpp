/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnassi <mnassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:28:03 by mnassi            #+#    #+#             */
/*   Updated: 2023/10/20 23:28:03 by mnassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

webserv::webserv(void) {
	
}
webserv::~webserv(void) {

}
void	webserv::setBuffer( std::string	buffer ) {
	this->buffer = buffer;
}
void webserv::request( void ) {
	std::map < st_, st_ >::iterator it_ = cont_.begin();
	std::cout << "--->" << static_cast<int>(buffer[buffer.length()- 2]) << std::endl;
	while (it_ != cont_.end())
		cont_.insert(std::pair < st_, st_ >());
}
std::string	webserv::getBuffer( void ) {
	return buffer;
}
void	webserv::set_up( void ) { 
	char	buffer[1024];
	int	_socket_cl, _socket_ser;
	const char *port = "8080";
	struct sockaddr_in server_, client_;
	_socket_ser = socket(AF_INET, SOCK_STREAM, 0);
	server_.sin_family = AF_INET;
	server_.sin_port = htons(atoi(port));
	server_.sin_addr.s_addr = INADDR_ANY;
	bind(_socket_ser, (struct sockaddr *)&server_, sizeof(server_));
	listen(_socket_ser, 5);
	std::cout << BOLD_GREEN << "Server is listenning at Port " << port << " ->" << DEF << std::endl;
	socklen_t length = sizeof(client_);
	_socket_cl = accept(_socket_ser, (struct sockaddr *)&client_, &length);
	recv(_socket_cl, buffer, 1024, 0);
	std::cout << BOLD_RED << "Request : \n" << DEF << buffer << std::endl;
	const char *response = "Received";
	send(_socket_cl, response, static_cast<std::string>(response).length(), 0);
	setBuffer(static_cast<std::string>(buffer));
	close(_socket_cl);
	close(_socket_ser);
}

