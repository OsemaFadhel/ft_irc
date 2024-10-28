/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:38:08 by lnicoter          #+#    #+#             */
/*   Updated: 2024/10/28 10:47:05 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/Server.hpp"


//substr e find per spostare il puntatore alla prima virgola
//new error: 2 channels that are going to be inserted with
//a space after the first , for example <channel1>, <channel2> the space messes up all the logic
//unfortunately is not possible to resolve it properly for now
//there's something that I'm missing... but i tried anything to make it work
//with a lot of casistics but with the keys is Impossible to handle it well without making problems
//on the handling of the vector of channels
std::vector<std::string>	Server::channelParser(std::string args)
{
	std::vector < std::string > numOfChannels;
	std::string onlyChannels = args.substr(0, args.find_first_of(" "));
	// std::vector < std::string > keys;

	size_t	i = 0;
	//loop for channels
	while (i != std::string::npos)
	{
		size_t pos = onlyChannels.find_first_of(",", i);
		std::string temp;
		if (pos != std::string::npos)
		{
			temp = onlyChannels.substr(i, pos - i);
			// std::cout << "temp1: " << temp << std::endl;
			i = pos + 1;
		}
		else
		{
			temp = onlyChannels.substr(i);
			// std::cout << "temp2: " << temp << std::endl;
			i = std::string::npos;
		}
		//trimming the string to remove the spaces and avoiding a sudden segfault
		temp.erase(0, temp.find_first_not_of(" "));
		temp.erase(temp.find_last_not_of(" ") + 1);

		// Controlla se la stringa è valida (non vuota e non contiene spazi)
		if (!temp.empty() && temp.find(' ') == std::string::npos)
		{
			numOfChannels.push_back(temp);
			// std::cout << "Channel added: " << temp << std::endl;
		}
		else
		{
			std::cout << "Invalid channel ignored: " << temp << std::endl;
		}
	}
	return (numOfChannels);
}

//for now it seems that the keyparser saves one of the keys two times
//before passing to the next one

std::vector< std::string >	Server::keyParser(std::string args)
{
	std::vector < std::string > keys;
	size_t	i = (args.find_first_of(" ")) + 1;
	std::string temp;

	//loop for keys
	while (i != std::string::npos)
	{
		size_t pos = args.find_first_of(",", i);
		if (pos != std::string::npos)
		{
			temp = args.substr(i, pos - i);
			std::cout << "temp1: " << temp << std::endl;
			// keys.push_back(temp);
			i = pos + 1;
		}
		else
		{
			temp = args.substr(i);
			std::cout << "temp2: " << temp << std::endl;
			i = std::string::npos;
			// keys.push_back(temp);
			// break;
		}

		temp.erase(0, temp.find_first_not_of(" "));
		temp.erase(temp.find_last_not_of(" ") + 1);

		// Controlla se la stringa è valida (non vuota e non contiene spazi)
		if (!temp.empty() && temp.find(' ') == std::string::npos)
		{
			keys.push_back(temp);
			std::cout << "Key added: " << temp << std::endl;
		}
		else
		{
			std::cout << "Invalid Key ignored: " << temp << std::endl;
		}
	}

	for (size_t i = 0; i < keys.size(); i++)
		std::cout << "keys: " << keys[i] << std::endl;
	return (keys);
}

//there's something else
//channel created but the messages are not well translated

void	Server::listOfUsersMsg(std::string channelName, Client &newUsr)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == channelName)
		{
			std::string serverMessage = ":" + SERVERNAME + " 353 " + SERVERNAME + " = " + channelName + " :";
			for (size_t j = 0; j < _channels[i].getUsrData().size(); j++)
				serverMessage += _channels[i].getUsrData()[j].first.getNickname() + " ";
			serverMessage += "\r\n";
			send(newUsr.getFd(), serverMessage.c_str(), serverMessage.length(), 0);

			std::string endOfListMessage = ":" + SERVERNAME + " 366 " + channelName + " :End of NAMES list\r\n";
			send(newUsr.getFd(), endOfListMessage.c_str(), endOfListMessage.size(), 0);

			std::string joinMessage = ":" + newUsr.getNickname() + "!127.0.0.1" + " JOIN :" + channelName + "\r\n";
			for (size_t j = 0; j < _channels[i].getUsrData().size(); j++)
				send(_channels[i].getUsrData()[j].first.getFd(), joinMessage.c_str(), joinMessage.size(), 0);

		}
	}
}

//the user is not joining the channel
//allora ho capito il messaggio ha questo tipo di formattazione
//:ft_irc <usr> :
//però... ft_irc sbaglia perché sarebbe una cosa globale e pare che
//facendo :ft_irc <usr> per il join non funzioni correttamente
void	Server::joinCreateChanMsg(Client clientToInsert, std::string channelName)
{
	std::cout<<GREEN<<"joinCreateChanMsg"<<RESET<<std::endl;
	std::cout<<"channel to create/join: "<<channelName<<std::endl;
	std::string serverMessage = ":" + clientToInsert.getNickname() + " JOIN " + channelName + "\r\n";
	send(clientToInsert.getFd(), serverMessage.c_str(), serverMessage.size(), 0);
	serverMessage = ":" + SERVERNAME + " " + clientToInsert.getNickname() + " JOIN " + channelName + "\r\n";
	send(clientToInsert.getFd(), serverMessage.c_str(), serverMessage.size(), 0);
	listOfUsersMsg(channelName, clientToInsert);
}

//function for checkChannelList
//to make it better i will do another function that stays in the server class
//if i won't be lazy i will change the implementation
void	checkExistence(bool& channelExists, size_t& channelIndex, std::vector<Channel>& _channels, std::vector<std::string>& numberOfChannels, int i)
{
	for (size_t j = 0; j < _channels.size(); j++)
	{
		if (_channels[j].getName() == numberOfChannels[i])
		{
			channelExists = true;
			channelIndex = j;
			break; // Esci dal ciclo, abbiamo trovato il canale
		}
	}
}


//un po' confusionario se mai trovassi soluzioni migliori lo ritoccherò
void	Server::channelHandling(std::vector<Channel>& _channels, size_t& channelIndex, Client clientToInsert, std::vector< std::string > keys)
{
	std::cout<<"limit and size "<<_channels[channelIndex].getLimit()<<" "<<_channels[channelIndex].getUsrData().size()<<std::endl;
	if (_channels[channelIndex].getModeValue('l') && _channels[channelIndex].getLimit() <= (int)_channels[channelIndex].getUsrData().size())
	{
		std::string errMessage = constructMessage(ERR_CHANNELISFULL, _channels[channelIndex].getName().c_str());
		send(clientToInsert.getFd(), errMessage.c_str(), errMessage.size(), 0);
		return ;
	}
	if (!_channels[channelIndex].getModeValue('i') || _channels[channelIndex].isInviterOp())
	{
		if (_channels[channelIndex].isInChannel(clientToInsert))
		{
			std::string errMessage = constructMessage(ERR_NICKNAMEINUSE, clientToInsert.getNickname().c_str());
			send(clientToInsert.getFd(), errMessage.c_str(), errMessage.size(), 0);
		}
		else
		{
			//check della password solo se l'utente non è stato invitato per ora è una casistica
			//che mi serve in questo caso specifico volendo potrei controllare le modalità separatamente
			if ((!_channels[channelIndex].getPassword().empty() && keys.size() > 0 && keys.size() >= channelIndex) || _channels[channelIndex].isInviterOp())
			{
				if (_channels[channelIndex].getPassword() == keys[channelIndex])
				{
					_channels[channelIndex].addClient(clientToInsert);
					joinCreateChanMsg(clientToInsert, _channels[channelIndex].getName());
				}
				else
				{
					std::string errMessage = constructMessage(ERR_BADCHANNELKEY, _channels[channelIndex].getName().c_str());
					send(clientToInsert.getFd(), errMessage.c_str(), errMessage.size(), 0);
				}
			}
			else if (_channels[channelIndex].getPassword().empty())
			{
				_channels[channelIndex].addClient(clientToInsert);
				std::cout << GREEN << "Client aggiunto correttamente al canale"
						<< RESET << std::endl;
				joinCreateChanMsg(clientToInsert, _channels[channelIndex].getName());
			}
			else
			{
				std::string errMessage = constructMessage(ERR_BADCHANNELKEY, _channels[channelIndex].getName().c_str());
				send(clientToInsert.getFd(), errMessage.c_str(), errMessage.size(), 0);
			}
		}
		_channels[channelIndex].setWhoInvited(-1);
	}
	else
	{
		std::string errMessage = constructMessage(ERR_INVITEONLYCHAN, _channels[channelIndex].getName().c_str());
		send(clientToInsert.getFd(), errMessage.c_str(), errMessage.size(), 0);
	}
}

void Server::checkChannelExist(std::vector<std::string> numberOfChannels, Client clientToInsert, std::vector< std::string > keys)
{
	for (size_t i = 0; i < numberOfChannels.size(); i++)
	{
		bool channelExists = false;
		size_t channelIndex = 0;

		// Controlla se il canale esiste già
		checkExistence(channelExists, channelIndex, _channels, numberOfChannels, i);

		if (channelExists)
			channelHandling(_channels, channelIndex, clientToInsert, keys);
		else
		{
			// Se il canale non esiste, creane uno nuovo
			Channel newChannel = Channel(clientToInsert, numberOfChannels[i]);
			if (!newChannel.getName().empty())
			{
				_channels.push_back(newChannel);
				std::cout << GREEN << "Nuovo canale creato e client aggiunto: "
							<< newChannel.getName()
							<< RESET << std::endl;
				joinCreateChanMsg(clientToInsert, newChannel.getName());
			}
		}
	}
}



/*


** Troubleshooting
** The parsing of the keys is on point and it works very well
** I should do the same checks for the keyparser
** Following another irc it seems the keys are ignored if the channel doesn't exist and it's
** the first time

** I must create a channel section in the irc client reference
** the answers are hidden in the RFC


   If a JOIN is successful, the user receives a JOIN message as
   confirmation and is then sent the channel's topic (using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.

! the modes defines if there's a password or not

*/

/*
I need a checker for the channel and see if it has the key up
if it is i need to put it in a map where every time someone joins is checked
*/

void	Server::Join(std::string args, int	clientSocket)
{
	Client	*clientToInsert = getClient(clientSocket);
	std::vector < Channel > _tmpChannels;
	std::vector < std::string > numOfChannels;
	std::vector < std::string > keys;


	numOfChannels = channelParser(args);
	//the keys works only if the channel already exists
	//the check of the keys must be put in the checkChannelExist function
	if (args.find_first_of(" ") != std::string::npos)
	{
		args = args.erase(0, args.find_first_of(" ") + 1);
		keys = keyParser(args);
	}
	else
		keys.clear();

	// for (size_t k = 0; k < keys.size(); k++)
	// 	std::cout << "keys: " << keys[k] << std::endl;
	std::cout<<"channel parsed "<<numOfChannels.size()<<std::endl;
	checkChannelExist(numOfChannels, *clientToInsert, keys);
}
