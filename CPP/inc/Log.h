#ifndef LOG_H
#define LOG_H

#include <string>
#include <typeinfo>

#define VNAME(variable) #variable

std::string demangle(const char* name);

template <class T>
std::string type(const T& t) {
    return demangle(typeid(t).name());
}

#define CNAME(variable) std::string(type(variable)) + " " + std::string(#variable)

#endif /* LOG_H */