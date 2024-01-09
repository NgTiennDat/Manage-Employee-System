#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "TimeKeeping.h"

using namespace std;

struct Employee {
    string employeeID;
    string firstName;
    string middleName;
    string lastName;
    string company;
    string department;
    string position;
    string birthDate;
    string hometown;
    string address;
    string email;
    string phoneNumber;
    string startDate;
};

struct Subsidirary {
    string name;
    vector<string> departments;
};

struct BKCorp {
    vector<Subsidirary> subComp;
};

// Read data from file
vector<Employee> readEmployeeDataFromFile(const string& filename) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open file for reading." << endl;
    }
    vector<Employee> employees;
    Employee employee;
    string line;
    while (getline(file, line)) {
        employee.employeeID = line;
        getline(file, employee.firstName);
        getline(file, employee.middleName);
        getline(file, employee.lastName);
        getline(file, employee.company);
        getline(file, employee.department);
        getline(file, employee.position);
        getline(file, employee.birthDate);
        getline(file, employee.hometown);
        getline(file, employee.address);
        getline(file, employee.email);
        getline(file, employee.phoneNumber);
        getline(file, employee.startDate);  
        employees.push_back(employee);
    }

    file.close();
    return employees;

}

// Count the employee of the corparion (only the person wiht position == "Nhan Vien")
int countTotalEmployees(const vector<Employee>& employees) {
    int count = 0;
    for(const Employee& emp : employees) {
        if(emp.position == "Nhan Vien") {
            count++;
        }
    }
    return count;
}

// Display the corporation
void displayBKCorporationInfo(const vector<Employee>& employees) {
    cout << "------------------------------------------" << endl;
    cout << "**** The information of BKCorporation ****" << endl;

    // Find and display President's name
    for (const Employee& president : employees) {
        if (president.position == "Chu Tich") {
            cout << "\n" << "The Corporation's President: " << president.firstName << " " << president.middleName << " " << president.lastName << endl;
        }
    }
    // Find and display subsidiary companies with directors and vice directors
    cout << "\n" << "--***-- Subsidiraries --***--" << endl;
    for (const Employee& director : employees) {
        if (director.position == "Giam Doc" && director.company != "BKCorp") {
            cout << "\n" << "--- Company: " << director.company << "\n\tDirector: " << director.firstName << " " << director.middleName << " " << director.lastName << endl;
            for (const Employee& vicedirector : employees) {
                if(vicedirector.position == "Pho Giam Doc" && vicedirector.company == director.company)
                cout <<"\tVice Director : " << vicedirector.firstName << " " << vicedirector.middleName << " " << vicedirector.lastName << endl;
            }
            cout << endl;
            // Find and display deparments, the heads and the deputies of departments
            cout << "\t--- Departments ---" << endl;
            for (const Employee& manager : employees) {
                if (manager.position == "Truong Phong" && manager.company == director.company) {
                    cout <<"\t\t"<< "-- " << manager.department << " --" << "\n\t\tHead of department: " << manager.firstName << " " << manager.middleName << " " << manager.lastName << endl;
                    for (const Employee& deputy : employees) {
                        if (deputy.position == "Pho Phong" && deputy.company == director.company && deputy.department == manager.department)
                            cout << "\t\tDeputy of department: " << deputy.firstName << " " << deputy.middleName << " " << deputy.lastName << endl;
                    }
                    cout << endl;
                }
            }
        }
    }
    // Print the total number of employees in the corporation
    cout << "*** The total number of employees in the corparation is: " << countTotalEmployees(employees)<< "\n\n";
}

// Search employee by name
void searchEmployee(const vector<Employee>& employees) {
    cout << "Type a name to search: ";
    string nameToSearch;
    getline(cin, nameToSearch);

    cout << "---------------------------------" << endl;
    cout << "Search results for " << nameToSearch << ":" << endl;
    bool found = false;
    // Loop through vector employees to find the name
    for(const Employee& employee : employees) {
        // Concatenate the first, middle, and last name to get the full name
        string fullName = employee.firstName + " " + employee.middleName + " " + employee.lastName;

        // Use the find function to check if the nameToSearch is in the fullName
        // If it is, print out the employee's details 
        if(fullName.find(nameToSearch) != string::npos) {
            cout << "EmployeeID: " << employee.employeeID << endl;
            cout << "Name: " << fullName << endl;
            cout << "Company: " << employee.company << endl;
            cout << "Department: " << employee.department << endl;
            cout << "Position: " << employee.position << endl;
            cout << "Birth Date: " << employee.birthDate << endl;
            cout << "Hometown: " << employee.hometown << endl;
            cout << "Address: " << employee.address << endl;
            cout << "Email: " << employee.email << endl;
            cout << "Phone number: " << employee.phoneNumber << endl;
            cout << "Start Date: " << employee.startDate << endl;
            cout << "---------------------------------" << endl;
            // Set found to true if a match is found
            found = true;
        }
    }

    if (!found) {
        cout << "There is no name which matches with the typed name: " << nameToSearch << "'." << endl;
    }
}

