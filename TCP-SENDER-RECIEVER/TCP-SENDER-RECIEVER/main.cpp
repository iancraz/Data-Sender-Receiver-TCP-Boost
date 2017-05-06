#include "cliente.h"
#include "servidor.h"
#define SIZE_SEND 900
#define SIZE_RECIVE 900

int main(void)
{
	servidor * server=NULL;
	cliente * client=NULL;
	char buffSend[SIZE_SEND];
	char buffRecive[SIZE_RECIVE];

	bool isServer = false;
	if (isServer)
	{
		server = new servidor;
		server->waitForCliente();//bloqueante
		server->receiveDataForCliente(buffRecive, SIZE_RECIVE);
		server->~servidor();
		std::cout << "Recivi: " << buffSend << std::endl;
	}
	else
	{
		client = new cliente;
		client->ConectToServer();
		client->sendData(buffSend, SIZE_SEND);
		client->~cliente();
		std::cout << "Envie: " << buffRecive << std::endl;

	}
	
	


	return 0;
}