#include "short_answer_question.h"

ShortAnswerQuestion::ShortAnswerQuestion() {

}

ShortAnswerQuestion::ShortAnswerQuestion(int set_question_number) {
	question_text_ = "";
	current_score_ = 0.0;
	max_possible_score_ = 0.0;
	question_number_ = set_question_number;
}

ShortAnswerQuestion::ShortAnswerQuestion(int set_question_number, string set_question) {
	question_text_ = set_question;
	current_score_ = 0.0;
	max_possible_score_ = 0.0;
	question_number_ = set_question_number;
}

bool ShortAnswerQuestion::SubmitStudentAnswer(string answer) {
	bool answer_was_correct = false;

	//https://notfaq.wordpress.com/2007/08/04/cc-convert-string-to-upperlower-case/
	std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

	for (unsigned i = 0; i < correct_answers_.size(); ++i) {
		string lower_case_correct_answer = correct_answers_[i];
		std::transform(lower_case_correct_answer.begin(), lower_case_correct_answer.end(), lower_case_correct_answer.begin(), ::tolower);

		if (answer == lower_case_correct_answer) {
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

bool ShortAnswerQuestion::operator==(const ShortAnswerQuestion& other) const {
	if (question_text_ != other.question_text_
		|| current_score_ != other.current_score_
		|| max_possible_score_ != other.max_possible_score_
		|| question_number_ != other.question_number_) {
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

bool ShortAnswerQuestion::operator!=(const ShortAnswerQuestion& other) const {
	return (!(*this == other));
}