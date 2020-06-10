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

//TODO: RENAME TESTS!

class Question {
private:
	string                     question_text;
	deque<double>			   available_points;
	vector<string>             correct_answers;
	vector<pair<string, bool>> student_answers; //string is what the student inputted, bool is if they got it correct
	double                     current_score;
public:
	//Create a question object with a question_text of "" and empty vectors for correct answers and student answers 
	Question();

	//Creates a question object with a question_text of set_question and empty vectors for correct answers and student answers 
	Question(string set_question);

	//Changes the question_text to set_question
	void                              SetQuestion(string set_question);

	//Returns the current question_text
	string                            GetQuestion() const;

	//Adds to_add to the vector containing correct answers
	void                              AddCorrectAnswer(string to_add);

	//Removes to_remove from the vector containing the correct answers. If it is not in that vector, nothing will be done
	void                              RemoveCorrectAnswer(string to_remove);

	//Clears the vector containing correct answers
	void                              ClearCorrectAnswers();

	//Returns a constant reference to the vector of correct answers
	const vector<string>&             GetCorrectAnswers() const;

	//Used when the student submits an answer. Looks through the vector of correct answers, and if their answer is right,
	//true is returned, and if it is wrong, false is returned. In either case, we save their answer, along with whether it
	//was right or not
	bool                              SubmitStudentAnswer(string answer);

	//Returns a constant reference to the vector containing all student answers,
	//as well as bools indicating if they were right or not
	const vector<pair<string, bool>>& GetStudentAnswers();

	//Clears the vector containing all student answers and bools indicating if they were right or not.
	void                              ClearStudentAnswers();

	//Takes a string of numbers separated by commas, with the first number being the score the student
	//can receive by getting the question right on their first try, the second being the score they can get 
	//for getting it right on the second try, and so forth, and savees these availalble points in a vector.
	//Clears previous available points vector, if not empty.
	//If there are 2 or more commas in a row,  if the string is just a single comma, or if 
	//the string contains any characters besides digits and commas, then clear the vector and return.
	void							  SetAvailablePoints(string available_points_string);

	//Returns a constant reference to the vector of available points
	const deque<double>&             GetAvailablePoints();

	//Returns the current score
	double                            GetCurrentScore();
};