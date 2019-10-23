
#include "String.h"
#include "mu_test.h"
#include <iostream>
#include<cstring>

UNIT(create_def_obj)
advcpp::String<char> s;
ASSERT_THAT(s.Size() == 0);
END_UNIT

UNIT(create_obj_from_char)
advcpp::String<char> s("hello world!!");
ASSERT_THAT(s.Size() == strlen("hello world!!"));
END_UNIT

UNIT(create_obj_from_obj)
advcpp::String<char> s1("hello world!!");
advcpp::String<char> s2(s1);
ASSERT_THAT(s1.Size() == s2.Size());
END_UNIT

UNIT(test_cpy_assign)
advcpp::String<char> s1("hello world!!");
advcpp::String<char> s2;
advcpp::String<char> s3;
s3 = s2 = s1;
std::cout << s3 << std::endl;
std::cout << s1 << std::endl;
ASSERT_THAT(s1.Size() == s3.Size());
ASSERT_THAT(s1 == s3);
END_UNIT


UNIT(test_cpy_assign_char)
advcpp::String<char> s1("hello world!!");
s1 = "hi";
ASSERT_THAT(s1.Size() == strlen("hi"));
END_UNIT

UNIT(test_concat)
advcpp::String<char> s1("hello");
advcpp::String<char> s2(" world!!");
s1 += s2;
ASSERT_EQUAL_INT(s1.Size(), strlen("hello world!!"));
ASSERT_EQUAL_INT(s1[4] , 'o');
ASSERT_THAT(s1[10] == 'd');
END_UNIT

UNIT(test_equal)
advcpp::String<char> s1("hello");
advcpp::String<char> s2("hello" );

ASSERT_THAT(s1==s1);
ASSERT_THAT(s1 == s2);
END_UNIT


UNIT(test_not_equal)
advcpp::String<char> s1("hello");
advcpp::String<char> s2("world" );
advcpp::String<char> s3("helloworld" );
ASSERT_THAT(s1 != s2);
s1+=s2;
ASSERT_THAT(s1==s3);
s3 = s2;
s1 = s2;
ASSERT_THAT(s1==s3);
END_UNIT

UNIT(test_operator_less)
advcpp::String<char> s1("hello");
advcpp::String<char> s2("world" );
advcpp::String<char> s3("hello!!!" );
ASSERT_THAT(s1 != s2);
ASSERT_THAT(s1<s2);
ASSERT_THAT(s1 < s3);
std::cout << s1 << " "<< s2 << " "<< s3 << std::endl;
END_UNIT

UNIT(test_wchar)
advcpp::String<wchar_t> s1(L"hello");
advcpp::String<wchar_t> s2(L"world" );
advcpp::String<wchar_t> s3(L"hello!!!" );
ASSERT_THAT(s1 != s2);
ASSERT_THAT(s1<s2);
ASSERT_THAT(s1 < s3);
ASSERT_THAT(s1 == L"hello");
std::wcout << s1 << L" "<< s2 << L" "<< s3 << std::endl;
END_UNIT

UNIT(test_concat_char)
advcpp::String<char> s1("hello");
s1 += " world!!";
ASSERT_THAT(s1.Size() == strlen("hello world!!"));
END_UNIT


UNIT(test_opSub)
const advcpp::String<char> s1("hello");
char c =s1[1];
ASSERT_THAT(c == 'e');
END_UNIT


UNIT(test_opSub2)
advcpp::String<char> s1("hello");
advcpp::String<char> s2("hallo");
s1[1] = 'a';
std::cout << s1 <<std::endl;
ASSERT_THAT(s1 == s2);
ASSERT_THAT(s1 == "hallo");
END_UNIT

UNIT(test_Add2)
advcpp::String<char> s1("hello");
advcpp::String<char> s3;
s3 = s1 + " world";
std::cout << s3<< std::endl;
ASSERT_THAT(s3 == "hello world");
END_UNIT

TEST_SUITE(c++ unitest string)
    TEST(create_def_obj)
    TEST(create_obj_from_char)
    TEST(create_obj_from_obj)
    TEST(test_cpy_assign)
    TEST(test_cpy_assign_char)
    TEST(test_concat)
    TEST(test_equal)
    TEST(test_not_equal)
    TEST(test_operator_less)
    TEST(test_wchar)
    TEST(test_concat_char)
    TEST(test_opSub)
    TEST(test_opSub2)
    //IGNORE_TEST(test_opequal)
//    IGNORE_TEST(test_opequal2)
//    IGNORE_TEST(test_Add)
    TEST(test_Add2)
//    IGNORE_TEST(test_not_equal)

END_SUITE



