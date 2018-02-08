#ifndef H_SERIAL
#define H_SERIAL

#include <stdlib.h>
#include <cxxabi.h>

bool demangle(const char* mangledName, std::string& realName) {
    int status = 0;
    char* s = abi::__cxa_demangle(mangledName, NULL, 0, &status);
    realName = (status == 0) ? s : mangledName;
    free(s);
    return status;
}

#endif