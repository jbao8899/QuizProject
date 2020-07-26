#include <iostream>
#include <string>
#include "fstream"

#include "question.h"
#include "short_answer_question.h"
#include "numerical_question.h"
#include "test_for_instructor.h"
#include "test_for_student.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ios;
using std::string;
using std::ifstream;
using std::ofstream;

//TestForStudent class. Question done function.

int main(){
	{
		TestForInstructor test_for_instructor("Test for testing");

		test_for_instructor.CreateQuestionCategory("First");
		test_for_instructor.CreateQuestionCategory("Empty");
		test_for_instructor.CreateQuestionCategory("Third");

		test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
		test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
		test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
		test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
		test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");
		test_for_instructor.GetUnassignedQuestions()[0]->SubmitStudentAnswer("purple");
		test_for_instructor.GetUnassignedQuestions()[0]->SubmitStudentAnswer("RED");
		test_for_instructor.GetUnassignedQuestions()[0]->SubmitStudentAnswer("yellow");

		test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
		test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
		test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
		test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
		dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
		dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");
		test_for_instructor.GetUnassignedQuestions()[1]->SubmitStudentAnswer("3");
		test_for_instructor.GetUnassignedQuestions()[1]->SubmitStudentAnswer("2");
		test_for_instructor.GetUnassignedQuestions()[1]->SubmitStudentAnswer("jiersjgiij");

		test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
		test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
		test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
		test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
		dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
		dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");
		test_for_instructor.GetUnassignedQuestions()[2]->SubmitStudentAnswer("3");
		test_for_instructor.GetUnassignedQuestions()[2]->SubmitStudentAnswer("2");
		test_for_instructor.GetUnassignedQuestions()[2]->SubmitStudentAnswer("GJ*E");

		test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
		test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
		test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
		test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
		test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");
		test_for_instructor.GetUnassignedQuestions()[3]->SubmitStudentAnswer("Abe");
		test_for_instructor.GetUnassignedQuestions()[3]->SubmitStudentAnswer("Abram");
		test_for_instructor.GetUnassignedQuestions()[3]->SubmitStudentAnswer("Abraham");

		test_for_instructor.SelectCurrentQuestion("1");
		test_for_instructor.AddCurrentQuestionToCategory("First");
		test_for_instructor.SelectCurrentQuestion("2");
		test_for_instructor.AddCurrentQuestionToCategory("First");
		test_for_instructor.SelectCurrentQuestion("3");
		test_for_instructor.AddCurrentQuestionToCategory("First");
		test_for_instructor.SelectCurrentQuestion("4");
		test_for_instructor.AddCurrentQuestionToCategory("Third");

		TestForStudent test_for_student(test_for_instructor);
		test_for_student.ChangeIfOrderOfQuestionsIsFixed();
		test_for_student.SetIndexOfCurrentQuestion("2");

		ofstream os("data.dat", ios::binary);

		cereal::PortableBinaryOutputArchive oarchive(os);

		oarchive(test_for_student);
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
		question_two.SetPermittedAbsoluteError("0.1");
		question_two.SetPermittedRelativeError("0.05");
		question_two.SubmitStudentAnswer("3");
		question_two.SubmitStudentAnswer("2");
		question_two.SubmitStudentAnswer("jiersjgiij");

		NumericalQuestion question_three(3, "What is the square root of 9?");
		question_three.AddCorrectAnswer("3");
		question_three.AddCorrectAnswer("-3");
		question_three.SetAvailablePoints("1.5,1.5,1.5,1.5");
		question_three.SetPermittedAbsoluteError("0.1");
		question_three.SetPermittedRelativeError("0.05");
		question_three.SubmitStudentAnswer("3");
		question_three.SubmitStudentAnswer("2");
		question_three.SubmitStudentAnswer("GJ*E");

		ShortAnswerQuestion question_four(4, "What is Abraham Lincoln's Name?");
		question_four.AddCorrectAnswer("Abraham");
		question_four.AddCorrectAnswer("Lincoln");
		question_four.AddCorrectAnswer("Abraham Lincoln");
		question_four.SetAvailablePoints("2");
		question_four.SubmitStudentAnswer("Abe");
		question_four.SubmitStudentAnswer("Abram");
		question_four.SubmitStudentAnswer("Abraham");

		ifstream is("data.dat", ios::binary);
		cereal::PortableBinaryInputArchive iarchive(is);

		TestForStudent test_for_student;

		iarchive(test_for_student);

		is.close();

		//Assert::AreEqual(test_for_student.GetNameOfTest(), (string)"Test for testing");
		//Assert::AreEqual(test_for_student.GetMaxPossibleScore(), 6.5);
		//Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)2);
		//Assert::IsFalse(test_for_student.IsOrderOfQuestionsFixed());

		//Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[0]) == question_one);
		//Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[1]) == question_two);
		//Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[1]) == question_three);
		//Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[0]) == question_four);
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
