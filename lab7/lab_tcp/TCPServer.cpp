#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/time.h>

using namespace std;

volatile sig_atomic_t running = 1;

void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        cout << "\nПолучен сигнал завершения..." << endl;
        running = 0;
    }
}

int main()
{
    signal(SIGINT, handleSignal);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        cerr << "Ошибка создания сокета!" << endl;
        return 1;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

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

    if (listen(serverSocket, 5) < 0)
    {
        cerr << "Ошибка listen!" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "TCP сервер запущен на порту 54000" << endl;
    cout << "Ожидание подключений..." << endl;
    cout << "Для остановки нажмите Ctrl+C" << endl;

    while (running)
    {
        sockaddr_in clientAddr{};
        socklen_t clientSize = sizeof(clientAddr);
        
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        
        if (clientSocket < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                continue;
            }
            else if (!running)
            {
                break;
            }
            else
            {
                cerr << "Ошибка accept: " << strerror(errno) << endl;
                continue;
            }
        }

        if (!running)
        {
            close(clientSocket);
            break;
        }

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        cout << "Подключен клиент: " << clientIP << ":" << ntohs(clientAddr.sin_port) << endl;

        char buffer[4096];
        bool clientConnected = true;

        struct timeval clientTimeout;
        clientTimeout.tv_sec = 1;
        clientTimeout.tv_usec = 0;
        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, &clientTimeout, sizeof(clientTimeout));

        while (clientConnected && running)
        {
            memset(buffer, 0, sizeof(buffer));
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            
            if (bytesReceived > 0)
            {
                buffer[bytesReceived] = '\0';
                cout << "[" << clientIP << ":" << ntohs(clientAddr.sin_port) << "] ";
                cout << buffer << endl;

                if (strcmp(buffer, "shutdown") == 0)
                {
                    cout << "Получена команда на выключение сервера" << endl;
                    string response = "Сервер выключается...";
                    send(clientSocket, response.c_str(), response.length(), 0);
                    running = 0;
                    clientConnected = false;
                }
                else if (strcmp(buffer, "exit") == 0)
                {
                    string response = "Клиент отключен";
                    send(clientSocket, response.c_str(), response.length(), 0);
                    clientConnected = false;
                }
                else
                {
                    send(clientSocket, buffer, bytesReceived, 0);
                }
            }
            else if (bytesReceived == 0)
            {
                cout << "Клиент отключился: " << clientIP << ":" << ntohs(clientAddr.sin_port) << endl;
                clientConnected = false;
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                {
                    continue;
                }
                else if (!running)
                {
                    clientConnected = false;
                }
                else
                {
                    cerr << "Ошибка recv: " << strerror(errno) << endl;
                    clientConnected = false;
                }
            }
        }

        close(clientSocket);
        cout << "Соединение закрыто: " << clientIP << ":" << ntohs(clientAddr.sin_port) << endl;
    }

    close(serverSocket);
    cout << "Сервер завершает работу" << endl;
    return 0;
}