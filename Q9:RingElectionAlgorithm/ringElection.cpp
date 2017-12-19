#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Process{
public:
	int id;
	bool alive;
};

Process p[100];
int initiatorID = -1;
int coordinatorID = -1;
int numberOfProcesses = -1;

void display(){
	int i;
	cout << "Number Of Processes: " << numberOfProcesses << endl;
	for(i=0; i<numberOfProcesses; i++){
		cout << "P" << p[i].id << "-> ";
		if(p[i].alive){
			cout << "Alive ";
		}
		else{
			cout << "Dead ";
		}
		if(p[i].id == initiatorID){
			cout << "-> Initiator ";
		}
		if(p[i].id == coordinatorID){
			cout << "-> Coordinator ";
		}
		cout << endl;
	}
	cout << endl;
}

void buildRing(){
	std::vector<Process> aliveProcesses;
	int numberOfAliveProcesses = 0, i;
	for(i=0; i<numberOfProcesses; i++){
		if(p[i].alive){
			aliveProcesses.push_back(p[i]);
			numberOfAliveProcesses++;
		}
	}
	int index = -1;
	for(i=0; i<numberOfAliveProcesses; i++){
		//cout << aliveProcesses[i].id << " ";
		if(aliveProcesses[i].id == initiatorID){
			//cout << "Initiator index = " << i << endl;
			index = i;
			break;
		}
	}

	for(i=0; i<numberOfAliveProcesses; i++){
		int curProcess, nextProcess;
		curProcess = index;
		nextProcess = (index+1)%numberOfAliveProcesses;
		cout << "Message from P" << aliveProcesses[curProcess].id << " -> P" << aliveProcesses[nextProcess].id << endl;
		index = (index+1)%numberOfAliveProcesses;
	}
	coordinatorID = aliveProcesses[numberOfAliveProcesses-1].id;
	cout << "New chosen coordinator: " << coordinatorID << endl << endl;
}

void initializeProcesses(){
	cout << "Enter the Number Of Processes: ";
	cin >> numberOfProcesses;
	int i;
	for(i=0; i<numberOfProcesses; i++){
		p[i].id = i;
		p[i].alive = true;
	}
	initiatorID = 0; //default initial value
	display();
	buildRing();
}

void crashProcess(){
	cout << "Enter the process id of the process to crash: ";
	int crashProcessID, i, newInitiatorID;
	cin >> crashProcessID;
	p[crashProcessID].alive = false;
	if(crashProcessID == initiatorID){
		bool found = false;
		while(!found){
			newInitiatorID = rand()%numberOfProcesses;
			if(p[newInitiatorID].alive){
				found = true;
			}
		}
		initiatorID = newInitiatorID;
	}
	display();
	buildRing();	
}

void recoverProcess(){
	cout << "Enter the process id of the process to recover: ";
	int recoverID;
	cin >> recoverID;
	p[recoverID].alive = true;
	display();	
	buildRing();
}

int main(int argc, char const *argv[]) {
	initializeProcesses();
	int choice = 0;
	while(1){
		cout << "1. Crash Process\n2. Recover Process\n3. Display\n4. Exit\n";
		cin >> choice;
		switch(choice){
			case 1:
				crashProcess();
				break;
			case 2:
				recoverProcess();
				break;
			case 3:
				display();
				break;
			case 4:
				exit(0);
			default: break;
		}
	}
	return 0;
}