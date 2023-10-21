/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnassi <mnassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 00:50:02 by mnassi            #+#    #+#             */
/*   Updated: 2023/10/21 00:50:02 by mnassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int main(int ac, char **av) {
	if (ac != 2)
		return std::cout << BOLD_RED << "Usage : \n" << "\t Add an argument and Send a Message" << std::endl, 0;
	int client_socket;
	char buffer[1024];
	struct sockaddr_in server_;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_.sin_family = AF_INET;
	server_.sin_port = htons(8080);
	server_.sin_addr.s_addr = INADDR_ANY;
	strcpy(buffer, "");
	connect(client_socket, (struct sockaddr *)&server_, sizeof(server_));
	std::string	response = "Hello Server";
	strcpy(buffer, response.c_str());
	send(client_socket, av[1], strlen(av[1]), 0);
	recv(client_socket, buffer, 1024, 0);
	std::cout << "Server Said : " << buffer << std::endl;  
	close(client_socket);
}