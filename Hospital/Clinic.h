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

	// add patient to end of queue
	void addPatient(Patient);

	// add patient to front of queue after other critical patients
	void addCriticalPatient(Patient);

	// operate on patient at the front of the queue
	void operate();

	// remove given patient from the queue
	void cancelPatient(string);

	// list all patients in queue
	void listPatients();

	void addLog(Patient, string);

	void rescheduleAll();
};