#include "common/common.h"
#include <pqxx/pqxx>

class Database {
	std::string ip;

	Database();
	static std::unique_ptr<pqxx::connection> conn;
public:
	static pqxx::connection& getInstance();
};

void checkConnection(ipAddress& ipAddr);