/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:18:11 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/21 12:24:48 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "Server.hpp"
#include <cstdarg>

std::string constructMessage(const std::string& format, ...);

// The server sends Replies 001 to 004 to a user upon successful registration.
// ":ft_irc :Welcome to the Internet Relay Network <nick>!<user>@<host>"
#define RPL_WELCOME ":ft_irc 001 %s :Welcome to %s Network, %s\r\n" //size of string = 44

#define RPL_YOURHOST ":ft_irc 002 %s :Your host is %s, running version %s\r\n" // Static size: 54

#define RPL_CREATED ":ft_irc 003 %s :This server was created %s\r\n" // Static size: 45

#define RPL_MYINFO ":ft_irc 004 %s %s %s %s %s\r\n" // Static size: 29

#define RPL_NAMREPLY ":ft_irc 353 %s = %s :%s\r\n" // Static size: 29

#define RPL_NOTOPIC ":ft_irc 331 %s :No topic is set\r\n" // Static size: 34 channel

#define RPL_TOPIC ":ft_irc 332 %s :%s\r\n" // Static size: 21 channel, topic

//ERROR REPLIES

#define ERR_INPUTTOOLONG ":ft_irc 401 %s :Input line too long\r\n" // Static size: 33

#define ERR_NOSUCHNICK ":ft_irc 401 %s :No such nick/channel\r\n" // Static size: 31

#define ERR_NOSUCHSERVER ":ft_irc 402 %s :No such server\r\n" // Static size: 26

#define ERR_NOSUCHCHANNEL ":ft_irc 403 %s :No such channel\r\n" // Static size: 34

#define ERR_CANNOTSENDTOCHAN ":ft_irc 404 %s :Cannot send to channel\r\n" // Static size: 33

#define ERR_TOOMANYCHANNELS ":ft_irc 405 %s :You have joined too many channels\r\n" // Static size: 43

#define ERR_WASNOSUCHNICK ":ft_irc 406 %s :There was no such nickname\r\n" // Static size: 34

#define ERR_TOOMANYTARGETS ":ft_irc 407 %s :%s recipients. %s\r\n" // Static size: 34

#define ERR_NOSUCHSERVICE ":ft_irc 408 %s :No such service\r\n" // Static size: 31

#define ERR_NOORIGIN ":ft_irc 409 :No origin specified\r\n" // Static size: 30

#define ERR_NORECIPIENT ":ft_irc 411 :No recipient given (%s)\r\n" // Static size: 37

#define ERR_NOTEXTTOSEND ":ft_irc 412 :No text to send\r\n" // Static size: 26

#define ERR_NOTOPLEVEL ":ft_irc 413 %s :No toplevel domain specified\r\n" // Static size: 35

#define ERR_WILDTOPLEVEL ":ft_irc 414 %s :Wildcard in toplevel domain\r\n" // Static size: 39

#define ERR_BADMASK ":ft_irc 415 %s :Bad Server/host mask\r\n" // Static size: 29

#define ERR_UNKNOWNCOMMAND ":ft_irc 421 %s :Unknown command\r\n" // Static size: 30

#define ERR_NOMOTD ":ft_irc 422 :MOTD File is missing\r\n" // Static size: 29

#define ERR_NOADMININFO ":ft_irc 423 %s :No administrative info available\r\n" // Static size: 43

#define ERR_FILEERROR ":ft_irc 424 :File error doing %s on %s\r\n" // Static size: 35

#define ERR_NONICKNAMEGIVEN ":ft_irc 431 :No nickname given\r\n" // Static size: 33

#define ERR_ERRONEUSNICKNAME ":ft_irc 432 %s :Erroneous nickname\r\n" // Static size: 37

#define ERR_NICKNAMEINUSE ":ft_irc 433 %s :Nickname is already in use\r\n" // Static size: 45

#define ERR_NICKCOLLISION ":ft_irc 436 %s :Nickname collision KILL from %s@%s\r\n" // Static size: 45

