#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
	int numberOfEventsP1, numberOfEventsP2, i, j, k;
	cout << "Enter the number of events in process1 and process2:" << endl;
	cin >> numberOfEventsP1 >> numberOfEventsP2;
	int timerP1[numberOfEventsP1], timerP2[numberOfEventsP2];
	int curtime = 1;
	for(i=0; i<numberOfEventsP1; i++){
		timerP1[i] = curtime;
		curtime += 1;
	} 

	curtime = 1;
	for(i=0; i<numberOfEventsP2; i++){
		timerP2[i] = curtime;
		curtime += 1;
	}
	
	cout << "Enter the dependency matrix\n";
	cout << "0 : No dependency\n";
	cout << "1 : Dependency from event i of process1 1 to event j of process2\n";
	cout << "2 : Dependency from event j of process1 2 to event i of process2\n";
	int dependencyMatrix[numberOfEventsP1][numberOfEventsP2];

	for(i=0; i<numberOfEventsP1; i++){
		for(j=0; j<numberOfEventsP2; j++){
			cout << "i: " << i << " j: " << j << ":\t";
			cin >> dependencyMatrix[i][j];
		}
	}

	for(i=0; i<numberOfEventsP1; i++){
		for(j=0; j<numberOfEventsP2; j++){
			if(dependencyMatrix[i][j] == 1){
				if(timerP1[i]+1 > timerP2[j]){
					timerP2[j] = timerP1[i]+1;
					for(k=j; k<numberOfEventsP2-1; k++){
						timerP2[k+1] = timerP2[k] + 1;
					}
				}
			}
			else if(dependencyMatrix[i][j] == -1){
				if(timerP2[j]+1 > timerP1[i]){
					timerP1[i] = timerP2[j]+1;
					for(k=i; k<numberOfEventsP1-1; k++){
						timerP1[k+1] = timerP1[k] + 1;
					}
				}
			}
		}
	}

	cout << "Logical clock for process1:\n";
	for(i=0; i<numberOfEventsP1; i++){
		cout << "Event " << i << ": " << timerP1[i] << endl; 
	}
	cout << endl;

	cout << "Logical clock for process2:\n";
	for(i=0; i<numberOfEventsP2; i++){
		cout << "Event " << i << ": " << timerP2[i] << endl; 
	}
	cout << endl;

	return 0;
}
