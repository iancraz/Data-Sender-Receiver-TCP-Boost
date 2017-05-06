
#include "servidor.h"

//servidor()
//recive como paramtro un int, que representa el puerto que el srvidor escucha,
//en caso que ese puerto no sea indicado, el puerto por defecto es 12345.
//
servidor::servidor(UINT32 port)
{
	portNumber = port;//asigno el puerto al servidor
	ioServer = new boost::asio::io_service();//creo el io_service del servidor
	ServerSocket = new boost::asio::ip::tcp::socket(*ioServer);//creo el socket del servidor
	conectionServerAceptor = new boost::asio::ip::tcp::acceptor(*ioServer,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portNumber));//creo el aceptor del servidor
	//std::cout << std::endl << "El puerto " << portNumber << " se creo" << std::endl;
	serverResolver = new boost::asio::ip::tcp::resolver(*ioServer);
}

servidor::~servidor()
{
	delete ioServer;
	delete ServerSocket;
	delete conectionServerAceptor;
	delete serverResolver;
}

//waitForCliente()
//metodo bloqueante, que espera la conexion del cliente.
//

void servidor::waitForCliente()
{
	conectionServerAceptor->accept(*ServerSocket);
}
//receiveDataForCliente
//previamente se deve llamar a waitforcleinte()
//recive como paramteros un arreglo de char(buffer) y una int,
//con la cantidad de elementos de dicho arreglo.
//si se puedo recivir toda la informacion devuelve un true, caso contrario
//devuelve un false.
bool servidor::receiveDataForCliente(char * buffer_t, int bufferSize)
{
	UINT16 longitudDelMensaje = 0;
	boost::system::error_code error;
	char bufferTemp[900];
	do
	{
		longitudDelMensaje	= ServerSocket->read_some(boost::asio::buffer(bufferTemp), error);//recive la informacion del cliente y la guarda en bufferTemp

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



void cpychar(char * a, char * b, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		a[i] = b[i];
	}

}

bool charcomp(char * a, char * b, int size)
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
bool servidor::nonBlockinReceiveDataForCliente(char * buffer_t, int bufferSize)
{
	
	UINT16 longitudDelMensaje = 0;
	boost::system::error_code error;
	char bufferTemp[900];
	char bufferToTest[900];
	cpychar(bufferTemp, bufferToTest, 900);
	
	
	boost::function<void(const boost::system::error_code&, std::size_t)> handler(
		boost::bind(&servidor::writeCompletitionCallback, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	boost::asio::async_read(*ServerSocket, boost::asio::buffer(bufferTemp), handler);
	//ServerSocket->async_read_some(boost::asio::buffer(bufferTemp), handler);
	
	if (false== charcomp(bufferToTest, bufferTemp,900))
	{
		cpychar(buffer_t, bufferTemp, 900);//copio el buffer
		
		return true;
	}
	else
	{
		return false;
	}
	
}

void servidor::writeCompletitionCallback(const boost::system::error_code & error, std::size_t transfered_bytes)
{
	
	std::cout << std::endl << "Write Callback called" << std::endl;
}


//sendData()
//recive un arreglo de char, que son lo elementos que mandara. tambien recive
//un int con la cantidad de elementos que se necesitan enviar
//
bool servidor::sendData(char * dataToSend_t, unsigned int sizeData)
{
	char DataToSend[900];

	for (size_t i = 0; i < sizeData; i++)
	{
		DataToSend[i] = dataToSend_t[i];
	}
	std::cout << DataToSend[0];

	boost::function<void(const boost::system::error_code&, std::size_t)> handler(
		boost::bind(&servidor::writeCompletitionCallback, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	boost::asio::async_write(*ServerSocket, boost::asio::buffer(DataToSend), handler);

	return true;
}

