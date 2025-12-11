#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>

using namespace std;

int main()
{
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0)
    {
        cerr << "Ошибка создания сокета!" << endl;
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cerr << "Ошибка привязки сокета!" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "UDP сервер запущен на порту 54000" << endl;
    cout << "Ожидание сообщений от клиентов..." << endl;
    cout << "Для остановки сервера нажмите Ctrl+C" << endl;

    char buffer[4096];
    sockaddr_in clientAddr;
    socklen_t clientSize = sizeof(clientAddr);

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        memset(&clientAddr, 0, sizeof(clientAddr));

        int bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&clientAddr, &clientSize);
        
        if (bytesReceived < 0)
        {
            if (errno == EINTR)  // Ctrl+C
            {
                cout << "Сервер получает сигнал завершения..." << endl;
                break;
            }
            else if (errno == EAGAIN || errno == EWOULDBLOCK)  // Таймаут
            {
                continue;
            }
            else
            {
                cerr << "Ошибка recvfrom: " << strerror(errno) 
                     << " (код: " << errno << ")" << endl;
                continue;
            }
        }

        buffer[bytesReceived] = '\0';
        
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        
        cout << "[" << clientIP << ":" << ntohs(clientAddr.sin_port) << "] ";
        cout << buffer << endl;

        if (strcmp(buffer, "shutdown") == 0)
        {
            cout << "Получена команда на выключение сервера" << endl;
            string response = "Сервер выключается...";
            sendto(serverSocket, response.c_str(), response.length(), 0,
                   (sockaddr*)&clientAddr, clientSize);
            break;
        }
        
        if (strcmp(buffer, "exit") == 0)
        {
            string response = "Клиент отключен, сервер работает";
            sendto(serverSocket, response.c_str(), response.length(), 0, (sockaddr*)&clientAddr, clientSize);
            continue;
        }

        sendto(serverSocket, buffer, bytesReceived, 0, (sockaddr*)&clientAddr, clientSize);
    }

    cout << "Сервер завершает работу" << endl;
    close(serverSocket);
    return 0;
}