#include "Buffer.h"
#include "mu_test.h"

class Cat{
public:
	Cat() { ++n;}
	Cat(Cat const&) {++n;++c;}
	Cat& operator=(Cat const&) {++g; return *this;}
	~Cat() {--n;}

	static int n;
	static int c;
    static int g;
//	static int v[];
};



int Cat::g = 0;
int Cat::n = 0;
int Cat::c = 0;
//int Cat::v[4];


UNIT(Buffer_MemFunc_Test)

	ASSERT_THAT(Cat::n == 0);
	Cat kat;
	{
		advcpp::Buffer<Cat> buf(100);
        
		ASSERT_THAT(Cat::n == 1);
		buf.Put(kat, 0);
		ASSERT_THAT(Cat::c == 1);
		ASSERT_THAT(Cat::n == 2);
	}

	ASSERT_EQUAL_INT(Cat::n, 1);

END_UNIT

UNIT(Buffer_assignement_test)

	ASSERT_EQUAL_INT(Cat::n, 0);
	
	{   
        Cat::c = 0;
		advcpp::Buffer<Cat> buf(100);
        Cat kat;
		ASSERT_THAT(Cat::n == 1);
		buf.Put(kat, 0);
		ASSERT_THAT(Cat::c == 1);
		ASSERT_THAT(Cat::n == 2);
        advcpp::Buffer<Cat> buf2(80);
        ASSERT_THAT(Cat::n == 2);
        buf2 = buf;
        ASSERT_THAT(Cat::n == 3);
	}

	ASSERT_EQUAL_INT(Cat::n, 0);

END_UNIT

UNIT(Buffer_duplicate_put_test)

	ASSERT_EQUAL_INT(Cat::n, 0);
	
	{   
        Cat::c = 0;
		advcpp::Buffer<Cat> buf(100);
        Cat kat;
		ASSERT_THAT(Cat::n == 1);
		buf.Put(kat, 0);
        ASSERT_THAT(Cat::n == 2);
        try
        {
            buf.Put(kat,0);
        }
        catch(const std::exception& e)
        {

        }
        
		ASSERT_THAT(Cat::c == 1);
		ASSERT_EQUAL_INT(Cat::n , 2);
	}

	ASSERT_EQUAL_INT(Cat::n, 0);

END_UNIT

UNIT(Buffer_get_test)

	ASSERT_EQUAL_INT(Cat::n, 0);
	
	{   
        Cat::c = 0;
		advcpp::Buffer<Cat> buf(100);
        Cat kat;
        Cat kat2;
		ASSERT_THAT(Cat::n == 2);
		buf.Put(kat, 0);
        ASSERT_THAT(Cat::n == 3);
        kat2 = buf.Get(0);
		ASSERT_THAT(Cat::c == 1);
		ASSERT_EQUAL_INT(Cat::n , 3);
        ASSERT_EQUAL_INT(Cat::g ,2);

	}

	ASSERT_EQUAL_INT(Cat::n, 0);

END_UNIT

UNIT(Buffer_grow_test)

	ASSERT_EQUAL_INT(Cat::n, 0);
	
	{   
        Cat::c = 0;
		advcpp::Buffer<Cat> buf(100);
        Cat kat;
        
		ASSERT_THAT(Cat::n == 1);
		buf.Put(kat, 0);
        ASSERT_THAT(Cat::n == 2);
        buf.Grow(2);
        ASSERT_EQUAL_INT(buf.Capacity() ,102);
		ASSERT_EQUAL_INT(Cat::n , 2);
        
	}

	ASSERT_EQUAL_INT(Cat::n, 0);

END_UNIT

template<typename T>
void fillBuffWithCat(advcpp::Buffer<T>& buff, size_t N)
{
	while(N--)
	{
		buff.Put(T(), N);
	}
}

UNIT(Buffer_shrink_test)
	const int N = 1000;
	advcpp::Buffer<Cat> buf(N);
	ASSERT_THAT(Cat::n == 0);
	fillBuffWithCat<Cat>(buf, N);
	ASSERT_THAT(Cat::n == N);
	buf.Shrink(N/2);
	ASSERT_EQUAL_INT(Cat::n , N/2);
END_UNIT

TEST_SUITE(c++ buffer test)

    TEST(Buffer_MemFunc_Test)
    TEST(Buffer_assignement_test)
    TEST(Buffer_duplicate_put_test)
    TEST(Buffer_get_test)
    TEST(Buffer_grow_test)
	TEST(Buffer_shrink_test)

END_SUITE