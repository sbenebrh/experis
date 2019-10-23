#ifndef IPARSER_H
#define IPARSER_H

#include <vector>

namespace smartHome
{

class ConfigurationAgent;

class IParser
{
public:
    virtual std::vector<ConfigurationAgent> Parse() = 0;

};

}

#endif
