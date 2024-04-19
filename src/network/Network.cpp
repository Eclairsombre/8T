#include "Network.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <cassert>

using json = nlohmann::json;

Network::Network()
{
    this->PORT = 8080;
    this->updateFileName = "update.json";
    this->saveFileName = "save.json";
    this->serverIpAddr = "192.168.113.236";
}
Network::Network(std::string IP)
{
    this->PORT = 8080;
    this->updateFileName = "update.json";
    this->saveFileName = "save.json";
    this->serverIpAddr = IP;
}

Network::~Network()
{
}

std::string Network::getServerIPaddr()
{

    return this->serverIpAddr;
}

std::string Network::getLocalIpAddr()
{

    //  Open a pipe to the hostname command
    FILE *pipe = popen("hostname -I", "r");
    if (!pipe)
    {
        std::cerr << "Error: Failed to open pipe.\n";
        return "EXIT_FAILURE";
    }

    // Read the IP address from the pipe
    char buffer[128];
    std::string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    // Close the pipe
    pclose(pipe);

    // Print the IP address
    // std::cout << "Your IP address: " << result;

    return result;
}

void Network ::setServerIpAddr(std::string IP)
{

    this->serverIpAddr = IP;
}

void Network::changePort(int port)
{
    this->PORT = port;
}

void Network::setupdateFileName(std::string name)
{

    this->updateFileName = name;
}

void Network::setsaveFileName(std::string name)
{

    this->saveFileName = name;
}

int Network::server()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach the socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        char bufferReceive[3000] = {0};
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        //---------------------------------------client message reception---------------------------
        read(new_socket, bufferReceive, 3000);

        std::string requestType = bufferReceive;

        if (requestType == "receive")
        {

            //---------------------------------------send file "data.json" to the client-------------------
            std::ifstream dataFile("data.json", std::ios::binary | std::ios::ate);
            if (!dataFile) // ouvrir le fichier pour s'assurer que tout est bon
            {
                std::cerr << "Imposible to open the file\n";
                exit(EXIT_FAILURE);
            }

            std::streamsize size = dataFile.tellg(); // This is for getting the size of the file
            dataFile.seekg(0, std::ios::beg);

            std::vector<char> buffer(size);
            if (dataFile.read(buffer.data(), size))
            {
                /* Le fichier a été lu avec succès */
                send(new_socket, buffer.data(), size, 0);
            }
            //---------------------------------------send file "data.json" to the client-------------------
        }

        else
        {

            std::ofstream DATA("data.json");
            DATA << bufferReceive;
        }

        //---------------------------------------receive the client message---------------------------

        std::cout << "Message envoyé au client\n";
        close(new_socket);
    }

    return 0;
}

int Network::client(std::string mode)
{

    int sock = 0;
    struct sockaddr_in serv_addr;

    char bufferRead[3000] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "\n Socket creation error \n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    const char *ipOfTheServer = getServerIPaddr().c_str();
    if (inet_pton(AF_INET, ipOfTheServer, &serv_addr.sin_addr) <= 0)
    {
        std::cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "\nConnection Failed \n";
        return -1;
    }

    //---------------------------------------send the file "data.json" to the client-------------------
    if (mode == "send")
    {

        std::ifstream dataFile("data.json", std::ios::binary | std::ios::ate);
        while (!dataFile)
        {
            std::ifstream dataFile("data.json", std::ios::binary | std::ios::ate);
        }

        std::streamsize size = dataFile.tellg(); // To get the size of the file
        dataFile.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        if (dataFile.read(buffer.data(), size))
        {
            /* The file has been read successfully */
            send(sock, buffer.data(), size, 0);
        }
    }
    //---------------------------------------send the file "data.json" to the client-------------------

    if (mode == "receive")
    {
        std::string sms = mode;
        send(sock, sms.c_str(), sms.size(), 0);
        int valread = read(sock, bufferRead, 3000); // read the socket
        if (valread == 0)
        {
            std::cout << "network receive error" << std::endl;
            return -1;
        }

        std::ofstream DATA("data.json");
        DATA << bufferRead;
    }
    return 0;
}
json Network::readJson()
{

    std::ifstream file_in("data.json");
    if (file_in.peek() != std::ifstream::traits_type::eof())
    {

        // Read the JSON file
        std::ifstream file("data.json");
        json data;
        file >> data;
        file.close();
        return data;
    }
    else
    {
        std::cout << "The file is blank " << std::endl;
    }
    return -1;
}

json Network::readJson(std::string fichier = "data.json")
{

    std::ifstream file_in(fichier);
    if (file_in.peek() != std::ifstream::traits_type::eof())
    {

        // Read the JSON file
        std::ifstream file(fichier);
        json data;
        file >> data;
        file.close();
        return data;
    }
    else
    {
        std::cout << "The file is blank " << std::endl;
    }
    return -1;
}

