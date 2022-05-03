#pragma once
#include <string>
#include <vector>

using namespace std;

struct Patient {
	string firstName;
	string lastName;
	string ssn;
	bool critical;
};

struct Node {
	Patient data;
	Node* nextNode;
};

class Clinic {
private:
	int patientCount;
	Node* head;
	vector<vector<string>> log;

public:
	Clinic();
	~Clinic();

	vector<vector<string>> getLog() { return log; }

	// pre: Patient info given
	// post: Patient added to end of queue
	void addPatient(Patient);

	// pre: Patient info given
	// post: Patient added to beginning of queue
	void addCriticalPatient(Patient);

	// pre: none
	// post: First patient removed from queue for operation
	void operate();

	// pre: SSN of patient given
	// post: Patient is removed from queue
	void cancelPatient(string);

	// pre: none
	// post: All patient info is printed to console
	void listPatients();

	// pre: Patient info and action is given
	// post: Action is added to clinic log
	void addLog(Patient, string);

	// pre: none
	// post: All remaining patients are logged as "reschedule"
	void rescheduleAll();
};