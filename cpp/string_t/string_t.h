#ifndef __STRING_T_H__
#define __STRING_T_H__

#include <iostream> // ostream 
using namespace std; //ostream

#define BUFFER_SIZE 256

class String_t
{
	private: 
		char* 			m_str; 										// the string
		unsigned int 	m_capacity;									// the actual capacity of the string
				
		static bool 		s_caseSens;								// static member for the sensitivity of upper case and lower case or not
		static unsigned int s_capacity;								// static member of the initial capacity of string can be change by setter
		
		char* CreateFrom(const char* _str);							// create m_str from char*
		char* ConvertSring(int(*_f)(int)); 							// go over every letters of the string and invoke _f
		char* ExtendString(const char* _str1, int _flag); 			// add char* to the string at the begining or the end according to the flag
		void* operatornew(size_t _size);  

	public:
		//CTOR & DCTOR
		String_t(); 												// default ctor
		String_t(const char* _str);									// constructor from
		String_t(const String_t& _str);								// copy constructor
		~String_t();												// DCTOR

		// OPERATOR
		String_t& 	operator=(const String_t& _str);  				// assignement operator
		String_t& 	operator+=(const String_t& _str); 				// add string at the end of the string
		String_t& 	operator+=(const char* _str); 					// add char* at the end of the string
		bool 		operator<(const String_t& _str) const;			// check if the string is smaller than another string 
		bool 		operator>(const String_t& _str) const;			// check if the string is bigger than another string 
		bool 		operator<=(const String_t& _str) const;			// check if the string is smaller equal than another string
		bool 		operator>=(const String_t& _str) const; 		// check if the string is bigger equal than another string 
		bool 		operator==(const String_t& _str) const; 		// check if two strings are equal
		bool 		operator!=(const String_t& _str) const; 		// check if two strings are differente
		char& 		operator[](unsigned int _index) ; 				// change the _indexth letter
		const char& operator[](size_t _index)const;					// return the i
		String_t 	operator()(int _start, unsigned int _len) const;// return the substring from the _Start for _len char warning if he have overhead return ""
		
		//FUNCTIONS
		int 				Length() const; 						// return the length of the string
		int 				Compare(const String_t& _str) const; 	// give the length of str
		void 				SetString(const char* _str); 			// set the string 
		inline void 		Print() const; 							// return the size of the string
		bool 				Contains(const String_t& _str) const; 	// check if string is substring of the object	
		String_t&			UpperCases();							// change every letters of the string to upper cases
		String_t&			LowerCases();							// change every letters of the string to lower cases
		String_t&			Prepend(const char* _str);				// add char * to the begining of string 
		String_t&			Prepend(const String_t& _str); 			// add string to the begining of string 
		inline const char* 	GetString() const;						// return the char *
		int 				PosFirstOcc(char _letter) const;		// return the index of first occurence of a letter and -1 if doesnt exist
		int  				PosLastOcc(char _letter) const;			// return the index of last occurence of a letter and -1 if doesnt exist

		//STATIC FUNCTIONS(GETTERS//SETTERS) 
		static bool 		IsCaseSens() { return s_caseSens;}		// return case sensitive or not
		static bool 		SetCaseSens(bool _flag) ;				// set the case sens
		static unsigned int GetCapacity() { return s_capacity;}		// get the initial capacity of strings
		static unsigned int SetCapacity(unsigned int _capacity);	// set the initial capacity of strings

};

ostream& operator<<(ostream& _os, const String_t& _str);			//tostring
istream& operator>>(istream& _is, String_t _str);					// get info about string from user.Warning max size is 256

inline void 		String_t::Print() const 	{ cout << m_str;}
inline const char* 	String_t::GetString() const { return m_str;}

#endif /*__STRING_T_H__*/
