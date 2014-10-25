#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct homework{
	string identifier;
	int num_of_problems;
	struct problem{
		string identifier;
		string answer;
		struct response{
			string text;
			int value;
		}responses[20];
		int num_of_responses;
		int value;
	}problems[100];
	int num_of_students;
	struct student{
		string firstname;
		string lastname;
		int num_of_results;
		struct result{
			string text;
			int value;
		}results[100];
	}students[30];
}hw;


void newHomework()
{
	string input;
	cout<<"Homework Identifier: ";
	cin>>input;
	if(input == " "){
		cout<<"Averting new homework.";
		return;
	}else
		hw.identifier = input;
	cout<<"Number of Problems: ";
	cin>>hw.num_of_problems;

	for(int i = 0;i < hw.num_of_problems;i++){
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"Problem identifier: ";
		getline(cin, hw.problems[i].identifier);
		cout<<"Correct answer: ";
		getline(cin, hw.problems[i].answer);
		cout<<"Value: ";
		cin>>hw.problems[i].value;
		hw.problems[i].num_of_responses = 0;
	}
	hw.num_of_students = 0;
}

void newStudent()
{
	int n = hw.num_of_students, r;
	bool responding;
	int option;
	hw.num_of_students++;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout<<"Enter student first name: ";
	getline(cin, hw.students[n].firstname);
	cout<<"Enter student last name: ";
	getline(cin, hw.students[n].lastname);
	for(int i = 0; i < hw.num_of_problems;i++){
		cout<<"("<<hw.problems[i].identifier<<")\n"<<"Correct Answer: "<<hw.problems[i].answer<<endl;
		cout<<"[0] Create a new response\n";
		cout<<"[1] ("<<hw.problems[i].value<<") Correct.\n";
		for(int x = 0;x < hw.problems[i].num_of_responses;x++)
			cout<<"["<<x+2<<"] ("<<hw.problems[i].responses[x].value<<") "<<hw.problems[i].responses[x].text<<"\n";
		responding = true;
		do{
			cin>>option;
			switch(option){
			case 0:
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout<<"Response: ";
				r = hw.problems[i].num_of_responses++;
				getline(cin, hw.problems[i].responses[r].text);
				cout<<"Value: ";
				cin>>hw.problems[i].responses[r].value;
				hw.students[n].results[i].text = hw.problems[i].responses[r].text;
				hw.students[n].results[i].value = hw.problems[i].responses[r].value;
				cout<<"Response selected.\n";
				responding = false;
				break;
			case 1: cout<<"Full value earned, correct.\n";
				hw.students[n].results[i].text = "Correct.";
				hw.students[n].results[i].value = hw.problems[i].value;
				responding = false;
				break;
			default:
				if(option >= hw.problems[i].num_of_responses + 2)
					cout<<"Please select a response.\n";
				else{
					cout<<"Response selected: "<<hw.problems[i].responses[option-2].text<<"\n";
					hw.students[n].results[i].text = hw.problems[i].responses[option-2].text;
					hw.students[n].results[i].value = hw.problems[i].responses[option-2].value;
					responding = false;
				}
				break;
			}
		}while(responding);
	}
}

void Gradesheet()
{
	float percent, total;
	ofstream student;
	ofstream gradebook;
	gradebook.open("Results\\gradesheet.txt");
	gradebook<<hw.identifier<<endl;
	gradebook<<"Students Graded "<<hw.num_of_students<<endl;
	gradebook<<"Number of Problems "<<hw.num_of_problems<<endl;
	gradebook<<"Problems:\n";
	total = 0;
	for(int x = 0;x < hw.num_of_problems;x++){
		total += hw.problems[x].value;
		gradebook<<hw.problems[x].identifier<<" ("<<hw.problems[x].value<<" Points)\n";
	}
	for(int i = 0; i < hw.num_of_students;i++){
		percent = 0;
		student.open("Results\\"+hw.students[i].firstname + hw.students[i].lastname + "_" + hw.identifier + "_" + "feedback.txt");
		student<<"Student Name: "<<hw.students[i].firstname<<" "<<hw.students[i].lastname<<endl;
		for(int x = 0;x < hw.num_of_problems;x++){
			student<<"("<<hw.problems[x].identifier<<") ["<<
				hw.students[i].results[x].value<<"/"<<hw.problems[x].value<<" Points] "<<
				hw.students[i].results[x].text<<"\n";
			percent += hw.students[i].results[x].value;
		}
		percent /= total;
		student<<"\n\nFinal Grade: "<<(percent*100)<<"%\n";
		gradebook<<hw.students[i].firstname<<" "<<hw.students[i].lastname<<" "<<(percent*100)<<endl;
	}
	student.close();
	gradebook.close();
}

void main()
{
	int option;
	bool done = false;
	hw.identifier = "";
	hw.num_of_problems = 0;
	hw.num_of_students = 0;
	do{
		cout<<"Main menu:\n";
		if(hw.identifier != "")
			cout<<"Currently working on homework for "<<hw.identifier<<endl;
		cout<<"[1] Start a new homework assignment\n";
		cout<<"[2] Start a new student\n";
		//cout<<"[3] Adjust a student\n";
		cout<<"[4] Save Grades\n";
		cout<<"[5] Done\n";
		cin>>option;
		switch(option){
		case 1: newHomework(); break;
		case 2: newStudent(); break;
		//case 3: changeStudent(); break;
		case 4: Gradesheet(); break;
		case 5: done = true; break;
		default: cout<<"That is not an option.\n";
		}
	}while(!done);
}