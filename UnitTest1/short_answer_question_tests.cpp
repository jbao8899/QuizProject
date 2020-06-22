#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <iostream>
#include <vector>
//Must include .cpp files for some reason once added inheritance
#include "../QuizProject/question.h"
#include "../QuizProject/question.cpp"
#include "../QuizProject/short_answer_question.h"
#include "../QuizProject/short_answer_question.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace shortanswerquestiontests {		
	TEST_CLASS(ShortAnswerQuestionTests) {
	public:
		TEST_METHOD(DefaultConstructor) {
			ShortAnswerQuestion question;
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
		}

		TEST_METHOD(CustomQuestionConstructorEmptyString) {
			ShortAnswerQuestion question("");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
		}

		TEST_METHOD(CustomQuestionConstructorLengthOneString) {
			ShortAnswerQuestion question("a");
			string q_text = "a";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(CustomQuestionConstructor) {
			ShortAnswerQuestion question("8BADF00D");
			string q_text = "8BADF00D";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(GetSetQuestion) {
			ShortAnswerQuestion question;
			question.SetQuestion("Have you ever had a tangerine?");
			string q_text = "Have you ever had a tangerine?";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(GetSetQuestionEmpty) {
			ShortAnswerQuestion question;
			question.SetQuestion("");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
		}

		TEST_METHOD(GetSetQuestionLength1) {
			ShortAnswerQuestion question("Should be gone");
			question.SetQuestion("5");
			string q_text = "5";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(AddGetRemoveAnswersSingleEmptyString) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("");
			string a1 = "";
			vector<string> answers;
			answers.push_back(a1);
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddGetRemoveAnswersThreeAnswers) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("abcdefg");
			question.AddCorrectAnswer("");
			question.AddCorrectAnswer("H0r5eRAD1$h");
			string a1 = "abcdefg";
			string a2 = "";
			string a3 = "H0r5eRAD1$h";
			vector<string> answers;
			answers.push_back(a1);
			answers.push_back(a2);
			answers.push_back(a3);
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddGetRemoveAnswersAddAndRemoveAnswers) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("first");
			question.AddCorrectAnswer("second");
			question.AddCorrectAnswer("removed!");
			question.RemoveCorrectAnswer("removed!");
			question.AddCorrectAnswer("Also removed!");
			question.RemoveCorrectAnswer("Also removed!");
			question.AddCorrectAnswer("done");
			string a1 = "first";
			string a2 = "second";
			string a3 = "done";
			vector<string> answers;
			answers.push_back(a1);
			answers.push_back(a2);
			answers.push_back(a3);
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); i++) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(RemoveAnswerWhenNotThere) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("first");
			string a1 = "first";
			vector<string> answers;
			answers.push_back(a1);
			question.RemoveCorrectAnswer("Nothing happens");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); i++) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(RemoveAnswerWhenNotThereTwo) {
			ShortAnswerQuestion question;
			question.RemoveCorrectAnswer("Nothing happens");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(AnswerQuestionSingleCorrectAnswer) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("first");
			vector<string> answers;
			answers.push_back("first");
			Assert::IsTrue(question.SubmitStudentAnswer("first"));
			Assert::AreEqual(question.GetStudentAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetStudentAnswers().size(); i++) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, answers[i]);
				Assert::IsTrue(question.GetStudentAnswers()[i].second);
			}
		}

		TEST_METHOD(AnswerQuestionMultipleAnswers) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("forth correct");
			question.AddCorrectAnswer("second correct");
			question.AddCorrectAnswer("third correct");
			question.AddCorrectAnswer("first correct");
			pair<string, bool> a1("first correct", true);
			pair<string, bool> a2("second correct", true);
			pair<string, bool> a3("first wrong", false);
			pair<string, bool> a4("second wrong", false);
			pair<string, bool> a5("third correct", true);
			pair<string, bool> a6("", false);
			pair<string, bool> a7(" ", false);
			pair<string, bool> a8("forth correct", true);

			vector<string> answers;
			answers.push_back("first correct");
			answers.push_back("second correct");
			answers.push_back("first wrong");
			answers.push_back("second wrong");
			answers.push_back("third correct");
			answers.push_back("");
			answers.push_back(" ");
			answers.push_back("forth correct");

			Assert::IsTrue(question.SubmitStudentAnswer(answers[0]));
			Assert::IsTrue(question.SubmitStudentAnswer(answers[1]));
			Assert::IsFalse(question.SubmitStudentAnswer(answers[2]));
			Assert::IsFalse(question.SubmitStudentAnswer(answers[3]));
			Assert::IsTrue(question.SubmitStudentAnswer(answers[4]));
			Assert::IsFalse(question.SubmitStudentAnswer(answers[5]));
			Assert::IsFalse(question.SubmitStudentAnswer(answers[6]));
			Assert::IsTrue(question.SubmitStudentAnswer(answers[7]));

			Assert::AreEqual(question.GetStudentAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetStudentAnswers().size(); i++) {
				Assert::AreEqual(answers[i], question.GetStudentAnswers()[i].first);
				if (i == 0 || i == 1 || i == 4 || i == 7) {
					Assert::IsTrue(question.GetStudentAnswers()[i].second);
				}
				else {
					Assert::IsFalse(question.GetStudentAnswers()[i].second);
				}
			}
		}

		TEST_METHOD(ClearCorrectAnswersWhenNoneExist) {
			ShortAnswerQuestion question;
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenSomeExist) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("forth correct");
			question.AddCorrectAnswer("second correct");
			question.AddCorrectAnswer("third correct");
			question.AddCorrectAnswer("first correct");
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswerAndAddNew) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("forth correct");
			question.ClearCorrectAnswers();
			question.AddCorrectAnswer("new answer");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)1);
			Assert::AreEqual(question.GetCorrectAnswers()[0], (string)"new answer");
		}

		TEST_METHOD(ClearStudentAnswerWhenThereAreNone) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersWhenThereAreTwo) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SubmitStudentAnswer("correct");
			question.SubmitStudentAnswer("wrong");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersAndAddNewOne) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SubmitStudentAnswer("correct");
			question.SubmitStudentAnswer("wrong");
			question.ClearStudentAnswers();
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)1);
			Assert::AreEqual(question.GetStudentAnswers()[0].first, (string)"correct");
			Assert::IsTrue(question.GetStudentAnswers()[0].second);
		}

		TEST_METHOD(SetAvailablePointsEmptyString) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		}

		TEST_METHOD(SetAvailablePointsCommaOnly) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints(",");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		}

		TEST_METHOD(SetAvailablePointsDoubleComma) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("5,4,3,2,,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		}

		TEST_METHOD(SetAvailablePointsContainsSpaces) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("10, 8, 6, 4, 2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		}

		TEST_METHOD(SetAvailablePointsContainsLetter) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("5,3,1a");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		}

		TEST_METHOD(SetAvailablePointsContainsSymbol) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("5!,3,2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		}

		TEST_METHOD(SetAvailablePointsOneAttemptAllowed) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)1);
			Assert::AreEqual(question.GetAvailablePoints()[0], 5.0);
		}

		TEST_METHOD(SetAvailablePointsFiveAttemptsAllowed) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("10,10,8,5,3");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)5);
			Assert::AreEqual(question.GetAvailablePoints()[0], 10.0);
			Assert::AreEqual(question.GetAvailablePoints()[1], 10.0);
			Assert::AreEqual(question.GetAvailablePoints()[2], 8.0);
			Assert::AreEqual(question.GetAvailablePoints()[3], 5.0);
			Assert::AreEqual(question.GetAvailablePoints()[4], 3.0);
		}

		TEST_METHOD(SetAvailablePointsDecimalValues) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)4);
			Assert::AreEqual(question.GetAvailablePoints()[0], 1.5);
			Assert::AreEqual(question.GetAvailablePoints()[1], 0.75);
			Assert::AreEqual(question.GetAvailablePoints()[2], 0.5);
			Assert::AreEqual(question.GetAvailablePoints()[3], 0.25);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectFirstTry) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectSecondTry) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5,3");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 3.0);
		}

		TEST_METHOD(AnswerQuestionsPointsZeroPointsRanOutOfTries) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("incorrect");
			question.SubmitStudentAnswer("still not right");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(AnswerQuestionsPointsSubsequentCorrectAnswersDoNotReduceSCore) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.AddCorrectAnswer("Also correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("Also correct");
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectAndIncorrectAnswers) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.AddCorrectAnswer("Also correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("Also correct");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 3.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCaseDoesNotMatter) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("cOrReCt12345^&*()");
			question.SetAvailablePoints("3.5");
			question.SubmitStudentAnswer("CoRrEcT12345^&*()");
			Assert::AreEqual(question.GetCurrentScore(), 3.5);
		}
	};
}