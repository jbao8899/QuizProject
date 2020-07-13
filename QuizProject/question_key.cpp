//#include "pch.h"
#include "question_key.h"

QuestionKey::QuestionKey(int set_question_index, string set_question_label) {
	question_index = set_question_index;
	question_label = set_question_label;
}

bool QuestionKey::operator==(const QuestionKey& other) const {
	if (question_index == other.question_index || question_label == other.question_label) {
		return true;
	}
	else {
		return false;
	}
}

bool QuestionKey::operator!=(const QuestionKey& other) const {
	return !(*this == other);
}