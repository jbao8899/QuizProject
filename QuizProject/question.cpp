#include "pch.h"
#include "question.h"

void Question::SetQuestion(string set_question) {
	question_text_ = set_question;
}

string Question::GetQuestion() const {
	return question_text_;
}

void Question::AddCorrectAnswer(string to_add) {
	correct_answers_.push_back(to_add);
}

void Question::RemoveCorrectAnswer(string to_remove) {
	if (find(correct_answers_.begin(), correct_answers_.end(), to_remove) != correct_answers_.end()) {
		correct_answers_.erase(std::remove(correct_answers_.begin(), correct_answers_.end(), to_remove), correct_answers_.end());
	}
}

void Question::ClearStudentAnswers() {
	student_answers_.clear();
}

const vector<string>& Question::GetCorrectAnswers() const {
	return correct_answers_;
}

bool Question::SubmitStudentAnswer(string answer) {
	bool answer_was_correct = false;
	for (unsigned i = 0; i < correct_answers_.size(); ++i) {
		if (answer == correct_answers_[i]) {
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

const vector<pair<string, bool>>& Question::GetStudentAnswers() {
	return student_answers_;
}

void Question::ClearCorrectAnswers() {
	correct_answers_.clear();
}

void Question::SetAvailablePoints(string available_points_string) {
	available_points_.clear();

	if (available_points_string == ""
		|| available_points_string == ","
		|| available_points_string.find(",,") != std::string::npos) {
		return;
	}

	for (unsigned i = 0; i < available_points_string.length(); ++i) {
		if (available_points_string[i] == ' '
			|| (!isdigit(available_points_string[i])
				&& available_points_string[i] != ','
				&& available_points_string[i] != '.')) {
			return;
		}
	}

	while (true) {
		size_t comma_location = available_points_string.find(",");
		if (comma_location == string::npos) {
			string num = available_points_string;
			if (count(num.begin(), num.end(), '.') > 1) {
				available_points_.clear();
				return;
			}
			available_points_.push_back(stod(num));
			break;
		}
		else {
			string num = available_points_string.substr(0, comma_location);
			if (count(num.begin(), num.end(), '.') > 1) {
				available_points_.clear();
				return;
			}
			available_points_string = available_points_string.substr(comma_location + 1);
			available_points_.push_back(stod(num));
		}
	}
}

const deque<double>& Question::GetAvailablePoints() {
	return available_points_;
}

double Question::GetCurrentScore() {
	return current_score_;
}