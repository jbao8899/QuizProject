#pragma once
#include "question.h"
class NumericalQuestion : public Question {
private:
	//If the absolute error of the student's answer (|correct_answer - student answer|) exceeds this value,
	//then their answer is wrong. If this value is negative, then it will not be checked.
	double permitted_absolute_error;

	//If the relative error of the student's answer (|correct_answer - student answer| / |correct_answer|)
	//exceeds this value, then their answer is wrong. If this value is negative, then it will not be checked.
	double permitted_relative_error;

public:
	//Create a NumericalQuestion object with a question_text of "", an empty deque for available_points
	// empty vectors for correct_answers and student answers, a current score of 0,
	// and 0 permitted_absolute_error and 0 permitted_relative_error
	NumericalQuestion();

	//Create a NumericalQuestion object with a question_text of set_question, an empty deque for available_points
	// empty vectors for correct_answers and student answers, a current score of 0,
	// and 0 permitted_absolute_error and 0 permitted_relative_error
	NumericalQuestion(string set_question);

	//Changes the permitted_absolute_error to set_permitted_absolute_error
	void SetPermittedAbsoluteError(double set_permitted_absolute_error);

	//Returns the current permitted_absolute_error
	double GetPermittedAbsoluteError() const;

	//Changes the permitted_relative_error to set_permitted_relative_error
	void SetPermittedRelativeError(double set_permitted_relative_error);

	//Returns the current permitted_relative_error
	double GetPermittedRelativeError() const;
};