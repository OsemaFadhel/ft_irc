/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:18:11 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/24 22:03:37 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "Server.hpp"

// The server sends Replies 001 to 004 to a user upon successful registration.

#define RPL_WELCOME(nick, user, host) ":ft_irc 001 " nick " :Welcome to the Internet Relay Network " nick "!" user "@" host "\r\n"

#define RPL_YOURHOST(nick) ":ft_irc 002 " nick " :Your host is " SERVERNAME ", running version " VERSION "\r\n"

#define RPL_CREATED(nick, date) ":ft_irc 003 " nick ":This server was created " date "\r\n"

#define RPL_MYINFO(nick, user_modes, channel_modes) ":ft_irc 004 " nick " " SERVERNAME " " VERSION " " user_modes " " channel_modes "\r\n"

// ERROR REPLIES

#define ERR_NOSUCHNICK(nick) ":ft_irc 401 " nick " :No such nick/channel\r\n"

#define ERR_NOSUCHSERVER(server) ":ft_irc 402 " server " :No such server\r\n"

#define ERR_NOSUCHCHANNEL(channel) ":ft_irc 403 " channel " :No such channel\r\n"

#define ERR_CANNOTSENDTOCHAN(channel) ":ft_irc 404 " channel " :Cannot send to channel\r\n"

#define ERR_TOOMANYCHANNELS(channel) ":ft_irc 405 " channel " :You have joined too many channels\r\n"

#define ERR_WASNOSUCHNICK(nick) ":ft_irc 406 " nick " :There was no such nickname\r\n"

#define ERR_TOOMANYTARGETS(target, error_code, abort_msg) ":ft_irc 407 " target " :" error_code " recipients. " abort_msg "\r\n"

#define ERR_NOSUCHSERVICE(service) ":ft_irc 408 " service " :No such service\r\n"

#define ERR_NOORIGIN ":ft_irc 409 :No origin specified\r\n"

#define ERR_NORECIPIENT(command) ":ft_irc 411 :No recipient given (" command ")\r\n"

#define ERR_NOTEXTTOSEND ":ft_irc 412 :No text to send\r\n"

#define ERR_NOTOPLEVEL(mask) ":ft_irc 413 " mask " :No toplevel domain specified\r\n"

#define ERR_WILDTOPLEVEL(mask) ":ft_irc 414 " mask " :Wildcard in toplevel domain\r\n"

#define ERR_BADMASK(mask) ":ft_irc 415 " mask " :Bad Server/host mask\r\n"

#define ERR_UNKNOWNCOMMAND(command) ":ft_irc 421 " command " :Unknown command\r\n"

#define ERR_NOMOTD ":ft_irc 422 :MOTD File is missing\r\n"

#define ERR_NOADMININFO(server) ":ft_irc 423 " server " :No administrative info available\r\n"

#define ERR_FILEERROR(file_op, file) ":ft_irc 424 :File error doing " file_op " on " file "\r\n"

#define ERR_NONICKNAMEGIVEN ":ft_irc 431 :No nickname given\r\n"

#define ERR_ERRONEUSNICKNAME(nick) ":ft_irc 432 " nick " :Erroneous nickname\r\n"

#define ERR_NICKNAMEINUSE(nick) ":ft_irc 433 " nick " :Nickname is already in use\r\n"

// 436 ERR_NICKCOLLISION "<nick> :Nickname collision KILL from <user>@<host>"
#define ERR_NICKCOLLISION(nick, user, host) ":ft_irc 436 " nick " :Nickname collision KILL from " user "@" host "\r\n"

// 437 ERR_UNAVAILRESOURCE "<nick/channel> :Nick/channel is temporarily unavailable"
#define ERR_UNAVAILRESOURCE(target) ":ft_irc 437 " target " :Nick/channel is temporarily unavailable\r\n"

// 441 ERR_USERNOTINCHANNEL "<nick> <channel> :They aren't on that channel"
#define ERR_USERNOTINCHANNEL(nick, channel) ":ft_irc 441 " nick " " channel " :They aren't on that channel\r\n"

// 442 ERR_NOTONCHANNEL "<channel> :You're not on that channel"
#define ERR_NOTONCHANNEL(channel) ":ft_irc 442 " channel " :You're not on that channel\r\n"

// 443 ERR_USERONCHANNEL "<user> <channel> :is already on channel"
#define ERR_USERONCHANNEL(user, channel) ":ft_irc 443 " user " " channel " :is already on channel\r\n"

// 444 ERR_NOLOGIN "<user> :User not logged in"
#define ERR_NOLOGIN(user) ":ft_irc 444 " user " :User not logged in\r\n"

