#pragma once

#include <algorithm>
#include <cmath>
#include <deque>
#include <string>
#include <utility>
#include <vector>

using std::abs;
using std::count;
using std::deque;
using std::find;
using std::pair;
using std::string;
using std::vector;

class Question {
protected:
	string                     question_text_;
	deque<double>			   available_points_;
	vector<string>             correct_answers_;
	vector<pair<string, bool>> student_answers_; //string is what the student inputted, bool is if they got it correct
	double                     current_score_;
	double                     max_possible_score_; //The maximum value set in the available_points_ deque.
	int					       question_number_;
public:
	//Changes the question_text_ to set_question
	virtual void                              SetQuestion(string set_question);

	//Returns the current question_text_
	virtual string                            GetQuestion() const;

	//Adds to_add to the vector containing correct answers
	virtual void                              AddCorrectAnswer(string to_add);

	//Returns a constant reference to the vector of correct answers
	virtual const vector<string>&             GetCorrectAnswers() const;

	//Removes to_remove from the vector containing the correct answers. If it is not in that vector, nothing will be done
	virtual void                              RemoveCorrectAnswer(string to_remove);

	//Clears the vector containing correct answers
	virtual void                              ClearCorrectAnswers();

	//Used when the student submits an answer. Looks through the vector of correct answers, and if their answer is right,
	//true is returned, and if it is wrong, false is returned. In either case, we save their answer, along with whether it
	//was right or not
	virtual bool                              SubmitStudentAnswer(string answer);

	//Returns a constant reference to the vector containing all student answers,
	//as well as bools indicating if they were right or not
	virtual const vector<pair<string, bool>>& GetStudentAnswers();

	//Clears the vector containing all student answers and bools indicating if they were right or not.
	virtual void                              ClearStudentAnswers();

	//Takes a string of numbers separated by commas, with the first number being the score the student
	//can receive by getting the question right on their first try, the second being the score they can get 
	//for getting it right on the second try, and so forth, and savees these availalble points in a vector.
	//Clears previous available points vector, if not empty.
	//If there are 2 or more commas in a row,  if the string is just a single comma, or if 
	//the string contains any characters besides digits,periods, and commas, then clear the vector and return.
	//If the numbers are not in descending order (any number in the string is strictly less than the next one), then
	//clear the vector and return.
	//Also clear the vector and return if there are 2 or more periods in any of the numbers.
	virtual void                              SetAvailablePoints(string available_points_string);

	//Returns a constant reference to the vector of available points
	virtual const deque<double>&              GetAvailablePoints();

	//Returns the current_score_
	virtual double                            GetCurrentScore();

	//Returns the max_possible_score_
	virtual double                            GetMaxPossibleScore();

	//Returns the question_number_.
	virtual int                               GetQuestionNumber();
};