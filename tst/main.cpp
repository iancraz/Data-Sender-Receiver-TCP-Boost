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

#include "../src/cliente.h"
#include "../src/servidor.h"
#define SIZE_SEND 600
#define SIZE_RECIVE 800
// es el principal
int main(void)
{
	servidor * server=NULL;
	cliente * client=NULL;
	char buffSend[SIZE_SEND];
	char buffRecive[SIZE_RECIVE];


	bool isServer = true;
	if (isServer)
	{
		size_t size = 0;
		server = new servidor;
		server->waitForCliente();//bloqueante
		server->receiveDataForCliente(buffRecive, SIZE_RECIVE);
		/*while (size<=0) {
			size = server->nonBlockinReceiveDataForCliente(buffRecive, SIZE_RECIVE);

		}*/

		server->~servidor();
		std::cout << "Recivi: " << buffRecive << std::endl;
		std::cout << "Longitud: " << size << std::endl;
	}
	else
	{
		strcpy(buffSend, "provando el sittema de networking qon linea largaaaaaa");

		client = new cliente;
		client->ConectToServer();
		getchar();
		client->sendData(buffSend, strlen(buffSend)+1);
		client->~cliente();
		std::cout << "Envie: " << buffSend << std::endl;

	}




	return 0;
}