void Network::putbraks(std::string fichier)
{
    json test;

    std::ofstream file(fichier);

    file << std::setw(4) << test << std::endl; // Pretty print with indentation
    file.close();
    std::cout << "JSON data has been written to " << fichier << std::endl;
}

void Network ::updateFile(std::string cible, json resultat) // this function allows to add elements to a Json file, by specifying a target (it is useful if we want to nest the data)
{

    // create a JSON object by reading from the existing file
    json copy;

    std::ifstream file_in("data.json");
    if (file_in.peek() != std::ifstream::traits_type::eof())
    {
        if (file_in.is_open())
        {
            file_in >> copy;
        }
    }

    // Write the new data into the JSON object
    copy[cible] = resultat;

    std::ofstream file_out("data.json");
    if (file_out.is_open())
    {
        // write the JSON data to the file with indentation (just for readability)
        file_out << std::setw(4) << copy << std::endl;
        file_out.close();
        std::cout << "JSON data has been written to " << "data.json" << std::endl;
    }
    else
    {
        std::cout << "Failed to open file " << "data.json" << " for writing." << std::endl;
    }
}

void Network ::updateFile(std::string cible, json resultat, std::string fichier) // this function allows to add elements to a Json file, by specifying a target (it is useful if we want to nest the data)
{

    json copy;

    std::ifstream file_in(fichier);
    if (file_in.peek() != std::ifstream::traits_type::eof())
    {
        if (file_in.is_open())
        {
            file_in >> copy;
        }
    }

    copy[cible] = resultat;

    std::ofstream file_out(fichier);
    if (file_out.is_open())
    {

        file_out << std::setw(4) << copy << std::endl;
        file_out.close();
        std::cout << "JSON data has been written to " << fichier << std::endl;
    }
    else
    {
        std::cout << "Failed to open file " << fichier << " for writing." << std::endl;
    }
}

void Network::updateFile(json datafile, std::string destinationfile)
{

    json datafile2;
    std::ifstream file_in(destinationfile);
    if (file_in.is_open())
    {
        file_in >> datafile2;
        file_in.close();
    }
    datafile.merge_patch(datafile2);

    std::ofstream file_out(destinationfile);

    if (file_out.is_open())
    {

        file_out << std::setw(4) << datafile << std::endl;

        file_out.close();
        std::cout << "JSON data has been written to " << destinationfile << std::endl;
    }
    else
    {
        std::cout << "Failed to open file " << destinationfile << " for writing." << std::endl;
    }
}

void Network::deleteFromFile(std::string cible)
{

    json copy;

    std::ifstream file_in("data.json");
    if (file_in.peek() != std::ifstream::traits_type::eof())
    {
        if (file_in.is_open())
        {
            file_in >> copy;
        }
    }

    // delete the target from the JSON object
    copy.erase(cible);

    std::ofstream file_out("data.json");
    if (file_out.is_open())
    {

        file_out << std::setw(4) << copy << std::endl;
        file_out.close();
        std::cout << "JSON data has been written to " << "data.json" << std::endl;
    }
    else
    {
        std::cout << "Failed to open file " << "data.json" << " for writing." << std::endl;
    }
}

void Network::mergeJson(std::string fromfile, std::string tofile)
{

    updateFile(readJson(fromfile), tofile);
}

void Network::copyJson(std::string fromfile, std::string tofile)
{
    json copy = readJson(fromfile);
    std::ofstream file3(tofile);
    file3 << std::setw(4) << tofile << std::endl;
    file3.close();
}
void Network::clearJson()
{
    std::ofstream file("data.json");
    putbraks("data.json");
    file.close();
}

void Network::clearJson(std::string fichier)
{
    std::ofstream file(fichier);
    putbraks(fichier);
    file.close();
}

void Network::createJson(std::string fichier)
{

    std::ofstream file(fichier);
    file.close();
    putbraks(fichier);
}

void Network::afficher(json data)
{

    std::cout << data << std::endl;
}

void Network::testwrite(std::string fichier)
{

    // This hole function is just for testing purposes
    json data;
    json data2;

    data2["name"] = "John f";
    data2["age"] = 45;
    data2["city"] = "New York";

    data["name"] = data2;
    data["age"] = 30;
    data["city"] = "New York";
    data["numero"] = "53";
    data["numero2"] = "53";

    std::ofstream file(fichier);

    file << std::setw(4) << data << std::endl;
    file.close();
    std::cout << "JSON data has been written to " << fichier << std::endl;
}

int Network::sendFile()
{
    return client("send");
}

int Network::receiveFile()
{

    int value = client("receive");

    int tryCount = 0;

    while (value == -1 && tryCount < 30)
    {
        value = client("receive");
        std::cout << "network receive error" << std::endl;
        tryCount++;
    }
    if (tryCount == 30)
    {
        assert(value != -1);
    }

    return value;
}

void Network::setNetworkStatus(bool status)
{
    networkStatus = status;
}

bool Network::getNetworkStatus()
{
    return networkStatus;
}

bool Network::networkStatus = false;