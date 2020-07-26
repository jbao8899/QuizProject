#include "pch.h"
#include "CppUnitTest.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//Must include .cpp files for some reason once added inheritance
#include "../QuizProject/numerical_question.h"
#include "../QuizProject/numerical_question.cpp"
#include "../QuizProject/question.h"
#include "../QuizProject/question.cpp"
#include "../QuizProject/short_answer_question.h"
#include "../QuizProject/short_answer_question.cpp"
#include "../QuizProject/test_for_instructor.h"
#include "../QuizProject/test_for_instructor.cpp"
#include "../QuizProject/test_for_student.h"
#include "../QuizProject/test_for_student.cpp"

//TODO: Implement and test TestForStudent

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::vector;

namespace TestCases {
	TEST_CLASS(ShortAnswerQuestionTests) {
	public:
		TEST_METHOD(DefaultConstructor) {
			ShortAnswerQuestion question;
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 0);
		}

		TEST_METHOD(ConstructorTakingOnlyQuestionNumber) {
			ShortAnswerQuestion question(3);
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 3);
		}

		TEST_METHOD(CustomQuestionConstructorEmptyString) {
			ShortAnswerQuestion question(1111, "");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 1111);
		}

		TEST_METHOD(CustomQuestionConstructorLengthOneString) {
			ShortAnswerQuestion question(0, "a");
			string q_text = "a";
			Assert::AreEqual(question.GetQuestion(), q_text);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 0);
		}

		TEST_METHOD(CustomQuestionConstructor) {
			ShortAnswerQuestion question(-100, "8BADF00D");
			string q_text = "8BADF00D";
			Assert::AreEqual(question.GetQuestion(), q_text);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), -100);
		}

		TEST_METHOD(GetSetQuestion) {
			ShortAnswerQuestion question(1);
			question.SetQuestion("Have you ever had a tangerine?");
			string q_text = "Have you ever had a tangerine?";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(GetSetQuestionEmpty) {
			ShortAnswerQuestion question(1);
			question.SetQuestion("");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
		}

		TEST_METHOD(GetSetQuestionLength1) {
			ShortAnswerQuestion question(328, "Should be gone");
			question.SetQuestion("5");
			string q_text = "5";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(AddGetRemoveAnswersSingleEmptyString) {
			ShortAnswerQuestion question(1);
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
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("abcdefg");
			question.AddCorrectAnswer("");
			question.AddCorrectAnswer("H0r5eRAD1$h");
			vector<string> answers;
			answers.push_back("abcdefg");
			answers.push_back("");
			answers.push_back("H0r5eRAD1$h");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddGetRemoveAnswersAddAndRemoveAnswers) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("first");
			question.AddCorrectAnswer("second");
			question.AddCorrectAnswer("removed!");
			question.RemoveCorrectAnswer("removed!");
			question.AddCorrectAnswer("Also removed!");
			question.RemoveCorrectAnswer("Also removed!");
			question.AddCorrectAnswer("done");
			vector<string> answers;
			answers.push_back("first");
			answers.push_back("second");
			answers.push_back("done");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(RemoveAnswerWhenNotThere) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("first");
			vector<string> answers;
			answers.push_back("first");
			question.RemoveCorrectAnswer("Nothing happens");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(RemoveAnswerWhenNotThereTwo) {
			ShortAnswerQuestion question(1);
			question.RemoveCorrectAnswer("Nothing happens");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenNoneExist) {
			ShortAnswerQuestion question(1);
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenSomeExist) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("forth correct");
			question.AddCorrectAnswer("second correct");
			question.AddCorrectAnswer("third correct");
			question.AddCorrectAnswer("first correct");
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswerAndAddNew) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("forth correct");
			question.ClearCorrectAnswers();
			question.AddCorrectAnswer("new answer");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)1);
			Assert::AreEqual(question.GetCorrectAnswers()[0], (string)"new answer");
		}

		TEST_METHOD(AnswerQuestionSingleCorrectAnswer) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("first");
			vector<string> answers;
			answers.push_back("first");
			Assert::IsTrue(question.SubmitStudentAnswer("first"));
			Assert::AreEqual(question.GetStudentAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetStudentAnswers().size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, answers[i]);
				Assert::IsTrue(question.GetStudentAnswers()[i].second);
			}
		}

		TEST_METHOD(AnswerQuestionMultipleAnswers) {
			ShortAnswerQuestion question(1);
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
			for (unsigned i = 0; i < question.GetStudentAnswers().size(); ++i) {
				Assert::AreEqual(answers[i], question.GetStudentAnswers()[i].first);
				if (i == 0 || i == 1 || i == 4 || i == 7) {
					Assert::IsTrue(question.GetStudentAnswers()[i].second);
				}
				else {
					Assert::IsFalse(question.GetStudentAnswers()[i].second);
				}
			}
		}

		TEST_METHOD(ClearStudentAnswerWhenThereAreNone) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("correct");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersWhenThereAreTwo) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("correct");
			question.SubmitStudentAnswer("correct");
			question.SubmitStudentAnswer("wrong");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersAndAddNewOne) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("correct");
			question.SubmitStudentAnswer("correct");
			question.SubmitStudentAnswer("wrong");
			question.ClearStudentAnswers();
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)1);
			Assert::AreEqual(question.GetStudentAnswers()[0].first, (string)"correct");
			Assert::IsTrue(question.GetStudentAnswers()[0].second);
		}

		TEST_METHOD(FailToSetAvailablePointsEmptyString) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsCommaOnly) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints(",");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsDoubleComma) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("5,4,3,2,,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsContainsSpaces) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("10, 8, 6, 4, 2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsTwoPeriods) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("10, 5.5, 6.2, 4, 2..1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToFailToSetAvailablePointsContainsLetter) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("5,3,1a");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsContainsSymbol) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("5!,3,2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsScoresNotDescendingOrder) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("10,9,8,7,6,7,4,3,2,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsScoresAscendingOrder) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("0.1,0.2,0.3,0.4,0.5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(SetAvailablePointsOneAttemptAllowed) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)1);
			Assert::AreEqual(question.GetAvailablePoints()[0], 5.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 5.0);
		}

		TEST_METHOD(SetAvailablePointsFiveAttemptsAllowed) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("10,10,8,5,3");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)5);
			Assert::AreEqual(question.GetAvailablePoints()[0], 10.0);
			Assert::AreEqual(question.GetAvailablePoints()[1], 10.0);
			Assert::AreEqual(question.GetAvailablePoints()[2], 8.0);
			Assert::AreEqual(question.GetAvailablePoints()[3], 5.0);
			Assert::AreEqual(question.GetAvailablePoints()[4], 3.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 10.0);
		}

		TEST_METHOD(SetAvailablePointsDecimalValues) {
			ShortAnswerQuestion question(1);
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)4);
			Assert::AreEqual(question.GetAvailablePoints()[0], 1.5);
			Assert::AreEqual(question.GetAvailablePoints()[1], 0.75);
			Assert::AreEqual(question.GetAvailablePoints()[2], 0.5);
			Assert::AreEqual(question.GetAvailablePoints()[3], 0.25);
			Assert::AreEqual(question.GetMaxPossibleScore(), 1.5);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectFirstTry) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectSecondTry) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5,3");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 3.0);
		}

		TEST_METHOD(AnswerQuestionsPointsZeroPointsRanOutOfTries) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("incorrect");
			question.SubmitStudentAnswer("still not right");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(AnswerQuestionsPointsSubsequentCorrectAnswersDoNotReduceSCore) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("correct");
			question.AddCorrectAnswer("Also correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("Also correct");
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectAndIncorrectAnswers) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("correct");
			question.AddCorrectAnswer("Also correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("Also correct");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 3.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCaseDoesNotMatter) {
			ShortAnswerQuestion question(1);
			question.AddCorrectAnswer("cOrReCt12345^&*()");
			question.SetAvailablePoints("3.5");
			question.SubmitStudentAnswer("CoRrEcT12345^&*()");
			Assert::AreEqual(question.GetCurrentScore(), 3.5);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentQuestionText) {
			ShortAnswerQuestion first_question(1, "apples");
			ShortAnswerQuestion second_question(1, "oranges");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentQuestionText) {
			ShortAnswerQuestion first_question(1, "apples");
			ShortAnswerQuestion second_question(1, "oranges");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentCurrentScore) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.SetAvailablePoints("12,11,10,8,5,3");
			first_question.AddCorrectAnswer("abc");
			first_question.SubmitStudentAnswer("xyz");
			first_question.SubmitStudentAnswer("abc");
			ShortAnswerQuestion second_question(1, "same");
			second_question.SetAvailablePoints("12,10.5,10,8,5,3");
			second_question.AddCorrectAnswer("abc");
			second_question.SubmitStudentAnswer("xyz");
			second_question.SubmitStudentAnswer("abc");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentCurrentScore) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.SetAvailablePoints("12,11,10,8,5,3");
			first_question.AddCorrectAnswer("abc");
			first_question.SubmitStudentAnswer("xyz");
			first_question.SubmitStudentAnswer("abc");
			ShortAnswerQuestion second_question(1, "same");
			second_question.SetAvailablePoints("12,10.5,10,8,5,3");
			second_question.AddCorrectAnswer("abc");
			second_question.SubmitStudentAnswer("xyz");
			second_question.SubmitStudentAnswer("abc");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentMaxPossibleScore) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.SetAvailablePoints("12,11,10,8,5,3");
			first_question.AddCorrectAnswer("abc");
			first_question.SubmitStudentAnswer("xyz");
			ShortAnswerQuestion second_question(1, "same");
			second_question.SetAvailablePoints("13,11,10,8,5,3");
			second_question.AddCorrectAnswer("abc");
			second_question.SubmitStudentAnswer("xyz");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentMaxPossibleScore) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.SetAvailablePoints("12,11,10,8,5,3");
			first_question.AddCorrectAnswer("abc");
			first_question.SubmitStudentAnswer("xyz");
			ShortAnswerQuestion second_question(1, "same");
			second_question.SetAvailablePoints("13,11,10,8,5,3");
			second_question.AddCorrectAnswer("abc");
			second_question.SubmitStudentAnswer("xyz");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentQuestionNumber) {
			ShortAnswerQuestion first_question(1, "same");
			ShortAnswerQuestion second_question(2, "same");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentQuestionNumber) {
			ShortAnswerQuestion first_question(1, "same");
			ShortAnswerQuestion second_question(2, "same");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthAvailablePointsDeque) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.SetAvailablePoints("5,4,3,2,1");
			ShortAnswerQuestion second_question(1, "same");
			second_question.SetAvailablePoints("5,4,3,2");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthAvailablePointsDeque) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.SetAvailablePoints("5,4,3,2,1");
			ShortAnswerQuestion second_question(1, "same");
			second_question.SetAvailablePoints("5,4,3,2");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentAvailablePointsDeque) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.SetAvailablePoints("5,3,1");
			ShortAnswerQuestion second_question(1, "same");
			second_question.SetAvailablePoints("5,3,0.95");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentAvailablePointsDeque) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.SetAvailablePoints("5,3,1");
			ShortAnswerQuestion second_question(1, "same");
			second_question.SetAvailablePoints("5,3,0.95");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthCorrectAnswersVector) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("a");
			first_question.AddCorrectAnswer("a");
			first_question.AddCorrectAnswer("a");
			ShortAnswerQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("a");
			second_question.AddCorrectAnswer("a");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthCorrectAnswersVector) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("a");
			first_question.AddCorrectAnswer("a");
			first_question.AddCorrectAnswer("a");
			ShortAnswerQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("a");
			second_question.AddCorrectAnswer("a");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentCorrectAnswersVector) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("a");
			first_question.AddCorrectAnswer("b");
			first_question.AddCorrectAnswer("c");
			ShortAnswerQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("aa");
			second_question.AddCorrectAnswer("b");
			second_question.AddCorrectAnswer("c");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentCorrectAnswersVector) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("a");
			first_question.AddCorrectAnswer("b");
			first_question.AddCorrectAnswer("c");
			ShortAnswerQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("aa");
			second_question.AddCorrectAnswer("b");
			second_question.AddCorrectAnswer("c");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthStudentAnswersVector) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("a");
			first_question.SubmitStudentAnswer("a");
			ShortAnswerQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("a");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthStudentAnswersVector) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("a");
			first_question.SubmitStudentAnswer("a");
			ShortAnswerQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("a");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentStudentAnswersVector) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("a");
			first_question.SubmitStudentAnswer("b");
			first_question.SubmitStudentAnswer("a");
			ShortAnswerQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("a");
			second_question.SubmitStudentAnswer("c");
			second_question.SubmitStudentAnswer("a");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentStudentAnswersVector) {
			ShortAnswerQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("a");
			first_question.SubmitStudentAnswer("b");
			first_question.SubmitStudentAnswer("a");
			ShortAnswerQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("a");
			second_question.SubmitStudentAnswer("c");
			second_question.SubmitStudentAnswer("a");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(QuestionSameAsItself) {
			ShortAnswerQuestion question(1, "text");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("foo");
			question.AddCorrectAnswer("bar");
			question.AddCorrectAnswer("foobar");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("foobar");
			Assert::IsTrue(question == question);
		}

		TEST_METHOD(QuestionNotDifferentFromItself) {
			ShortAnswerQuestion question(1, "text");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("foo");
			question.AddCorrectAnswer("bar");
			question.AddCorrectAnswer("foobar");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("foobar");
			Assert::IsFalse(question != question);
		}

		TEST_METHOD(QuestionSameAsIdenticalQuestion) {
			ShortAnswerQuestion first_question(1, "text");
			first_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			first_question.AddCorrectAnswer("a");
			first_question.AddCorrectAnswer("b");
			first_question.AddCorrectAnswer("c");
			first_question.SubmitStudentAnswer("d");
			first_question.SubmitStudentAnswer("a");

			ShortAnswerQuestion second_question(1, "text");
			second_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			second_question.AddCorrectAnswer("a");
			second_question.AddCorrectAnswer("b");
			second_question.AddCorrectAnswer("c");
			second_question.SubmitStudentAnswer("d");
			second_question.SubmitStudentAnswer("a");
			Assert::IsTrue(first_question == second_question);
		}

		TEST_METHOD(QuestionNotDifferentFromIdenticalQuestion) {
			ShortAnswerQuestion first_question(1, "text");
			first_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			first_question.AddCorrectAnswer("a");
			first_question.AddCorrectAnswer("b");
			first_question.AddCorrectAnswer("c");
			first_question.SubmitStudentAnswer("d");
			first_question.SubmitStudentAnswer("a");

			ShortAnswerQuestion second_question(1, "text");
			second_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			second_question.AddCorrectAnswer("a");
			second_question.AddCorrectAnswer("b");
			second_question.AddCorrectAnswer("c");
			second_question.SubmitStudentAnswer("d");
			second_question.SubmitStudentAnswer("a");
			Assert::IsFalse(first_question != second_question);
		}

		TEST_METHOD(QuestionIsCompletedIfCurrentScoreEqualsMaximumScore) {
			ShortAnswerQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("a");
			question.AddCorrectAnswer("b");
			question.AddCorrectAnswer("c");
			question.SubmitStudentAnswer("a");

			Assert::IsTrue(question.IsQuestionCompleted());
		}

		TEST_METHOD(QuestionIsCompletedIfCurrentScoreGreaterThanZero) {
			ShortAnswerQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("a");
			question.AddCorrectAnswer("b");
			question.AddCorrectAnswer("c");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("a");

			Assert::IsTrue(question.IsQuestionCompleted());
		}

		TEST_METHOD(QuestionIsCompletedIfNoAvailablePointsLeft) {
			ShortAnswerQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("a");
			question.AddCorrectAnswer("b");
			question.AddCorrectAnswer("c");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("still wrong");
			question.SubmitStudentAnswer("also incorrect");
			question.SubmitStudentAnswer("not right");

			Assert::IsTrue(question.IsQuestionCompleted());
		}

		TEST_METHOD(QuestionNotCompletedIfNoAttemptsToAnswer) {
			ShortAnswerQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("a");
			question.AddCorrectAnswer("b");
			question.AddCorrectAnswer("c");

			Assert::IsFalse(question.IsQuestionCompleted());
		}

		TEST_METHOD(QuestionIsNotCompletedIfNoRightAnswerAndStillHaveAttemptsLeft) {
			ShortAnswerQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("a");
			question.AddCorrectAnswer("b");
			question.AddCorrectAnswer("c");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("still wrong");

			Assert::IsFalse(question.IsQuestionCompleted());
		}

		TEST_METHOD(SaveAndLoadShortAnswerQuestion) {
			{
				ShortAnswerQuestion question(73, "What are the primary colors?");
				question.AddCorrectAnswer("red");
				question.AddCorrectAnswer("blue");
				question.AddCorrectAnswer("yellow");
				question.SetAvailablePoints("1.5,0.75,0.5,0.25");
				question.SubmitStudentAnswer("purple");
				question.SubmitStudentAnswer("RED");
				question.SubmitStudentAnswer("yellow");

				ofstream os("testing.dat", ios::binary);

				cereal::PortableBinaryOutputArchive oarchive(os);

				oarchive(question);
				os.close();
			}

			{
				ShortAnswerQuestion same_as_question(73, "What are the primary colors?");
				same_as_question.AddCorrectAnswer("red");
				same_as_question.AddCorrectAnswer("blue");
				same_as_question.AddCorrectAnswer("yellow");
				same_as_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
				same_as_question.SubmitStudentAnswer("purple");
				same_as_question.SubmitStudentAnswer("RED");
				same_as_question.SubmitStudentAnswer("yellow");

				ifstream is("testing.dat", ios::binary);
				cereal::PortableBinaryInputArchive iarchive(is);

				ShortAnswerQuestion question;

				iarchive(question);

				is.close();

				Assert::IsTrue(question == same_as_question);
			}
		}
	};

	TEST_CLASS(NumericalQuestionTests) {
	public:
		TEST_METHOD(DefaultConstructor) {
			NumericalQuestion question;
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 0);
		}

		TEST_METHOD(ConstructorTakingOnlyQuestionNumber) {
			NumericalQuestion question(4346);
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 4346);
		}

		TEST_METHOD(CustomQuestionConstructorEmptyString) {
			NumericalQuestion question(7, "");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 7);
		}

		TEST_METHOD(CustomQuestionConstructorLengthOneString) {
			NumericalQuestion question(16, "a");
			string q_text = "a";
			Assert::AreEqual(question.GetQuestion(), q_text);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 16);
		}

		TEST_METHOD(CustomQuestionConstructor) {
			NumericalQuestion question(2, "8BADF00D");
			string q_text = "8BADF00D";
			Assert::AreEqual(question.GetQuestion(), q_text);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
			Assert::AreEqual(question.GetQuestionNumber(), 2);
		}

		TEST_METHOD(GetSetPermittedAbsoluteError) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError("5.1");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 5.1);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(GetSetPermittedNegativeAbsoluteError) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError("-37.5");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), -37.5);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetAbsoluteErrorTwoPeriods) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError("5..1");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetAbsoluteErrorTwoMinuses) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError("--2");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetAbsoluteErrorMinusInWrongPlace) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError("5-2");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetAbsoluteErrorEmptyString) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError("");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetAbsoluteErrorJustASpace) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError(" ");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetAbsoluteErrorSpaceInFront) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError(" 0.1");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetAbsoluteErrorNotANumber) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError("banana");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetAbsoluteErrorContainsNonNumerical) {
			NumericalQuestion question(1);
			question.SetPermittedAbsoluteError("0.37s");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}
		TEST_METHOD(GetSetPermittedRelativeError) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError("0.078");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.078);
		}

		TEST_METHOD(GetSetPermittedNegativeRelativeError) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError("-2.3");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), -2.3);
		}

		TEST_METHOD(CannotSetRelativeErrorTwoPeriods) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError("5..1");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetRelativeErrorTwoMinuses) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError("--2");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetRelativeErrorMinusInWrongPlace) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError("5-2");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetRelativeErrorEmptyString) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError("");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetRelativeErrorJustASpace) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError(" ");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetRelativeErrorSpaceInFront) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError(" 0.1");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetRelativeErrorNotANumber) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError("banana");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CannotSetRelativeErrorContainsNonNumerical) {
			NumericalQuestion question(1);
			question.SetPermittedRelativeError("0.37s");
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(GetSetQuestion) {
			NumericalQuestion question(1);
			question.SetQuestion("What is 5 + 5?");
			string q_text = "What is 5 + 5?";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(GetSetQuestionEmpty) {
			NumericalQuestion question(1);
			question.SetQuestion("");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
		}

		TEST_METHOD(GetSetQuestionLength1) {
			NumericalQuestion question(5, "Should be gone");
			question.SetQuestion("5");
			string q_text = "5";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(FailToAddEmptyStringAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddSpaceAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer(" ");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddWordAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("aeftrser");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddNumberWithLetterAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5a");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddNumberWithSymbolAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("2.1!");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddMixOfCharactersAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("UIH8efhfrui9#*9e");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddNumberWithTwoPeriodsAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5.3.1");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(AddIntegerAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("8");
			vector<string> answers;
			answers.push_back("8");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < answers.size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddDoubleAsCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("3.1415");
			vector<string> answers;
			answers.push_back("3.1415");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < answers.size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddMultipleCorrectAnswers) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("8");
			question.AddCorrectAnswer("3.1415");
			question.AddCorrectAnswer("1.1");
			question.AddCorrectAnswer("1.1");
			vector<string> answers;
			answers.push_back("8");
			answers.push_back("3.1415");
			answers.push_back("1.1");
			answers.push_back("1.1");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < answers.size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddNegativeCorrectAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("-3.89");
			vector<string> answers;
			answers.push_back("-3.89");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < answers.size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(FailToAddCorrectAnswersWithMultipleNegativeSignsOrNegativeSignsInWrongPlaces) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("--3.89");
			question.AddCorrectAnswer("5-2");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddCorrectAnswerThatIsJustNegativeSign) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("-");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(AddMultipleCorrectAnswersAndFailToAddSome) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("banana");
			question.AddCorrectAnswer("8");
			question.AddCorrectAnswer("");
			question.AddCorrectAnswer(" ");
			question.AddCorrectAnswer("3.1415");
			question.AddCorrectAnswer("!@#$%^&*()");
			question.AddCorrectAnswer("1.1");
			question.AddCorrectAnswer("3..4");
			question.AddCorrectAnswer("1.1");
			question.AddCorrectAnswer("dfhzzudo8s5hys78ghu78ghEF7");
			vector<string> answers;
			answers.push_back("8");
			answers.push_back("3.1415");
			answers.push_back("1.1");
			answers.push_back("1.1");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < answers.size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(RemoveAnswersSingleAnswer) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5");
			question.RemoveCorrectAnswer("5");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(AddGetRemoveAnswersThreeAnswers) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("3.14");
			question.AddCorrectAnswer("2.57");
			question.AddCorrectAnswer("10");
			question.RemoveCorrectAnswer("2.57");
			vector<string> answers;
			answers.push_back("3.14");
			answers.push_back("10");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddGetRemoveAnswersAddAndRemoveAnswers) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("1");
			question.AddCorrectAnswer("2");
			question.AddCorrectAnswer("3");
			question.RemoveCorrectAnswer("3");
			question.AddCorrectAnswer("4");
			question.RemoveCorrectAnswer("4");
			question.AddCorrectAnswer("5");
			vector<string> answers;
			answers.push_back("1");
			answers.push_back("2");
			answers.push_back("5");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(RemoveAnswerWhenNotThere) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5");
			vector<string> answers;
			answers.push_back("5");
			question.RemoveCorrectAnswer("2");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(RemoveAnswerWhenNotThereTwo) {
			NumericalQuestion question(1);
			question.RemoveCorrectAnswer("5");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenNoneExist) {
			NumericalQuestion question(1);
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenSomeExist) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5.5");
			question.AddCorrectAnswer("1.23");
			question.AddCorrectAnswer("-5");
			question.AddCorrectAnswer("0");
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswerAndAddNew) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5");
			question.ClearCorrectAnswers();
			question.AddCorrectAnswer("3");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)1);
			Assert::AreEqual(question.GetCorrectAnswers()[0], (string)"3");
		}

		TEST_METHOD(SubmitSingleAnswerExactlyCorrect) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5.1689");
			question.SetAvailablePoints("5,3,1");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("5.1689", true));

			Assert::IsTrue(question.SubmitStudentAnswer("5.1689"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(SubmitSingleAnswerWithinAbsoluteAndRelativeErrorLimits) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5.1689");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("0.01");
			question.SetPermittedRelativeError("0.002");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("5.16", true));

			Assert::IsTrue(question.SubmitStudentAnswer("5.16"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(SubmitSingleAnswerWithinAbsoluteErrorLimitsNotCareAboutRelative) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("1000.0");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("10.0");
			question.SetPermittedRelativeError("-1");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("1009.999", true));

			Assert::IsTrue(question.SubmitStudentAnswer("1009.999"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(SubmitSingleAnswerWithinRelativeErrorLimitsNotCareAboutAbsolute) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("-21489.349");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("-439889.489389");
			question.SetPermittedRelativeError("0.001");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("-21469.8505", true));

			Assert::IsTrue(question.SubmitStudentAnswer("-21469.8505"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		//Any answer will be right in this case
		TEST_METHOD(SubmitSingleAnswerNotCareAboutRelativeOrAbsoluteError) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("432690930");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("-0.37");
			question.SetPermittedRelativeError("-2");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("-0.328957", true));

			Assert::IsTrue(question.SubmitStudentAnswer("-0.328957"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(SubmitSingleAnswerCareAboutBothAbsoluteAndRelativeErrorAndHaveTooMuchAbsoluteError) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("-21489.349");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("19.49");
			question.SetPermittedRelativeError("0.001");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("-21469.8505", false));

			Assert::IsFalse(question.SubmitStudentAnswer("-21469.8505"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(SubmitSingleAnswerCareAboutBothAbsoluteAndRelativeErrorAndHaveTooMuchRelativeError) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("1000.0");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("10.0");
			question.SetPermittedRelativeError("0.0099");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("1009.999", false));

			Assert::IsFalse(question.SubmitStudentAnswer("1009.999"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(SubmitSingleAnswerCareAboutBothAbsoluteAndRelativeErrorAndHaveTooMuchOfBoth) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("-0.000218");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("0.000001");
			question.SetPermittedRelativeError("0.00499");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("-0.00021691", false));

			Assert::IsFalse(question.SubmitStudentAnswer("-0.00021691"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(SubmitSingleAnswerCareAboutAbsoluteErrorOnlyAndHaveTooMuch) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("0.000000001");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("0.0000000005");
			question.SetPermittedRelativeError("-293573948");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("0.0000000016", false));

			Assert::IsFalse(question.SubmitStudentAnswer("0.0000000016"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(SubmitSingleAnswerCareAboutRelativeErrorOnlyAndHaveTooMuch) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("8934956759948.5");
			question.SetAvailablePoints("5,3,1");
			question.SetPermittedAbsoluteError("-1");
			question.SetPermittedRelativeError("0.05");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("9381704597946", false));

			Assert::IsFalse(question.SubmitStudentAnswer("9381704597946"));
			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(SubmitMultipleAnswers) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("100.0");
			question.SetAvailablePoints("5,4,3,2,1");
			question.SetPermittedAbsoluteError("5.0");
			question.SetPermittedRelativeError("0.05");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("9381704597946", false));
			expected_student_answers.push_back(pair<string, bool>("101.54893489", true));
			expected_student_answers.push_back(pair<string, bool>("95", true));
			expected_student_answers.push_back(pair<string, bool>("105.0", true));
			expected_student_answers.push_back(pair<string, bool>("94.999", false));


			Assert::IsFalse(question.SubmitStudentAnswer("9381704597946"));
			Assert::IsTrue(question.SubmitStudentAnswer("101.54893489"));
			Assert::IsTrue(question.SubmitStudentAnswer("95"));
			Assert::IsTrue(question.SubmitStudentAnswer("105.0"));
			Assert::IsFalse(question.SubmitStudentAnswer("94.999"));

			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 4.0);
		}

		TEST_METHOD(SubmitMultipleAnswersRanOutOfAttempts) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("100.0");
			question.SetAvailablePoints("5,3");
			question.SetPermittedAbsoluteError("5.0");
			question.SetPermittedRelativeError("0.05");

			vector<pair<string, bool>> expected_student_answers;
			expected_student_answers.push_back(pair<string, bool>("9381704597946", false));
			expected_student_answers.push_back(pair<string, bool>("94.999", false));
			expected_student_answers.push_back(pair<string, bool>("101.54893489", true));
			expected_student_answers.push_back(pair<string, bool>("95", true));
			expected_student_answers.push_back(pair<string, bool>("105.0", true));


			Assert::IsFalse(question.SubmitStudentAnswer("9381704597946"));
			Assert::IsFalse(question.SubmitStudentAnswer("94.999"));
			Assert::IsTrue(question.SubmitStudentAnswer("101.54893489"));
			Assert::IsTrue(question.SubmitStudentAnswer("95"));
			Assert::IsTrue(question.SubmitStudentAnswer("105.0"));

			Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
			for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
				Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
				Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
			}
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(ClearStudentAnswerWhenThereAreNone) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersWhenThereAreTwo) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("5");
			question.SubmitStudentAnswer("6");
			question.SubmitStudentAnswer("5");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersAndAddNewOne) {
			NumericalQuestion question(1);
			question.AddCorrectAnswer("2.0");
			question.SubmitStudentAnswer("2.0");
			question.SubmitStudentAnswer("3.0");
			question.ClearStudentAnswers();
			question.SubmitStudentAnswer("2.0");
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)1);
			Assert::AreEqual(question.GetStudentAnswers()[0].first, (string)"2.0");
			Assert::IsTrue(question.GetStudentAnswers()[0].second);
		}

		TEST_METHOD(FailToSetAvailablePointsEmptyString) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsCommaOnly) {
			NumericalQuestion question(1);
			question.SetAvailablePoints(",");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsDoubleComma) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("5,4,3,2,,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsContainsSpaces) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("10, 8, 6, 4, 2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsTwoPeriods) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("10, 5.5, 6.2, 4, 2..1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToFailToSetAvailablePointsContainsLetter) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("5,3,1a");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsContainsSymbol) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("5!,3,2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsScoresNotDescendingOrder) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("10,9,8,7,6,7,4,3,2,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsScoresAscendingOrder) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("0.1,0.2,0.3,0.4,0.5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(SetAvailablePointsOneAttemptAllowed) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)1);
			Assert::AreEqual(question.GetAvailablePoints()[0], 5.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 5.0);
		}

		TEST_METHOD(SetAvailablePointsFiveAttemptsAllowed) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("10,10,8,5,3");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)5);
			Assert::AreEqual(question.GetAvailablePoints()[0], 10.0);
			Assert::AreEqual(question.GetAvailablePoints()[1], 10.0);
			Assert::AreEqual(question.GetAvailablePoints()[2], 8.0);
			Assert::AreEqual(question.GetAvailablePoints()[3], 5.0);
			Assert::AreEqual(question.GetAvailablePoints()[4], 3.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 10.0);
		}

		TEST_METHOD(SetAvailablePointsDecimalValues) {
			NumericalQuestion question(1);
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)4);
			Assert::AreEqual(question.GetAvailablePoints()[0], 1.5);
			Assert::AreEqual(question.GetAvailablePoints()[1], 0.75);
			Assert::AreEqual(question.GetAvailablePoints()[2], 0.5);
			Assert::AreEqual(question.GetAvailablePoints()[3], 0.25);
			Assert::AreEqual(question.GetMaxPossibleScore(), 1.5);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentQuestionText) {
			NumericalQuestion first_question(1, "apples");
			NumericalQuestion second_question(1, "oranges");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentQuestionText) {
			NumericalQuestion first_question(1, "apples");
			NumericalQuestion second_question(1, "oranges");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentCurrentScore) {
			NumericalQuestion first_question(1, "same");
			first_question.SetAvailablePoints("12,11,10,8,5,3");
			first_question.AddCorrectAnswer("5.0");
			first_question.SubmitStudentAnswer("100.0");
			first_question.SubmitStudentAnswer("5.0");
			NumericalQuestion second_question(1, "same");
			second_question.SetAvailablePoints("12,10.5,10,8,5,3");
			second_question.AddCorrectAnswer("5.0");
			second_question.SubmitStudentAnswer("100.0");
			second_question.SubmitStudentAnswer("5.0");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentCurrentScore) {
			NumericalQuestion first_question(1, "same");
			first_question.SetAvailablePoints("12,11,10,8,5,3");
			first_question.AddCorrectAnswer("5.0");
			first_question.SubmitStudentAnswer("100.0");
			first_question.SubmitStudentAnswer("5.0");
			NumericalQuestion second_question(1, "same");
			second_question.SetAvailablePoints("12,10.5,10,8,5,3");
			second_question.AddCorrectAnswer("5.0");
			second_question.SubmitStudentAnswer("100.0");
			second_question.SubmitStudentAnswer("5.0");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentMaxPossibleScore) {
			NumericalQuestion first_question(1, "same");
			first_question.SetAvailablePoints("12,11,10,8,5,3");
			first_question.AddCorrectAnswer("5.0");
			first_question.SubmitStudentAnswer("100.0");
			NumericalQuestion second_question(1, "same");
			second_question.SetAvailablePoints("13,10.5,10,8,5,3");
			second_question.AddCorrectAnswer("5.0");
			second_question.SubmitStudentAnswer("100.0");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentMaxPossibleScore) {
			NumericalQuestion first_question(1, "same");
			first_question.SetAvailablePoints("12,11,10,8,5,3");
			first_question.AddCorrectAnswer("5.0");
			first_question.SubmitStudentAnswer("100.0");
			NumericalQuestion second_question(1, "same");
			second_question.SetAvailablePoints("13,10.5,10,8,5,3");
			second_question.AddCorrectAnswer("5.0");
			second_question.SubmitStudentAnswer("100.0");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentQuestionNumber) {
			NumericalQuestion first_question(1, "same");
			NumericalQuestion second_question(2, "same");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentQuestionNumber) {
			NumericalQuestion first_question(1, "same");
			NumericalQuestion second_question(2, "same");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentMaxPermittedAbsoluteError) {
			NumericalQuestion first_question(1, "same");
			first_question.SetPermittedAbsoluteError("0.01");
			NumericalQuestion second_question(1, "same");
			second_question.SetPermittedAbsoluteError("0.011");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentMaxPermittedAbsoluteError) {
			NumericalQuestion first_question(1, "same");
			first_question.SetPermittedAbsoluteError("0.01");
			NumericalQuestion second_question(1, "same");
			second_question.SetPermittedAbsoluteError("0.011");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentMaxPermittedRelativeError) {
			NumericalQuestion first_question(1, "same");
			first_question.SetPermittedRelativeError("0.00001");
			NumericalQuestion second_question(1, "same");
			second_question.SetPermittedRelativeError("0.00000999999999");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentMaxPermittedRelativeError) {
			NumericalQuestion first_question(1, "same");
			first_question.SetPermittedRelativeError("0.00001");
			NumericalQuestion second_question(1, "same");
			second_question.SetPermittedRelativeError("0.00000999999999");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthAvailablePointsDeque) {
			NumericalQuestion first_question(1, "same");
			first_question.SetAvailablePoints("5,4,3,2,1");
			NumericalQuestion second_question(1, "same");
			second_question.SetAvailablePoints("5,4,3,2");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthAvailablePointsDeque) {
			NumericalQuestion first_question(1, "same");
			first_question.SetAvailablePoints("5,4,3,2,1");
			NumericalQuestion second_question(1, "same");
			second_question.SetAvailablePoints("5,4,3,2");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentAvailablePointsDeque) {
			NumericalQuestion first_question(1, "same");
			first_question.SetAvailablePoints("5,3,1");
			NumericalQuestion second_question(1, "same");
			second_question.SetAvailablePoints("5,3,0.95");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentAvailablePointsDeque) {
			NumericalQuestion first_question(1, "same");
			first_question.SetAvailablePoints("5,3,1");
			NumericalQuestion second_question(1, "same");
			second_question.SetAvailablePoints("5,3,0.95");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthCorrectAnswersVector) {
			NumericalQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("3");
			first_question.AddCorrectAnswer("3");
			first_question.AddCorrectAnswer("3");
			NumericalQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("3");
			second_question.AddCorrectAnswer("3");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthCorrectAnswersVector) {
			NumericalQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("3");
			first_question.AddCorrectAnswer("3");
			first_question.AddCorrectAnswer("3");
			NumericalQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("3");
			second_question.AddCorrectAnswer("3");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentCorrectAnswersVector) {
			NumericalQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("1");
			first_question.AddCorrectAnswer("2");
			first_question.AddCorrectAnswer("3");
			NumericalQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("1.5");
			second_question.AddCorrectAnswer("2");
			second_question.AddCorrectAnswer("3");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentCorrectAnswersVector) {
			NumericalQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("1");
			first_question.AddCorrectAnswer("2");
			first_question.AddCorrectAnswer("3");
			NumericalQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("1.5");
			second_question.AddCorrectAnswer("2");
			second_question.AddCorrectAnswer("3");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthStudentAnswersVector) {
			NumericalQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("3");
			first_question.SubmitStudentAnswer("3");
			NumericalQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("3");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthStudentAnswersVector) {
			NumericalQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("3");
			first_question.SubmitStudentAnswer("3");
			NumericalQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("3");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(TwoQuestionsNotSameIfDifferentStudentAnswersVector) {
			NumericalQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("3");
			first_question.SubmitStudentAnswer("4");
			first_question.SubmitStudentAnswer("3");
			NumericalQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("3");
			second_question.SubmitStudentAnswer("3.9");
			second_question.SubmitStudentAnswer("3");
			Assert::IsFalse(first_question == second_question);
		}

		TEST_METHOD(TwoQuestionsDifferentIfDifferentStudentAnswersVector) {
			NumericalQuestion first_question(1, "same");
			first_question.AddCorrectAnswer("3");
			first_question.SubmitStudentAnswer("4");
			first_question.SubmitStudentAnswer("3");
			NumericalQuestion second_question(1, "same");
			second_question.AddCorrectAnswer("3");
			second_question.SubmitStudentAnswer("3.9");
			second_question.SubmitStudentAnswer("3");
			Assert::IsTrue(first_question != second_question);
		}

		TEST_METHOD(QuestionSameAsItself) {
			NumericalQuestion question(1, "text");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("5");
			question.AddCorrectAnswer("6");
			question.AddCorrectAnswer("7");
			question.SetPermittedAbsoluteError("0.1");
			question.SetPermittedRelativeError("0.02");
			question.SubmitStudentAnswer("10");
			question.SubmitStudentAnswer("5");
			Assert::IsTrue(question == question);
		}

		TEST_METHOD(QuestionNotDifferentFromItself) {
			NumericalQuestion question(1, "text");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("5");
			question.AddCorrectAnswer("6");
			question.AddCorrectAnswer("7");
			question.SetPermittedAbsoluteError("0.1");
			question.SetPermittedRelativeError("0.02");
			question.SubmitStudentAnswer("10");
			question.SubmitStudentAnswer("5");
			Assert::IsFalse(question != question);
		}

		TEST_METHOD(QuestionSameAsIdenticalQuestion) {
			NumericalQuestion first_question(1, "text");
			first_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			first_question.AddCorrectAnswer("5");
			first_question.AddCorrectAnswer("6");
			first_question.AddCorrectAnswer("7");
			first_question.SetPermittedAbsoluteError("0.1");
			first_question.SetPermittedRelativeError("0.02");
			first_question.SubmitStudentAnswer("10");
			first_question.SubmitStudentAnswer("5");

			NumericalQuestion second_question(1, "text");
			second_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			second_question.AddCorrectAnswer("5");
			second_question.AddCorrectAnswer("6");
			second_question.AddCorrectAnswer("7");
			second_question.SetPermittedAbsoluteError("0.1");
			second_question.SetPermittedRelativeError("0.02");
			second_question.SubmitStudentAnswer("10");
			second_question.SubmitStudentAnswer("5");
			Assert::IsTrue(first_question == second_question);
		}

		TEST_METHOD(QuestionNotDifferentFromIdenticalQuestion) {
			NumericalQuestion first_question(1, "text");
			first_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			first_question.AddCorrectAnswer("5");
			first_question.AddCorrectAnswer("6");
			first_question.AddCorrectAnswer("7");
			first_question.SetPermittedAbsoluteError("0.1");
			first_question.SetPermittedRelativeError("0.02");
			first_question.SubmitStudentAnswer("10");
			first_question.SubmitStudentAnswer("5");

			NumericalQuestion second_question(1, "text");
			second_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			second_question.AddCorrectAnswer("5");
			second_question.AddCorrectAnswer("6");
			second_question.AddCorrectAnswer("7");
			second_question.SetPermittedAbsoluteError("0.1");
			second_question.SetPermittedRelativeError("0.02");
			second_question.SubmitStudentAnswer("10");
			second_question.SubmitStudentAnswer("5");
			Assert::IsFalse(first_question != second_question);
		}

		TEST_METHOD(QuestionIsCompletedIfCurrentScoreEqualsMaximumScore) {
			NumericalQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("1");
			question.AddCorrectAnswer("2");
			question.AddCorrectAnswer("3");
			question.SubmitStudentAnswer("1");

			Assert::IsTrue(question.IsQuestionCompleted());
		}

		TEST_METHOD(QuestionIsCompletedIfCurrentScoreGreaterThanZero) {
			NumericalQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("1");
			question.AddCorrectAnswer("2");
			question.AddCorrectAnswer("3");
			question.SubmitStudentAnswer("222.5");
			question.SubmitStudentAnswer("1");

			Assert::IsTrue(question.IsQuestionCompleted());
		}

		TEST_METHOD(QuestionIsCompletedIfNoAvailablePointsLeft) {
			NumericalQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("1");
			question.AddCorrectAnswer("2");
			question.AddCorrectAnswer("3");
			question.SubmitStudentAnswer("0.5");
			question.SubmitStudentAnswer("-999");
			question.SubmitStudentAnswer("21988328");
			question.SubmitStudentAnswer("32988.3298437");

			Assert::IsTrue(question.IsQuestionCompleted());
		}

		TEST_METHOD(QuestionNotCompletedIfNoAttemptsToAnswer) {
			NumericalQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("1");
			question.AddCorrectAnswer("2");
			question.AddCorrectAnswer("3");

			Assert::IsFalse(question.IsQuestionCompleted());
		}

		TEST_METHOD(QuestionIsNotCompletedIfNoRightAnswerAndStillHaveAttemptsLeft) {
			NumericalQuestion question(1, "Question");
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question.AddCorrectAnswer("1");
			question.AddCorrectAnswer("2");
			question.AddCorrectAnswer("3");
			question.SubmitStudentAnswer("4");
			question.SubmitStudentAnswer("5");

			Assert::IsFalse(question.IsQuestionCompleted());
		}

		TEST_METHOD(SaveAndLoadNumericalQuestion) {
			{
				NumericalQuestion question(1, "What is the square root of 4?");
				question.AddCorrectAnswer("2");
				question.AddCorrectAnswer("-2");
				question.SetAvailablePoints("1.5,0.75,0.5,0.25");
				question.SubmitStudentAnswer("3");
				question.SubmitStudentAnswer("2");
				question.SetPermittedAbsoluteError("0.1");
				question.SetPermittedRelativeError("0.05");
				question.SubmitStudentAnswer("jiersjgiij");

				ofstream os("testing.dat", ios::binary);

				cereal::PortableBinaryOutputArchive oarchive(os);

				oarchive(question);
				os.close();
			}

			{
				NumericalQuestion same_as_question(1, "What is the square root of 4?");
				same_as_question.AddCorrectAnswer("2");
				same_as_question.AddCorrectAnswer("-2");
				same_as_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
				same_as_question.SubmitStudentAnswer("3");
				same_as_question.SubmitStudentAnswer("2");
				same_as_question.SubmitStudentAnswer("jiersjgiij");
				same_as_question.SetPermittedAbsoluteError("0.1");
				same_as_question.SetPermittedRelativeError("0.05");

				ifstream is("testing.dat", ios::binary);
				cereal::PortableBinaryInputArchive iarchive(is);

				NumericalQuestion question;

				iarchive(question);

				is.close();

				Assert::IsTrue(question == same_as_question);
			}
		}
	};

	//TEST_CLASS(QuestionKeyTests) {
	//public:
	//	TEST_METHOD(TwoQuestionKeysEqualIfSameQuestionIndex) {
	//		QuestionKey key_one(3, "apples");
	//		QuestionKey key_two(3, "oranges");
	//		Assert::IsTrue(key_one == key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysNotDifferentIfSameQuestionIndex) {
	//		QuestionKey key_one(3, "apples");
	//		QuestionKey key_two(3, "oranges");
	//		Assert::IsFalse(key_one != key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysEqualIfSameQuestionLabel) {
	//		QuestionKey key_one(347867845, "UY5848&878efy&4t");
	//		QuestionKey key_two(-17, "UY5848&878efy&4t");
	//		Assert::IsTrue(key_one == key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysNotDifferentIfSameQuestionLabel) {
	//		QuestionKey key_one(347867845, "UY5848&878efy&4t");
	//		QuestionKey key_two(-17, "UY5848&878efy&4t");
	//		Assert::IsFalse(key_one != key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysEqualIfSameQuestionIndexAndQuestionLabel) {
	//		QuestionKey key_one(57, "word");
	//		QuestionKey key_two(57, "word");
	//		Assert::IsTrue(key_one == key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysNotDifferentIfSameSameQuestionIndexAndQuestionLabel) {
	//		QuestionKey key_one(57, "word");
	//		QuestionKey key_two(57, "word");
	//		Assert::IsFalse(key_one != key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysNotEqualIfDifferentQuestionIndexAndQuestionLabel) {
	//		QuestionKey key_one(1, "banana");
	//		QuestionKey key_two(0, "bananna");
	//		Assert::IsFalse(key_one == key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysDifferentIfIfDifferentQuestionIndexAndQuestionLabel) {
	//		QuestionKey key_one(1, "banana");
	//		QuestionKey key_two(0, "bananna");
	//		Assert::IsTrue(key_one != key_two);
	//	}
	//};

	TEST_CLASS(TestForInstructorTests) {
	public:
		TEST_METHOD(ConstructorEmptyStringName) {
			TestForInstructor test("");
			Assert::AreEqual(test.GetNameOfTest(), (string)"");
			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual((int)test.GetAssignedQuestions().size(), 0);
			Assert::IsTrue(test.GetCurrentQuestion().expired());
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::AreEqual(test.GetNextQuestionNumber(), 1);
		}

		TEST_METHOD(ConstructorOneCharacterStringName) {
			TestForInstructor test("5");
			Assert::AreEqual(test.GetNameOfTest(), (string)"5");
			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual((int)test.GetAssignedQuestions().size(), 0);
			Assert::IsTrue(test.GetCurrentQuestion().expired());
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::AreEqual(test.GetNextQuestionNumber(), 1);
		}

		TEST_METHOD(Constructor) {
			TestForInstructor test("Ag2*UGHr78ys589shru7y*(th7a8grui");
			Assert::AreEqual(test.GetNameOfTest(), (string)"Ag2*UGHr78ys589shru7y*(th7a8grui");
			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual((int)test.GetAssignedQuestions().size(), 0);
			Assert::IsTrue(test.GetCurrentQuestion().expired());
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::AreEqual(test.GetNextQuestionNumber(), 1);
		}

		TEST_METHOD(AddShortAnswerAndNumericalQuestions) {
			TestForInstructor test("test");
			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);

			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[1]) == question_two);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2]) == question_three);
		}

		TEST_METHOD(CreateQuestionCategories) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("Bananas");

			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);
			Assert::IsTrue(test.GetAssignedQuestions()[0] == tuple<string, int, vector<shared_ptr<Question>>>("History", -1, vector<shared_ptr<Question>>()));
			Assert::IsTrue(test.GetAssignedQuestions()[1] == tuple<string, int, vector<shared_ptr<Question>>>("Math", -1, vector<shared_ptr<Question>>()));
			Assert::IsTrue(test.GetAssignedQuestions()[2] == tuple<string, int, vector<shared_ptr<Question>>>("Bananas", -1, vector<shared_ptr<Question>>()));
		}

		TEST_METHOD(CreateQuestionCategoriesAndCannotHaveTwoCategoriesWithSameName) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("Bananas");
			test.CreateQuestionCategory("Math");

			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);
			Assert::IsTrue(test.GetAssignedQuestions()[0] == tuple<string, int, vector<shared_ptr<Question>>>("History", -1, vector<shared_ptr<Question>>()));
			Assert::IsTrue(test.GetAssignedQuestions()[1] == tuple<string, int, vector<shared_ptr<Question>>>("Math", -1, vector<shared_ptr<Question>>()));
			Assert::IsTrue(test.GetAssignedQuestions()[2] == tuple<string, int, vector<shared_ptr<Question>>>("Bananas", -1, vector<shared_ptr<Question>>()));
		}

		TEST_METHOD(SelectQuestionInUnassignedQuestions) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			NumericalQuestion question(3, "What is 3 times 7?");

			test.SelectCurrentQuestion("3");
			shared_ptr<NumericalQuestion> current_question = dynamic_pointer_cast<NumericalQuestion>(test.GetCurrentQuestion().lock());
			Assert::IsTrue(*current_question == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectQuestionThatDoesNotExist) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("0");
			NumericalQuestion question(3, "What is 3 times 7?");

			shared_ptr<NumericalQuestion> current_question = dynamic_pointer_cast<NumericalQuestion>(test.GetCurrentQuestion().lock());
			Assert::IsTrue(*current_question == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectOtherQuestionThatDoesNotExist) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("2");
			ShortAnswerQuestion question(2, "What is George Washington's name?");
			test.SelectCurrentQuestion("24");

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectQuestionBecauseStringIsNotNumerical) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("2");
			ShortAnswerQuestion question(2, "What is George Washington's name?");
			test.SelectCurrentQuestion("abc");

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectQuestionBecauseStringContainsSymbol) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("2");
			ShortAnswerQuestion question(2, "What is George Washington's name?");
			test.SelectCurrentQuestion("1!");

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectQuestionBecauseStringIsDecimal) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("2");
			ShortAnswerQuestion question(2, "What is George Washington's name?");
			test.SelectCurrentQuestion("1.5");

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectQuestionBecauseStringIsEmpty) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("2");
			ShortAnswerQuestion question(2, "What is George Washington's name?");
			test.SelectCurrentQuestion("");

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectQuestionBecauseStringIsSpace) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("2");
			ShortAnswerQuestion question(2, "What is George Washington's name?");
			test.SelectCurrentQuestion(" ");

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectQuestionBecauseStringContainsSpace) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("2");
			ShortAnswerQuestion question(2, "What is George Washington's name?");
			test.SelectCurrentQuestion(" 3");

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(FailToSelectQuestionBecauseStringContainsPeriod) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("2");
			ShortAnswerQuestion question(2, "What is George Washington's name?");
			test.SelectCurrentQuestion("1.");

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(AddQuestionsToCategoriesFromUnassigned) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");
			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");
			Assert::AreEqual(test.GetCurrentCategory(), (string)"History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");
			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(FailToAddQuestionToCategoryBecauseItWasDeleted) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("2");
			test.DeleteCurrentQuestion();
			test.AddCurrentQuestionToCategory("History");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)2);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
		}

		TEST_METHOD(FailToAddQuestionToCategoryBecauseItHasDifferentMaxScore) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Questions");

			test.GetUnassignedQuestions()[0]->SetAvailablePoints("5,4,3,2,1");
			test.GetUnassignedQuestions()[1]->SetAvailablePoints("5,4,3,2,1");
			test.GetUnassignedQuestions()[2]->SetAvailablePoints("6,4,3,2,1");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Questions");
			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("Questions");
			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Questions");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			question_one.SetAvailablePoints("5,4,3,2,1");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			question_two.SetAvailablePoints("5,4,3,2,1");
			NumericalQuestion question_three(3, "What is 3 times 7?");
			question_three.SetAvailablePoints("6,4,3,2,1");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)1);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)1);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Questions");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_two);
		}

		TEST_METHOD(AddQuestionToCategoryEvenThoughAvailablePointsDifferAllowedBecauseSameMaxScore) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Questions");

			test.GetUnassignedQuestions()[0]->SetAvailablePoints("5,4,3,2,1");
			test.GetUnassignedQuestions()[1]->SetAvailablePoints("5,4,3,2,1");
			test.GetUnassignedQuestions()[2]->SetAvailablePoints("5,5,5,5,5,5,4.2,4,3,2.7,2,1");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Questions");
			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("Questions");
			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Questions");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			question_one.SetAvailablePoints("5,4,3,2,1");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			question_two.SetAvailablePoints("5,4,3,2,1");
			NumericalQuestion question_three(3, "What is 3 times 7?");
			question_three.SetAvailablePoints("5,5,5,5,5,5,4.2,4,3,2.7,2,1");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)1);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"Questions");

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Questions");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)3);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_two);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[2]) == question_three);
		}
		TEST_METHOD(SelectAssignedQuestion) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");
			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");
			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			ShortAnswerQuestion question_two(2, "What is George Washington's name?");

			test.SelectCurrentQuestion("2");
			Assert::AreEqual(test.GetCurrentCategory(), (string)"History");
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question_two);
		}

		TEST_METHOD(MoveQuestionFromOneCategoryToAnother) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");
			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");
			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("Math");

			ShortAnswerQuestion question_two(2, "What is George Washington's name?");

			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)3);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[2]) == question_two);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");
		}

		TEST_METHOD(MovingQuestionThatIsAlreadyInCategoryDoesNothing) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		}

		TEST_METHOD(CannotAddQuestionToCategoryIfNoCurrentQuestion) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
		}

		TEST_METHOD(CannotAddQuestionToNonexistantCategory) {
			TestForInstructor test("test");
			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Category");
			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Does not exist");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[1]) == question_two);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2]) == question_three);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)1);
			Assert::IsTrue(test.GetAssignedQuestions()[0] == tuple<string, int, vector<shared_ptr<Question>>>("Category", -1, vector<shared_ptr<Question>>()));
		}

		TEST_METHOD(CannotRemoveQuestionFromCategoryIfNoCurrentQuestion) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.RemoveCurrentQuestionFromCategory();

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
		}

		TEST_METHOD(CannotRemoveQuestionFromCategoryIfNotInCategory) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("2");
			test.RemoveCurrentQuestionFromCategory();

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[1]) == question_two);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2]) == question_three);
		}

		TEST_METHOD(CannotRemoveQuestionFromCategoryIfQuestionWasDeleted) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("1");
			test.DeleteCurrentQuestion();
			test.RemoveCurrentQuestionFromCategory();

			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");

			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(RemoveQuestionFromCategory) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");
			test.RemoveCurrentQuestionFromCategory();

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)1);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_three);

			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(RemoveQuestionsFromCategories) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");
			test.RemoveCurrentQuestionFromCategory();

			test.SelectCurrentQuestion("1");
			test.RemoveCurrentQuestionFromCategory();

			test.SelectCurrentQuestion("2");
			test.RemoveCurrentQuestionFromCategory();

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_three);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[2]) == question_two);

			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
		}

		TEST_METHOD(CannotDeleteQuestionIfNoCurrentQuestion) {
			TestForInstructor test("test");

			test.DeleteCurrentQuestion();

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(DeleteUnassignedQuestion) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.SelectCurrentQuestion("1");
			test.DeleteCurrentQuestion();

			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)2);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)0);

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[0]) == question_two);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1]) == question_three);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(DeleteQuestionInAssignedQuestions) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");
			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");
			Assert::AreEqual(test.GetCurrentCategory(), (string)"History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");
			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");

			test.DeleteCurrentQuestion();

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(DeleteNonexistentCategory) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.DeleteQuestionCategory("Does not exist");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");
		}

		TEST_METHOD(DeleteCategoryContainingNoQuestions) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Empty");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.DeleteQuestionCategory("Empty");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");
		}

		TEST_METHOD(DeleteCategoryContainingQuestions) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.DeleteQuestionCategory("History");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)1);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)1);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[0]) == question_two);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");
		}

		TEST_METHOD(DeleteCategoryContainingCurrentQuestion) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.DeleteQuestionCategory("Math");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)2);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)1);

			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_two);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(CannotSwitchOrderOfCategoriesBecauseFirstCategoryDoesNotExist) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Biology");

			test.SwitchOrderOfCategories("Chemistry", "History");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Biology");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(CannotSwitchOrderOfCategoriesBecauseSecondCategoryDoesNotExist) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Biology");

			test.SwitchOrderOfCategories("History", "Chemistry");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Biology");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(CannotSwitchOrderOfCategoriesBecauseNeitherExists) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Biology");

			test.SwitchOrderOfCategories("Literature", "Physics");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Biology");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(SwitchOrderOfTwoCategories) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Biology");

			test.SwitchOrderOfCategories("Math", "Biology");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Biology");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		}

		TEST_METHOD(SwitchOrderOfTwoCategoriesContainingQuestions) {
			TestForInstructor test("test");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Biology");

			test.AddNumericalQuestion("What is 5!?");
			test.AddCurrentQuestionToCategory("Math");
			test.AddShortAnswerQuestion("Who came first, Ivan the Great or Ivan the Terrible?");
			test.AddCurrentQuestionToCategory("History");
			test.AddShortAnswerQuestion("Which is thicker, a microtubule or a microfilament?");
			test.AddCurrentQuestionToCategory("Biology");

			NumericalQuestion question_one(1, "What is 5!?");
			ShortAnswerQuestion question_two(2, "Who came first, Ivan the Great or Ivan the Terrible?");
			ShortAnswerQuestion question_three(3, "Which is thicker, a microtubule or a microfilament?");

			test.SwitchOrderOfCategories("Math", "Biology");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Biology");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[2])[0]) == question_one);

			Assert::AreEqual(test.GetCurrentCategory(), (string)"Biology");
		}

		TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseCategoryDoesNotExist) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.ChangeNumberOfQuestionsToAskFromCategory("Literature", "3");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringEmpty) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", "");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringIsSpace) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", " ");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringNotANumber) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", "UJHbueih7YT47yg#*(");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringIsDecimal) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", "2.3");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringContainsLetter) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", "812a");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(ChangeNumberOfQuestionsToAskFromCategoryOnce) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", "1");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), 1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(ChangeNumberOfQuestionsToAskFromCategoryRepeatedly) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");

			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", "1");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), 1);

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", "-97218");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -97218);

			test.ChangeNumberOfQuestionsToAskFromCategory("Math", "2");

			NumericalQuestion question_one(1, "What is 5 + 3?");
			ShortAnswerQuestion question_two(2, "What is George Washington's name?");
			NumericalQuestion question_three(3, "What is 3 times 7?");

			Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), 2);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

			Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
			Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
			Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
		}

		TEST_METHOD(GetMaxAvailablePointsWhenNoAssignedQuestions) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.GetUnassignedQuestions()[0]->SetAvailablePoints("5,4,3,2,1");
			test.GetUnassignedQuestions()[1]->SetAvailablePoints("3");
			test.GetUnassignedQuestions()[2]->SetAvailablePoints("9.1,4.8,1.35");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			Assert::AreEqual(test.GetMaxAvailableScore(), 0.0);
		}

		TEST_METHOD(GetMaxAvailablePointsWhenQuestionsAssignedButHaveNoAvailablePoints) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");
			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");
			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Math");

			Assert::AreEqual(test.GetMaxAvailableScore(), 0.0);
		}

		TEST_METHOD(GetMaxAvailablePointsWhenQuestionsAssigned) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.GetUnassignedQuestions()[0]->SetAvailablePoints("5,4,3,2,1");
			test.GetUnassignedQuestions()[1]->SetAvailablePoints("3");
			test.GetUnassignedQuestions()[2]->SetAvailablePoints("9.1,4.8,1.35");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Other Math");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");
			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");
			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Other Math");

			Assert::AreEqual(test.GetMaxAvailableScore(), 17.1);
		}

		TEST_METHOD(GetMaxAvailablePointsWhenSomeQuestionsAssigned) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.GetUnassignedQuestions()[0]->SetAvailablePoints("5,4,3,2,1");
			test.GetUnassignedQuestions()[1]->SetAvailablePoints("3");
			test.GetUnassignedQuestions()[2]->SetAvailablePoints("9.1,4.8,1.35");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");
			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");

			Assert::AreEqual(test.GetMaxAvailableScore(), 8.0);
		}

		TEST_METHOD(GetMaxAvailablePointsWhenQuestionsAssignedAndSomeAnswersSubmitted) {
			TestForInstructor test("test");

			test.AddNumericalQuestion("What is 5 + 3?");
			test.AddShortAnswerQuestion("What is George Washington's name?");
			test.AddNumericalQuestion("What is 3 times 7?");

			test.GetUnassignedQuestions()[0]->SetAvailablePoints("5,4,3,2,1");
			test.GetUnassignedQuestions()[1]->SetAvailablePoints("3");
			test.GetUnassignedQuestions()[2]->SetAvailablePoints("9.1,4.8,1.35");

			test.GetUnassignedQuestions()[0]->AddCorrectAnswer("8");
			test.GetUnassignedQuestions()[1]->AddCorrectAnswer("George Washington");
			test.GetUnassignedQuestions()[2]->AddCorrectAnswer("21");

			test.CreateQuestionCategory("Math");
			test.CreateQuestionCategory("History");
			test.CreateQuestionCategory("Other Math");

			test.SelectCurrentQuestion("1");
			test.AddCurrentQuestionToCategory("Math");
			test.SelectCurrentQuestion("2");
			test.AddCurrentQuestionToCategory("History");
			test.SelectCurrentQuestion("3");
			test.AddCurrentQuestionToCategory("Other Math");

			get<2>(test.GetAssignedQuestions()[0])[0]->SubmitStudentAnswer("8");
			get<2>(test.GetAssignedQuestions()[1])[0]->SubmitStudentAnswer("Abraham Lincoln");

			Assert::AreEqual(test.GetMaxAvailableScore(), 17.1);
		}

		TEST_METHOD(SaveAndLoadTest) {
			{
				TestForInstructor test("Test for testing");

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
				dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
				dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");
				test.GetUnassignedQuestions()[1]->SubmitStudentAnswer("3");
				test.GetUnassignedQuestions()[1]->SubmitStudentAnswer("2");
				test.GetUnassignedQuestions()[1]->SubmitStudentAnswer("jiersjgiij");

				test.AddNumericalQuestion("What is the square root of 9?");
				test.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
				test.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
				test.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
				dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
				dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");
				test.GetUnassignedQuestions()[2]->SubmitStudentAnswer("3");
				test.GetUnassignedQuestions()[2]->SubmitStudentAnswer("2");
				test.GetUnassignedQuestions()[2]->SubmitStudentAnswer("GJ*E");

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

				ofstream os("testing.dat", ios::binary);

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

				ifstream is("testing.dat", ios::binary);
				cereal::PortableBinaryInputArchive iarchive(is);

				TestForInstructor test;

				iarchive(test);

				is.close();

				Assert::AreEqual(test.GetNameOfTest(), (string)"Test for testing");
				
				Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)1);
				Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[0]) == question_four);

				Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

				Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Art");
				Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
				Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
				Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);

				Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"Math");
				Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), 2);
				Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)2);
				Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
				Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[1])[1]) == question_three);

				Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Empty");
				Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
				Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

				Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question_one);
				Assert::AreEqual(test.GetCurrentCategory(), (string)"Art");
				Assert::AreEqual(test.GetNextQuestionNumber(), 5);
			}
		}
	};

	TEST_CLASS(TestForStudentTests) {
	public:
		TEST_METHOD(CreateTestForStudentWithDefaultConstructor) {
			TestForStudent test;

			Assert::AreEqual(test.GetNameOfTest(), (string)"");
			Assert::AreEqual(test.GetQuestions().size(), (size_t)0);
			Assert::AreEqual(test.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(test.GetIndexOfCurrentQuestion(), (unsigned)0);
			Assert::IsTrue(test.IsOrderOfQuestionsFixed());
		}

		TEST_METHOD(CreateTestForStudentFromTestForInstructor) {
			TestForInstructor test_for_instructor("Test for testing");
			
			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

			test_for_instructor.AddShortAnswerQuestion("Unassigned Question");
			test_for_instructor.GetUnassignedQuestions()[4]->AddCorrectAnswer("Correct");
			test_for_instructor.GetUnassignedQuestions()[4]->SetAvailablePoints("5,4,3,2,1");

			test_for_instructor.SelectCurrentQuestion("1");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("2");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("3");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("4");
			test_for_instructor.AddCurrentQuestionToCategory("Third");

			TestForStudent test_for_student(test_for_instructor);

			ShortAnswerQuestion question_one(1, "What are the primary colors?");
			question_one.AddCorrectAnswer("red");
			question_one.AddCorrectAnswer("blue");
			question_one.AddCorrectAnswer("yellow");
			question_one.SetAvailablePoints("1.5,0.75,0.5,0.25");

			NumericalQuestion question_two(2, "What is the square root of 4?");
			question_two.AddCorrectAnswer("2");
			question_two.AddCorrectAnswer("-2");
			question_two.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question_two.SetPermittedAbsoluteError("0.1");
			question_two.SetPermittedRelativeError("0.05");

			NumericalQuestion question_three(3, "What is the square root of 9?");
			question_three.AddCorrectAnswer("3");
			question_three.AddCorrectAnswer("-3");
			question_three.SetAvailablePoints("1.5,1.5,1.5,1.5");
			question_three.SetPermittedAbsoluteError("0.1");
			question_three.SetPermittedRelativeError("0.05");

			ShortAnswerQuestion question_four(4, "What is Abraham Lincoln's Name?");
			question_four.AddCorrectAnswer("Abraham");
			question_four.AddCorrectAnswer("Lincoln");
			question_four.AddCorrectAnswer("Abraham Lincoln");
			question_four.SetAvailablePoints("2");

			Assert::AreEqual(test_for_student.GetNameOfTest(), (string)"Test for testing");
			Assert::AreEqual(test_for_student.GetMaxPossibleScore(), 6.5);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
			Assert::IsTrue(test_for_student.IsOrderOfQuestionsFixed());

			Assert::AreEqual(test_for_student.GetQuestions().size(), (size_t)4);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[0]) == question_one);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[1]) == question_two);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[2]) == question_three);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[3]) == question_four);
		}


		TEST_METHOD(CreateTestForStudentFromTestForInstructorContainingCategoryWithRandomOrder) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("FirstAndOnly");
			test_for_instructor.ChangeNumberOfQuestionsToAskFromCategory("FirstAndOnly", "3");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");


			test_for_instructor.SelectCurrentQuestion("1");
			test_for_instructor.AddCurrentQuestionToCategory("FirstAndOnly");
			test_for_instructor.SelectCurrentQuestion("2");
			test_for_instructor.AddCurrentQuestionToCategory("FirstAndOnly");
			test_for_instructor.SelectCurrentQuestion("3");
			test_for_instructor.AddCurrentQuestionToCategory("FirstAndOnly");
			test_for_instructor.SelectCurrentQuestion("4");
			test_for_instructor.AddCurrentQuestionToCategory("FirstAndOnly");

			TestForStudent test_for_student(test_for_instructor);

			ShortAnswerQuestion question_one(1, "What are the primary colors?");
			question_one.AddCorrectAnswer("red");
			question_one.AddCorrectAnswer("blue");
			question_one.AddCorrectAnswer("yellow");
			question_one.SetAvailablePoints("1.5,0.75,0.5,0.25");

			NumericalQuestion question_two(2, "What is the square root of 4?");
			question_two.AddCorrectAnswer("2");
			question_two.AddCorrectAnswer("-2");
			question_two.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question_two.SetPermittedAbsoluteError("0.1");
			question_two.SetPermittedRelativeError("0.05");

			NumericalQuestion question_three(3, "What is the square root of 9?");
			question_three.AddCorrectAnswer("3");
			question_three.AddCorrectAnswer("-3");
			question_three.SetAvailablePoints("1.5,1.5,1.5,1.5");
			question_three.SetPermittedAbsoluteError("0.1");
			question_three.SetPermittedRelativeError("0.05");

			ShortAnswerQuestion question_four(4, "What is Abraham Lincoln's Name?");
			question_four.AddCorrectAnswer("Abraham");
			question_four.AddCorrectAnswer("Lincoln");
			question_four.AddCorrectAnswer("Abraham Lincoln");
			question_one.SetAvailablePoints("1.5,0.75,0.5,0.25");

			int question_appearance_count[4] = { 0, 0, 0, 0 };

			Assert::AreEqual(test_for_student.GetNameOfTest(), (string)"Test for testing");
			Assert::AreEqual(test_for_student.GetMaxPossibleScore(), 4.5);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
			Assert::IsTrue(test_for_student.IsOrderOfQuestionsFixed());

			Assert::AreEqual(test_for_student.GetQuestions().size(), (size_t)3);
			for (unsigned i = 0; i < test_for_student.GetQuestions().size(); ++i) {
				if (dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[i]) != nullptr
					&& *dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[i]) == question_one) {
					++question_appearance_count[0];
				}
				else if (dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[i]) != nullptr
					&& *dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[i]) == question_two) {
					++question_appearance_count[1];
				}
				else if (dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[i]) != nullptr
					&& *dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[i]) == question_three) {
					++question_appearance_count[2];
				}
				else if (dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[i]) != nullptr
					&& *dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[i]) == question_four) {
					++question_appearance_count[3];
				}
				else {
					Assert::IsTrue(false);
				}
			}

			for (unsigned i = 0; i < 4; ++i) {
				Assert::IsTrue(question_appearance_count[i] == 0 || question_appearance_count[i] == 1);
			}
		}

		TEST_METHOD(ChangeIfOrderOfQuestionsIsFixed) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

			test_for_instructor.SelectCurrentQuestion("1");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("2");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("3");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("4");
			test_for_instructor.AddCurrentQuestionToCategory("Third");

			TestForStudent test_for_student(test_for_instructor);

			Assert::IsTrue(test_for_student.IsOrderOfQuestionsFixed());
			test_for_student.ChangeIfOrderOfQuestionsIsFixed();
			Assert::IsFalse(test_for_student.IsOrderOfQuestionsFixed());
			test_for_student.ChangeIfOrderOfQuestionsIsFixed();
			Assert::IsTrue(test_for_student.IsOrderOfQuestionsFixed());
		}

		TEST_METHOD(GetNextQuestionAndPreviousQuestionWhenOrderNotFixed) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			ShortAnswerQuestion question_one(1, "What are the primary colors?");
			question_one.AddCorrectAnswer("red");
			question_one.AddCorrectAnswer("blue");
			question_one.AddCorrectAnswer("yellow");
			question_one.SetAvailablePoints("1.5,0.75,0.5,0.25");

			NumericalQuestion question_two(2, "What is the square root of 4?");
			question_two.AddCorrectAnswer("2");
			question_two.AddCorrectAnswer("-2");
			question_two.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question_two.SetPermittedAbsoluteError("0.1");
			question_two.SetPermittedRelativeError("0.05");

			NumericalQuestion question_three(3, "What is the square root of 9?");
			question_three.AddCorrectAnswer("3");
			question_three.AddCorrectAnswer("-3");
			question_three.SetAvailablePoints("1.5,1.5,1.5,1.5");
			question_three.SetPermittedAbsoluteError("0.1");
			question_three.SetPermittedRelativeError("0.05");

			ShortAnswerQuestion question_four(4, "What is Abraham Lincoln's Name?");
			question_four.AddCorrectAnswer("Abraham");
			question_four.AddCorrectAnswer("Lincoln");
			question_four.AddCorrectAnswer("Abraham Lincoln");
			question_four.SetAvailablePoints("2");

			//Get next question
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetNextQuestion().lock()) == question_two);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)1);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetNextQuestion().lock()) == question_three);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)2);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetNextQuestion().lock()) == question_four);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)3);

			//Cannot get next question if index_of_current_question_ == questions_.size() - 1
			Assert::IsTrue(test_for_student.GetNextQuestion().expired());
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)3);

			//Get previous question
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetPreviousQuestion().lock()) == question_three);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)2);
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetPreviousQuestion().lock()) == question_two);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)1);
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetPreviousQuestion().lock()) == question_one);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);

			//Cannot get previous question if index_of_current_question_ == 0
			Assert::IsTrue(test_for_student.GetPreviousQuestion().expired());
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(GetNextQuestionAndPreviousQuestionWhenOrderIsFixed) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

			test_for_instructor.SelectCurrentQuestion("1");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("2");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("3");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("4");
			test_for_instructor.AddCurrentQuestionToCategory("Third");

			TestForStudent test_for_student(test_for_instructor);

			ShortAnswerQuestion question_one(1, "What are the primary colors?");
			question_one.AddCorrectAnswer("red");
			question_one.AddCorrectAnswer("blue");
			question_one.AddCorrectAnswer("yellow");
			question_one.SetAvailablePoints("1.5,0.75,0.5,0.25");

			NumericalQuestion question_two(2, "What is the square root of 4?");
			question_two.AddCorrectAnswer("2");
			question_two.AddCorrectAnswer("-2");
			question_two.SetAvailablePoints("1.5,0.75,0.5,0.25");
			question_two.SetPermittedAbsoluteError("0.1");
			question_two.SetPermittedRelativeError("0.05");

			NumericalQuestion question_three(3, "What is the square root of 9?");
			question_three.AddCorrectAnswer("3");
			question_three.AddCorrectAnswer("-3");
			question_three.SetAvailablePoints("1.5,1.5,1.5,1.5");
			question_three.SetPermittedAbsoluteError("0.1");
			question_three.SetPermittedRelativeError("0.05");

			ShortAnswerQuestion question_four(4, "What is Abraham Lincoln's Name?");
			question_four.AddCorrectAnswer("Abraham");
			question_four.AddCorrectAnswer("Lincoln");
			question_four.AddCorrectAnswer("Abraham Lincoln");
			question_four.SetAvailablePoints("2");

			//Cannot GetNextQuestion because order is fixed and have not completed current question
			Assert::IsTrue(test_for_student.GetNextQuestion().expired());
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);

			//Answer first question correctly
			test_for_student.GetQuestions()[0]->SubmitStudentAnswer("red");
			question_one.SubmitStudentAnswer("red");

			//Can GetNextQuestion
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetNextQuestion().lock()) == question_two);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)1);

			//Cannot GetNextQuestion because order is fixed and have not completed current question
			Assert::IsTrue(test_for_student.GetNextQuestion().expired());
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)1);

			//Can GetPreviousQuestion
			Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetPreviousQuestion().lock()) == question_one);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);

			//Go to second question
			weak_ptr<Question> current = test_for_student.GetNextQuestion();
			//Complete it by answering incorrectly repeatedly
			current.lock()->SubmitStudentAnswer("5");
			current.lock()->SubmitStudentAnswer("6");
			current.lock()->SubmitStudentAnswer("983454785");
			current.lock()->SubmitStudentAnswer("8");
			question_two.SubmitStudentAnswer("5");
			question_two.SubmitStudentAnswer("6");
			question_two.SubmitStudentAnswer("983454785");
			question_two.SubmitStudentAnswer("8");

			//Can GetNextQuestion
			Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetNextQuestion().lock()) == question_three);
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)2);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfOrderOfQuestionsFixed) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

			test_for_instructor.SelectCurrentQuestion("1");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("2");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("3");
			test_for_instructor.AddCurrentQuestionToCategory("First");
			test_for_instructor.SelectCurrentQuestion("4");
			test_for_instructor.AddCurrentQuestionToCategory("Third");

			TestForStudent test_for_student(test_for_instructor);

			test_for_student.SetIndexOfCurrentQuestion("1");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfIndexIsEmptyString) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion("");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfIndexIsSpace) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion(" ");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfIndexIsNotNumber) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion("aji98ej4t5huighcHEFR&*");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfIndexIsDecimal) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion("1.5");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfIndexContainsNonNumericalCharacter) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion("2a");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfIndexIsNegative) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion("-5");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfIndexIsGreaterThanSizeOfQuestionsVector) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion("100");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(CannotSetIndexOfCurrentQuestionIfIndexIsEqualToSizeOfQuestionsVector) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion("4");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);
		}

		TEST_METHOD(SetIndexOfCurrentQuestion) {
			TestForInstructor test_for_instructor("Test for testing");

			test_for_instructor.CreateQuestionCategory("First");
			test_for_instructor.CreateQuestionCategory("Empty");
			test_for_instructor.CreateQuestionCategory("Third");

			test_for_instructor.AddShortAnswerQuestion("What are the primary colors?");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("red");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("blue");
			test_for_instructor.GetUnassignedQuestions()[0]->AddCorrectAnswer("yellow");
			test_for_instructor.GetUnassignedQuestions()[0]->SetAvailablePoints("1.5,0.75,0.5,0.25");

			test_for_instructor.AddNumericalQuestion("What is the square root of 4?");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("2");
			test_for_instructor.GetUnassignedQuestions()[1]->AddCorrectAnswer("-2");
			test_for_instructor.GetUnassignedQuestions()[1]->SetAvailablePoints("1.5,0.75,0.5,0.25");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[1])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddNumericalQuestion("What is the square root of 9?");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("3");
			test_for_instructor.GetUnassignedQuestions()[2]->AddCorrectAnswer("-3");
			test_for_instructor.GetUnassignedQuestions()[2]->SetAvailablePoints("1.5,1.5,1.5,1.5");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedAbsoluteError("0.1");
			dynamic_pointer_cast<NumericalQuestion>(test_for_instructor.GetUnassignedQuestions()[2])->SetPermittedRelativeError("0.05");

			test_for_instructor.AddShortAnswerQuestion("What is Abraham Lincoln's Name?");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->AddCorrectAnswer("Abraham Lincoln");
			test_for_instructor.GetUnassignedQuestions()[3]->SetAvailablePoints("2");

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

			test_for_student.SetIndexOfCurrentQuestion("1");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)1);

			test_for_student.SetIndexOfCurrentQuestion("3");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)3);

			test_for_student.SetIndexOfCurrentQuestion("0");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)0);

			test_for_student.SetIndexOfCurrentQuestion("2");
			Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)2);
		}

		TEST_METHOD(SaveAndLoadTestForStudent) {
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

				ofstream os("testing.dat", ios::binary);

				cereal::PortableBinaryOutputArchive oarchive(os);

				oarchive(test_for_student);
				os.close();
			}

			{
				ShortAnswerQuestion question_one(1, "What are the primary colors?");
				question_one.AddCorrectAnswer("red");
				question_one.AddCorrectAnswer("blue");
				question_one.AddCorrectAnswer("yellow");
				question_one.SetAvailablePoints("1.5,0.75,0.5,0.25");
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

				ifstream is("testing.dat", ios::binary);
				cereal::PortableBinaryInputArchive iarchive(is);

				TestForStudent test_for_student;

				iarchive(test_for_student);

				is.close();

				Assert::AreEqual(test_for_student.GetNameOfTest(), (string)"Test for testing");
				Assert::AreEqual(test_for_student.GetMaxPossibleScore(), 6.5);
				Assert::AreEqual(test_for_student.GetIndexOfCurrentQuestion(), (unsigned)2);
				Assert::IsFalse(test_for_student.IsOrderOfQuestionsFixed());

				Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[0]) == question_one);
				Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[1]) == question_two);
				Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test_for_student.GetQuestions()[2]) == question_three);
				Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test_for_student.GetQuestions()[3]) == question_four);
			}
		}
	};
}