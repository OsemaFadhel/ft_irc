/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:37:21 by ofadhel           #+#    #+#             */
/*   Updated: 2024/10/07 16:58:39 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Replies.hpp"

std::string constructMessage(const std::string& format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[512];  // Adjust size as necessary
	vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
	va_end(args);

	std::cout << "Constructed message: " << buffer << std::endl;
	return std::string(buffer);
}
