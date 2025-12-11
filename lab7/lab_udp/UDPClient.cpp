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
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0)
    {
        cerr << "Ошибка создания сокета!" << endl;
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    cout << "UDP клиент запущен" << endl;

    char buffer[4096];
    string userInput;

    while (true)
    {
        cout << "> ";
        getline(cin, userInput);

        if (userInput.empty())
            continue;

        sendto(clientSocket, userInput.c_str(), userInput.length(), 0,
               (sockaddr*)&serverAddr, sizeof(serverAddr));

        if (userInput == "exit")
        {
            cout << "Клиент завершает работу" << endl;
            break;
        }

        if (userInput == "shutdown")
        {
            sockaddr_in fromAddr{};
            socklen_t fromSize = sizeof(fromAddr);
            memset(buffer, 0, sizeof(buffer));
            
            recvfrom(clientSocket, buffer, sizeof(buffer) - 1, 0,
                     (sockaddr*)&fromAddr, &fromSize);
            
            cout << "Сервер: " << buffer << endl;
            break;
        }

        sockaddr_in fromAddr{};
        socklen_t fromSize = sizeof(fromAddr);
        memset(buffer, 0, sizeof(buffer));
        
        int receivedBytes = recvfrom(clientSocket, buffer, sizeof(buffer) - 1, 0,
                                     (sockaddr*)&fromAddr, &fromSize);
        
        if (receivedBytes > 0)
        {
            buffer[receivedBytes] = '\0';
            cout << "Сервер: " << buffer << endl;
        }
    }

    close(clientSocket);
    cout << "Клиент остановлен" << endl;
    return 0;
}