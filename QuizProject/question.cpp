#include "pch.h"
#include "question.h"

void Question::SetQuestion(string set_question) {
	question_text = set_question;
}

string Question::GetQuestion() const {
	return question_text;
}

void Question::AddCorrectAnswer(string to_add) {
	correct_answers.push_back(to_add);
}

void Question::RemoveCorrectAnswer(string to_remove) {
	if (find(correct_answers.begin(), correct_answers.end(), to_remove) != correct_answers.end()) {
		correct_answers.erase(std::remove(correct_answers.begin(), correct_answers.end(), to_remove), correct_answers.end());
	}
}

void Question::ClearStudentAnswers() {
	student_answers.clear();
}

const vector<string>& Question::GetCorrectAnswers() const {
	return correct_answers;
}

bool Question::SubmitStudentAnswer(string answer) {
	bool answer_was_correct = false;
	for (unsigned i = 0; i < correct_answers.size(); ++i) {
		if (answer == correct_answers[i]) {
			answer_was_correct = true;
			break;
		}
	}

	if (answer_was_correct && !available_points.empty() && available_points[0] > current_score) {
		current_score = available_points[0];
	}
	if (!available_points.empty()) {
		available_points.pop_front();
	}

	student_answers.push_back(pair<string, bool>(answer, answer_was_correct));
	return answer_was_correct;
}

const vector<pair<string, bool>>& Question::GetStudentAnswers() {
	return student_answers;
}

void Question::ClearCorrectAnswers() {
	correct_answers.clear();
}

void Question::SetAvailablePoints(string available_points_string) {
	available_points.clear();

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
				available_points.clear();
				return;
			}
			available_points.push_back(stod(num));
			break;
		}
		else {
			string num = available_points_string.substr(0, comma_location);
			if (count(num.begin(), num.end(), '.') > 1) {
				available_points.clear();
				return;
			}
			available_points_string = available_points_string.substr(comma_location + 1);
			available_points.push_back(stod(num));
		}
	}
}

const deque<double>& Question::GetAvailablePoints() {
	return available_points;
}

double Question::GetCurrentScore() {
	return current_score;
}