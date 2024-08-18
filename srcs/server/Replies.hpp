/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:18:11 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/18 16:42:23 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

// The server sends Replies 001 to 004 to a user upon successful registration.

#define RPL_WELCOME(nick, user, host) ":ft_irc 001 " nick " :Welcome to the Internet Relay Network " nick "!" user "@" host

#define RPL_YOURHOST(servername, version) ":ft_irc 002 " servername " :Your host is " servername ", running version " version

#define RPL_CREATED(date) ":ft_irc 003 :This server was created " date

#define RPL_MYINFO(servername, version, user_modes, channel_modes) ":ft_irc 004 " servername " " version " " user_modes " " channel_modes

// ERROR REPLIES

#define ERR_NOSUCHNICK(nick) ":ft_irc 401 " nick " :No such nick/channel"

#define ERR_NOSUCHSERVER(server) ":ft_irc 402 " server " :No such server"

#define ERR_NOSUCHCHANNEL(channel) ":ft_irc 403 " channel " :No such channel"

#define ERR_CANNOTSENDTOCHAN(channel) ":ft_irc 404 " channel " :Cannot send to channel"

#define ERR_TOOMANYCHANNELS(channel) ":ft_irc 405 " channel " :You have joined too many channels"

#define ERR_WASNOSUCHNICK(nick) ":ft_irc 406 " nick " :There was no such nickname"

#define ERR_TOOMANYTARGETS(target, error_code, abort_msg) ":ft_irc 407 " target " :" error_code " recipients. " abort_msg

#define ERR_NOSUCHSERVICE(service) ":ft_irc 408 " service " :No such service"

#define ERR_NOORIGIN ":ft_irc 409 :No origin specified"

#define ERR_NORECIPIENT(command) ":ft_irc 411 :No recipient given (" command ")"

#define ERR_NOTEXTTOSEND ":ft_irc 412 :No text to send"

#define ERR_NOTOPLEVEL(mask) ":ft_irc 413 " mask " :No toplevel domain specified"

#define ERR_WILDTOPLEVEL(mask) ":ft_irc 414 " mask " :Wildcard in toplevel domain"

#define ERR_BADMASK(mask) ":ft_irc 415 " mask " :Bad Server/host mask"

#define ERR_UNKNOWNCOMMAND(command) ":ft_irc 421 " command " :Unknown command"

#define ERR_NOMOTD ":ft_irc 422 :MOTD File is missing"

#define ERR_NOADMININFO(server) ":ft_irc 423 " server " :No administrative info available"

#define ERR_FILEERROR(file_op, file) ":ft_irc 424 :File error doing " file_op " on " file

#define ERR_NONICKNAMEGIVEN ":ft_irc 431 :No nickname given"

#define ERR_ERRONEUSNICKNAME(nick) ":ft_irc 432 " nick " :Erroneous nickname"

#define ERR_NICKNAMEINUSE(nick) ":ft_irc 433 " nick " :Nickname is already in use"

// 436 ERR_NICKCOLLISION "<nick> :Nickname collision KILL from <user>@<host>"
#define ERR_NICKCOLLISION(nick, user, host) ":ft_irc 436 " nick " :Nickname collision KILL from " user "@" host

// 437 ERR_UNAVAILRESOURCE "<nick/channel> :Nick/channel is temporarily unavailable"
#define ERR_UNAVAILRESOURCE(target) ":ft_irc 437 " target " :Nick/channel is temporarily unavailable"

// 441 ERR_USERNOTINCHANNEL "<nick> <channel> :They aren't on that channel"
#define ERR_USERNOTINCHANNEL(nick, channel) ":ft_irc 441 " nick " " channel " :They aren't on that channel"

// 442 ERR_NOTONCHANNEL "<channel> :You're not on that channel"
#define ERR_NOTONCHANNEL(channel) ":ft_irc 442 " channel " :You're not on that channel"

// 443 ERR_USERONCHANNEL "<user> <channel> :is already on channel"
#define ERR_USERONCHANNEL(user, channel) ":ft_irc 443 " user " " channel " :is already on channel"

// 444 ERR_NOLOGIN "<user> :User not logged in"
#define ERR_NOLOGIN(user) ":ft_irc 444 " user " :User not logged in"