#define ERR_UNAVAILRESOURCE ":ft_irc 437 %s :Nick/channel is temporarily unavailable\r\n" // Static size: 45

#define ERR_USERNOTINCHANNEL ":ft_irc 441 %s %s :They aren't on that channel\r\n" // Static size: 39

#define ERR_NOTONCHANNEL ":ft_irc 442 %s :You're not on that channel\r\n" // Static size: 33

#define ERR_USERONCHANNEL ":ft_irc 443 %s %s :is already on channel\r\n" // Static size: 43

#define ERR_NOLOGIN ":ft_irc 444 %s :User not logged in\r\n" // Static size: 28

#define ERR_SUMMONDISABLED ":ft_irc 445 :SUMMON has been disabled\r\n" // Static size: 33

#define ERR_USERSDISABLED ":ft_irc 446 :USERS has been disabled\r\n" // Static size: 29

#define ERR_NOTREGISTERED ":ft_irc 451 :You have not registered\r\n" // Static size: 39

#define ERR_NEEDMOREPARAMS ":ft_irc 461 %s :Not enough parameters\r\n" // Static size: 41

#define ERR_ALREADYREGISTRED ":ft_irc 462 :Unauthorized command (already registered)\r\n" // Static size: 57

#define ERR_NOPERMFORHOST ":ft_irc 463 :Your host isn't among the privileged\r\n" // Static size: 53

#define ERR_PASSWDMISMATCH ":ft_irc 464 :Password incorrect\r\n" // Static size: 34

#define ERR_YOUREBANNEDCREEP ":ft_irc 465 :You are banned from this server\r\n" // Static size: 35

#define ERR_YOUWILLBEBANNED ":ft_irc 466 :You will be banned\r\n" // Static size: 29

#define ERR_KEYSET ":ft_irc 467 %s :Channel key already set\r\n" // Static size: 35

#define ERR_CHANNELISFULL ":ft_irc 471 %s :Cannot join channel (+l)\r\n" // Static size: 44

#define ERR_UNKNOWNMODE ":ft_irc 472 %s :is unknown mode char to me for %s\r\n" // Static size: 53

#define ERR_INVITEONLYCHAN ":ft_irc 473 %s :Cannot join channel (+i)\r\n" // Static size: 33

#define ERR_BANNEDFROMCHAN ":ft_irc 474 %s :Cannot join channel (+b)\r\n" // Static size: 34

#define ERR_BADCHANNELKEY ":ft_irc 475 %s :Cannot join channel (+k)\r\n" // Static size: 43

#define ERR_BADCHANMASK ":ft_irc 476 %s :Bad Channel Mask\r\n" // Static size: 43

#define ERR_NOCHANMODES ":ft_irc 477 %s :Channel doesn't support modes\r\n" // Static size: 36

#define ERR_BANLISTFULL ":ft_irc 478 %s %s :Channel list is full\r\n" // Static size: 35

#define ERR_NOPRIVILEGES ":ft_irc 481 :Permission Denied- You're not an IRC operator\r\n" // Static size: 48

#define ERR_CHANOPRIVSNEEDED ":ft_irc 482 %s :You're not channel operator\r\n" // Static size: 35

#define ERR_CANTKILLSERVER ":ft_irc 483 :You can't kill a server!\r\n" // Static size: 31

#define ERR_RESTRICTED ":ft_irc 484 :Your connection is restricted!\r\n" // Static size: 34

#define ERR_UNIQOPPRIVSNEEDED ":ft_irc 485 :You're not the original channel operator\r\n" // Static size: 43

#define ERR_NOOPERHOST ":ft_irc 491 :No O-lines for your host\r\n" // Static size: 29

#define ERR_UMODEUNKNOWNFLAG ":ft_irc 501 :Unknown MODE flag\r\n" // Static size: 29

#define ERR_USERSDONTMATCH ":ft_irc 502 :Cannot change mode for other users\r\n" // Static size: 36

#endif

//for more information look at the rfc to know more about the arguments
//it needs to be used in the constructMessage function
