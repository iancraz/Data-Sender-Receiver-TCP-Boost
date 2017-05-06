#include "cliente.h"
#include "servidor.h"
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
		server = new servidor;
		server->waitForCliente();//bloqueante
		//server->receiveDataForCliente(buffRecive, SIZE_RECIVE);
		while (1) {
			server->nonBlockinReceiveDataForCliente(buffRecive, SIZE_RECIVE);

		}
		
		server->~servidor();
		std::cout << "Recivi: " << buffRecive << std::endl;
		std::cout << "Y en la ultima posicion: " << buffRecive[SIZE_SEND - 1] << std::endl;
	}
	else
	{
		strcpy(buffSend, "provando el sittema de networking qon linea largaaaaaa");
		buffSend[SIZE_SEND - 1] = 'A';
		client = new cliente;
		client->ConectToServer();
		getchar();
		client->sendData(buffSend, SIZE_SEND);
		client->~cliente();
		std::cout << "Envie: " << buffSend << std::endl;

	}
	
	


	return 0;
}