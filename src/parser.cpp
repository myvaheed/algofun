/*
 * parser.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: myvaheed
 */

#include <parser.h>
#include <stack.h>

using std::string;
using std::vector;

vector<string> Parser::parse(string const& line) {
	vector<string> symbs;

	bool wasSpace = false;
	bool wasSpec = true; //beginning

	for (auto ch : line) {
		if (ch == ' ') {
			wasSpace = true;
			wasSpec = false;
			continue;
		}
		if (SPEC_CHARS::isSpec(ch)) {
			wasSpec = true;
			wasSpace = false;
			symbs.push_back(string(1, ch));
			continue;
		} else {

			if (wasSpace || wasSpec) {
				symbs.push_back(string(1, ch));
			} else
				symbs.back() = symbs.back() + ch;

		}
		wasSpace = false;
		wasSpec = false;
	}

	return std::move(symbs);
}

Queue<string> Parser::to_postfix(vector<string> parsed) {
	Queue<string> postfixed;
	Queue<string> infix;

	// $ - a special symbol to indicate begin/end of the expression
	const char IND = '$';

	parsed.insert(parsed.begin(), string(1, IND));
	parsed.push_back(string(1, IND));

	for (auto elem : parsed)
		infix.enqueue(std::move(elem));

	Stack<string> stack;
	stack.push(infix.dequeue());

	while (!infix.is_empty()) {

		const char top = vector<char>(stack.top().c_str(),
				stack.top().c_str() + stack.top().size() + 1)[0];
		const char next = vector<char>(infix.front().c_str(),
				infix.front().c_str() + infix.front().size() + 1)[0];

		if (!SPEC_CHARS::isSpec(next) && next != IND) {
			postfixed.enqueue(infix.dequeue());
			continue;
		}

		if (top == IND) {
			if (next == SPEC_CHARS::R_PARANTH)
				throw InvalidInfixExpression();

			if (next == IND)
				//IT IS ALL
				infix.dequeue(); //to exit
			else
				stack.push(infix.dequeue());

		} else if (top == SPEC_CHARS::PLUS || top == SPEC_CHARS::MINUS) {

			if (next == SPEC_CHARS::PRODUCT || next == SPEC_CHARS::DEVIDE
					|| next == SPEC_CHARS::L_PARANTH)
				stack.push(infix.dequeue());
			else
				postfixed.enqueue(stack.pop());

		} else if (top == SPEC_CHARS::PRODUCT || top == SPEC_CHARS::DEVIDE) {

			if (next == SPEC_CHARS::L_PARANTH)
				stack.push(infix.dequeue());
			else
				postfixed.enqueue(stack.pop());

		} else if (top == SPEC_CHARS::L_PARANTH) {

			if (next == IND)
				throw InvalidInfixExpression();

			if (next == SPEC_CHARS::R_PARANTH) {
				stack.pop();
				infix.dequeue();
			} else
				stack.push(infix.dequeue());

		}
	}

	return std::move(postfixed);
}

//https://en.wikipedia.org/wiki/Reverse_Polish_notation
double Parser::evaluate(string const& line) {

	Stack<string> RPN;
	Queue<string> postfixed = to_postfix(parse(line));

	double result;

	while (!postfixed.is_empty()) {

		const char next = vector<char>(postfixed.front().c_str(),
				postfixed.front().c_str() + postfixed.front().size() + 1)[0];

		if (!SPEC_CHARS::isSpec(next))
			RPN.push(postfixed.dequeue());
		else {
			try {
				string right = RPN.pop();
				string left = RPN.pop();
				double r = std::stod(right);
				double l = std::stod(left);

				const char op = next;
				postfixed.dequeue();

				if (op == SPEC_CHARS::PLUS)
					result = l + r;
				if (op == SPEC_CHARS::PRODUCT)
					result = l * r;
				if (op == SPEC_CHARS::MINUS)
					result = l - r;
				if (op == SPEC_CHARS::DEVIDE)
					result = l / r;

				RPN.push(std::to_string(result));
			} catch (std::invalid_argument&) {
				throw std::runtime_error(
						"Can not evaluate expressions with variable");
			} catch (std::length_error&) {
				throw InvalidPostfixExpression();
			}
		}
	}
	return std::stod(RPN.pop());
}

