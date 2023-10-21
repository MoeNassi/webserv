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

void	webserv::readFile( st_ file) {
	std::fstream	read(file);
	// if (!read.is_open())
	st_				input;
	size_t			found_it;

	while (std::getline(read, input)) {
		found_it = input.find("=");
		if (found_it != std::string::npos)
			cont_[input.substr(0, found_it - 1)] = input.substr(found_it + 1);
	}
	for (std::map < st_, st_ >::iterator it; it != cont_.end(); it++)
		std::cout << "first -> : " << it->first << "second -> : " << it->second << std::endl;
}

int main( int ac, char **av ) {
	if (ac != 2)
		return std::cout << BOLD_RED << "Usage : \n" << DEF << BOLD_GREEN << "\tAdd the config file\n" << DEF << std::endl, 0;
	webserv	inst_;
	char buffer[1024];
	int	client_socket, server_socket;
	struct	sockaddr_in	server_, client_;
	inst_.readFile(av[1]);
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_.sin_family = AF_INET;
	server_.sin_port = htons(8080);
	server_.sin_addr.s_addr = INADDR_ANY;
	bind(server_socket, (struct sockaddr *)&server_, sizeof(server_));
	listen(server_socket, 5);
	std::cout << BOLD_GREEN << "Server is Opened on port 8080 ...." << DEF << std::endl;
	for (int i = 0; i < 10 ; i++) {
		socklen_t length = sizeof(client_);
		client_socket = accept(server_socket, (struct sockaddr *)&client_, &length);
		recv(client_socket, buffer, 1024, 0);
		std::cout << "Received a message from  client : " << buffer << std::endl;
		const char * response = "Hello Client, You are connected with the server";
		send(client_socket, response, static_cast<std::string>(response).length(), 0);
	}
	close(server_socket);
	close(client_socket);
}