#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

struct Employee1 {
    string empID;
    string day, month, year;
    string name;
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
};

void TimeKeeping() {
    // Open the file "1.10.txt" to read data
    ifstream inputFile("1.10.txt");                            //Print data 
    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
    }
    // Prompt the user to enter the ID to search for
    string search_term;
    cout << "Enter the ID to search for: ";
    getline(cin, search_term);                      //Searching for ID

    // Initialize a flag to indicate whether the employee is found
    bool found = false;

    // Read the file line by line
    string line;
    int i;
    int startCutting = 0;
    int endCutting = 10;
    string range1;
    cout <<"---------------------------------------------------------------------------------------------------------------------" <<endl;
    cout << "No.         Name                           Day of work                  Start Time               End Time" << endl;
    cout <<"---------------------------------------------------------------------------------------------------------------------"<<endl;
    while (getline(inputFile, line )) {
        range1 = line.substr(startCutting, endCutting - startCutting + 1);       // Choose a range to cut string to get a specific data
        // If the range contains the search term, print the line and set the flag to true
        if (range1.find(search_term) != string::npos) {
            replace(line.begin(), line.end(), '_', ' ');
            cout << line << endl;
            found = true;
        }
    }
    // Close the file
    inputFile.close();

    // If the employee is not found, print a message indicating so
    if (!found) {
        cout << "Employee not found in the file!" << endl;
    }
    
    // Open the file "1.10.txt" again to read data
    ifstream file("1.10.txt");
     // Create a vector of Employee1 objects
    vector<Employee1> employees;
    // Initialize a variable to store the total shortfall in a month
    double shortfallinMonth  = 0;

    // Print error message if something is wrong when openning file
    if (!file) {
        cerr << "Error opening the file.\n";
    }

    // Read the file line by line                                                            
    while (getline(file, line)) {
        // Create a new Employee1 object and read the employee data from the line
        Employee1 emp;
        istringstream iss(line);
        iss >> emp.empID >> emp.name >> emp.day >> emp.month >> emp.year;
        iss >> emp.startHour  >> emp.startMinute;
        iss >> emp.endHour >>  emp.endMinute;
        // Add the new employee to the vector of employees
        employees.push_back(emp);
    }

    // Loop through the vector of employees
    for (const auto& emp : employees) {

        // If the employee's ID matches the search term, calculate the time shortfall for each day
        if (emp.empID == search_term) {
            int totalStartMinutes = emp.startHour * 60 + emp.startMinute;
            int totalEndMinutes = emp.endHour * 60 + emp.endMinute;
            int expectedWorkMinutes = 10 * 60;                                   // 8 hours workday + 2 hour break
            int actualWorkMinutes = totalEndMinutes - totalStartMinutes;
            double actualWorkHours = actualWorkMinutes / 60.0;
            double shortfallMinutes = (expectedWorkMinutes - actualWorkMinutes) / 60.0;

            // Print the actual work hours and the shortfall
            if(shortfallMinutes < 0){
                cout << "This employee has worked " << round(actualWorkHours) << " hours and work more " << round(abs(shortfallMinutes)) << " than the required hour in a day.\n";
            } else {
                cout <<"This employee has worked " << round(actualWorkHours) << " hours and work less " << round(abs(shortfallMinutes)) << " than the required hour in a day.\n";
            }
            shortfallinMonth = shortfallinMonth + shortfallMinutes;
        }
    }

    // Add the shortfall to the total shortfall in a month
    if(shortfallinMonth < 0 && found == true) {
        cout << "This employee has worked more " << round(abs(shortfallinMonth)) << " hours than the required hour in a month" << endl;
    } else if(shortfallinMonth > 0 && found == true) {
        cout << "This employee has worked less " << round(abs(shortfallinMonth)) << " hours than the required hour in a month" << endl;
    }
    file.close(); 
}