// Contruct the corporation (the subsidiaries and the departments)
void constructCompAndDep(BKCorp& corp, const vector<Employee>& employees) {
    // Loop through the vector of employees and Check if the employee's position is "Giam Doc" and the company is not "BKCorp"
    for (const Employee& director : employees) {
        if (director.position == "Giam Doc" && director.company != "BKCorp") {
            // Create a new Subsidirary object
            Subsidirary comp;
            // Set the name of the Subsidirary to the company of the director
            comp.name = director.company;
            // This for loop like the previous one
            for (const Employee& manager : employees) {
                if (manager.position == "Truong Phong" && manager.company == director.company) {
                    comp.departments.push_back(manager.department);
                }
            }
            corp.subComp.push_back(comp);
        }
    }
}

// Display the department information
void displayUnitInfo(const BKCorp& corporation, const vector<Employee>& employees) {
    // Declare variables to store the company and department names
    string subCompany;
    string dept;
    cout << "Enter company's name: ";
    getline(cin, subCompany);
    
    // If the entered company is "BKCorp", display the employees of "BKCorp"
    if (subCompany == "BKCorp") {
        for (const Employee& unitEmp : employees) {
            if (unitEmp.company == subCompany)
                cout << "ID: " << unitEmp.employeeID << " | Name: " << unitEmp.firstName << " " << unitEmp.middleName << " " << unitEmp.lastName << endl;
        }
    }
    else {
        // If the entered company is not "BKCorp", find the subsidiary in the corporation
        bool foundSub = false;
        for (int i = 0; i < corporation.subComp.size(); i++) {
            if (corporation.subComp[i].name == subCompany) {
                foundSub = true;
                // If the subsidiary is found, display its information
                cout << setw(5) << "------- The information of " << subCompany << " -----------" << endl;
                for (const Employee& unitEmp : employees) {
                    if (unitEmp.company == subCompany && unitEmp.position != "Truong Phong" && unitEmp.position != "Pho Phong")
                        cout << setw(10) << "ID: " << unitEmp.employeeID << " | Name: " << unitEmp.firstName << " " << unitEmp.middleName << " " << unitEmp.lastName << endl;
                }
                cout << "Enter department's name: ";
                getline(cin, dept);
                // Find the department in the subsidiary
                bool foundDept = false;
                for (int j = 0; j < corporation.subComp[i].departments.size(); j++) {
                    if (corporation.subComp[i].departments[j] == dept) {
                        foundDept = true;
                        // If the department is found, display its information
                        cout << setw(5) << "------- The information of " << dept << " -----------" << endl;
                        for (const Employee& unitEmp : employees) {
                            if (unitEmp.company == subCompany && unitEmp.department == dept && unitEmp.position != "Truong Phong" 
                            && unitEmp.position != "Pho Phong" && unitEmp.position != "Giam Doc" && unitEmp.position != "Pho Giam Doc") {
                                cout << setw(10) << "ID: " << unitEmp.employeeID << " | Name: " << unitEmp.firstName << " " << unitEmp.middleName << " " << unitEmp.lastName << endl;
                            }
                        }
                    }
                }
                // If the department is not found, print a message indicating so
                if(!foundDept) {
                    cout << "There is no department which you searched in the subsidiary!" << endl;
                }
            }
        }
        // If the subsidiary is not found, print a message indicating so
        if(!foundSub) {
            cout << "There is no sub company which you search in corporation!" << endl;
        }
    }
}

