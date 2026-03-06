#include "main.h"

void printUsage(pqxx::work& txn, const std::string& title, const std::string& query)
{
    std::cout << "\n===== " << title << " =====\n";

    pqxx::result res = txn.exec(query);

    for (const auto& row : res)
    {
        for (const auto& field : row)
        {
            std::cout << field.name() << ": " << field.c_str() << std::endl;
        }
        std::cout << "-------------------------\n";
    }
}

int main(){
    std::string ip, port = "5432", dbname, user, password;
    std::cout << "Enter IP address: ";
    std::cin >> ip;
    std::cout << "Enter port (default 5432): ";
    std::string port_input;
    std::cin >> port_input;
    if (!port_input.empty())
        port = port_input;
    std::cout << "Enter database name: ";
    std::cin >> dbname;
    std::cout << "Enter username: ";
    std::cin >> user;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::string conn_str = "postgresql://" + user + ":" + password + "@" + ip + ":" + port + "/" + dbname;
    
    try{
        pqxx::connection conn(conn_str);
        if (!conn.is_open()) {
            std::cerr << "Failed to connect to database." << std::endl;
            return -1;
        }

        std::cout << "\nConnected to " << conn.dbname() << '\n';
        pqxx::work txn(conn);

        // server info
        printUsage(txn, "\nServer Version",
        "SELECT version();");

        // system info
        printUsage(txn, "Server Network Info",
        "SELECT COALESCE(inet_server_addr()::text, 'local_socket') AS server_ip, "
        "inet_server_port() AS server_port;");

        // current db
        printUsage(txn, "Current Database",
        "SELECT current_database() AS database_name, "
        "current_user AS user_name;");

        // db size
        printUsage(txn, "Database Size",
        "SELECT current_database() AS db_name, "
        "pg_size_pretty(pg_database_size(current_database())) AS db_size;");

        // list of tables
        printUsage(txn, "List of Tables",
        "SELECT schemaname, tablename "
        "FROM pg_tables "
        "WHERE schemaname NOT IN ('pg_catalog', 'information_schema', 'pg_toast');");

        // table sizes (исправленный вариант)
        printUsage(txn, "Table Sizes",
        "SELECT relname AS table_name, "
        "pg_size_pretty(pg_total_relation_size(relid)) AS size "
        "FROM pg_catalog.pg_statio_user_tables "
        "ORDER BY pg_total_relation_size(relid) DESC;");

        // main server settings
        printUsage(txn, "Main Server Settings",
        "SELECT name, setting, unit "
        "FROM pg_settings "
        "WHERE name IN ("
        "'max_connections', "
        "'shared_buffers', "
        "'work_mem', "
        "'maintenance_work_mem', "
        "'effective_cache_size', "
        "'max_worker_processes'"
        ");");
        txn.commit();
        conn.close();
    }catch(const std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}