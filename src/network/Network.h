#ifndef NETWORK
#define NETWORK

#include <string>
#include "json.hpp"

using json = nlohmann::json;
//  #include <iostream>
//  #include <fstream>
//  #include "json.hpp" // Include the nlohmann/json library
// using json = nlohmann::json;

/**
 * @class network
 * @brief This class is used to create an object that can be sent over lan
 */
class Network
{
private:
    std::string serverIpAddr;   // the ip address of the server
    int PORT;                   // the port of the server
    std::string updateFileName; // the name of the file that will be updated
    std::string saveFileName;   // the name of the file that will be saved
    static bool networkStatus;  // the status of the network

public:
    /**
     * @brief Construct a new Network object
     *
     */
    Network();

    /**
     * @brief Construct a new Network object
     *
     * @param IP
     */
    Network(std::string IP);

    /**
     * @brief Destroy the Network object
     *
     */
    ~Network();

    /**
     * @brief Get the Server IP address
     *
     * @return std::string
     */
    std::string getServerIPaddr();

    /**
     * @brief Get the Local IP address
     *
     * @return std::string
     */
    std::string getLocalIpAddr();

    /**
     * @brief Set the Server IP address
     *
     * @param IP
     */
    void setServerIpAddr(std::string IP); // set the server ip address

    /**
     * @brief Get the Port
     *
     * @return int
     */
    void changePort(int port);

    /**
     * @brief set the name of the file that will be updated
     *
     * @param name
     */
    void setupdateFileName(std::string name);

    /**
     * @brief set the name of the file that will be saved
     *
     * @param name
     */
    void setsaveFileName(std::string name);

    /**
     * @brief create a client
     *
     * @param mode
     * @return int
     */
    int client(std::string mode);

    /**
     * @brief create a server
     *
     * @return int
     */
    int server();

    /**
     * @brief send a file to the server
     *
     * @return int
     */
    int sendFile();

    /**
     * @brief receive the file from the server
     *
     * @return int
     */
    int receiveFile();

    /**
     * @brief read the json file and return it
     *
     * @return json
     */
    json readJson();

    /**
     * @brief read the json file and return it
     *
     * @param fichier
     * @return json
     */
    json readJson(std::string fichier);

    /**
     * @brief update the file with the new json
     *
     * @param cible
     * @param resultat
     */
    void updateFile(std::string cible, json resultat);

    /**
     * @brief update the file with the new json
     *
     * @param cible
     * @param resultat
     * @param fichier
     */
    void updateFile(std::string cible, json resultat, std::string fichier);

    /**
     * @brief update the file with the new json
     *
     * @param datafile
     * @param destinationfile
     */
    void updateFile(json datafile, std::string destinationfile);

    /**
     * @brief delete the json from the file
     *
     * @param cible
     */
    void deleteFromFile(std::string cible);

    /**
     * @brief delete the json from the file
     *
     * @param cible
     * @param fichier
     */
    void mergeJson(std::string fromfile, std::string tofile);
    /**
     * @brief put brackets in the file
     *
     * @param fichier
     */
    void putbraks(std::string fichier);

    /**
     * @brief copy the json and put it in another file (it overwrites the destination file)
     *
     * @param fromfile
     * @param tofile
     */
    void copyJson(std::string fromfile, std::string tofile);

    /**
     * @brief clear the json from the file
     *
     */
    void clearJson();

    /**
     * @brief clear the json from the file
     *
     * @param fichier
     */
    void clearJson(std::string fichier);

    /**
     * @brief create a json file
     *
     */
    void createJson(std::string fichier);

    /**
     * @brief show the json
     *
     * @param data
     */
    void afficher(json data);

    /**
     * @brief test the write function
     *
     * @param fichier
     */
    void testwrite(std::string fichier);

    /**
     * @brief Set the Network Status object
     *
     * @param status
     */
    void setNetworkStatus(bool status);

    /**
     * @brief Get the Network Status object
     *
     * @return bool
     */
    bool getNetworkStatus();
};

#endif // NETWORK