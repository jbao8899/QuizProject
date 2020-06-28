#pragma once

#include <memory>
#include <queue>
#include <utility>

#include "numerical_question.h"
#include "short_answer_question.h"

using std::make_shared;
using std::shared_ptr;
using std::tuple;
using std::weak_ptr;

class Test {
private:
	string name_of_test_;

	// All the Questions that have been created, but which have not been removed or assigned.
	vector<shared_ptr<Question>> unassigned_questions_;

	//A vector containing tuples of strings, ints, and vectors of shared_ptrs to Questions that have been assigned
	//The string is just a label for the sub-vector contained within the tuple
	//If the int is negative, then all of the Questions in the corresponding sub-vector will be given in the order they were pushed
	//If the int is positive and has value n, then we will give out n random Questions from that sub-vector
	vector<tuple<string, int, vector<shared_ptr<Question>>>> assigned_questions_;

	//The current question being viewed by the test maker or the test taker
	weak_ptr<Question> current_question_;

	//The number of the next question.
	int next_question_number_;
public:
	//Creates a new Question with question_text_ equal to set_question_text,
	//adds it to unassigned_questions_, and sets it as the current_question_
	//Its question_number_ will be next_question_number_, and next_question_number_ will be incremented by 1.
	void AddQuestion(string set_question_text);

	//Pushes a new tuple containing a string (category_name), the integer -1, and an empty vector of shared_ptrs to Questions
	//to the vector assigned_questions_. If a tuple containing category_name as its string already exists, then nothing
	//will be done.
	void CreateQuestionCategory(string category_name);

	//If no tuple within assigned_questions_ contains the string category_name, nothing will happen.
	//Otherwise, we will push shared_ptrs of all Questions within that tuple's vector into unassigned_questions_ and then pop that tuple
	//from assigned_questions_
	void DeleteQuestionCategory(string category_name);

	//If there is no tuple within assigned_questions_ entitled category_name, nothing will happen.
	//If there is one entitled category_name (with category_name as its string),
	//then we will set the int in that tuple to number_of_questions (turned to int via stoi).
	//If number_of_questions is not a vald int, then nothing will be done.
	void ChangeNumberOfQuestionsToAskFromCategory(string category_name, string number_of_questions);

	//We will iterate through assigned_questions_ to search for a category (tuple) with a string value of category_name.
	//if this is not found, then nothing will happen.
	//If the current_question_ is already within the tuple with a string value of category_name, then nothing will be done.
	//If the current_question_ is within unassigned_questions, then a shared_ptr referring to it will be pushed to the vector within
	//the tuple with a string value of category_name, and then it will be popped from unassigned_questions.
	//If the current_question_ is within the vector of one of the tuples within assigned_questions_, and category_name_ is not the string
	//stored in that tuple, then a shared_ptr referring to it will be pushed to the vector within
	//the tuple with a string value of category_name, and then it will be popped from its vector within assigned_questions_
	//If current_question_ does not refer to a Question object, then nothing will be done
	void AddCurrentQuestionToCategory(string category_name);

	//If current_question_ refers to nothing, then nothing is done.
	//Otherwise, we look for it in unassigned_questions_ and assigned_questions_, and pop it out of the vectors that it is in
	void DeleteCurrentQuestion();
};