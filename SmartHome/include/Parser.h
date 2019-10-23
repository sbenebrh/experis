#ifndef PARSER_H
#define PARSER_H


#include "CommonRefs.h"
#include "IParser.h"
namespace smartHome
{

class Parser:public IParser
{
public:
    Parser(const std::string& filepath);

private:
    virtual std::vector<ConfigurationAgent> Parse();
    unordered_map<std::string, std::string> configMap(const std::string&);

private:
    std::string m_filePath;
};

}


#endif
