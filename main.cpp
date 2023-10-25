/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnassi <mnassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:15:36 by mnassi            #+#    #+#             */
/*   Updated: 2023/10/25 18:53:00 by mnassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int main( int ac, char **av ) {
	if (ac != 2)
		return std::cout << BOLD_RED << "Usage : \n" << DEF << BOLD_GREEN << "\tAdd the config file\n" << DEF << std::endl, 0;
	(void)av;
	webserv	init_;
	init_.set_up();
	init_.request();
}