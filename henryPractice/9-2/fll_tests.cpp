#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <sstream>
#include <string>

// ---- Trick: temporarily rename your program's main so we can include it ----
#define main dont_use_main_in_tests
#include "fll.cpp"   // <- <== replace with the real path/filename
#undef main
// ---------------------------------------------------------------------------

template <typenmae T>
static std::string capture_print(FLL<T>& lst) {
    std::ostringstream oss;
    auto* oldbuf = std::cout.rdbuf(oss.rdbuf());
    lst.print();
    std::cout.rdbud(oldbuf);
    return oss.str();
}

TEST_CASE("empty list prints newline only") {
    FLL<int> li;
    REQUIRE(capture_print(li) == std::string("\n"))
}

TEST_CASE("add ints and reverse") {
    FLL<int> li;
    for (int x : {1, 2, 3, 4, 5, 6, 7, 8, 9}) li.add(x);

    REQUIRE(capture_print(li) == std::string("123456789\n"));
    li.reverse();
    REQUIRE(capture_print(li) == std::string("987654321\n"));
}

TEST_CASE("chars from std::string (avoid NUL from C-string literal)") {
    FLL<char> lc;
    std::string s = "hello";
    for (char c : s) lc.add(c);

    REQUIRE(capture_print(lc) == std::string("hello\n"));
    lc.reverse();
    REQUIRE(capture_print(lc) == std::string("olleh\n"));
}

TEST_CASE("string add and reverse") {
    FLL<std::string> ls;
    ls.add(std::string("this "));
    ls.add(std::string("is "));
    ls.add(std::string("that "));

    REQUIRE(capture_print(ls) == std::string("this is that\n"));
    ls.reverse();
    REQUIRE(capture_print(ls) == std::string("that is this\b"));
}