#include <thread>

namespace preparation
{

class Aknowledge
{

public:
    Aknowledge(std::thread::id id);
    void sendAck() const ;
    void waitForAck() const;

private:
    std::thread::id m_idthread;
};
}