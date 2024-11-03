/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeExec.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:22:56 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/28 10:44:32 by ofadhel          ###   ########.fr       */
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
	(void) hypotheticalArgs;
	Client	*isOp = getClientByfd(clientSocket);

	if (!isOp)
	{
		std::cout<<"the user does not exist "<<std::endl;
		return ;
	}
	if (!isOperator(*isOp))
	{
		std::string errMessage = constructMessage(ERR_CHANOPRIVSNEEDED, isOp->getNickname().c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	// if (hypotheticalArgs.empty())
	// {
	// 	std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
	// 	send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
	// 	return ;
	// }
	//i need to tell the others that the channel is invite only
	if (mode[0] == '+' && this->_mode['i'] != true)
	{
		this->_mode['i'] = true;
		std::string modeMessage = constructMessage(RPL_CHANNELMODEIS, this->_name.c_str(), "+i", "");
		send(clientSocket, modeMessage.c_str(), modeMessage.size(), 0);
		broadcastMessage(modeMessage, clientSocket);
	}
	else if (mode[0] == '-' && this->_mode['i'] != false)
	{
		this->_mode['i'] = false;
		std::string modeMessage = constructMessage(RPL_CHANNELMODEIS, this->_name.c_str(), "-i", "");
		broadcastMessage(modeMessage, clientSocket);
	}
	else
	{
		std::string	errMessage = constructMessage(ERR_KEYSET, this->_name.c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
	}
}
//put the check for the keys
void	Channel::kMode(std::string mode, std::string hypotheticalArgs, int clientSocket)
{
	Client	*isOp = getClientByfd(clientSocket);

	if (!isOperator(*isOp))
	{
		std::string errMessage = constructMessage(ERR_CHANOPRIVSNEEDED, isOp->getNickname().c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	if (hypotheticalArgs.empty())
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	//i need to tell the others that the channel is invite only
	if (mode[0] == '+' && this->_mode['k'] != true)
	{
		this->_mode['k'] = true;
		std::string modeMessage = constructMessage(RPL_CHANNELMODEIS, this->_name.c_str(), "+k", hypotheticalArgs.c_str());
		this->_password = hypotheticalArgs;
		send(clientSocket, modeMessage.c_str(), modeMessage.size(), 0);
		broadcastMessage(modeMessage, clientSocket);
	}
	else if (mode[0] == '-' && this->_mode['k'] != false)
	{
		this->_mode['k'] = false;
		std::string modeMessage = constructMessage(RPL_CHANNELMODEIS, this->_name.c_str(), "+k", hypotheticalArgs.c_str());
		send(clientSocket, modeMessage.c_str(), modeMessage.size(), 0);
		this->_password = "";
		broadcastMessage(modeMessage, clientSocket);
	}
	else
	{
		std::string	errMessage = constructMessage(ERR_KEYSET, this->_name.c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
	}
}


void	Channel::oMode(std::string mode, std::string hypotheticalArgs, int clientSocket)
{
	Client	*isOp = getClientByfd(clientSocket);
	std::vector< std::pair < Client, int > >::iterator it;

	std::cout << "hypotheticalArgs " << hypotheticalArgs << std::endl;
	if (!isOperator(*isOp))
	{
		std::string errMessage = constructMessage(ERR_CHANOPRIVSNEEDED, isOp->getNickname().c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	if (hypotheticalArgs.empty())
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	if (mode[0] == '+' && mode[1] == 'o')
	{
		for (it = _usrData.begin(); it != _usrData.end(); it++)
		{
			if (it->first.getNickname() == hypotheticalArgs)
			{
				it->second = 1;
				std::string modeMessage = constructMessage(RPL_CHANNELMODEIS, this->_name.c_str(), "+o", hypotheticalArgs.c_str());
				return ;
			}
		}
	}
	else if (mode[0] == '-' && mode[1] == 'o')
	{
		for (it = _usrData.begin(); it != _usrData.end(); it++)
		{
			if (it->first.getNickname() == hypotheticalArgs)
			{
				it->second = 0;
				std::string modeMessage = constructMessage(RPL_CHANNELMODEIS, this->_name.c_str(), "-o", hypotheticalArgs.c_str());
				return ;
			}
		}
	}
	//case where the hypotheticalArgs is not in the channel
	std::string errMessage = constructMessage(ERR_NOSUCHNICK, hypotheticalArgs.c_str(), hypotheticalArgs.c_str());
	send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
}

void	Channel::tMode(std::string mode, std::string hypotheticalArgs, int clientSocket)
{
	Client	*isOp = getClientByfd(clientSocket);

	if (!isOperator(*isOp))
	{
		std::string errMessage = constructMessage(ERR_CHANOPRIVSNEEDED, isOp->getNickname().c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	if (hypotheticalArgs.empty())
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	//i need to tell the others that the channel is invite only
	if (mode[0] == '+' && this->_mode['t'] != true)
	{
		this->_mode['t'] = true;
	}
	else if (mode[0] == '-' && this->_mode['r'] != false)
	{
		this->_mode['t'] = false;
	}
	else
	{
		std::string	errMessage = constructMessage(ERR_KEYSET, this->_name.c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
	}
}

void	Channel::lMode(std::string mode, std::string hypotheticalArgs, int clientSocket)
{
	Client	*isOp = getClientByfd(clientSocket);

	if (!isOperator(*isOp))
	{
		std::string errMessage = constructMessage(ERR_CHANOPRIVSNEEDED, isOp->getNickname().c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	if (hypotheticalArgs.empty())
	{
		std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	//i need to tell the others that the channel is invite only
	if (mode[0] == '+' && this->_mode['l'] != true)
	{
		std::stringstream ss(hypotheticalArgs);
		ss >> this->_limit;
		std::cout<<"limit "<<this->_limit<<std::endl;
		if (this->_limit <= 0)
		{
			std::string	errMessage = constructMessage(ERR_NEEDMOREPARAMS, "MODE");
			send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
			return ;
		}
		this->_mode['l'] = true;
	}
	else if (mode[0] == '-' && this->_mode['l'] != false)
	{
		this->_mode['l'] = false;
		_limit = 0;
	}
	else
	{
		std::string	errMessage = constructMessage(ERR_KEYSET, this->_name.c_str());
		send(clientSocket, errMessage.c_str(), errMessage.size(), 0);
	}
}
