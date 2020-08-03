#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "question.h"
#include "short_answer_question.h"
#include "numerical_question.h"
#include "test_for_instructor.h"
#include "test_for_student.h"

using std::cin;
using std::cout;
using std::endl;
using std::filesystem::exists;
using std::getline;
using std::ifstream;
//using std::make_unique;
using std::ios;
using std::ofstream;
using std::string;
using std::to_string;
//using std::unique_ptr;

//TODO:: Go to question!!!

void PrintQuestionBasic(shared_ptr<Question> to_print) {
	cout << to_print->GetQuestionNumber() << ". " << to_print->GetQuestion() << endl;
}

void PrintQuestionForTeacher(shared_ptr<Question> to_print) {
	cout << to_print->GetQuestionNumber() << ". " << to_print->GetQuestion() << endl;
	//cout << "Current score: " << to_print->GetCurrentScore() << endl;
	//cout << "Maximum possible score: " << to_print->GetMaxPossibleScore() << endl;

	if (dynamic_pointer_cast<NumericalQuestion>(to_print) != nullptr) {
		if (dynamic_pointer_cast<NumericalQuestion>(to_print)->GetMaxPermittedAbsoluteError() < 0) {
			cout << "The absolute error of the student's answer is not being checked for this question." << endl;
		}
		else {
			cout << "If the absolute error of the student's answer exceeds " << dynamic_pointer_cast<NumericalQuestion>(to_print)->GetMaxPermittedAbsoluteError() << ", then they will get the question wrong." << endl;
		}

		if (dynamic_pointer_cast<NumericalQuestion>(to_print)->GetPermittedRelativeError() < 0) {
			cout << "The relative error of the student's answer is not being checked for this question." << endl;
		}
		else {
			cout << "If the relative error of the student's answer exceeds " << dynamic_pointer_cast<NumericalQuestion>(to_print)->GetPermittedRelativeError() << ", then they will get the question wrong." << endl;
		}
	}

	if (to_print->GetAvailablePoints().empty() == true) {
		cout << "No points are available for this question." << endl;
	}
	else {
		cout << "Available points: ";
		for (unsigned i = 0; i < to_print->GetAvailablePoints().size(); ++i) {
			cout << to_print->GetAvailablePoints()[i];
			if (i != to_print->GetAvailablePoints().size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}

	if (to_print->GetCorrectAnswers().empty() == true) {
		cout << "You have not yet added any correct answers!" << endl;
	}
	else {
		cout << "Correct answers: ";
		for (unsigned i = 0; i < to_print->GetCorrectAnswers().size(); ++i) {
			cout << to_print->GetCorrectAnswers()[i];
			if (i != to_print->GetCorrectAnswers().size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}

	//if (to_print->GetStudentAnswers().empty() == true) {
	//	cout << "No answers have been submitted." << endl;
	//}
	//else {
	//	cout << "Submitted answers: " << endl;
	//	for (unsigned i = 0; i < to_print->GetStudentAnswers().size(); ++i) {
	//		cout << to_print->GetStudentAnswers()[i].first;
	//		if (to_print->GetStudentAnswers()[i].second == true) {
	//			cout << " - Correct" << endl;
	//		}
	//		else {
	//			cout << " - Incorrect" << endl;
	//		}
	//	}
	//}
}

void PrintQuestionForStudent(shared_ptr<Question> to_print) {
	cout << to_print->GetQuestion() << endl;
	cout << "Current score: " << to_print->GetCurrentScore() << " / " << to_print->GetMaxPossibleScore() << endl;

	if (to_print->IsQuestionCompleted() == true) {
		cout << "You cannot submit any more answers to this question!" << endl;
	}

	if (dynamic_pointer_cast<NumericalQuestion>(to_print) != nullptr) {
		if (dynamic_pointer_cast<NumericalQuestion>(to_print)->GetMaxPermittedAbsoluteError() < 0) {
			cout << "The absolute error of your answer is not being checked for this question!" << endl;
		}
		else {
			cout << "If the absolute error of your answer exceeds " << dynamic_pointer_cast<NumericalQuestion>(to_print)->GetMaxPermittedAbsoluteError() << ", then you will get the question wrong!" << endl;
		}

		if (dynamic_pointer_cast<NumericalQuestion>(to_print)->GetPermittedRelativeError() < 0) {
			cout << "The relative error of your answer is not being checked for this question!" << endl;
		}
		else {
			cout << "If the relative error of your answer exceeds " << dynamic_pointer_cast<NumericalQuestion>(to_print)->GetPermittedRelativeError() << ", then you will get the question wrong!" << endl;
		}
	}

	if (to_print->GetAvailablePoints().empty() == true) {
		cout << "No points are available for this question!" << endl;
	}
	else {
		cout << "Available points: ";
		for (unsigned i = 0; i < to_print->GetAvailablePoints().size(); ++i) {
			cout << to_print->GetAvailablePoints()[i];
			if (i != to_print->GetAvailablePoints().size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}

	if (to_print->GetStudentAnswers().empty() == true) {
		cout << "You have not submitted any answers." << endl;
	}
	else {
		cout << "Submitted answers: " << endl;
		for (unsigned i = 0; i < to_print->GetStudentAnswers().size(); ++i) {
			cout << to_print->GetStudentAnswers()[i].first;
			if (to_print->GetStudentAnswers()[i].second == true) {
				cout << " - Correct" << endl;
			}
			else {
				cout << " - Incorrect" << endl;
			}
		}
	}
}

int main(){
	string state = "Start";
	string name_of_test_being_taken = "";
	shared_ptr<TestForInstructor> test_for_instructor;
	shared_ptr<TestForStudent> test_for_student;

	while (true) {
		cout << endl;
		if (state == "Start") {
			cout << "Enter 1 to start creating a test." << endl;
			cout << "Enter 2 to load a test you have been working on creating. (Choose this option to create a version of the test you can take)." << endl;
			cout << "Enter 3 to load and take a test" << endl;
			cout << "Enter 0 to exit." << endl;

			string choice;
			getline(cin, choice);

			if (choice == "1") {
				cout << "Enter the name of the test you wish to create." << endl;
				string name_of_test;
				getline(cin, name_of_test);

				string file_name = "TestsForInstructor\\" + name_of_test + ".dat";

				if (exists(file_name) == true) {
					cout << "A test with that name already exists!" << endl;
					continue;
				}

				test_for_instructor = make_shared<TestForInstructor>(name_of_test);
				state = "Creating Test";
			}
			else if (choice == "2") {
				cout << "Enter the name of the test you wish to load." << endl;
				string name_of_test;
				getline(cin, name_of_test);

				string file_name = "TestsForInstructor\\" + name_of_test + ".dat";

				if (exists(file_name) == false) {
					cout << "That test does not exist!" << endl;
					continue;
				}

				ifstream is(file_name, ios::binary);
				cereal::PortableBinaryInputArchive iarchive(is);

				iarchive(test_for_instructor);

				is.close();

				state = "Creating Test";
			}
			else if (choice == "3") {
				cout << "Enter the name of the test you wish to take." << endl;
				string name_of_test;
				getline(cin, name_of_test);

				string file_name = "TestsForStudent\\" + name_of_test + ".dat";

				if (exists(file_name) == false) {
					cout << "That test does not exist!" << endl;
					continue;
				}

				name_of_test_being_taken = file_name;

				ifstream is(file_name, ios::binary);
				cereal::PortableBinaryInputArchive iarchive(is);

				iarchive(test_for_student);

				is.close();

				state = "Taking Test";
			}
			else if (choice == "0") {
				return 0;
			}
			else {
				cout << "That is not a valid action." << endl;
				continue;
			}

		}
		else if (state == "Creating Test") {
			if (test_for_instructor->GetNameOfTest().empty() == true) {
				cout << "This test does not have a name yet!" << endl;
			}
			else {
				cout << test_for_instructor->GetNameOfTest() << ":" <<  endl;
			}

			cout << endl;

			if (test_for_instructor->GetUnassignedQuestions().size() == 0) {
				cout << "There are no unassigned questions." << endl;
			}
			else {
				cout << "Unassigned Questions: " << endl;
				for (unsigned i = 0; i < test_for_instructor->GetUnassignedQuestions().size(); ++i) {
					PrintQuestionBasic(test_for_instructor->GetUnassignedQuestions()[i]);
				}
			}

			cout << endl;

			if (test_for_instructor->GetAssignedQuestions().size() == 0) {
				cout << "There are no categories of assigned questions." << endl;
			}
			else {
				cout << "Question Categories: " << endl;
				for (unsigned i = 0; i < test_for_instructor->GetAssignedQuestions().size(); ++i) {
					cout << get<0>(test_for_instructor->GetAssignedQuestions()[i]) << endl;

					if (get<1>(test_for_instructor->GetAssignedQuestions()[i]) < 0) {
						cout << "All questions from this category will be asked." << endl;
					}
					else {
						cout << "Up to " << get<1>(test_for_instructor->GetAssignedQuestions()[i]) << " questions from this category will be asked, in a random order." << endl;
					}

					for (unsigned j = 0; j < get<2>(test_for_instructor->GetAssignedQuestions()[i]).size(); ++j) {
						PrintQuestionBasic(get<2>(test_for_instructor->GetAssignedQuestions()[i])[j]);
					}

					if (get<2>(test_for_instructor->GetAssignedQuestions()[i]).size() == 0) {
						cout << "There are no questions in this category" << endl;
					}
				}
			}

			while (true) {
				cout << endl;

				bool current_question_exists = !test_for_instructor->GetCurrentQuestion().expired();
				bool current_question_is_numerical = false;
				if (current_question_exists && dynamic_pointer_cast<NumericalQuestion>(test_for_instructor->GetCurrentQuestion().lock()) != nullptr) {
					current_question_is_numerical = true;
				}

				if (current_question_exists) {
					cout << "Current Question:" << endl;
					PrintQuestionForTeacher(test_for_instructor->GetCurrentQuestion().lock());
				}
				if (test_for_instructor->GetCurrentCategory() != "") {
					cout << "The current question is in the category named " << test_for_instructor->GetCurrentCategory() << "." << endl;
				}
				cout << endl;

				cout << "Enter 1 to set the name of this test." << endl;
				cout << "Enter 2 to add a short answer question to this test." << endl;
				cout << "Enter 3 to add a numerical question to this test." << endl;
				cout << "Enter 4 to add a category of questions to this test." << endl;
				cout << "Enter 5 to choose which question to work on." << endl;

				if (current_question_exists) {
					cout << "Enter 6 to change the text of the current question." << endl;
					cout << "Enter 7 to add a correct answer to the current question." << endl;
					cout << "Enter 8 to remove a correct answer from the current question." << endl;
					cout << "Enter 9 to remove all correct answers from the current question." << endl;
					cout << "Enter 10 to set the available points for the current question." << endl;
					if (current_question_is_numerical) {
						cout << "Enter 11 to set the maximum permitted absolute error for the current question." << endl;
						cout << "Enter 12 to set the maximum permitted relative error for the current question." << endl;
					}
					cout << "Enter 13 to add the current question to a category of questions." << endl;
					cout << "Enter 14 to remove the current question from its category." << endl;
					cout << "Enter 15 to delete the current question." << endl;
				}

				cout << "Enter 16 to remove a category of questions (Questions in it will be unassigned but not deleted)." << endl;
				cout << "Enter 17 to switch the order of two categories." << endl;
				cout << "Enter 18 to change the number of questions to ask from a category." << endl;
				cout << "Enter 19 to save this test." << endl;
				cout << "Enter 20 to print a summary of this test's contents." << endl;
				cout << "Enter 21 to create a copy of this test that you can take." << endl;
				cout << "Enter 0 to stop working on this test, without saving." << endl;

				string creating_test_choice;
				getline(cin, creating_test_choice);

				if (creating_test_choice == "1") {
					cout << "What do you want this test to be named?" << endl;
					string name_of_test;
					getline(cin, name_of_test);
					
					test_for_instructor->SetNameOfTest(name_of_test);
				}
				else if (creating_test_choice == "2") {
					cout << "Enter the short answer question you wish to ask." << endl;
					string question_text;
					getline(cin, question_text);

					test_for_instructor->AddShortAnswerQuestion(question_text);
				}
				else if (creating_test_choice == "3") {
					cout << "Enter the numerical question you wish to ask." << endl;
					string question_text;
					getline(cin, question_text);

					test_for_instructor->AddNumericalQuestion(question_text);
				}
				else if (creating_test_choice == "4") {
					cout << "Enter the name of the category you wish to add. Nothing will be done if a category with that name already exists." << endl;
					string category_name;
					getline(cin, category_name);

					test_for_instructor->CreateQuestionCategory(category_name);
				}
				else if (creating_test_choice == "5") {
					cout << "Enter the number of the question which you wish to select." << endl;
					cout << "Nothing will be done if no question with that number exists or if you enter something that is not an integer." << endl;
					string question_number;
					getline(cin, question_number);

					test_for_instructor->SelectCurrentQuestion(question_number);
				}
				else if (creating_test_choice == "6" && current_question_exists) {
					cout << "Enter the question you wish to ask." << endl;
					string question;
					getline(cin, question);

					test_for_instructor->GetCurrentQuestion().lock()->SetQuestion(question);
				}
				else if (creating_test_choice == "7" && current_question_exists) {
					cout << "Enter the correct answer you wish to add." << endl;
					if (current_question_is_numerical) {
						cout << "If you enter anything except an integer or a decimal number, then nothing will be done." << endl;
					}

					string correct_answer;
					getline(cin, correct_answer);

					test_for_instructor->GetCurrentQuestion().lock()->AddCorrectAnswer(correct_answer);
				}
				else if (creating_test_choice == "8" && current_question_exists) {
					cout << "Enter the correct answer you wish to remove." << endl;
					cout << "Nothing will be done if that answer is not listed as a correct answer." << endl;

					string to_remove;
					getline(cin, to_remove);

					test_for_instructor->GetCurrentQuestion().lock()->RemoveCorrectAnswer(to_remove);
				}
				else if (creating_test_choice == "9" && current_question_exists) {
					cout << "Removed all correct answers from the current question." << endl;

					test_for_instructor->GetCurrentQuestion().lock()->ClearCorrectAnswers();
				}
				else if (creating_test_choice == "10" && current_question_exists) {
					cout << "Enter a list of numbers separated by commas, with the first number being the score the student" << endl;
					cout <<	"can receive by getting the question right on their first try, the second being the score they " << endl;
					cout << "can get for getting it right on the second try, and so forth." << endl;
					cout << "Every number in this sequence must be less than or equal to the previous number." << endl;
					cout << "You can input integers and decimals, but do not include any negative numbers or non-numerical symbols besides periods." << endl;
					cout << "Do not put any spaces in your list." << endl;
					cout << "Nothing will be done if your list of numbers does not fulfill these requirements." << endl;

					string available_points_string;
					getline(cin, available_points_string);

					test_for_instructor->GetCurrentQuestion().lock()->SetAvailablePoints(available_points_string);
				}
				else if (creating_test_choice == "11" && current_question_is_numerical) {
					cout << "Enter the maximum permitted absolute error for the current question." << endl;
					cout << "If you enter something that is not a valid decimal number, then nothing will be done." << endl;
					cout << "Enter a negative value if you do not want the absolute error of a student's answer to be checked." << endl;

					string set_max_permitted_absolute_error;
					getline(cin, set_max_permitted_absolute_error);

					dynamic_pointer_cast<NumericalQuestion>(test_for_instructor->GetCurrentQuestion().lock())->SetMaxPermittedAbsoluteError(set_max_permitted_absolute_error);
				}
				else if (creating_test_choice == "12" && current_question_is_numerical) {
					cout << "Enter the maximum permitted relative error for the current question." << endl;
					cout << "If you enter something that is not a valid decimal number, then nothing will be done." << endl;
					cout << "Enter a negative value if you do not want the relative error of a student's answer to be checked." << endl;

					string set_max_permitted_relative_error;
					getline(cin, set_max_permitted_relative_error);

					dynamic_pointer_cast<NumericalQuestion>(test_for_instructor->GetCurrentQuestion().lock())->SetMaxPermittedRelativeError(set_max_permitted_relative_error);
				}
				else if (creating_test_choice == "13" && current_question_exists) {
					cout << "Enter the category you wish to move the current question to." << endl;
					cout << "If that category does not exist or if the current question's maximum possible score does not equal" << endl;
					cout << "the maximum possible score of the other questions in that category, then nothing will be done" << endl;

					string category_name;
					getline(cin, category_name);

					test_for_instructor->AddCurrentQuestionToCategory(category_name);
				}
				else if (creating_test_choice == "14" && current_question_exists) {
					cout << "The current question was removed from its category." << endl;

					test_for_instructor->RemoveCurrentQuestionFromCategory();
				}
				else if (creating_test_choice == "15" && current_question_exists) {
					cout << "The current question was deleted." << endl;

					test_for_instructor->DeleteCurrentQuestion();
				}
				else if (creating_test_choice == "16") {
					cout << "Enter the name of the category of questions you wish to delete." << endl;
					cout << "Nothing will be done if no category with that name exists." << endl;
					string category_name;
					getline(cin, category_name);

					test_for_instructor->DeleteQuestionCategory(category_name);
				}
				else if (creating_test_choice == "17") {
					cout << "Enter the name of the first category." << endl;
					string first_category;
					getline(cin, first_category);
					
					cout << "Enter the name of the second category." << endl;
					string second_category;
					getline(cin, second_category);

					cout << "If either of the categories you entered does not exist, then nothing will be done." << endl;

					test_for_instructor->SwitchOrderOfCategories(first_category, second_category);
				}
				else if (creating_test_choice == "18") {
					cout << "Enter the name of category you wish to modify." << endl;
					cout << "If no category of questions with this name exists, then nothing will be done." << endl;
					string category_name;
					getline(cin, category_name);

					cout << "Enter the number of questions from this category that you wish to ask." << endl;
					cout << "If you enter something other than an integer, then nothing will be done" << endl;
					cout << "If you enter a positive integer n, then a student will be asked min(n, number of questions in this category)" << endl;
					cout << "questions from this category, in random order" << endl;
					cout << "If you enter a negative integer, then a student will be asked every question in this category, in the order shown" << endl;
					string number_of_questions;
					getline(cin, number_of_questions);


					test_for_instructor->ChangeNumberOfQuestionsToAskFromCategory(category_name, number_of_questions);
				}
				else if (creating_test_choice == "19") {
					string file_name = "TestsForInstructor\\" + test_for_instructor->GetNameOfTest() + ".dat";

					if (exists(file_name) == true) {
						cout << "A test with that name already exists!" << endl;
						cout << "Type 1 if you wish to overwrite it, and anything else if you do not (Then, you will have to rename this test to save it" << endl;

						string overwrite_or_not;
						getline(cin, overwrite_or_not);

						if (overwrite_or_not != "1") {
							continue;
						}
					}
					
					{
						ofstream os(file_name, ios::binary);

						cereal::PortableBinaryOutputArchive oarchive(os);

						oarchive(test_for_instructor);
						os.close();
					}

					cout << "Test was saved to " << file_name << "!" << endl;
				}
				else if (creating_test_choice == "20") {
					break;
				}
				else if (creating_test_choice == "21") {
					string file_name;
					for (int i = 0; ; ++i) {
						file_name = "TestsForStudent\\" + test_for_instructor->GetNameOfTest() + "_" + to_string(i) + ".dat";
						if (!exists(file_name)) {
							break;
						}
					}

					cout << "Do you want the test-taker to be able to go back and forth between questions at will? If so, enter 1. If not, enter anything else" << endl;
					bool order_fixed = true;
					string fixed_or_not;
					getline(cin, fixed_or_not);
					if (fixed_or_not == "1") {
						order_fixed = false;
					}

					{
						ofstream os(file_name, ios::binary);

						cereal::PortableBinaryOutputArchive oarchive(os);

						shared_ptr<TestForStudent> test_for_student = make_shared<TestForStudent>(*test_for_instructor);

						if (order_fixed == false) {
							test_for_student->ChangeIfOrderOfQuestionsIsFixed();
						}

						oarchive(test_for_student);
						os.close();
					}

					cout << "Test was saved to " << file_name << "!" << endl;
				}
				else if (creating_test_choice == "0") {
					cout << "Are you sure you want to discard this test?" << endl;
					cout << "Type 1 if you are sure you want to discard it!" << endl;
					cout << "If you saved it before, the file will not be deleted, but any changes you made this time will not be saved." << endl;

					string discard;
					getline(cin, discard);

					if (discard == "1") {
						cout << "Test discarded!" << endl;
						test_for_instructor.reset();
						state = "Start";
						break;
					}
					else {
						cout << "Test not discarded!" << endl;
					}
				}
				else {
					cout << "That is not a valid option!" << endl;
					continue;
				}
			}
		}
		else if (state == "Taking Test") {
			if (test_for_student->GetNameOfTest() != "") {
				cout << test_for_student->GetNameOfTest() << endl;
			}

			bool is_order_of_questions_fixed = test_for_student->IsOrderOfQuestionsFixed();

			while (true) {
				cout << endl;

				weak_ptr<Question> current_question = test_for_student->GetQuestions()[test_for_student->GetIndexOfCurrentQuestion()];

				cout << "Current score: " << test_for_student->GetCurrentScore() << " / " << test_for_student->GetMaxPossibleScore() << endl;
				cout << "You are on question " << (test_for_student->GetIndexOfCurrentQuestion() + 1) << " of " << (test_for_student->GetQuestions().size()) << "." << endl;
				PrintQuestionForStudent(current_question.lock());

				cout << "Enter 1 to go to the previous question. Nothing will be done if this is the first question." << endl;
				if (is_order_of_questions_fixed == true) {
					cout << "Enter 2 to go to the next question. Nothing will be done if this is the last question or if you have not finished this question." << endl;
				}
				else {
					cout << "Enter 2 to go to the next question. Nothing will be done if this is the last question." << endl;
				}
				if (is_order_of_questions_fixed == false) {
					cout << "Enter 3 to go to a particular question." << endl;
				}
				if (current_question.lock()->IsQuestionCompleted() == false) {
					cout << "Enter 4 to submit an answer to this question." << endl;
				}
				cout << "Enter 5 to save this test. Choose this option if you wish to exit." << endl;

				string taking_test_choice;
				getline(cin, taking_test_choice);

				if (taking_test_choice == "1") {
					if (test_for_student->GetPreviousQuestion().expired() == true) {
						cout << "No previous question exists." << endl;
					}
					continue;
				}
				else if (taking_test_choice == "2") {
					if (test_for_student->GetNextQuestion().expired() == true) {
						cout << "You cannot go to the next question." << endl;
					}
					continue;
				}
				else if (taking_test_choice == "3" && is_order_of_questions_fixed == false) {
					cout << "Enter the number of the question you wish to go to." << endl;
					cout << "If you do not enter a valid question number, nothing will be done. Do not enter a period." << endl;

					string question_to_go_to;
					getline(cin, question_to_go_to);
					
					test_for_student->GoToQuestionNumber(question_to_go_to);
				}
				else if (taking_test_choice == "4" && current_question.lock()->IsQuestionCompleted() == false) {
					cout << "Enter the answer you wish to submit." << endl;

					string answer_to_submit;
					getline(cin, answer_to_submit);

					if (current_question.lock()->SubmitStudentAnswer(answer_to_submit) == true) {
						cout << answer_to_submit << " is correct!" << endl;
					}
					else {
						cout << answer_to_submit << " is wrong!" << endl;
					}
				}
				else if (taking_test_choice == "5") {
					{
						ofstream os(name_of_test_being_taken, ios::binary);

						cereal::PortableBinaryOutputArchive oarchive(os);

						oarchive(test_for_student);
						os.close();
					}

					cout << "Test was saved to " << name_of_test_being_taken << "!" << endl;

					cout << "Enter 1 if you wish to exit to the start screen, and anything else if you wish to continue." << endl;

					string exit_or_not;
					getline(cin, exit_or_not);

					if (exit_or_not == "1") {
						test_for_student.reset();
						state = "Start";
						break;
					}
				}
				else {
					cout << "That is not a valid option!" << endl;
					continue;
				}
			}
		}
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
