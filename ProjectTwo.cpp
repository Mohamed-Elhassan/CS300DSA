#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <limits> // For numeric_limits
using namespace std;

// Define a structure to hold course information
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

// Function to split a string by a delimiter (used for parsing prerequisites)
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Load the courses from the file into the map
void loadCourses(string fileName, map<string, Course>& courses) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file '" << fileName << "'." << endl;
        return;
    }
    else {
        cout << "File '" << fileName << "' opened successfully." << endl;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseId, title, prereq;

        // Parse the course ID and title
        getline(ss, courseId, ',');
        getline(ss, title, ',');

        // Parse prerequisites
        vector<string> prerequisites;
        while (getline(ss, prereq, ',')) {
            if (!prereq.empty()) {  // Skip empty values
                prerequisites.push_back(prereq);
            }
        }

        // Create a course and add to the map
        Course course = { courseId, title, prerequisites };
        courses[courseId] = course;
    }

    cout << "Courses loaded successfully!" << endl;
}

// Print the courses in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    for (const auto& pair : courses) {
        cout << pair.first << ", " << pair.second.title << endl;
    }
}

// Print detailed information about a specific course
void printCourseInfo(const map<string, Course>& courses, string courseId) {
    auto it = courses.find(courseId);
    if (it != courses.end()) {
        cout << "Course ID: " << it->second.courseId << endl;
        cout << "Title: " << it->second.title << endl;
        cout << "Prerequisites: ";
        if (it->second.prerequisites.empty()) {
            cout << "None";
        }
        else {
            for (const string& prereq : it->second.prerequisites) {
                cout << prereq << " ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}

// Menu function
void displayMenu() {
    cout << "Welcome to the course planner:" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do?: ";
}

int main() {
    map<string, Course> courses;
    int choice;
    string fileName, courseId;

    do {
        displayMenu();

        // Input validation to ensure an integer is entered
        while (!(cin >> choice)) {
            // Clear error flag
            cin.clear();
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice: ";
        }

        // Clear input buffer after choice to handle newlines when using getline for file name
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            getline(cin, fileName);  // Use getline to allow file names with spaces
            loadCourses(fileName, courses);
            break;
        case 2:
            cout << "Here is a sample schedule: \n";
            printCourseList(courses);
            break;
        case 3:
            cout << "Enter course ID: ";
            cin >> courseId;
            printCourseInfo(courses, courseId);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << "Invalid choice. Please select again." << endl;
        }
    } while (choice != 9);

    return 0;
}
