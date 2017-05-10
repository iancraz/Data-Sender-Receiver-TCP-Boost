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