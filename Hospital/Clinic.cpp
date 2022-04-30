#include "Clinic.h"
#include <iostream>
#include <iomanip>

Clinic::Clinic() {
	head = nullptr;
	patientCount = 0;
}

Clinic::~Clinic() {
	Node* currNode, * lastNode;
	if (head == nullptr) return;
	currNode = head;
	lastNode = head;
	head = nullptr;
	while (currNode->nextNode != nullptr) {
		currNode = currNode->nextNode;
		delete lastNode;
		lastNode = currNode;
	}
	delete currNode;
	lastNode = nullptr;
	currNode = nullptr;
}

void Clinic::addPatient(Patient p) {
	if (patientCount >= 10) {
		cout << "Clinic is full" << endl;
		return;
	}

	Node* newNode = new Node{ p, nullptr };

	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* currNode = head;
		while (currNode->nextNode != nullptr)
			currNode = currNode->nextNode;
		currNode->nextNode = newNode;
	}
	cout << "Patient added" << endl;
	addLog(p, "added");
	patientCount++;
}

void Clinic::addCriticalPatient(Patient p) {
	if (patientCount >= 10) {
		cout << "Clinic is full" << endl;
		return;
	}

	if (head == nullptr) {
		head = new Node{ p, nullptr };
	}
	else if (!head->data.critical) {
		head = new Node{ p, head };
	}
	else {
		Node* lastNode = head;
		Node* nextNode = head->nextNode;
		while (nextNode != nullptr && nextNode->data.critical) {
			lastNode = nextNode;
			nextNode = nextNode->nextNode;
		}
		lastNode->nextNode = new Node{ p, nextNode };
	}
	cout << "Patient added" << endl;
	addLog(p, "added");
	patientCount++;
}

void Clinic::operate() {
	if (head == nullptr) {
		cout << "No patients to operate on" << endl;
		return;
	}
	Node* currNode = head;
	cout << "Operated on: " << currNode->data.firstName << " " << currNode->data.lastName << endl;
	addLog(currNode->data, "operated");
	head = head->nextNode;
	delete currNode;
	currNode = nullptr;
	patientCount--;
}

void Clinic::cancelPatient(string id) {
	Node* currNode = head;
	Node* lastNode = currNode;
	if (head == nullptr) {
		cout << "Patient not found" << endl;
		return;
	}

	if (head->data.ssn == id) {
		head = head->nextNode;
		delete currNode;
		currNode = nullptr;
		patientCount--;
		return;
	}

	while (currNode->nextNode != nullptr) {
		lastNode = currNode;
		currNode = currNode->nextNode;
		if (currNode->data.ssn == id) {
			cout << "Removed " << currNode->data.firstName << " " << currNode->data.lastName << endl;
			addLog(currNode->data, "canceled");
			lastNode->nextNode = currNode->nextNode;
			patientCount--;
			delete currNode;
			currNode = nullptr;
			return;
		}
	}

	cout << "Patient not found" << endl;

}

void Clinic::listPatients() {
	Node* currNode = head;
	if (currNode == nullptr) {
		cout << "No patients in clinic" << endl;
		return;
	}
	cout << setw(20) << left << "NAME" << setw(15) << "SSN" << "STATUS" << endl;
	while (currNode != nullptr) {
		cout << setw(20) << left << currNode->data.firstName + " " + currNode->data.lastName << setw(15) << currNode->data.ssn << (currNode->data.critical ? "CRITICAL" : "REG") << endl;
		currNode = currNode->nextNode;
	}
}

void Clinic::addLog(Patient p, string type) {
	vector<string> data;
	time_t t = time(0);   // get time now

	struct tm now;
	localtime_s(&now, &t);
	string time = to_string(now.tm_hour) + ':' + to_string(now.tm_min);
	
	data.push_back(p.firstName);
	data.push_back(p.lastName);
	data.push_back(p.ssn);
	data.push_back((p.critical ? "CRITICAL" : "REG"));
	data.push_back(type);
	data.push_back(time);
	log.push_back(data);
}

void Clinic::rescheduleAll() {
	Node* currNode = head;
	if (currNode == nullptr) {
		cout << "No patients in clinic" << endl;
		return;
	}

	while (currNode != nullptr) {
		addLog(currNode->data, "reschedule");
		currNode = currNode->nextNode;
	}
}