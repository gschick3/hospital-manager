#include "Clinic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void readFile(Clinic&, Clinic&, Clinic&, string);
void writeLog(Clinic&, Clinic&, Clinic&, string);
int mainMenu();
int clinicMenu();

int main() {
	Clinic heart, lung, plastic;
	Clinic* clinic = nullptr;
	readFile(heart, lung, plastic, "patient.csv");

	while (true) {
		int choice;

		system("cls");
		choice = mainMenu();
		system("cls");

		switch (choice) {
		case 1:
			clinic = &heart;
			cout << "Welcome to the Heart Clinic" << endl;
			break;
		case 2:
			clinic = &lung;
			cout << "Welcome to the Lung Clinic" << endl;
			break;
		case 3:
			clinic = &plastic;
			cout << "Welcome to Plastic Surgery" << endl;
			break;
		case 4:
			heart.rescheduleAll();
			lung.rescheduleAll();
			plastic.rescheduleAll();

			writeLog(heart, lung, plastic, "log.txt");
			return 0;
		default:
			cout << "This is impossible" << endl;
			break;
		}

		bool inClinic = true;
		while (inClinic) {
			choice = clinicMenu();
			switch (choice) {
			case 1: {
				Patient p;
				cout << "Enter patient first and last name: ";
				cin >> p.firstName >> p.lastName;
				cout << "Enter patient SSN: ";
				cin >> p.ssn;
				p.critical = false;
				clinic->addPatient(p);
				break;
			}
			case 2: {
				Patient p;
				cout << "Enter patient first and last name: ";
				cin >> p.firstName >> p.lastName;
				cout << "Enter patient SSN: ";
				cin >> p.ssn;
				p.critical = true;
				clinic->addCriticalPatient(p);
				break;
			}
			case 3: {
				clinic->operate();
				break;
			}
			case 4: {
				string ssn;
				cout << "Enter patient SSN: ";
				cin >> ssn;
				clinic->cancelPatient(ssn);
				break;
			}
			case 5: {
				clinic->listPatients();
				break;
			}
			case 6: {
				inClinic = false;
				break;
			}
			default:
				break;
			}
		}
		clinic = nullptr;
	}
}

void readFile(Clinic& heart, Clinic& lung, Clinic& plastic, string filename) {
	ifstream inFile(filename);

	if (inFile.fail()) {
		cout << "Failed to open file. " << endl;
		return;
	}

	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string clinic, firstName, lastName, ssn;

		getline(ss, clinic, ','); // get clinic
		getline(ss, firstName, ','); // get first name
		getline(ss, lastName, ','); // get last name

		getline(ss, ssn, ','); // get ssn as string
		Patient p{ firstName, lastName, ssn, false };
		if (clinic == "HC")
			heart.addPatient(p);
		else if (clinic == "LC")
			lung.addPatient(p);
		else if (clinic == "PS")
			plastic.addPatient(p);
		else if (clinic == "Q") return;
		else
			cout << "Clinic not found" << endl;
	}
	inFile.close();
}

void writeLog(Clinic& heart, Clinic& lung, Clinic& plastic, string filename) {
	ofstream outFile(filename);
	if (outFile.fail()) {
		cout << "Failure writing log" << endl;
		return;
	}
	outFile << "HEART CLINIC" << endl << endl;
	outFile << left << setw(8) << "TIME" << setw(20) << "NAME" << setw(15) << "SSN" << setw(10) << "STATUS" << "ACTION" << endl;
	for (vector<string> v : heart.getLog())
		outFile << setw(8) << v.at(5) << setw(20) << left << v.at(0) + " " + v.at(1) << setw(15) << v.at(2) << setw(10) << v.at(3) << v.at(4) << endl;

	outFile << endl << endl;
	outFile << "LUNG CLINIC" << endl << endl;
	outFile << left << setw(8) << "TIME" << setw(20) << "NAME" << setw(15) << "SSN" << setw(10) << "STATUS" << "ACTION" << endl;
	for (vector<string> v : lung.getLog())
		outFile << setw(8) << v.at(5) << setw(20) << left << v.at(0) + " " + v.at(1) << setw(15) << v.at(2) << setw(10) << v.at(3) << v.at(4) << endl;

	outFile << endl << endl;
	outFile << "PLASTIC SURGERY" << endl << endl;
	outFile << left << setw(8) << "TIME" << setw(20) << "NAME" << setw(15) << "SSN" << setw(10) << "STATUS" << "ACTION" << endl;
	for (vector<string> v : plastic.getLog())
		outFile << setw(8) << v.at(5) << setw(20) << left << v.at(0) + " " + v.at(1) << setw(15) << v.at(2) << setw(10) << v.at(3) << v.at(4) << endl;

	outFile.close();
}

int mainMenu() {
	int choice = 0;
	while (choice > 4 || choice < 1) {
		cout << endl;
		cout << "WELCOME TO RESEARCH HOSPITAL" << endl;
		cout << "1: Heart Clinic" << endl;
		cout << "2: Lung Clinic" << endl;
		cout << "3: Plastic Surgery" << endl;
		cout << "4: Quit" << endl;
		cout << "> ";
		cin >> choice;
	}
	return choice;
}

int clinicMenu() {
	int choice = 0;
	while (choice > 6 || choice < 1) {
		cout << endl;
		cout << "1: Add Patient" << endl;;
		cout << "2: Add Critical Patient" << endl;
		cout << "3: Take out Patient for operation" << endl;
		cout << "4: Cancel Patient" << endl;
		cout << "5: List Patients in queue" << endl;
		cout << "6: Change Department or exit" << endl;
		cout << "> ";
		cin >> choice;
	}
	return choice;
}