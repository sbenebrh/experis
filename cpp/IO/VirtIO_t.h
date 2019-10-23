#ifndef __VIRTIO_T_H__
#define __VIRTIO_T_H__

#include<string>
#include <cstdio>
using namespace std;
class VirtIO_t
{//TODO: check file ==
public:
 enum File_status
    {
        ok_e, 
		cant_open_file_e, 
		bad_access_e,
		writeErr_e,
        readErr_e
    };
                              VirtIO_t():m_file(NULL), m_fileName(""), m_status(bad_access_e){};                                                // default CTOR
    virtual                   ~VirtIO_t(){fclose(m_file);}                                 // DCTOR (pure virtual)
                              VirtIO_t(const string& _path,const string& _mod) ;           // CTOR from 

    const   string&           GetFileName() const               { return m_fileName;}
    const   string&           GetAccess() const                 { return m_mod;}
    const   size_t            GetLength() ;
            size_t            GetPosition() const               { if(m_file == NULL){throw string("not opened file");} return ftell(m_file);}
            File_status       GetStatus()const                  { return m_status;}

            void              SetPosition(size_t _position)     { if(m_file == NULL){throw string("not opened file");} if(GetLength() >= _position)fseek(m_file, _position, SEEK_SET); }

            void              open(const string& _path, const string& _mod);              // if the default ctor was used, invoke open to open the file
            void              MoveTobegin()                     { if(m_file == NULL){throw string("not opened file");} fseek(m_file, 0, SEEK_SET);}
            void              Close()                           { if(m_file == NULL){throw string("not opened file");} fclose(m_file); m_status = bad_access_e; m_file = NULL;}

    virtual VirtIO_t&       operator<<(int _value)           = 0;
    virtual VirtIO_t&       operator<<(unsigned int _value)  = 0;
    virtual VirtIO_t&       operator<<(char _value)          = 0;
    virtual VirtIO_t&       operator<<(unsigned char _value) = 0;
    virtual VirtIO_t&       operator<<(short _value)         = 0; 
    virtual VirtIO_t&       operator<<(unsigned short _value)= 0; 
    virtual VirtIO_t&       operator<<(long _value)          = 0;
    virtual VirtIO_t&       operator<<(unsigned long _value) = 0; 
    virtual VirtIO_t&       operator<<(float _value)         = 0;
    virtual VirtIO_t&       operator<<(double _value)        = 0;
     
    virtual VirtIO_t&       operator>>(int& _value)          = 0; 
    virtual VirtIO_t&       operator>>(unsigned int& _value) = 0; 
    virtual VirtIO_t&       operator>>(double& _value)       = 0;    
    virtual VirtIO_t&       operator>>(float& _value)        = 0;
    virtual VirtIO_t&       operator>>(long& _value)         = 0;
    virtual VirtIO_t&       operator>>(unsigned long& _value)= 0;
    virtual VirtIO_t&       operator>>(short& _value)        = 0;
    virtual VirtIO_t&       operator>>(unsigned short& _value)= 0;
    virtual VirtIO_t&       operator>>(char& _value)         = 0;
    virtual VirtIO_t&       operator>>(unsigned char& _value)= 0;


protected:

            void            SetStatus(File_status _status)      { m_status = _status;}       
            FILE*           GetFILE() const                     { return m_file;}
            void            CheckWriteMode()  ; //throw exception
            void            CheckReadMode(); //throw exception            
private:
    string m_fileName;
    string m_mod;
    FILE* m_file;
    File_status m_status;

                            VirtIO_t(const VirtIO_t& _virtIO);                              // COPY CTOR
        VirtIO_t&           operator=(const VirtIO_t& _virtIO);                             // operator assignement
   
};








#endif //__VIRTIO_T_H__