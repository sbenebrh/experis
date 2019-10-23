
#include <istream>
#include <fstream>

#include "mu_test.h"
#include "Parser.h"
std::ifstream is("/home/samuel/Downloads/books-tiny.txt");
advcpp::Parser p(is, "|");

UNIT(test_parser_creation)

ASSERT_THAT(advcpp::Parser::NumberOfLine() == 0);
std::tr1::unordered_map<std::string, std::string> m = p.nextBookRecord();
m = p.nextBookRecord();
ASSERT_THAT(m["ISBN"] == "195153448");
END_UNIT


UNIT(test_parser)

ASSERT_THAT(advcpp::Parser::NumberOfLine() == 2);
std::tr1::unordered_map<std::string, std::string> m = p.nextBookRecord();
while(!m.empty())
{
    m = p.nextBookRecord(); 
}

ASSERT_EQUAL_INT(advcpp::Parser::NumberOfLine() , 15);
END_UNIT

TEST_SUITE(parser test)
    TEST(test_parser_creation)
    TEST(test_parser)
END_SUITE
