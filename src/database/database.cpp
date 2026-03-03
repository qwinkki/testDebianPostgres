#include "database.h"

pqxx::connection& Database::getInstance() {
	if (!conn) static Database instance;
	return *conn;
}

std::unique_ptr<pqxx::connection> Database::conn = nullptr;
Database::Database() {
	std::cout << "start connecting to Database\n";
	if(!conn)
		try {
			conn = std::make_unique<pqxx::connection>("postgresql://postgres:123@" + ip + ":5432/UniversityRecords");
			if (conn->is_open())
				std::cout << "database opening.. "  << "OK\n";
			else {
				std::cout << "ERROR: Database in not opened\n";
				exit(1);
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			exit(1);
		}
}

void checkConnection(ipAddress& ipAddr) {
 try{
	 std::string request = "postgresql://postgres:123@" + ipAddr.getip() + ":5432/test";
	pqxx::connection conn(request.c_str());
	if(conn.is_open()) std::cout << "Connectoed to " << conn.dbname() << '\n';
	else throw "error to connect\n";
 }  catch(std::exception& e){
	std::cerr << e.what() << '\n';
 } 
}