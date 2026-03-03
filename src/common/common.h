#include <iostream>
#include <string>
#include <vector>

class ipAddress {
    std::string ip;
public:
    ipAddress(std::string ip) : ip(ip) {}
    void setip(ipAddress& other) {
        ip = other.ip;
    }
    std::string getip() const {
        return ip;
    }
};