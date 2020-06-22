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
