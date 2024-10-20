# ft_irc

Create your own IRC server in C++, fully compatible with an official client.

<h2 align="center"> Installation </h2>

```bash
#clone the repo
git clone https://github.com/OsemaFadhel/ft_irc.git
cd ft_irc

#compile and start the server
make && ./ircserv <PORT> <PASS> #change the PORT with one available like '6969' and set a PASS of your choice

```

Now using netcat or KVIrc (other clients might work too) connect to the server and have fun talking to your friends ;)

<h3 align="left"> Available commands </h3>

```bash
- PASS <password> #to access the server
- NICK  <nickname> #example NICK Wiz
- USER <user> <mode> <unused> <realname> #example USER guest 0 * :Ronnie Reagan !!!ONE TIME USE AT REGISTRATION!!!
- JOIN <channel>
- PRIVMSG <nickname or channel_name>  <text to be sent> #example PRIVMSG Angel :yes I'm receiving it !
- QUIT <optional message> #example  QUIT :Gone to have lunch

# CHANNEL OPERATIONS

- MODE <...>
- TOPIC <channel> [ <topic> ]
   #TOPIC #test :another topic      ; Command to set the topic on #test
   #                                to "another topic".

   #TOPIC #test :                   ; Command to clear the topic on
                                   #test.

   #TOPIC #test                     ; Command to check the topic for
                                   #test.
- INVITE <nickname> <channel> #example INVITE Wiz #Twilight_Zone
- KICK <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
	#example  KICK &Melbourne Matthew         ; Command to kick Matthew from
	#                          &Melbourne

	#KICK #Finnish John :Speaking English
        #                           ; Command to kick John from #Finnish
        #                           using "Speaking English" as the
        #                           reason (comment).

```


<h2 align="center"> Server Setup Description </h2>


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

- createSocket: Sets up the server socket. Read below.
- fd_set is a data structure used by the select() system call to represent a set of file descriptors. <br>
  It is used with the select() function to check which file descriptors are ready for reading, allowing efficient handling of multiple sockets or files.
  In this case, readfds will be used to track file descriptors for reading operations (i.e., to check if data is available to read without blocking).
- startLoop: Enters a loop to handle incoming client connections and monitor file descriptor activity. Read below.

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

```cpp

//int socket(int domain, int type, int protocol);
 socket(AF_INET6, SOCK_STREAM, 0);

```

- socket: Creates an endpoint for communication and returns a file descriptor for the socket. Creates an IPv6 TCP socket for the server.
  - Parameters:
   	- AF_INET6: Specifies the address family for IPv6.
   	- SOCK_STREAM: Specifies the socket type as TCP (connection-oriented).
	- 0: Specifies the protocol, where 0 lets the system choose the appropriate protocol for the given socket type.

<br>

```cpp

//int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

```

- setsockopt: Configures the socket's behavior, such as allowing address reuse.
  - Parameters:
   	- socket: The file descriptor returned by socket().
   	- SOL_SOCKET: Specifies that the options are at the socket level.
	- SO_REUSEADDR: Allows reuse of local addresses.
	- opt: A pointer to the option value (set to 1 in this case, allowing address reuse).
 	- sizeof(opt): Specifies the length of the option value.
<br>

```cpp

_serverAddr.sin6_family = AF_INET6;
_serverAddr.sin6_addr = in6addr_any;
_serverAddr.sin6_port = htons(_port);

```

- The first line tells the server to use IPv6 (AF_INET6).
- The second line sets the server to listen on any available IPv6 address (in6addr_any). <br>
	This assigns the address to which the server will bind, which in this case is in6addr_any, representing any available IPv6 address on the machine.
- The third line sets the port number, converting it to the correct network byte order using htons().
<br>

```cpp

//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
bind(_serverSocket, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr));

```

- bind: Binds the socket to the specified address and port.
  - Parameters:
   	- _serverSocket: The file descriptor for the server's socket.
   	- (struct sockaddr*)&_serverAddr: The address to bind the socket to.
	- sizeof(_serverAddr): The size of the address structure.
<br>

```cpp

//int listen(int sockfd, int backlog);
listen(_serverSocket, 50)
```

- listen: Marks the socket as a passive socket, which will accept incoming connection requests.
  - Parameters:
   	- _serverSocket: The file descriptor for the server's socket.
   	- 50: The maximum length of the queue for pending connections.
<br><br>

<h3>Start Loop Function</h3>

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

<br>

```cpp

//```cpp

//int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
select(maxfds + 1, &readfds, NULL, NULL, NULL);

```

- select: Monitors file descriptors for readability.
  - Parameters:
   	- nfds: The highest-numbered file descriptor in any of the three sets, plus one. This tells select() how many file descriptors to check. In this case, it's maxfds + 1 because maxfds is the largest file descriptor currently being monitored.
  	- readfds: A pointer to an fd_set that contains the file descriptors you want to check for readability. &readfds holds the file descriptors that are being monitored for read events.
  	- writefds: Set to NULL, meaning no file descriptors are being checked for writability in this call.
  	- exceptfds: Set to NULL, meaning no file descriptors are being checked for exceptional conditions.
  	- timeout: Set to NULL, meaning the function will block indefinitely until one or more file descriptors are ready.
<br>

```cpp

//int FD_ISSET(int fd, fd_set *set);
FD_ISSET(_serverSocket, &readfds);
```
- FD_ISSET: Checks if the server socket or a client socket is ready for reading.
   - Parameters:
   	- fd: The file descriptor you want to check (in this case, _serverSocket).
  	- set: The set of file descriptors being checked (in this case, &readfds).
<br>

- acceptClient: Accepts a new client connection if a request is detected on the server socket.


<h3>Set Maxfds Function</h3>

- FD_ZERO: Clears the set of file descriptors.
- FD_SET: Adds the server and client sockets to the set for monitoring.
- maxfds: Updates the maximum file descriptor number to handle in select.



















<!--
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
-->
