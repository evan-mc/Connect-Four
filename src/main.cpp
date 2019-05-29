#include "Game.h"
#include "Game_Network.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "MenuScreen.h"
#include "Screen.h"
int main() 
{
	/*Screen* mainScreen = new MenuScreen;

	int returnVal = 1;
	sf::RenderWindow window(sf::VideoMode(640, 480), "Connect Four", sf::Style::Close);
	while (returnVal != 0)
	{
		returnVal = mainScreen->run(window);
		if (returnVal == 2) //local
		{
			delete mainScreen;
			mainScreen = new Game(true);
		}
		else if (returnVal == 3) //bot
		{
			delete mainScreen;
			mainScreen = new Game(false);
		}
	}

	delete mainScreen;*/

	/*sf::RenderWindow window(sf::VideoMode(640, 480), "Connect Four", sf::Style::Close);

	std::cout << "Your IP address is: " << sf::IpAddress::getPublicAddress();

	std::cout << "\nAre you a client or server? c for client, s for server: ";
	char input;
	std::cin >> input;
	sf::Packet packet1;
	sf::Packet packet2;
	if (input == 'c')
	{
		std::cout << "you are a client\n";

		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect("localhost", 53000);
		if (status != sf::Socket::Done)
		{
			std::cout << "couldn't connect to server\n";
		}
		sf::Uint16 num = 2;
		while (window.isOpen())
		{
			if (num % 2 == 0)
			{
				std::cout << "\nsay something to send\n";

				std::cout << "enter age: ";
				sf::Uint16 age;
				std::cin >> age;

				packet1 << age;
				socket.send(packet1);
				packet1.clear();

				--num;
			}
			else
			{
				socket.receive(packet2);

				sf::Uint16 age2;
				packet2 >> age2;
				std::cout << "\nage: " << age2;

				++num;
			}

		}

	}
	else
	{
		std::cout << "you are a server\n";

		sf::TcpListener listener;

		// bind the listener to a port
		if (listener.listen(53000) != sf::Socket::Done)
		{
			std::cout << "couldnt listen on port\n";
		}
		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "couldn't accept a client\n";
		}
		sf::Uint16 num = 1;
		while (window.isOpen())
		{	
			if (num % 2 == 0)
			{
				std::cout << "\nsay something to send\n";

				std::cout << "enter a number: ";
				sf::Uint16 age;
				std::cin >> age;
				
				packet2 << age;
				client.send(packet2);
				packet2.clear();

				--num;
			}
			else
			{
				client.receive(packet1);

				sf::Uint16 age;
				packet1 >> age;
				std::cout << "\nage: " << age;

				++num;
			}
		}

		// use "client" to communicate with the connected client,
		// and continue to accept new connections with the listener
	}*/

	std::cout << "local: " << sf::IpAddress::getLocalAddress();
	sf::RenderWindow window(sf::VideoMode(640, 480), "Connect Four", sf::Style::Close);
	std::cout << "Enter server(s) or client(c): ";
	char inp;
	std::cin >> inp;
	if (inp == 's')
	{
		Game_Network server(inp);
		server.run(window);
	}
	else
	{
		Game_Network client(inp);
		client.run(window);
	}


}