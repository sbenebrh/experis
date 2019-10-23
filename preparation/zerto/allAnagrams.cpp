
#include <iostream>
#include <istream>
#include <bits/stdc++.h> 
#include <algorithm> 

namespace preparation
{



class Print
{
public:

    void operator()(const std::pair<std::string , std::vector<std::string > > & obj )
    {
    
        std::vector<std::string>::const_iterator it = obj.second.begin();
        std::vector<std::string>::const_iterator end = obj.second.end();
        for(;it != end; ++it)
        {
            std::cout << *it << " ";
        }
        std::cout <<std:: endl;
    }
};
void printAnagram(std::string line)
{
    std::stringstream is(line);
    std::string word;
    std::map<std::string, std::vector<std::string> > m;


    while(is>>word)
    {
        std::string sorted_word = word;
        std::sort(sorted_word.begin(), sorted_word.end());
        m[sorted_word].push_back(word);
    }
    
    std::for_each(m.begin(),m.end(),Print());
}
}

int main()
{
    std::string line;
    std::cout<<"please enter a sentence" <<std::endl;
    getline(std::cin,line);
    preparation::printAnagram(line);
}


