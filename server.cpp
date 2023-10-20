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

int main() {
	char buffer[1024];
	int	client_socket, server_socket;
	struct	sockaddr_in	server_, client_;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_.sin_family = AF_INET;
	server_.sin_port = htons(8080);
	server_.sin_addr.s_addr = INADDR_ANY;
	bind(server_socket, (struct sockaddr *)&server_, sizeof(server_));
	listen(server_socket, 5);
	std::cout << "Server is Opened on port 8080 ...." << std::endl;
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