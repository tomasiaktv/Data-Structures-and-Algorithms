//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Ian Tomasiak
// Version     : 1.0
// Description : ABCU Advising Assistance Program
//============================================================================

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//============================================================================
// Course structure
//============================================================================

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

//============================================================================
// Tree node structure
//============================================================================

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

//============================================================================
// Binary Search Tree class
//============================================================================

class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void Insert(Course course);
    void PrintCourseList();
    Course Search(string courseNumber);
};

// Constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Destructor
BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

// Recursively delete all nodes
void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert a course into the tree
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

// Recursive helper for inserting a course
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

// Print courses in alphanumeric order
void BinarySearchTree::PrintCourseList() {
    inOrder(root);
}

// In-order traversal: left, current, right
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);

        cout << node->course.courseNumber << ", "
            << node->course.courseTitle << endl;

        inOrder(node->right);
    }
}

// Search for one course by course number
Course BinarySearchTree::Search(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        if (current->course.courseNumber == courseNumber) {
            return current->course;
        }
        else if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    Course emptyCourse;
    return emptyCourse;
}

//============================================================================
// Helper functions
//============================================================================

// Remove spaces from the beginning and end of a string
string trim(string str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");

    if (first == string::npos || last == string::npos) {
        return "";
    }

    return str.substr(first, last - first + 1);
}

// Convert course number input to uppercase
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Split one CSV line into separate values
vector<string> splitLine(string line) {
    vector<string> tokens;
    string token;
    stringstream ss(line);

    while (getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

// Check whether a course number exists in the list of course numbers
bool courseExists(vector<string> courseNumbers, string courseNumber) {
    for (string number : courseNumbers) {
        if (number == courseNumber) {
            return true;
        }
    }

    return false;
}

//============================================================================
// Load course data from file
//============================================================================

bool loadCourses(string fileName, BinarySearchTree& courseTree) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return false;
    }

    vector<Course> tempCourses;
    vector<string> courseNumbers;
    string line;

    // First pass: read each line and create course objects
    while (getline(inputFile, line)) {
        if (trim(line).empty()) {
            continue;
        }

        vector<string> tokens = splitLine(line);

        // Each line must have at least course number and course title
        if (tokens.size() < 2) {
            cout << "Error: Invalid file format. Each line must include a course number and course title." << endl;
            inputFile.close();
            return false;
        }

        Course course;
        course.courseNumber = toUpperCase(tokens[0]);
        course.courseTitle = tokens[1];

        // Any remaining tokens are prerequisites
        for (unsigned int i = 2; i < tokens.size(); ++i) {
            string prerequisite = toUpperCase(trim(tokens[i]));

            // Ignore blank prerequisite fields caused by extra commas
            if (!prerequisite.empty()) {
                course.prerequisites.push_back(prerequisite);
            }
        }

        tempCourses.push_back(course);
        courseNumbers.push_back(course.courseNumber);
    }

    inputFile.close();

    // Second pass: validate that all prerequisites exist as courses
    for (Course course : tempCourses) {
        for (string prerequisite : course.prerequisites) {
            prerequisite = trim(prerequisite);

            if (!prerequisite.empty() && !courseExists(courseNumbers, prerequisite)) {
                cout << "Error: Prerequisite " << prerequisite
                    << " does not exist as a course in the file." << endl;
                return false;
            }
        }
    }

    // If validation passes, insert all courses into the tree
    for (Course course : tempCourses) {
        courseTree.Insert(course);
    }

    return true;
}

//============================================================================
// Main
//============================================================================

int main() {
    BinarySearchTree courseTree;

    int choice = 0;
    bool dataLoaded = false;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string fileName;

            cout << "Enter file name: ";
            getline(cin, fileName);

            if (loadCourses(fileName, courseTree)) {
                dataLoaded = true;
                cout << "Course data loaded successfully." << endl;
            }

            break;
        }

        case 2:
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }
            else {
                cout << "Here is a sample schedule:" << endl;
                courseTree.PrintCourseList();
            }

            break;

        case 3: {
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }
            else {
                string courseNumber;

                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);

                courseNumber = toUpperCase(trim(courseNumber));

                Course course = courseTree.Search(courseNumber);

                if (course.courseNumber.empty()) {
                    cout << "Course " << courseNumber << " not found." << endl;
                }
                else {
                    cout << course.courseNumber << ", " << course.courseTitle << endl;

                    if (course.prerequisites.empty()) {
                        cout << "Prerequisites: None" << endl;
                    }
                    else {
                        cout << "Prerequisites: ";

                        for (unsigned int i = 0; i < course.prerequisites.size(); ++i) {
                            Course prerequisite = courseTree.Search(course.prerequisites[i]);

                            cout << prerequisite.courseNumber << ", "
                                << prerequisite.courseTitle;

                            if (i < course.prerequisites.size() - 1) {
                                cout << " | ";
                            }
                        }

                        cout << endl;
                    }
                }
            }

            break;
        }

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}