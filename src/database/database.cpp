#include "database.h"

void initializeDatabase(){
 try{
    pqxx::connection conn ("postgresql://postgres:123@192.168.1.117:5432/test");
    if(conn.is_open()) std::cout << "Connectoed to " << conn.dbname() << '\n';
    else throw "error to connect\n";
 }  catch(std::exception& e){
    std::cerr << e.what() << '\n';
 } 
}