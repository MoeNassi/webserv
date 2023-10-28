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
void	webserv::setMethod_( std::string Method_ ) {
	this->Method_ = Method_;
}
void	webserv::setURI( std::string URI ) {
	this->UniformRI = URI;
}
void	webserv::setVersion( std::string version ) {
	this->HTTPVersion_ = version;
}
void	webserv::setBody( std::string body ) {
	this->body = body;
}
std::string	&webserv::getVersion( void ) {
	return HTTPVersion_;
}
std::string	&webserv::getURI( void ) {
	return UniformRI;
}
std::string	&webserv::getMethod_( void ) {
	return Method_;
}
std::string	&webserv::getBody( void ) {
	return body;
}
std::string	&webserv::getBuffer( void ) {
	return buffer;
}
void	webserv::CheckForBody( st_ request_ ) {
	std::vector < std::pair < st_, st_ > >::iterator it_ = headers.begin();
	for (; it_ != headers.end(); it_++) {
		if ((!it_->first.compare("Content-Length") && atoi(it_->second.c_str()) > 0)
			|| (!it_->first.compare("Transfer-Encoding") && !it_->second.compare("chunked"))) { //if it exist and method is post and its value is diff to "chunked" : 501 Not Implimented
				request_.erase(0, request_.find("\r\n") + 2);
				setBody(request_);
		}
	if (it_ == headers.end() && !getMethod_().compare("POST"))
		perror("400 Bad Request\n");
	}
}
void	webserv::FillHeaders_( st_ request_ ) {
	for (int i = 0; request_.substr(0, 2) != "\r\n" && !request_.empty(); i++) {
		size_t found_it = request_.find(": ");
		if (found_it != std::string::npos) {
			st_ key = request_.substr(0, found_it);
			request_.erase(0, found_it + 2);
			size_t found_end = request_.find("\r\n");
			if (found_end == std::string::npos || key.empty())
				break ;
			st_ value = request_.substr(0, found_end);
			request_.erase(0, found_end + 2);
			headers.push_back(std::make_pair(key, value));
		}
		else
			perror("MetaData Error\n");
	}
	CheckForBody( request_ );
}
bool	checkURI( st_ URI ) { // check for body size if its smaller than the one in config file
	if (URI.length() > 2048)
		perror("414 Request-URI Too Long\n");
	st_ Allowed = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	for (int i = 0; URI[i]; i++) {
		int check = 0;
		for (; Allowed[check]; check++)
			if (Allowed[check] == URI[i])
				break ;
		if (Allowed[check] == '\0')
			perror("400 Bad Request\n");
	}
	return true;
}
void webserv::HTTPRequest( void ) {
	size_t delete_ = 0;
	st_	request = this->getBuffer();
	for (int i = 0; request[i]; i++) {
		delete_ = request.find(" ");
		if (delete_ != std::string::npos && Method_.empty())
			this->setMethod_(request.substr(0, delete_));
		else if (delete_ != std::string::npos && UniformRI.empty()) {
			checkURI( request.substr(0, delete_) );
			this->setURI(request.substr(0, delete_));
		}
		else
			break ;
		request.erase(0, delete_ + 1);
	}
	delete_ = request.find("\r\n");
	if (delete_ != std::string::npos)
		setVersion(request.substr(0, delete_));
	request.erase(0, delete_ + 2);
	FillHeaders_(request);
}
void	webserv::printVec(void) {
	std::cout << "Method : " << getMethod_() << " URI : " << getURI() << " V : " << getVersion() << " Body : " << getBody() << std::endl;
	for (std::vector < std::pair < st_, st_ > >::iterator it_ = headers.begin(); it_ != headers.end(); it_++)
		std::cout << it_->first << " ->> " << it_->second << std::endl;
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
	// std::cout << BOLD_RED << "Request : \n" << DEF << buffer << std::endl;
	const char *response = "Received";
	send(_socket_cl, response, static_cast<std::string>(response).length(), 0);
	setBuffer(static_cast<std::string>(buffer));
	close(_socket_cl);
	close(_socket_ser);
}

