#include "pch.h"
#include "short_answer_question.h"

ShortAnswerQuestion::ShortAnswerQuestion() {
	question_text_ = "";
	current_score_ = 0.0;
}

ShortAnswerQuestion::ShortAnswerQuestion(string set_question) {
	question_text_ = set_question;
	current_score_ = 0.0;
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