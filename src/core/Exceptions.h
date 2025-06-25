#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

class CapacityException : public std::runtime_error {
public:
    CapacityException(const std::string& message) : std::runtime_error(message) {}
};

#endif // EXCEPTIONS_H
