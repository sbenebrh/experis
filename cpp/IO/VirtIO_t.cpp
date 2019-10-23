#include "VirtIO_t.h"
#include <string>


VirtIO_t::VirtIO_t(const string& _path,const string& _mod): m_fileName(_path), m_mod(_mod)
{
    m_file = fopen(m_fileName.c_str(), m_mod.c_str());
    m_status = (m_file == NULL ? cant_open_file_e: ok_e);
}

const size_t  VirtIO_t::GetLength()
{
    int current = ftell(m_file);
    if(current < 0)
    {
        m_status = bad_access_e;
        return 0;
    }
    fseek(m_file, 0,SEEK_END);
    size_t length = ftell(m_file);
    fseek(m_file, current, SEEK_SET); 
    return length;
}


void VirtIO_t::open(const string& _path, const string& _mod)
{
    m_file = fopen(_path.c_str(), _mod.c_str());
    m_status = (m_file == NULL ? cant_open_file_e: ok_e);
}

void VirtIO_t::CheckWriteMode() 
{
    if(m_file == NULL || GetAccess() == "r" || GetAccess() == "rb")
    {
        SetStatus(writeErr_e);
        throw string("read only");
    }
}

void VirtIO_t::CheckReadMode() 
{
    if(m_file == NULL || GetAccess() == "w" || GetAccess() == "Wb" || GetAccess() == "a" || GetAccess() == "ab")
    {
        SetStatus(readErr_e);
        throw string("write only");
    }
}