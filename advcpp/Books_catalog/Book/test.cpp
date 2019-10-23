#include "mu_test.h"

#include "Book.h"
#include "Author.h"
#include "Publisher.h"


#include <tr1/memory>

using advcpp::Author;
using advcpp::Book;
using advcpp::Publisher;

using std::tr1::shared_ptr;

const int isbn = 12345;
const std::string title = "test";
const int year = 1990;
shared_ptr<advcpp::Author> auth(new Author("james colins"));
shared_ptr<advcpp::Publisher> publi(new Publisher("Galian"));

UNIT(test_Book1)

Book b(isbn, title, auth, year, publi);
ASSERT_THAT(b.GetISBN() == isbn);
ASSERT_THAT(b.GetTitle() == title);
ASSERT_THAT(auth.use_count() == 2);
END_UNIT

UNIT(test_Book2)

Book b(isbn, title, auth, year, publi);
Book c(isbn, title, auth, year, publi);
ASSERT_THAT(b.GetISBN() == isbn);
ASSERT_THAT(b.GetTitle() == title);
ASSERT_THAT(auth.use_count() == 3);
ASSERT_THAT(b == c);

END_UNIT

TEST_SUITE(book unitest )
    TEST(test_Book1)
    TEST(test_Book2)
END_SUITE