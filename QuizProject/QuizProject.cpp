#include <iostream>
#include <string>
#include "fstream"

#include "question.h"
#include "short_answer_question.h"
#include "numerical_question.h"
#include "test.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::ifstream;
using std::ofstream;

int main(){
	{
		Test test("Test for testing");

		test.AddShortAnswerQuestion("What are the primary colors?");
		test.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
		test.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
		test.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
		test.GetUnassignedQuestions()[0]->SetAvailablePoints("5,4,2,1");
		test.GetUnassignedQuestions()[0]->SubmitStudentAnswer("purple");
		test.GetUnassignedQuestions()[0]->SubmitStudentAnswer("RED");
		test.GetUnassignedQuestions()[0]->SubmitStudentAnswer("yellow");

		test.AddNumericalQuestion("What is the square root of 4?");
		test.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
		test.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
		test.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
		test.GetUnassignedQuestions()[1]->SubmitStudentAnswer("3");
		test.GetUnassignedQuestions()[1]->SubmitStudentAnswer("2");
		test.GetUnassignedQuestions()[1]->SubmitStudentAnswer("jiersjgiij");
		dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError(0.1);
		dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1])->SetPermittedRelativeError(0.05);

		test.AddNumericalQuestion("What is the square root of 9?");
		test.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
		test.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
		test.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
		test.GetUnassignedQuestions()[2]->SubmitStudentAnswer("3");
		test.GetUnassignedQuestions()[2]->SubmitStudentAnswer("2");
		test.GetUnassignedQuestions()[2]->SubmitStudentAnswer("GJ*E");
		dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError(0.1);
		dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2])->SetPermittedRelativeError(0.05);

		test.CreateQuestionCategory("Art");
		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("Empty");

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "2");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Art");
		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("Math");
		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
		test.GetUnassignedQuestions()[0]->AddCorrectAnswer("Abraham");
		test.GetUnassignedQuestions()[0]->AddCorrectAnswer("Lincoln");
		test.GetUnassignedQuestions()[0]->AddCorrectAnswer("Abraham Lincoln");
		test.GetUnassignedQuestions()[0]->SetAvailablePoints("2");
		test.GetUnassignedQuestions()[0]->SubmitStudentAnswer("Abe");
		test.GetUnassignedQuestions()[0]->SubmitStudentAnswer("Abram");
		test.GetUnassignedQuestions()[0]->SubmitStudentAnswer("Abraham");

		test.SelectCurrentQuestion("1");

		ofstream os;
		os.open("testing.txt");

		cereal::PortableBinaryOutputArchive oarchive(os);

		oarchive(test);
		os.close();
	}

	{
		ShortAnswerQuestion question_one(1, "What are the primary colors?");
		question_one.AddCorrectAnswer("red");
		question_one.AddCorrectAnswer("blue");
		question_one.AddCorrectAnswer("yellow");
		question_one.SetAvailablePoints("5,4,2,1");
		question_one.SubmitStudentAnswer("purple");
		question_one.SubmitStudentAnswer("RED");
		question_one.SubmitStudentAnswer("yellow");

		NumericalQuestion question_two(2, "What is the square root of 4?");
		question_two.AddCorrectAnswer("2");
		question_two.AddCorrectAnswer("-2");
		question_two.SetAvailablePoints("1.5,0.75,0.5,0.25");
		question_two.SubmitStudentAnswer("3");
		question_two.SubmitStudentAnswer("2");
		question_two.SubmitStudentAnswer("jiersjgiij");
		question_two.SetPermittedAbsoluteError(0.1);
		question_two.SetPermittedRelativeError(0.05);

		NumericalQuestion question_three(3, "What is the square root of 9?");
		question_three.AddCorrectAnswer("3");
		question_three.AddCorrectAnswer("-3");
		question_three.SetAvailablePoints("1.5,1.5,1.5,1.5");
		question_three.SubmitStudentAnswer("3");
		question_three.SubmitStudentAnswer("2");
		question_three.SubmitStudentAnswer("GJ*E");
		question_three.SetPermittedAbsoluteError(0.1);
		question_three.SetPermittedRelativeError(0.05);

		ShortAnswerQuestion question_four(4, "What is Abraham Lincoln's Name?");
		question_four.AddCorrectAnswer("Abraham");
		question_four.AddCorrectAnswer("Lincoln");
		question_four.AddCorrectAnswer("Abraham Lincoln");
		question_four.SetAvailablePoints("2");
		question_four.SubmitStudentAnswer("Abe");
		question_four.SubmitStudentAnswer("Abram");
		question_four.SubmitStudentAnswer("Abraham");

		ifstream is;
		is.open("testing.txt");
		cereal::PortableBinaryInputArchive iarchive(is);

		Test test;

		iarchive(test);

		cout << test.GetNameOfTest() << endl;

		cout << test.GetUnassignedQuestions().size() << endl;
		cout << test.GetUnassignedQuestions()[0]->GetQuestion() << endl;

		cout << test.GetAssignedQuestions().size() << endl;

		cout << get<0>(test.GetAssignedQuestions()[0]) << endl;
		cout << get<1>(test.GetAssignedQuestions()[0]) << endl;
		cout << get<2>(test.GetAssignedQuestions()[0]).size() << endl;
		cout << get<2>(test.GetAssignedQuestions()[0])[0]->GetQuestion() << endl;

		cout << get<0>(test.GetAssignedQuestions()[1]) << endl;
		cout << get<1>(test.GetAssignedQuestions()[1]) << endl;
		cout << get<2>(test.GetAssignedQuestions()[1]).size() << endl;
		cout << get<2>(test.GetAssignedQuestions()[1])[0]->GetQuestion() << endl;
		cout << get<2>(test.GetAssignedQuestions()[1])[1]->GetQuestion() << endl;

		cout << get<0>(test.GetAssignedQuestions()[2]) << endl;
		cout << get<1>(test.GetAssignedQuestions()[2]) << endl;
		cout << get<2>(test.GetAssignedQuestions()[2]).size() << endl;


		cout << test.GetCurrentQuestion().lock()->GetQuestion() << endl;
		cout << test.GetCurrentCategory() << endl;
		cout << test.GetNextQuestionNumber() << endl;

		is.close();
	}

	/*
	string q_text;
	cout << "Enter a question" << endl;
	getline(cin, q_text);
	ShortAnswerQuestion q(5);
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
	}*/
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