// 445 ERR_SUMMONDISABLED ":SUMMON has been disabled"
#define ERR_SUMMONDISABLED() ":ft_irc 445 :SUMMON has been disabled\r\n"

// 446 ERR_USERSDISABLED ":USERS has been disabled"
#define ERR_USERSDISABLED() ":ft_irc 446 :USERS has been disabled\r\n"

// 451 ERR_NOTREGISTERED ":You have not registered"
#define ERR_NOTREGISTERED() ":ft_irc 451 :You have not registered\r\n"

// 461 ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
#define ERR_NEEDMOREPARAMS(command) ":ft_irc 461 " command " :Not enough parameters\r\n"

// 462 ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
#define ERR_ALREADYREGISTRED() ":ft_irc 462 :Unauthorized command (already registered)\r\n"

// 463 ERR_NOPERMFORHOST ":Your host isn't among the privileged"
#define ERR_NOPERMFORHOST() ":ft_irc 463 :Your host isn't among the privileged\r\n"

// 464 ERR_PASSWDMISMATCH ":Password incorrect"
#define ERR_PASSWDMISMATCH() ":ft_irc 464 :Password incorrect\r\n"

// 465 ERR_YOUREBANNEDCREEP ":You are banned from this server"
#define ERR_YOUREBANNEDCREEP() ":ft_irc 465 :You are banned from this server\r\n"

// 466 ERR_YOUWILLBEBANNED
#define ERR_YOUWILLBEBANNED() ":ft_irc 466 :You will be banned\r\n"

// 467 ERR_KEYSET "<channel> :Channel key already set"
#define ERR_KEYSET(channel) ":ft_irc 467 " channel " :Channel key already set\r\n"

// 471 ERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"
#define ERR_CHANNELISFULL(channel) ":ft_irc 471 " channel " :Cannot join channel (+l)\r\n"

// 472 ERR_UNKNOWNMODE "<char> :is unknown mode char to me for <channel>"
#define ERR_UNKNOWNMODE(char, channel) ":ft_irc 472 " char " :is unknown mode char to me for " channel "\r\n"

// 473 ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
#define ERR_INVITEONLYCHAN(channel) ":ft_irc 473 " channel " :Cannot join channel (+i)\r\n"

// 474 ERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)"
#define ERR_BANNEDFROMCHAN(channel) ":ft_irc 474 " channel " :Cannot join channel (+b)\r\n"

// 475 ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)"
#define ERR_BADCHANNELKEY(channel) ":ft_irc 475 " channel " :Cannot join channel (+k)\r\n"

// 476 ERR_BADCHANMASK "<channel> :Bad Channel Mask"
#define ERR_BADCHANMASK(channel) ":ft_irc 476 " channel " :Bad Channel Mask\r\n"

// 477 ERR_NOCHANMODES "<channel> :Channel doesn't support modes"
#define ERR_NOCHANMODES(channel) ":ft_irc 477 " channel " :Channel doesn't support modes\r\n"

// 478 ERR_BANLISTFULL "<channel> <char> :Channel list is full"
#define ERR_BANLISTFULL(channel, char) ":ft_irc 478 " channel " " char " :Channel list is full\r\n"

// 481 ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator"
#define ERR_NOPRIVILEGES() ":ft_irc 481 :Permission Denied- You're not an IRC operator\r\n"

// 482 ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
#define ERR_CHANOPRIVSNEEDED(channel) ":ft_irc 482 " channel " :You're not channel operator\r\n"

// 483 ERR_CANTKILLSERVER ":You can't kill a server!"
#define ERR_CANTKILLSERVER() ":ft_irc 483 :You can't kill a server!\r\n"

// 484 ERR_RESTRICTED ":Your connection is restricted!"
#define ERR_RESTRICTED() ":ft_irc 484 :Your connection is restricted!\r\n"

// 485 ERR_UNIQOPPRIVSNEEDED ":You're not the original channel operator"
#define ERR_UNIQOPPRIVSNEEDED() ":ft_irc 485 :You're not the original channel operator\r\n"

// 491 ERR_NOOPERHOST ":No O-lines for your host"
#define ERR_NOOPERHOST() ":ft_irc 491 :No O-lines for your host\r\n"

// 501 ERR_UMODEUNKNOWNFLAG ":Unknown MODE flag"
#define ERR_UMODEUNKNOWNFLAG() ":ft_irc 501 :Unknown MODE flag\r\n"

// 502 ERR_USERSDONTMATCH ":Cannot change mode for other users"
#define ERR_USERSDONTMATCH() ":ft_irc 502 :Cannot change mode for other users\r\n"


#endif
