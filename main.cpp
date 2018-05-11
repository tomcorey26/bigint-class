
#include "catch/catch.hpp"
#include "bigint/bigint.h"
#include <sstream>
#include <fstream>

using std::string;

typedef std::vector<vec_bin> vec;

//TEST_CASE("Displaying scientific", "[methods]") {
//   SECTION("scientific()"){
//    bigint x2 = std::string("1234567891011121314151617181920");
//    REQUIRE(x2.scientific() == std::string("1.234E30");
//  }
//}

TEST_CASE("Constructors", "[constructors]") {
    SECTION("Default") {
        bigint x = 0;
        REQUIRE(x.getNumber() == vec{0});
    }
    SECTION("String") {
      bigint x("0");
      REQUIRE(x.getNumber() == vec{0});

      x = bigint("00012300"); // 12300
      REQUIRE(x.getNumber() == vec{0,0,3,2,1});
    }
}


//TEST_CASE("Displaying Bigints", "[display]") {

    //SECTION("to_string()") {
//        std::ostringstream oss;
//        bigint x = 12345;
//        oss << x;
//        REQUIRE(oss.str() == std::string("12,345"));
//    }
//}


TEST_CASE("Comparators", "[compare]") {
  SECTION("compare"){
    bigint i = 12;
    bigint g = 10;
    bigint l = 2;
    bigint z = g.pow(3);
    bigint j = i.pow(2);
    bigint u = l.pow(0);
    REQUIRE(z.getNumber()==vec{0,0,0,1});
    REQUIRE(j.getNumber()==vec{4,4,1});
    REQUIRE(u.getNumber()==vec{1});
  }

}

TEST_CASE("Arithmetic", "[math]") {
    SECTION("Division") {
        bigint x = 10;
        bigint y = 11;
        bigint z = x % y;
        REQUIRE(z.getNumber() == vec{0,1});
   }
}


//TEST_CASE("Arithmetic", "[math]") {
//    SECTION("Subtraction") {
//        bigint x = 2;
//        x.pow(2);
        //bigint z = x-y;
//        REQUIRE(x.getNumber() == vec{7,1,5});
//   }
//}



//TEST_CASE("Operators", "[operators]") {

//}
