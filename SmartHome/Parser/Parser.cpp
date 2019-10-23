#include "Parser.h"

#include <libconfig.h++>
#include <cassert>
#include <iostream>

#include "ConfigurationAgent.h"

using namespace libconfig;

namespace smartHome
{

Parser::Parser(const std::string& filepath)
: m_filePath(filepath)
{
}

std::vector<ConfigurationAgent> Parser::Parse()
{
    std::vector<ConfigurationAgent> configs;

    Config cfg;
    try
    {
        cfg.readFile(m_filePath.c_str());
    }
    catch(std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        assert(false and "impossible to open configfile");
    }

    const Setting& root = cfg.getRoot();
    const Setting& agents = root["agentsList"]["agents"];

    
    std::string name, type,room, floor, log,  config; 
    int count = agents.getLength();
    for(int i = 0; i < count ;++i)
    {
        const Setting& agent = agents[i];
        try
        {
            agent.lookupValue("name",name);
        }
        catch(const std::exception& e)
        {
            name = "default_name";
        }

        try
		{
			agent.lookupValue("type",type);
		}
		catch(const std::exception& e)
		{
			continue;
		}
        try
		{
			agent.lookupValue("floor",floor);
		}
		catch(const std::exception& e)
		{
    		floor = "Default_floor";
		}

		try
		{
			agent.lookupValue("room",room);
		}
		catch(const std::exception& e)
		{
    		room = "Default_room";
		}

        try
		{
			agent.lookupValue("log",log);
		}
		catch(const std::exception& e)
		{
    		log = "./security_log.txt";
		}

        try
		{
			agent.lookupValue("config",config);
		}
		catch(const std::exception& e)
		{
    		
		}
        unordered_map<std::string, std::string> temp = configMap(config);
        ConfigurationAgent config(name, type, room, floor,log, temp);
        configs.push_back(config);
    }
    return configs;

}

unordered_map<std::string, std::string> Parser::configMap(const std::string&)
{
    unordered_map<std::string , std::string> result;
    return result;
}


}