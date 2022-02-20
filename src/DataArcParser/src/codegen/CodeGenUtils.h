#ifndef CODE_GEN_UTILS_H_
#define CODE_GEN_UTILS_H_

#include <string>

class CodeGenUtils {
public:
    static std::string AddSuffix(const std::string& base, const std::string& suffix);

    static std::string RemoveSuffix(const std::string & name);
};

#endif