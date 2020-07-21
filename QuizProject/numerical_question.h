#pragma once
#include "question.h"

class NumericalQuestion : public Question {
private:
	//If the absolute error of the student's answer (|correct_answer - student answer|) exceeds this value,
	//then their answer is wrong. If this value is negative, then it will not be checked.
	double max_permitted_absolute_error_ = 0;

	//If the relative error of the student's answer (|correct_answer - student answer| / |correct_answer|)
	//exceeds this value, then their answer is wrong. If this value is negative, then it will not be checked.
	double max_permitted_relative_error_ = 0;

public:
	//Default constructor that sets nothing.
	NumericalQuestion();

	//Create a NumericalQuestion object with a question_text_ of "", an empty deque for available_points_
	// empty vectors for correct_answers_ and student answers, a current score of 0,
	// and 0 max_permitted_absolute_error_ and 0 max_permitted_relative_error_
	NumericalQuestion(int set_question_number);

	//Create a NumericalQuestion object with a question_text_ of set_question, an empty deque for available_points_
	// empty vectors for correct_answers_ and student answers, a current score of 0,
	// and 0 max_permitted_absolute_error_ and 0 max_permitted_relative_error_
	NumericalQuestion(int set_question_number, string set_question);

	//Changes the max_permitted_absolute_error_ to set_permitted_absolute_error (turned into a string).
	//If set_permitted_absolute_error is not a valid decimal number, then nothing will be done.
	void   SetPermittedAbsoluteError(string set_permitted_absolute_error);

	//Returns the current max_permitted_absolute_error_
	double GetPermittedAbsoluteError() const;

	//Changes the max_permitted_relative_error_ to set_permitted_relative_error
	//If set_permitted_relative_error is not a valid decimal number, then nothing will be done.
	void   SetPermittedRelativeError(string set_permitted_relative_error);

	//Returns the current max_permitted_relative_error_
	double GetPermittedRelativeError() const;

	//Adds to_add to the vector containing correct answers.
	// If to_add is not a number, then it is not added to that vector (function returns)
	void   AddCorrectAnswer(string to_add);

	//Used when the student submits an answer. Looks through the vector of correct answers, and if their answer is right,
	//true is returned, and if it is wrong, false is returned. In either case, we save their answer, along with whether it
	//was right or not
	//Any answer which is not a double is wrong.
	//An answer is right if its absolute error (|correct_answer - student answer|) is less than max_permitted_absolute_error_
	//and its relative error  (|correct_answer - student answer| / |correct_answer|) is less than max_permitted_relative_error_
	//If either of those values is negative, it will not be checked. If either is 0, then the student must get the answer exactly right.
	bool   SubmitStudentAnswer(string answer);

	bool   operator==(const NumericalQuestion& other) const;

	bool   operator!=(const NumericalQuestion& other) const;

	template <class Archive>
	void serialize(Archive& ar) {
		ar(cereal::base_class<Question>(this), max_permitted_absolute_error_, max_permitted_relative_error_);
	}
};

CEREAL_REGISTER_TYPE(NumericalQuestion)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Question, NumericalQuestion)