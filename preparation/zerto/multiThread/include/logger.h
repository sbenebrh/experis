#ifndef LOGGER_H
#define LOGGER_H


#include <tr1/memory>
#include <istream>

#include "NonCopyable.h"

namespace preparation
{

class Logger:advcpp::NonCopyable
{
public:
    static std::tr1::shared_ptr<Logger> GetInstance(const std::istream& ifstm);

    void SyncLog(const std::string & message) const;
    void AsyncLog(const std::string & message) const;

private:
    Logger(const std::istream&);

private:
    const std::istream& m_whereToWrite;
    static std::tr1::shared_ptr<Logger>  m_logger ;
    /*TODO need pointer to the waitable queue */

};
}

#endif