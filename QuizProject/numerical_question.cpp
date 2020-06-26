#include "pch.h"
#include "numerical_question.h"

NumericalQuestion::NumericalQuestion() {
	question_text = "";
	current_score = 0.0;
	permitted_absolute_error = 0.0;
	permitted_relative_error = 0.0;
}

NumericalQuestion::NumericalQuestion(string set_question) {
	question_text = set_question;
	current_score = 0.0;
	permitted_absolute_error = 0.0;
	permitted_relative_error = 0.0;
}

void NumericalQuestion::SetPermittedAbsoluteError(double set_permitted_absolute_error) {
	permitted_absolute_error = set_permitted_absolute_error;
}

double NumericalQuestion::GetPermittedAbsoluteError() const {
	return permitted_absolute_error;
}

void NumericalQuestion::SetPermittedRelativeError(double set_permitted_relative_error) {
	permitted_relative_error = set_permitted_relative_error;
}

double NumericalQuestion::GetPermittedRelativeError() const {
	return permitted_relative_error;
}

void NumericalQuestion::AddCorrectAnswer(string to_add) {
	//Checking that to_add is a decimal number
	for (unsigned i = 0; i < to_add.length(); i++) {
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

	correct_answers.push_back(to_add);
}

bool NumericalQuestion::SubmitStudentAnswer(string answer) {
	bool answer_was_correct = false;

	//Checking that answer is a decimal number. If it is not, return false (they answered question wrong)
	for (unsigned i = 0; i < answer.length(); i++) {
		if (!isdigit(answer[i]) && answer[i] != '.' && answer[i] != '-') {
			student_answers.push_back(pair<string, bool>(answer, answer_was_correct));
			return answer_was_correct;
		}
		if (answer[i] == '-' && i != 0) {
			student_answers.push_back(pair<string, bool>(answer, answer_was_correct));
			return answer_was_correct;
		}
	}
	if (count(answer.begin(), answer.end(), '.') > 1 || answer.length() == 0 || answer == "-") {
		student_answers.push_back(pair<string, bool>(answer, answer_was_correct));
		return answer_was_correct;
	}

	bool absolute_error_matters = true;
	if (permitted_absolute_error < 0) {
		absolute_error_matters = false;
	}

	bool relative_error_matters = true;
	if (permitted_relative_error < 0) {
		relative_error_matters = false;
	}

	double answer_as_double = stod(answer);

	for (unsigned i = 0; i < correct_answers.size(); i++) {
		//if your answer equals one of the correct answers exactly, then you got the question right.
		if (answer == correct_answers[i]) {
			answer_was_correct = true;
			break;
		}

		//If you do not care about absolute error or if your absolute error does not exceed the permitted_absolute_error
		// and if you do not care about relative error or if your relative error does not exceed the permitted_relative_error,
		// then you got the question right.
		if ((!absolute_error_matters || abs(stod(correct_answers[i]) - answer_as_double)  <= permitted_absolute_error)
			&& (!relative_error_matters || abs(stod(correct_answers[i]) - answer_as_double) / abs(stod(correct_answers[i])) <= permitted_relative_error)) {
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