/*
Copyright (C) 2018  Ian Cruz Diaz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <cstdint>
#define MY_ERROR -1
#define MY_EMPTY 0


class Server
{
public:
	Server(UINT32 port=12345);
	~Server();
	void waitForClient();
	void setPortNumber(UINT32 port = 12345);
	UINT32 getPortNumber();
	size_t receiveDataFromClient(char * buffer_t, int bufferSize);
	size_t NBReceiveDataFromClient(char * buffer_t, int bufferSize);
	bool sendData(char * dataToSend_t, unsigned int sizeData);
protected:
	UINT32 portNumber;
	boost::asio::io_service*  ioServer;
	boost::asio::ip::tcp::socket* ServerSocket;
	boost::asio::ip::tcp::acceptor* conectionServerAceptor;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};
