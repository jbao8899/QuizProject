// QuizProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "question.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

int main()
{	
	string q_text;
	cout << "Enter a question" << endl;
	getline(cin, q_text);
	Question q;
	q.SetQuestion(q_text);
	cout << "Enter some answers" << endl;
	while (true) {
		string a;
		getline(cin, a);
		if (a == "") {
			break;
		}
		else {
			q.AddCorrectAnswer(a);
		}
	}
	cout << q.GetQuestion() << endl;
	const vector<string>& answers = q.GetCorrectAnswers();
	for (unsigned i = 0; i < answers.size(); ++i) {
		cout << answers[i] << endl;
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
