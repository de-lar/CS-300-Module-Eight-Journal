#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Holds course data
struct Course {
    string name;
    vector<string> prerequisites;
};

// Function to load data from file into hash table
void loadDataStructure(const string& filename, unordered_map<string, Course>& courses) {
    ifstream file(filename); //Opens file
    //If file can not be opened, print error
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return; //exit function
    }

    string line;
    //Loops through lines in file
    while (getline(file, line)) {
        // Split the line into parameters
        size_t pos = line.find(",");
        string courseNumber = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        string name = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Extract prerequisites
        vector<string> prereqs;
        while (!line.empty()) {
            pos = line.find(",");
            string prereq = line.substr(0, pos);
            prereqs.push_back(prereq);
            if (pos == string::npos)
                break;
            line.erase(0, pos + 1);
        }

        // Store course information in the hash table
        Course course;
        course.name = name;
        course.prerequisites = prereqs;
        courses[courseNumber] = course;
    }

    file.close(); //close file
}

// Function to print the course list in alphanumeric order
void printCourseList(const unordered_map<string, Course>& courses) {
    vector<string> courseNumbers;
    //loop through map and store course information in vector
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }
    sort(courseNumbers.begin(), courseNumbers.end()); //sort course numbers in alphanumeric order

    cout << "Here is a sample schedule:" << endl;
    //Loop through sorted course numbers
    for (const string& courseNumber : courseNumbers) {
        //Print course information
        cout << courseNumber << ", " << courses.at(courseNumber).name << endl;
    }
}

// Function to print course information
void printCourse(const unordered_map<string, Course>& courses) {
    //Promt user to enter course number and store it
    string courseNumber;
    cout << "What course do you want to know about?";
    cin >> courseNumber;

    //Check if course exists in table
    if (courses.find(courseNumber) != courses.end()) {
        //Print course inforamtion
        cout << courseNumber << ", " << courses.at(courseNumber).name << endl;
        cout << " Prerequisites: ";
        //Loop through course information and print them
        for (const string& prereq : courses.at(courseNumber).prerequisites) {
            cout << prereq << ", ";
        }
        cout << endl;
    } else {
        cout << "Course not found." << endl; //If doesnt exist, print error
    }
}

int main() {
    unordered_map<string, Course> courses; //Hash table to store course
    bool exit = false;

    //Display menu and prompt user to select an option
    cout << "Welcome to the course planner." << endl;

    while (!exit) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        int choice;
        cin >> choice; //Read and stores user input

        switch(choice) {
            case 1:
                {
                    string filename;
                    cout << "Enter the file name: "; //File name should be ABCU_Advising_Program_Input.txt
                    cin >> filename;
                    loadDataStructure(filename, courses); //Call function to load data from file in the data structure
                    cout << "Data is loaded." << endl;
                    break;
                }
            case 2:
                printCourseList(courses); //Calls function to print course list
                break;
            case 3:
                printCourse(courses); //Calls functionn to print course information
                break;
            case 4:
                exit = true; //Set exit to true to exit the program
                break;
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    cout << "Thank you for using the course planner!" << endl;

    return 0;
}

