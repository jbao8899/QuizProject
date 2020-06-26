#pragma once

#include <string>

using std::string;

//A struct used as a key by the unordered_map storing questions in the test class. It contains an integer question_index, a string question_label,
// and overloaded == and != operators. If two QuestionKey structs have the same question_index, the same question_label, or both, then they are considered equal.
struct QuestionKey {
public:
	int    question_index;
	string question_label;

	QuestionKey(int set_question_index, string set_question_label);

	bool operator==(const QuestionKey& other) const;
	bool operator!=(const QuestionKey& other) const;
};