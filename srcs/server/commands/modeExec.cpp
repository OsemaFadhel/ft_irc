/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeExec.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:22:56 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/23 20:01:35 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"

// void		iMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
// void		tMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
// void		kMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
// void		oMode(std::string mode, std::string hypotheticalArgs, int clientSocket);
// void		lMode(std::string mode, std::string hypotheticalArgs, int clientSocket);

//only the operators can invite after this is setted up
//change this to accept a client so you can compare it and tell if it is an operator too
void	Channel::iMode(std::string mode, std::string hypotheticalArgs, int clientSocket)
{

	if (!hypotheticalArgs.empty())
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	if (mode[0] == '+')
	{
		// if ()
		this->_mode['i'] = true;
	}
	else
	{
		this->_mode['i'] = false;
	}
}