// Add employee
void addNewEmployee(vector<Employee>& employees, int& totalEmployees) {
    // Create a new Employee object
    Employee newEmployee;

    // Increment the total number of employees
    totalEmployees++;

    // Prompt the user to enter the employee's details and read the user's input
    cout << "Enter employee id: ";
    getline(cin, newEmployee.employeeID);

    cout << "Enter employee first name: ";
    getline(cin, newEmployee.firstName);
    
    cout << "Enter employee middle name: ";
    getline(cin, newEmployee.middleName);

    cout << "Enter employee last name: ";
    getline(cin, newEmployee.lastName);

    cout << "Enter employee company: ";
    getline(cin, newEmployee.company);

    cout << "Enter employee department: ";
    getline(cin, newEmployee.department);
    
    cout << "Enter employee position: ";
    getline(cin, newEmployee.position);
    
    cout << "Enter employee birthDate: ";
    getline(cin, newEmployee.birthDate);
    
    cout << "Enter employee hometown: ";
    getline(cin, newEmployee.hometown);

    cout << "Enter employee address: ";
    getline(cin, newEmployee.address);

    cout << "Enter employee email: ";
    getline(cin, newEmployee.email);

    cout << "Enter employee phoneNum: ";
    getline(cin, newEmployee.phoneNumber);

    cout << "Enter employee startDate: ";
    getline(cin, newEmployee.startDate);

    // Open the input file in append mode
    ofstream inputFile;
    inputFile.open("newInput.txt", ios::app);

    // Write the employee's details to the file
    inputFile << newEmployee.employeeID << endl;
    inputFile << newEmployee.firstName << endl;
    inputFile << newEmployee.middleName << endl;
    inputFile << newEmployee.lastName << endl;
    inputFile << newEmployee.company << endl;
    inputFile << newEmployee.department << endl;
    inputFile << newEmployee.position << endl;
    inputFile << newEmployee.birthDate << endl;
    inputFile << newEmployee.hometown << endl;
    inputFile << newEmployee.address << endl;
    inputFile << newEmployee.email << endl;
    inputFile << newEmployee.phoneNumber << endl;
    inputFile << newEmployee.startDate << endl;

    // Close the file
    inputFile.close();

    // Read the employee data from the file "newInput.txt"
    readEmployeeDataFromFile("newInput.txt");
    // Add the new employee to the vector of employees
    employees.push_back(newEmployee);

    // Print a success message and the total number of employees
    cout << "The new employee has been added successfully. Total employees: " << totalEmployees << endl;
}

