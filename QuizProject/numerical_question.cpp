//#include "pch.h"
#include "numerical_question.h"

NumericalQuestion::NumericalQuestion(int set_question_number) {
	question_text_ = "";
	current_score_ = 0.0;
	max_permitted_absolute_error_ = 0.0;
	max_permitted_relative_error_ = 0.0;
	max_possible_score_ = 0.0;
	question_number_ = set_question_number;
}

NumericalQuestion::NumericalQuestion(int set_question_number, string set_question) {
	question_text_ = set_question;
	current_score_ = 0.0;
	max_permitted_absolute_error_ = 0.0;
	max_permitted_relative_error_ = 0.0;
	max_possible_score_ = 0.0;
	question_number_ = set_question_number;
}

void NumericalQuestion::SetPermittedAbsoluteError(double set_permitted_absolute_error) {
	max_permitted_absolute_error_ = set_permitted_absolute_error;
}

double NumericalQuestion::GetPermittedAbsoluteError() const {
	return max_permitted_absolute_error_;
}

void NumericalQuestion::SetPermittedRelativeError(double set_permitted_relative_error) {
	max_permitted_relative_error_ = set_permitted_relative_error;
}

double NumericalQuestion::GetPermittedRelativeError() const {
	return max_permitted_relative_error_;
}

void NumericalQuestion::AddCorrectAnswer(string to_add) {
	//Checking that to_add is a decimal number
	for (unsigned i = 0; i < to_add.length(); ++i) {
		if (!isdigit(to_add[i]) && to_add[i] != '.' && to_add[i] != '-') {
			return;
		}
		if (to_add[i] == '-' && i != 0) {
			return;
		}
	}
	if (count(to_add.begin(), to_add.end(), '.') > 1 || to_add.length() == 0 || to_add == "-") {
		return;
	}

	correct_answers_.push_back(to_add);
}

bool NumericalQuestion::SubmitStudentAnswer(string answer) {
	bool answer_was_correct = false;

	//Checking that answer is a decimal number. If it is not, return false (they answered question wrong)
	for (unsigned i = 0; i < answer.length(); ++i) {
		if (!isdigit(answer[i]) && answer[i] != '.' && answer[i] != '-') {
			student_answers_.push_back(pair<string, bool>(answer, answer_was_correct));
			return answer_was_correct;
		}
		if (answer[i] == '-' && i != 0) {
			student_answers_.push_back(pair<string, bool>(answer, answer_was_correct));
			return answer_was_correct;
		}
	}
	if (count(answer.begin(), answer.end(), '.') > 1 || answer.length() == 0 || answer == "-") {
		student_answers_.push_back(pair<string, bool>(answer, answer_was_correct));
		return answer_was_correct;
	}

	bool absolute_error_matters = true;
	if (max_permitted_absolute_error_ < 0) {
		absolute_error_matters = false;
	}

	bool relative_error_matters = true;
	if (max_permitted_relative_error_ < 0) {
		relative_error_matters = false;
	}

	double answer_as_double = stod(answer);

	for (unsigned i = 0; i < correct_answers_.size(); ++i) {
		//if your answer equals one of the correct answers exactly, then you got the question right.
		if (answer == correct_answers_[i]) {
			answer_was_correct = true;
			break;
		}

		//If you do not care about absolute error or if your absolute error does not exceed the max_permitted_absolute_error_
		// and if you do not care about relative error or if your relative error does not exceed the max_permitted_relative_error_,
		// then you got the question right.
		if ((!absolute_error_matters || abs(stod(correct_answers_[i]) - answer_as_double)  <= max_permitted_absolute_error_)
			&& (!relative_error_matters || abs(stod(correct_answers_[i]) - answer_as_double) / abs(stod(correct_answers_[i])) <= max_permitted_relative_error_)) {
			answer_was_correct = true;
			break;
		}
	}

	if (answer_was_correct && !available_points_.empty() && available_points_[0] > current_score_) {
		current_score_ = available_points_[0];
	}
	if (!available_points_.empty()) {
		available_points_.pop_front();
	}

	student_answers_.push_back(pair<string, bool>(answer, answer_was_correct));
	return answer_was_correct;
}

bool NumericalQuestion::operator==(const NumericalQuestion& other) const {
	if (question_text_ != other.question_text_
		|| current_score_ != other.current_score_
		|| max_possible_score_ != other.max_possible_score_
		|| question_number_ != other.question_number_
		|| max_permitted_absolute_error_ != other.max_permitted_absolute_error_
		|| max_permitted_relative_error_ != other.max_permitted_relative_error_) {
		return false;
	}

	if (available_points_.size() != other.available_points_.size()) {
		return false;
	}
	for (unsigned i = 0; i < available_points_.size(); i++) {
		if (available_points_[i] != other.available_points_[i]) {
			return false;
		}
	}

	if (correct_answers_.size() != other.correct_answers_.size()) {
		return false;
	}
	for (unsigned i = 0; i < correct_answers_.size(); i++) {
		if (correct_answers_[i] != other.correct_answers_[i]) {
			return false;
		}
	}

	if (student_answers_.size() != other.student_answers_.size()) {
		return false;
	}
	for (unsigned i = 0; i < student_answers_.size(); i++) {
		if (student_answers_[i] != other.student_answers_[i]) {
			return false;
		}
	}

	return true;
}

bool NumericalQuestion::operator!=(const NumericalQuestion& other) const {
	return (!(*this == other));
}