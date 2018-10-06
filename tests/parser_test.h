/*
 * parser_test.h
 *
 *  Created on: Oct 6, 2018
 *      Author: myvaheed
 */

#ifndef PARSER_TEST_H_
#define PARSER_TEST_H_

#include <boost/test/auto_unit_test.hpp>
#include <parser.h>

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(ParserTest)

BOOST_AUTO_TEST_CASE(ParseLine) {
	Parser parser;
	std::vector<std::string> symbs = parser.parse(" 43.4+  x1 -(3* x2 )/(5* 3) ");
	BOOST_REQUIRE(symbs[0] == "43.4");
	BOOST_REQUIRE(symbs[1] == "+");
	BOOST_REQUIRE(symbs[2] == "x1");
	BOOST_REQUIRE(symbs[3] == "-");
	BOOST_REQUIRE(symbs[4] == "(");
	BOOST_REQUIRE(symbs[5] == "3");
	BOOST_REQUIRE(symbs[6] == "*");
	BOOST_REQUIRE(symbs[7] == "x2");
	BOOST_REQUIRE(symbs[8] == ")");
	BOOST_REQUIRE(symbs[9] == "/");
	BOOST_REQUIRE(symbs[10] == "(");
	BOOST_REQUIRE(symbs[11] == "5");
	BOOST_REQUIRE(symbs[12] == "*");
	BOOST_REQUIRE(symbs[13] == "3");
	BOOST_REQUIRE(symbs[14] == ")");
}

BOOST_AUTO_TEST_CASE(ToPostfix) {
	Parser parser;
	std::vector<std::string> symbs = parser.parse("a + b * c (2 - x) + v");
	Queue<std::string> postfixed = parser.to_postfix(symbs);
	BOOST_REQUIRE(postfixed.dequeue() == "a");
	BOOST_REQUIRE(postfixed.dequeue() == "b");
	BOOST_REQUIRE(postfixed.dequeue() == "c");
	BOOST_REQUIRE(postfixed.dequeue() == "2");
	BOOST_REQUIRE(postfixed.dequeue() == "x");
	BOOST_REQUIRE(postfixed.dequeue() == "-");
	BOOST_REQUIRE(postfixed.dequeue() == "*");
	BOOST_REQUIRE(postfixed.dequeue() == "+");
	BOOST_REQUIRE(postfixed.dequeue() == "v");
	BOOST_REQUIRE(postfixed.dequeue() == "+");
}

BOOST_AUTO_TEST_CASE(Evaluation) {
	Parser parser;
	BOOST_REQUIRE(0.5 == parser.evaluate("0.5"));
	BOOST_REQUIRE(6 == parser.evaluate("2 + 4"));
	BOOST_REQUIRE(0 == parser.evaluate("3*2 - (2 + 4)"));
	BOOST_REQUIRE(4 == parser.evaluate("3*2 - (2 + 4) /3"));
}


BOOST_AUTO_TEST_SUITE_END()



#endif /* PARSER_TEST_H_ */
