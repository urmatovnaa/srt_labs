#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        cerr << "Ошибка создания сокета!" << endl;
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cerr << "Ошибка подключения!" << endl;
        close(clientSocket);
        return 1;
    }

    cout << "TCP клиент запущен" << endl;

    char buffer[4096];
    string userInput;

    while (true)
    {
        cout << "> ";
        getline(cin, userInput);

        if (userInput.empty())
            continue;

        send(clientSocket, userInput.c_str(), userInput.length(), 0);

        if (userInput == "exit")
        {
            memset(buffer, 0, sizeof(buffer));
            recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            cout << "Сервер: " << buffer << endl;
            break;
        }

        if (userInput == "shutdown")
        {
            memset(buffer, 0, sizeof(buffer));
            recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            cout << "Сервер: " << buffer << endl;
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        int receivedBytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        
        if (receivedBytes > 0)
        {
            buffer[receivedBytes] = '\0';
            cout << "Сервер: " << buffer << endl;
        }
        else if (receivedBytes == 0)
        {
            cout << "Сервер отключился" << endl;
            break;
        }
    }

    close(clientSocket);
    cout << "Клиент остановлен" << endl;
    return 0;
}