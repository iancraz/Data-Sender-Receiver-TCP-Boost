
#include "cliente.h"

cliente::cliente()
{
	ioCliente = new boost::asio::io_service();
	clienteSocket = new boost::asio::ip::tcp::socket(*ioCliente);
	clienteResolver = new boost::asio::ip::tcp::resolver(*ioCliente);
}

cliente::~cliente()
{
	delete ioCliente;
	delete clienteSocket;
	delete clienteResolver;
}

//ConectToServer()
//metodo bloqueante que espera a conectarse con un servidor
//recive como paramteros 2 string. el primero, ipserver, es la ip del servidor
//y el segundo string, portnumber, es el numero del puerto en el cual el servidor
//esta escuchando
void cliente::ConectToServer(const char * ipServer, const char * portNumber)
{
	try 
	{
		endpoint = clienteResolver->resolve(boost::asio::ip::tcp::resolver::query(ipServer, portNumber));
		boost::asio::connect(*clienteSocket, endpoint);

	}
	catch (std::exception a)
	{
		std::cout << "Error al conectarse con el servidor, recuerde que este deve estar escuchando el puerto" << std::endl;
		exit(4);
	
	}
	
}
 
//sendData()
//recive un arreglo de char, que son lo elementos que mandara. tambien recive
//un int con la cantidad de elementos que se necesitan enviar
//

bool cliente::sendData(char * dataToSend_t, unsigned int sizeData)
{
	char DataToSend[900];
	
	for (size_t i = 0; i < sizeData; i++)
	{
		DataToSend[i] = dataToSend_t[i];
	}
	std::cout << DataToSend[0];

	boost::function<void(const boost::system::error_code&, std::size_t)> handler(
		boost::bind(&cliente::writeCompletitionCallback, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	
	boost::asio::async_write(*clienteSocket, boost::asio::buffer(DataToSend), handler);

	return true;

}

void cliente::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

//receiveDataForCliente
//previamente se deve llamar a waitforcleinte()
//recive como paramteros un arreglo de char(buffer) y una int,
//con la cantidad de elementos de dicho arreglo.
//si se puedo recivir toda la informacion devuelve un true, caso contrario
//devuelve un false.
bool cliente::receiveDataForServidor(char * buffer_t, int bufferSize)
{
	UINT16 longitudDelMensaje = 0;
	boost::system::error_code error;
	char bufferTemp[900];
	do
	{
		longitudDelMensaje = clienteSocket->read_some(boost::asio::buffer(bufferTemp), error);//recive la informacion del cliente y la guarda en bufferTemp

	} while (error);

	if (error != boost::asio::error::eof)
	{
		if (longitudDelMensaje <= bufferSize)
		{
			for (size_t i = 0; i < bufferSize; i++)//transfiero la informacion de un buffer al otro
			{
				buffer_t[i] = bufferTemp[i];
			}
			return true;
		}
		else// en caso que el buffer enviado por el usuario sea muy chico envio false
		{
			for (size_t i = 0; i < bufferSize; i++)//transfiero la informacion de un buffer al otro
			{
				buffer_t[i] = bufferTemp[i];
			}
			return false;
		}

	}
	else
	{
		return false;
	}



}



void cpychar_c(char * a, char * b, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		a[i] = b[i];
	}

}

bool charcomp_c(char * a, char * b, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}

	}
	return true;
}


//previamente se deve llamar a waitforcleinte()
//recive como paramteros un arreglo de char(buffer) y una int,
//con la cantidad de elementos de dicho arreglo.
//devuelve: true, si se recivio algo. false, si no se recivio nada
//nota: NO ES BLOQUEANTE!!!!!!!!!!!!!!!!!!!!!!!!
bool cliente::nonBlockinReceiveDataForServer(char * buffer_t, int bufferSize)
{

	UINT16 longitudDelMensaje = 0;
	boost::system::error_code error;
	char bufferTemp[900];
	char bufferToTest[900];
	cpychar_c(bufferTemp, bufferToTest, 900);


	boost::function<void(const boost::system::error_code&, std::size_t)> handler(
		boost::bind(&cliente::writeCompletitionCallback, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	boost::asio::async_read(*clienteSocket, boost::asio::buffer(bufferTemp), handler);
	//ServerSocket->async_read_some(boost::asio::buffer(bufferTemp), handler);

	if (false == charcomp_c(bufferToTest, bufferTemp, 900))
	{
		cpychar_c(buffer_t, bufferTemp, 900);//copio el buffer

		return true;
	}
	else
	{
		return false;
	}

}
