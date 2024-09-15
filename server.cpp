#include <bits/stdc++.h>
#include <sys/socket.h> // socket
#include <netinet/in.h> // address
#include <unistd.h>     // send, read, close

#define PORT 3003
#define BUFFER_SIZE 1024

using namespace std;
// We need to create a server which will handle GET request from client

string createResponse(string content_type, int content_len, string content)
{
    string response = "HTTP/1.1 200 OK \r\n"
                      "Content-Type: " +
                      content_type + "\r\n"
                                     "Content-Length: " +
                      to_string(content_len) + "\r\n"
                                               "\r\n" +
                      content;

    return response;
}

int main()
{

    // 1. Initialize socket
    // IPV4 = AF_INET
    // IPV6 = AF_INET6

    // TCP (Transmission control protocol) - SOCK_STREAM
    // UDP () - SOCK_DGRAM

    // Variables

    int server_socket;

    char buffer[BUFFER_SIZE];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0)
    {
        cout << "Socket connection error." << endl;
        return -1;
    }

    // 2. Bind address to socket

    // I. Create an address

    struct sockaddr_in address, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    socklen_t addr_len = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // II Bind socket to address
    if (bind(server_socket, (sockaddr *)&address, addr_len) < 0)
    {
        cout << "Binding error" << endl;
        return -1;
    }

    // 3. listen for the connection on port PORT

    if (listen(server_socket, 3) < 0)
    {
        cout << "Listen error" << endl;
        return -1;
    }

    cout << "Listening on http://localhost:" << PORT << endl;
    while (1)
    {
        // 4. Accept request

        int client_socket = accept(server_socket, (sockaddr *)&client_addr, &client_addr_len);

        if (client_socket < 0)
        {
            cout << "Client Socket failed" << endl;
            return -1;
        }

        cout << "Client connected" << endl;

        // 5. Send and read or close
        // 1 Read data from client
        read(client_socket, buffer, BUFFER_SIZE);

        cout << "Client Data : " << buffer << endl;
        string html_content = "<html><body><h1>Sonu!!</h1></body></html>";
        string res_data = createResponse("text/html", html_content.length(), html_content);
        if(send(client_socket, res_data.c_str(), res_data.length(), 0) < 0){
            cout << "send error" << endl;
        }
        close(client_socket);
    }

    // 6. close

    close(server_socket);


    return 0;
}