// Update the basic information of a employee
void updateEmployeeInfo(vector<Employee>& employees) {
    cout << "Get employee'id to update: ";
    string employeeId;
    getline(cin, employeeId);

    bool found = false; // Variable to check if the employee is found or not

    // Iterate through the list of employees to find the employee to update
    for(Employee& employee : employees) {
        if(employee.employeeID == employeeId) {
            found = true;
            
            while(true) {
                cout << "What information do you want to update:" << endl;
                cout << "1. First name" << endl;
                cout << "2. Middle name" << endl;
                cout << "3. Last name" << endl;
                cout << "4. Company" << endl;
                cout << "5. Department" << endl;
                cout << "6. Position" << endl;
                cout << "7. Birthday" << endl;
                cout << "8. Hometown" << endl;
                cout << "9. Address" << endl;
                cout << "10. Email" << endl;
                cout << "11. Phone number" << endl;
                cout << "12. Start day" << endl;
                cout << "0. Done!" << endl;
                cout << "Enter your option: ";

                int option;
                cin >> option;
                cin.ignore(); // Clear newline character

                string change = ""; // Information to update
                string input = ""; // Updated information

                // Handle user's choice
                switch (option) {
                    case 1:
                        change = employee.firstName;
                        break;
                    case 2:
                        change = employee.middleName;
                        break;
                    case 3:
                        change = employee.lastName;
                        break;
                    case 4:
                        change = employee.company;
                        break;
                    case 5:
                        change = employee.department;
                        break;
                    case 6:
                        change = employee.position;
                        break;
                    case 7:
                        change = employee.birthDate;
                        break;
                    case 8:
                        change = employee.hometown;
                        break;
                    case 9:
                        change = employee.address;
                        break;
                    case 10:
                        change = employee.email;
                        break;
                    case 11:
                        change = employee.phoneNumber;
                        break;
                    case 12:
                        change = employee.startDate;
                        break;
                    default:
                        cout << "Invalid option selected." << endl;
                    return;
                }

                // Require the user to enter new information
                cout << "Enter new value for " << change << " of employee with ID " << employeeId << ": ";
                getline(cin, input);

                // Update new information to the employee object
                if (change == employee.firstName) {
                    employee.firstName = input;
                } else if (change == employee.middleName) {
                    employee.middleName = input;
                } else if (change == employee.lastName) {
                    employee.lastName = input;
                } else if (change == employee.company) {
                    employee.company = input;
                } else if (change == employee.department) {
                    employee.department = input;
                } else if (change == employee.position) {
                    employee.position = input;
                } else if (change == employee.birthDate) {
                    employee.birthDate = input;
                } else if (change == employee.hometown) {
                    employee.hometown = input;
                } else if (change == employee.address) {
                    employee.address = input;
                } else if (change == employee.email) {
                    employee.email = input;
                } else if (change == employee.phoneNumber) {
                    employee.phoneNumber = input;
                } else if (change == employee.startDate) {
                    employee.startDate = input;
                }

                // Open a temporary file to write the updated employee list to
                ofstream tempFile("temp.txt");

                // Check whether opening the temporary file was successful or not
                if (!tempFile.is_open()) {
                    cout << "Failed to open file!" << endl;
                    return;
                }

                // Write employee list to temporary file
                for (const Employee& emp : employees) {
                    tempFile << emp.employeeID << endl;
                    tempFile << emp.firstName << endl;
                    tempFile << emp.middleName << endl;
                    tempFile << emp.lastName << endl;
                    tempFile << emp.company << endl;
                    tempFile << emp.department << endl;
                    tempFile << emp.position << endl;
                    tempFile << emp.birthDate << endl;
                    tempFile << emp.hometown << endl;
                    tempFile << emp.address << endl;
                    tempFile << emp.email << endl;
                    tempFile << emp.phoneNumber << endl;
                    tempFile << emp.startDate << endl;
                }

                tempFile.close();

                // Delete the original file
                if (remove("newInput.txt") != 0) {
                    cout << "Error deleting original file." << endl;
                    return;
                }
                
                // Rename the temporary file to the original file
                if (rename("temp.txt", "newInput.txt") != 0) {
                    cout << "Error renaming temp file." << endl;
                    return;
                }

                cout << "Employee information updated successfully." << endl;
                
                // Ask the user if they want to update continuously
                cout << "Do you want to continue updating? (y/n)" << endl;
                char continueOrNot;
                cin >> continueOrNot;
                bool isContinue = false;

                if(continueOrNot != 'y' && continueOrNot != 'Y') {
                    cout << "Updating employee information ends!" << endl;
                    return;
                }
                cin.ignore();
            }
        }
    }

    if (!found) {
        cout << "Employee with ID " << employeeId << " not found!" << endl;
    }
}

// The funtion to run the Employee Management System
void runningEMS() {
    // Create a vector of Employee objects and read the employee data from the file "newInput.txt"
    vector<Employee> emp;
    emp = readEmployeeDataFromFile("newInput.txt");

    // Create a BKCorp object and construct its subsidiaries and their departments
    BKCorp corporation;
    constructCompAndDep(corporation, emp);

    // Count the total number of employees
    int totalEmployees = countTotalEmployees(emp);

    // Declare a variable to store the user's option
    int option; 
    // Start a loop that continues until the user chooses option 7
    do {
        cout << "\n-------- Option List ----------\n";
        cout << "1. Display BK Corporation" << endl;
        cout << "2. Search employee" << endl;
        cout << "3. Display employee's working status" << endl;
        cout << "4. Display department" << endl;
        cout << "5. Add employee" << endl;
        cout << "6. Update employee" << endl;
        cout << "7. End the program" << endl;
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore(); // Clear the newline character from the input buffer

        // Perform an action based on the user's option
        switch(option) {
        case 1:
            displayBKCorporationInfo(emp);
            break;
        case 2:
            searchEmployee(emp);
            break;
        case 3:
            TimeKeeping();
            break;
        case 4:
            displayUnitInfo(corporation, emp);
            break;
        case 5:
            addNewEmployee(emp, totalEmployees);
            break;
        case 6:
            updateEmployeeInfo(emp);
            break;
        case 7:
            cout << "The program ends" << endl;
            break;
        default:
            cout << "Your option is invalid! Please, try again" << endl;
            break;
        }
    } while (option != 7); // End the loop if the user chooses option 7
}

int main() {
    runningEMS();
}
