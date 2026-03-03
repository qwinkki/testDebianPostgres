#include "main.h"

int main(){
    std::cout << "Enter debian IP address: ";
    std::string ip;    
    std::cin >> ip;
    ipAddress ipAddr(ip);
    checkConnection(ipAddr);

    std::cout << "Testing...\n";
    pqxx::work w(Database::getInstance());
    try{
        std::cout << "Creating table if not exists... ";
        w.exec("CREATE TABLE IF NOT EXISTS person (id SERIAL PRIMARY KEY, name TEXT NOT NULL, username TEXT NOT NULL)");
        w.commit();
        std::cout << "Successfully.\n";

        std::cout << "Inserting data... \n";
        std::cout << "Enter name: ";
        std::string name;
        std::cin >> name;
        std::cout << "Enter username: ";
        std::string username;
        std::cin >> username;
        w.exec_params("INSERT INTO person (name, username) VALUES ($1, $2)", 
            name, username);
        w.commit();
        std::cout << "Successfully.\n";
        
        std::cout << "Querying data... ";
        pqxx::result result = w.exec("SELECT * FROM person");
        for (const auto& row : result) {
            std::cout << "id: " << row["id"].as<int>() << ", name: " << row["name"].as<std::string>() 
                << ", username: " << row["username"].as<std::string>() << std::endl;
        }
        std::cout << "Successfully.\n";
    } catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
}