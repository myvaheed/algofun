/*
 * parser.h
 *
 *  Created on: Oct 6, 2018
 *      Author: myvaheed
 */

#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <string>
#include <vector>
#include <queue.h>

class InvalidInfixExpression : public std::runtime_error {
public:
	InvalidInfixExpression() : std::runtime_error("Invalid infix expression is entered") {}
};
class InvalidPostfixExpression : public std::runtime_error {
public:
	InvalidPostfixExpression() : std::runtime_error("Invalid postfix expression is entered") {}
};

using std::string;

class Parser {

	struct SPEC_CHARS {
		static const char PLUS = '+';
		static const char MINUS = '-';
		static const char PRODUCT = '*';
		static const char DEVIDE = '/';
		static const char L_PARANTH = '(';
		static const char R_PARANTH = ')';
		static bool isSpec(const char ch) {

			if (
					ch == PLUS ||
					ch == MINUS ||
					ch == PRODUCT ||
					ch == DEVIDE ||
					ch == L_PARANTH ||
					ch == R_PARANTH
				)
				return true;
			return false;
		};
	};

public:
	Queue<string> to_postfix(std::vector<string> parsed);

	std::vector<string> parse(string const& line);
	double evaluate(string const& line);
};




#endif /* INCLUDE_PARSER_H_ */