// 445 ERR_SUMMONDISABLED ":SUMMON has been disabled"
#define ERR_SUMMONDISABLED() ":ft_irc 445 :SUMMON has been disabled"

// 446 ERR_USERSDISABLED ":USERS has been disabled"
#define ERR_USERSDISABLED() ":ft_irc 446 :USERS has been disabled"

// 451 ERR_NOTREGISTERED ":You have not registered"
#define ERR_NOTREGISTERED() ":ft_irc 451 :You have not registered"

// 461 ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
#define ERR_NEEDMOREPARAMS(command) ":ft_irc 461 " command " :Not enough parameters"

// 462 ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
#define ERR_ALREADYREGISTRED() ":ft_irc 462 :Unauthorized command (already registered)"

// 463 ERR_NOPERMFORHOST ":Your host isn't among the privileged"
#define ERR_NOPERMFORHOST() ":ft_irc 463 :Your host isn't among the privileged"

// 464 ERR_PASSWDMISMATCH ":Password incorrect"
#define ERR_PASSWDMISMATCH() ":ft_irc 464 :Password incorrect"

// 465 ERR_YOUREBANNEDCREEP ":You are banned from this server"
#define ERR_YOUREBANNEDCREEP() ":ft_irc 465 :You are banned from this server"

// 466 ERR_YOUWILLBEBANNED
#define ERR_YOUWILLBEBANNED() ":ft_irc 466 :You will be banned"

// 467 ERR_KEYSET "<channel> :Channel key already set"
#define ERR_KEYSET(channel) ":ft_irc 467 " channel " :Channel key already set"

// 471 ERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"
#define ERR_CHANNELISFULL(channel) ":ft_irc 471 " channel " :Cannot join channel (+l)"

// 472 ERR_UNKNOWNMODE "<char> :is unknown mode char to me for <channel>"
#define ERR_UNKNOWNMODE(char, channel) ":ft_irc 472 " char " :is unknown mode char to me for " channel

// 473 ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
#define ERR_INVITEONLYCHAN(channel) ":ft_irc 473 " channel " :Cannot join channel (+i)"

// 474 ERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)"
#define ERR_BANNEDFROMCHAN(channel) ":ft_irc 474 " channel " :Cannot join channel (+b)"

// 475 ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)"
#define ERR_BADCHANNELKEY(channel) ":ft_irc 475 " channel " :Cannot join channel (+k)"

// 476 ERR_BADCHANMASK "<channel> :Bad Channel Mask"
#define ERR_BADCHANMASK(channel) ":ft_irc 476 " channel " :Bad Channel Mask"

// 477 ERR_NOCHANMODES "<channel> :Channel doesn't support modes"
#define ERR_NOCHANMODES(channel) ":ft_irc 477 " channel " :Channel doesn't support modes"

// 478 ERR_BANLISTFULL "<channel> <char> :Channel list is full"
#define ERR_BANLISTFULL(channel, char) ":ft_irc 478 " channel " " char " :Channel list is full"

// 481 ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator"
#define ERR_NOPRIVILEGES() ":ft_irc 481 :Permission Denied- You're not an IRC operator"

// 482 ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
#define ERR_CHANOPRIVSNEEDED(channel) ":ft_irc 482 " channel " :You're not channel operator"

// 483 ERR_CANTKILLSERVER ":You can't kill a server!"
#define ERR_CANTKILLSERVER() ":ft_irc 483 :You can't kill a server!"

// 484 ERR_RESTRICTED ":Your connection is restricted!"
#define ERR_RESTRICTED() ":ft_irc 484 :Your connection is restricted!"

// 485 ERR_UNIQOPPRIVSNEEDED ":You're not the original channel operator"
#define ERR_UNIQOPPRIVSNEEDED() ":ft_irc 485 :You're not the original channel operator"

// 491 ERR_NOOPERHOST ":No O-lines for your host"
#define ERR_NOOPERHOST() ":ft_irc 491 :No O-lines for your host"

// 501 ERR_UMODEUNKNOWNFLAG ":Unknown MODE flag"
#define ERR_UMODEUNKNOWNFLAG() ":ft_irc 501 :Unknown MODE flag"

// 502 ERR_USERSDONTMATCH ":Cannot change mode for other users"
#define ERR_USERSDONTMATCH() ":ft_irc 502 :Cannot change mode for other users"



#endif