#include <iostream>
#include <libraries/SFML-2.6.1/include/SFML/Network.hpp>
#include <windows.h>
#include <string>

using namespace std;

int main()
{
    sf::TcpSocket socket; //Создаем сокет
    sf::IpAddress ip = sf::IpAddress::getLocalAddress(); //Создаем адресс
    
    char type; //Создаем переменную, отвечающую за тип подключения
    int port = 2000;

    cout << "Enter type connecting: [c] - client, [s] - server\n";
    cin >> type;

    if (type == 's')
    {
        sf::TcpListener listener;
        listener.listen(port);

        if (listener.accept(socket) != sf::Socket::Done)
        {
            cout << "Operation error\n";
        }
    }
    else if (type == 'c')
    {
        if (socket.connect(ip, port) != sf::Socket::Done)
        {
            cout << "Operation error\n";
        }
    }

    string name;
    cout << "Enter your name\n>";
    cin >> name;

    socket.setBlocking(false);

    string message = "";
    sf::Packet packet;

    while(true)
    {
        if (GetAsyncKeyState(VK_INSERT))
        {
            cin >> message;
        }
        if (message != "")
        {
            packet.clear();
            packet << name << message;
            socket.send(packet);
            message = "";
        }
        if (socket.receive(packet) == sf::Socket::Done)
        {
            string nameRec;
            string messageRec;

            packet >> nameRec >> messageRec;
            cout << nameRec << ": " << messageRec << endl;
        }
    }

    system("pause");
}