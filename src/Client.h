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
#define MY_ERROR -1
#define MY_EMPTY 0
class Client
{
public:
	Client();
	~Client();
	void ConnectToServer(const char* ipServer="localhost", const char* portNumber="12345");
	bool sendData(char * dataToSend_t, unsigned int sizeData);
	size_t receiveDataFromServer(char * buffer_t, int bufferSize);
	size_t NBReceiveDataFromServer(char * buffer_t, int bufferSize);
protected:
	boost::asio::ip::tcp::resolver* clientResolver;
	boost::asio::ip::tcp::socket* clientSocket;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::io_service* ioClient;
};
