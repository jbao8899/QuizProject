#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <deque>

using std::string;
using std::vector;
using std::pair;
using std::find;
using std::deque;


class ShortAnswerQuestion : public Question {
public:
	//Create a ShortAnswerQuestion object with a question_text of "" and empty vectors for correct answers and student answers 
	ShortAnswerQuestion();

	//Creates a ShortAnswerQuestion object with a question_text of set_question and empty vectors for correct answers and student answers 
	ShortAnswerQuestion(string set_question);

	//Used when the student submits an answer. Looks through the vector of correct answers, and if their answer is right,
	//true is returned, and if it is wrong, false is returned. In either case, we save their answer, along with whether it
	//was right or not
	bool                              SubmitStudentAnswer(string answer);
};