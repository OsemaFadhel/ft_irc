# ft_irc

Create your own IRC server in C++, fully compatible with an official client.


<h2 align="center"> Description </h2>


<h3>Run Function</h3>

```cpp

void Server::run()
{
	createSocket();

	fd_set readfds;
	int maxfds = _serverSocket;

	std::cout << BOLD << CYAN << "IRC SERVER UP! WAITING FOR CLIENTS" << RESET << std::endl;
	startLoop(readfds, maxfds);
}

```

- createSocket: Sets up the server socket.
- fd_set: Initializes the set of file descriptors to be monitored for activity.
- startLoop: Enters a loop to handle incoming client connections and monitor file descriptor activity.

<h3>Create Socket Function</h3>

```cpp

void Server::createSocket()
{
	_serverSocket = socket(AF_INET6, SOCK_STREAM, 0);
	if (_serverSocket == -1)
		throw std::runtime_error("Failed to create the socket");

	int opt = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Failed to set socket options");

	std::memset(&_serverAddr, 0, sizeof(_serverAddr));
	_serverAddr.sin6_family = AF_INET6;
	_serverAddr.sin6_addr = in6addr_any;
	_serverAddr.sin6_port = htons(_port);

	if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Failed to set socket to non-blocking");

	if (bind(_serverSocket, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) == -1)
		throw std::runtime_error("Failed to bind the socket");

	if (listen(_serverSocket, 50) == -1)
		throw std::runtime_error("Failed to listen for connections");
}

```

- socket: Creates a TCP socket using the IPv6 protocol family.
- setsockopt: Configures the socket to allow reuse of the address (SO_REUSEADDR).
- memset: Initializes the server address structure (_serverAddr).
- htons: Converts the port number from host to network byte order.
- fcntl: Sets the socket to non-blocking mode.
- bind: Binds the socket to the specified address and port.
- listen: Puts the socket into a listening state for incoming connections.


<h3>Start Loop Function</h3>

```cpp

void Server::startLoop(fd_set& readfds, int& maxfds)
{
	while (1)
	{
		setMaxfds(maxfds, readfds);

		int selectfd = select(maxfds + 1, &readfds, NULL, NULL, NULL);

		if (selectfd == -1)
			throw std::runtime_error("Failed to select the socket");
		else if (selectfd == 0)
			std::cout << "Timeout expired before any file descriptors became ready" << std::endl;
		else
		{
			if (FD_ISSET(_serverSocket, &readfds) && acceptClient(&selectfd) == 1)
				continue;

			checkClientActivity(readfds);
		}
	}
}

```
- select: Monitors file descriptors for readability.
- FD_ISSET: Checks if the server socket or a client socket is ready for reading.
- accept: Accepts a new client connection if a request is detected on the server socket.


<h3>Set Maxfds Function</h3>

```cpp

void Server::setMaxfds(int &maxfds, fd_set &readfds)
{
	FD_ZERO(&readfds);
	FD_SET(_serverSocket, &readfds);

	for (size_t i = 0; i < _newfds.size(); ++i)
	{
		FD_SET(this->_newfds[i].id, &readfds);
		if (_newfds[i].id > maxfds)
			maxfds = _newfds[i].id;
	}
}

```

- FD_ZERO: Clears the set of file descriptors.
- FD_SET: Adds the server and client sockets to the set for monitoring.
- maxfds: Updates the maximum file descriptor number to handle in select.



# sources for nikotera

https://miro.com/app/board/uXjVMFuYfyA=/ </br>

[Beej what's a socket](https://beej.us/guide/bgnet/html/split-wide/what-is-a-socket.html#what-is-a-sockethttps://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf) </br>

[UNIVERSITY CHICAGO Basic irc](https://chi.cs.uchicago.edu/chirc/irc.html) </br>

[BASIC  Client and server connection using sockets in C++.](https://stackoverflow.com/questions/3509011/socket-programming-in-c) </br>

[Man Socket](https://www.linuxhowtos.org/manpages/2/socket.htm) </br>

[Man TCP](https://www.linuxhowtos.org/manpages/7/tcp.htm) </br>

[Handle multiple clients](https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/) </br>

[ADD info on sockets](https://stackoverflow.com/questions/52755987/working-out-how-many-clients-can-connect-to-some-tcp-server-code-i-am-using) </br>

[Client-Server Background](https://beej.us/guide/bgnet/html/#client-server-background) </br>

[RFC 2813](https://datatracker.ietf.org/doc/html/rfc2813) </br>

[MAINLY FOLLOW THIS NIKOTERA RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812) </br>

[RFC 2811](https://datatracker.ietf.org/doc/html/rfc2811) </br>

[RFC 2810](https://datatracker.ietf.org/doc/html/rfc2810) </br>

[RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459) </br>
