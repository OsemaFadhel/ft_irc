/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:11:54 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/05 12:29:48 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <map>
#include <string>
#include "../client/Client.hpp"
#include "../server/Server.hpp"

class Client;

class Channel
{
	private:
		std::map < std::string, Client* , std::string > _clients; //thinking name, client, operator or not
		std::string _name;
		std::string _topic;
		std::string _mode;
		std::string _password;
		int _limit;
	public:
		Channel();
		~Channel();

		//getters and setters
		std::string getName() const;
		std::string getTopic() const;
		std::string getMode() const;
		std::string getPassword() const;
		int getLimit() const;
		void setName(const std::string& name);
		void setTopic(const std::string& topic);
		void setMode(const std::string& mode);
		void setPassword(const std::string& password);
		void setLimit(int limit);

		/*something like this. each client has a channel
		so from the client class, we can call the channel class
		since vector: *it.kick(client); somtehing like this
		*/
		//channel commands for channel operators
		void kick(Client* client); // kick client
		void invite(Client* client); // invite client
		void topic(Client* client, const std::string& topic); // change or view topic
		void mode(Client* client, const std::string& mode); // change mode
		/*mode
		 i: Set/remove Invite-only channel
		 t: Set/remove the restrictions of the TOPIC command to channel operators
		 k: Set/remove the channel key (password)
		 o: Give/take channel operator privilege
		 l: Set/remove the user limit to channel
		*/
};

#endif
