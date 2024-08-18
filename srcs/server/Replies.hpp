/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:18:11 by ofadhel           #+#    #+#             */
/*   Updated: 2024/08/18 14:34:50 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP


// The server sends Replies 001 to 004 to a user upon successful registration.

# define RPL_WELCOME "Welcome to the Internet Relay Network %s!%s@%s"
# define RPL_YOURHOST "Your host is %s, running version %s"
# define RPL_CREATED "This server was created %s"
# define RPL_MYINFO "%s %s %s %s" // servername version user_modes chan_modes

// client registration replies

# define ERR_NEEDMOREPARAMS "%s :Not enough parameters"
# 
