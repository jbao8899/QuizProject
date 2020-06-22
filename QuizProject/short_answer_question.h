#pragma once
#include "question.h"

using std::transform;

class ShortAnswerQuestion : public Question {
public:
	//Create a ShortAnswerQuestion object with a question_text of "", an empty deque for available_points
	// empty vectors for correct_answers and student answers, and a current score of 0
	ShortAnswerQuestion();

	//Create a ShortAnswerQuestion object with a question_text of set_question, an empty deque for
	// available_points empty vectors for correct_answers and student answers, and a current score of 0
	ShortAnswerQuestion(string set_question);

	//Used when the student submits an answer. Looks through the vector of correct answers, and if their answer is right,
	//true is returned, and if it is wrong, false is returned. In either case, we save their answer, along with whether it
	//was right or not
	//Does not care about case (ex: If "George Washington" is a correct answer, then the student will get points for
	//submitting "george washington"
	bool                              SubmitStudentAnswer(string answer);
};