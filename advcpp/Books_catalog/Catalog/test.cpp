#include "Catalog.h"
#include "Book.h"
#include "mu_test.h"


UNIT(test_insert_catalog)
advcpp::Catalog cat;
cat.insert(12345, "hello is new", 1990, "john collins", "galia");
END_UNIT

UNIT(test_get_isbn)
advcpp::Catalog cat;
cat.insert(12345, "hello is new", 1990, "john collins", "galia");
std::tr1::shared_ptr<advcpp::Book> pBook = cat.GetBook(12345);
ASSERT_THAT(pBook -> GetAuthor() ->GetName() == "john collins");
ASSERT_EQUAL_INT(pBook.use_count() , 5);
END_UNIT



TEST_SUITE(catalog unitest)
    TEST(test_insert_catalog)
    TEST(test_get_isbn)
END_SUITE