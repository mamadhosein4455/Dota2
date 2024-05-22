#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using namespace std; 


class UUser {
private:
    string username;
    string password;
    int type;

public:
    UUser() {}

    UUser(const string& uname, const string& pwd, int t) : username(uname), password(pwd), type(t) {}
    string getUsername() const {
        return username;
    }

    void setUsername(const string& uname) {
        username = uname;
    }

    string getPassword() const {
        return password;
    }

    void setPassword(const string& pwd) {
        password = pwd;
    }

    int getType() const {
        return type;
    }

    void setType(int t) {
        type = t;
    }

    void displayUser() const {
        cout << "Username: " << username << ", Password: " << password << ", Type: " << type << endl;
    }
};

class Admin : public UUser {
public:
    Admin(const string& uname, const string& pwd, int t) : UUser(uname, pwd, t) {}

    void displayAdmin() const {
        cout << "Admin Username: " << getUsername() << endl;
        cout << "Admin Password: " << getPassword() << endl;
        cout << "Admin Type: " << getType() << endl;
    }

    void createAccount(const string& uname, const string& pwd, int t) {
        UUser newUser(uname, pwd, t);
        saveAccountToFile(newUser);
    }

    void editAccount(const string& uname, const string& pwd, const string& newUname = "", const string& newPwd = "", int newType = -1) {
        ifstream inFile("accounts.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        if (inFile.is_open() && tempFile.is_open()) {
            while (getline(inFile, line)) {
                stringstream ss(line);
                string fileUname, filePwd;
                int fileType;
                ss >> fileUname >> filePwd >> fileType;

                if (fileUname == uname && filePwd == pwd) {
                    found = true;
                    // Update the user's information
                    if (!newUname.empty()) {
                        fileUname = newUname;
                    }
                    if (!newPwd.empty()) {
                        filePwd = newPwd;
                    }
                    if (newType != -1) {
                        fileType = newType;
                    }
                    tempFile << fileUname << " " << filePwd << " " << fileType << endl;
                }
                else {
                    tempFile << line << endl;
                }
            }
            inFile.close();
            tempFile.close();

            if (found) {
                // Replace the old file with the new file
                remove("accounts.txt");
                rename("temp.txt", "accounts.txt");
                cout << "Account for " << uname << " has been updated." << endl;
            }
            else {
                remove("temp.txt");
                cout << "Error: Account for " << uname << " with provided password not found." << endl;
            }
        }
        else {
            cerr << "Error: Unable to open file for reading or writing." << endl;
        }
    }

    void deleteAccount(const string& uname, const string& pwd) {
        ifstream inFile("accounts.txt");
        ofstream tempFile("temp.txt");
        string line;
        bool found = false;

        if (inFile.is_open() && tempFile.is_open()) {
            while (getline(inFile, line)) {
                stringstream ss(line);
                string fileUname, filePwd;
                int fileType;
                ss >> fileUname >> filePwd >> fileType;

                if (fileUname == uname && filePwd == pwd) {
                    found = true;
                    // Do not write this account to the temp file, effectively deleting it
                }
                else {
                    tempFile << line << endl;
                }
            }
            inFile.close();
            tempFile.close();

            if (found) {
                // Replace the old file with the new file
                remove("accounts.txt");
                rename("temp.txt", "accounts.txt");
                cout << "Account for " << uname << " has been deleted." << endl;
            }
            else {
                remove("temp.txt");
                cout << "Error: Account for " << uname << " with provided password not found." << endl;
            }
        }
        else {
            cerr << "Error: Unable to open file for reading or writing." << endl;
        }
    }

    void printAccounts() {
        ifstream inFile("accounts.txt");
        string line;

        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                stringstream ss(line);
                string fileUname, filePwd;
                int fileType;
                ss >> fileUname >> filePwd >> fileType;

                if (fileType == 1) {
                    cout << "Student   username: " << fileUname << "  password: " << filePwd << endl;
                }
                else {
                    cout << "Professor username: " << fileUname << "  password: " << filePwd << endl;
                }
            }
            inFile.close();
        }
        else {
            cerr << "Error: Unable to open file for reading." << endl;
        }
    }

private:
    void saveAccountToFile(const UUser& user) {
        ofstream outFile("accounts.txt", ios::app);
        if (outFile.is_open()) {
            outFile << user.getUsername() << " " << user.getPassword() << " " << user.getType() << endl;
            outFile.close();
            cout << "Account for " << user.getUsername() << " has been saved to file." << endl;
        }
        else {
            cerr << "Unable to open file for writing." << endl;
        }
    }
};

class Darss {
private:
    string professor;
    string TheNameOfClass;
    vector<pair<string, int>> StudentOfClass;

public:
    void addClass(const string& username, const string& password, const string& className) {
        // ????? ???? ????? ?? ???? accounts ? ??? ??
        ifstream accountsFile("accounts.txt");
        bool professorExists = false;

        if (accountsFile.is_open()) {
            string line;
            while (getline(accountsFile, line)) {
                stringstream ss(line);
                string fileUname, filePwd;
                int fileType;
                ss >> fileUname >> filePwd >> fileType;

                if (fileUname == username && filePwd == password && fileType == 2) {
                    professorExists = true;
                    professor = username;
                    TheNameOfClass = className;
                    break;
                }
            }
            accountsFile.close();
        }

        if (!professorExists) {
            cout << "Error: Professor with provided username and password not found." << endl;
            return;
        }

        // ????? ??? ????? ? ??? ??? ?? ???? Classes
        ofstream classesFile("Classes.txt", ios::app);
        if (classesFile.is_open()) {
            classesFile << "Professor: " << professor << " Class: " << TheNameOfClass << endl;

            string studentName;
            int grade;

            while (true) {
                cout << "Enter student name (or type 'END' to finish): ";
                cin >> studentName;

                if (studentName == "END") {
                    break;
                }

                // ????? ???? ?????? ?? ???? accounts
                ifstream accountsFile("accounts.txt");
                bool studentExists = false;

                if (accountsFile.is_open()) {
                    string line;
                    while (getline(accountsFile, line)) {
                        stringstream ss(line);
                        string fileUname, filePwd;
                        int fileType;
                        ss >> fileUname >> filePwd >> fileType;

                        if (fileUname == studentName && fileType == 1) {
                            studentExists = true;
                            break;
                        }
                    }
                    accountsFile.close();
                }

                if (!studentExists) {
                    cout << "Error: Student with provided username not found." << endl;
                    continue;
                }

                cout << "Enter grade for " << studentName << ": ";
                cin >> grade;

                classesFile << "Student: " << studentName << " Grade: " << grade << endl;
                StudentOfClass.push_back(make_pair(studentName, grade));
            }

            classesFile.close();
        }
        else {
            cerr << "Error: Unable to open Classes file for writing." << endl;
        }
    }

    void addStudentsToClass(const string& professor, const string& className) {
        ifstream classesFile("Classes.txt");
        ofstream tempFile("tempClasses.txt", ios::app);
        string line;
        bool classExists = false;
        bool inTargetClass = false;

        if (classesFile.is_open() && tempFile.is_open()) {
            while (getline(classesFile, line)) {
                // Copy the line to the temporary file
                tempFile << line << endl;

                // Check if the current line matches the class we are looking for
                if (line == "Professor: " + professor + " Class: " + className) {
                    classExists = true;
                    inTargetClass = true;
                }
                else if (line.find("Professor: ") != string::npos && inTargetClass) {
                    // We reached a new class section, stop adding students
                    inTargetClass = false;
                }

                // If we are in the target class section, keep adding students
                if (inTargetClass) {
                    string studentName;
                    int grade;

                    while (true) {
                        cout << "Enter student name to add (or type 'END' to finish): ";
                        cin >> studentName;

                        if (studentName == "END") {
                            break;
                        }

                        // Check if student exists in accounts file
                        ifstream accountsFile("accounts.txt");
                        bool studentExists = false;

                        if (accountsFile.is_open()) {
                            string accLine;
                            while (getline(accountsFile, accLine)) {
                                stringstream ss(accLine);
                                string fileUname, filePwd;
                                int fileType;
                                ss >> fileUname >> filePwd >> fileType;

                                if (fileUname == studentName) {
                                    studentExists = true;
                                    break;
                                }
                            }
                            accountsFile.close();
                        }

                        if (!studentExists) {
                            cout << "Error: Student with provided username not found." << endl;
                            continue;
                        }

                        cout << "Enter grade for " << studentName << ": ";
                        cin >> grade;

                        tempFile << "Student: " << studentName << " Grade: " << grade << endl;
                    }
                }
            }
            classesFile.close();
            tempFile.close();

            if (classExists) {
                // Replace the old classes file with the updated temporary file
                remove("Classes.txt");
                rename("tempClasses.txt", "Classes.txt");
                cout << "Students added to the class successfully." << endl;
            }
            else {
                remove("tempClasses.txt");
                cout << "Error: Class with provided professor and name not found." << endl;
            }
        }
        else {
            cerr << "Error: Unable to open file for reading or writing." << endl;
        }
    }

    void removeStudentsFromClass(const string& professor, const string& className) {
        ifstream classesFile("Classes.txt");
        ofstream tempFile("tempClasses.txt", ios::app);
        string line;
        bool classExists = false;
        bool inTargetClass = false;
        bool studentRemoved = false;

        if (classesFile.is_open() && tempFile.is_open()) {
            while (getline(classesFile, line)) {
                // Check if the current line matches the class we are looking for
                if (line == "Professor: " + professor + " Class: " + className) {
                    classExists = true;
                    inTargetClass = true;
                    tempFile << line << endl;
                }
                else if (line.find("Professor: ") != string::npos && inTargetClass) {
                    // We reached a new class section, stop removing students
                    inTargetClass = false;
                }

                if (!inTargetClass) {
                    // Copy the line to the temporary file if we are not in the target class
                    tempFile << line << endl;
                }
                else {
                    // If we are in the target class, ask for students to remove
                    while (true) {
                        string studentName;
                        cout << "Enter student name to remove (or type 'END' to finish): ";
                        cin >> studentName;

                        if (studentName == "END") {
                            break;
                        }

                        bool studentExists = false;
                        vector<string> remainingStudents;

                        // Rewind the file stream to the beginning of the target class section
                        streampos pos = classesFile.tellg();

                        while (getline(classesFile, line)) {
                            if (line.find("Student: " + studentName) != string::npos) {
                                studentExists = true;
                                studentRemoved = true;
                            }
                            else if (line.find("Professor: ") != string::npos) {
                                // Reached a new class section
                                inTargetClass = false;
                                break;
                            }
                            else {
                                remainingStudents.push_back(line);
                            }
                        }

                        if (studentExists) {
                            cout << "Student " << studentName << " has been removed from the class." << endl;
                            if (remainingStudents.empty()) {
                                cout << "The class is now empty." << endl;
                                break;
                            }
                            // Write remaining students back to temp file
                            for (const string& student : remainingStudents) {
                                tempFile << student << endl;
                            }
                        }
                        else {
                            cout << "Error: Student " << studentName << " not found in the class." << endl;
                            classesFile.clear();
                            classesFile.seekg(pos);
                        }
                    }
                }
            }
            classesFile.close();
            tempFile.close();

            if (classExists) {
                // Replace the old classes file with the updated temporary file
                remove("Classes.txt");
                rename("tempClasses.txt", "Classes.txt");

                if (studentRemoved) {
                    cout << "Selected students have been removed from the class." << endl;
                }
                else {
                    cout << "No students were removed from the class." << endl;
                }
            }
            else {
                remove("tempClasses.txt");
                cout << "Error: Class with provided professor and name not found." << endl;
            }
        }
        else {
            cerr << "Error: Unable to open file for reading or writing." << endl;
        }
    }

    void editStudentGradesInClass(const string& professor, const string& className) {
        ifstream classesFile("Classes.txt");
        string line;
        bool classExists = false;
        bool inTargetClass = false;
        bool studentsExist = false;

        if (classesFile.is_open()) {
            // Check if the class exists and if it has students
            while (getline(classesFile, line)) {
                if (line == "Professor: " + professor + " Class: " + className) {
                    classExists = true;
                    inTargetClass = true;
                    continue;
                }

                if (inTargetClass && line.find("Professor: ") != string::npos) {
                    inTargetClass = false;
                }

                if (inTargetClass && line.find("Student: ") != string::npos) {
                    studentsExist = true;
                }
            }

            classesFile.close();

            if (!classExists) {
                cout << "Error: Class with provided professor and name not found." << endl;
                return;
            }

            if (!studentsExist) {
                cout << "The class is empty." << endl;
                return;
            }

            // Editing student grades
            while (true) {
                string inputStudentName;
                cout << "Enter student name to edit grade (or type 'END' to finish): ";
                cin >> inputStudentName;

                if (inputStudentName == "END") {
                    break;
                }

                bool studentFound = false;

                classesFile.open("Classes.txt");
                ofstream tempFile("tempClasses.txt");

                if (classesFile.is_open() && tempFile.is_open()) {
                    inTargetClass = false;

                    while (getline(classesFile, line)) {
                        if (line == "Professor: " + professor + " Class: " + className) {
                            inTargetClass = true;
                            tempFile << line << endl;
                            continue;
                        }

                        if (inTargetClass && line.find("Professor: ") != string::npos) {
                            inTargetClass = false;
                        }

                        if (inTargetClass && line.find("Student: " + inputStudentName + " ") != string::npos) {
                            studentFound = true;
                            string studentName, discard;
                            int grade;
                            stringstream ss(line);
                            ss >> discard >> studentName >> discard >> grade;

                            cout << "Enter new grade for " << studentName << ": ";
                            int newGrade;
                            cin >> newGrade;

                            tempFile << "Student: " << studentName << " Grade: " << newGrade << endl;
                        }
                        else {
                            tempFile << line << endl;
                        }
                    }

                    classesFile.close();
                    tempFile.close();

                    remove("Classes.txt");
                    rename("tempClasses.txt", "Classes.txt");

                    if (studentFound) {
                        cout << "Grade updated successfully for " << inputStudentName << "." << endl;
                    }
                    else {
                        cout << "Error: Student " << inputStudentName << " not found in the class." << endl;
                    }
                }
                else {
                    cerr << "Error: Unable to open file for reading or writing." << endl;
                    return;
                }
            }
        }
        else {
            cerr << "Error: Unable to open file for reading." << endl;
        }
    }

    void printClassDetails(const string& professor, const string& className) {
        ifstream classesFile("Classes.txt");
        string line;
        bool classExists = false;
        bool inTargetClass = false;

        if (classesFile.is_open()) {
            while (getline(classesFile, line)) {
                if (line == "Professor: " + professor + " Class: " + className) {
                    classExists = true;
                    inTargetClass = true;
                    cout << line << endl; // Print class header
                    continue;
                }

                if (inTargetClass && line.find("Professor: ") != string::npos) {
                    inTargetClass = false;
                }

                if (inTargetClass) {
                    cout << line << endl; // Print student details
                }
            }

            if (!classExists) {
                cout << "Error: Class with provided professor and name not found." << endl;
            }

            classesFile.close();
        }
        else {
            cerr << "Error: Unable to open file for reading." << endl;
        }
    }


};


class HomeWork {
    string professor;
    string TheNameOfClass;
    vector<pair<string, int>> StudentOfClass;
    string TheNameOfHomeWork;
    string homework;

public:
    void addHomeWork(const string& professor, const string& className) {
        ifstream classesFile("Classes.txt");
        string line;
        bool classExists = false;
        bool inTargetClass = false;

        // ????? ???? ???? ? ?????? ????? ????????? ?? ????
        if (classesFile.is_open()) {
            while (getline(classesFile, line)) {
                if (line == "Professor: " + professor + " Class: " + className) {
                    classExists = true;
                    inTargetClass = true;
                    this->professor = professor;
                    this->TheNameOfClass = className;
                    continue;
                }

                if (inTargetClass && line.find("Professor: ") != string::npos) {
                    inTargetClass = false;
                }

                if (inTargetClass && line.find("Student: ") != string::npos) {
                    string studentName;
                    stringstream ss(line);
                    ss.ignore(9); // Skip "Student: "
                    ss >> studentName;
                    StudentOfClass.push_back(make_pair(studentName, 0)); // initial grade set to 0
                }
            }
            classesFile.close();

            if (!classExists) {
                cout << "Error: Class with provided professor and name not found." << endl;
                return;
            }
        }
        else {
            cerr << "Error: Unable to open classes file for reading." << endl;
            return;
        }

        // Get homework details
        cout << "Enter the name of the homework: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, TheNameOfHomeWork);

        cout << "Enter the text of the homework: ";
        getline(cin, homework);

        // Add student names and grades
        vector<pair<string, int>> enteredStudents;
        while (true) {
            cout << "Enter student name (or END to finish): ";
            string studentName;
            cin >> studentName;
            if (studentName == "END") break;

            bool studentExists = false;
            for (const auto& student : StudentOfClass) {
                if (student.first == studentName) {
                    studentExists = true;
                    break;
                }
            }

            if (!studentExists) {
                cout << "Error: Student not found in the class." << endl;
                continue;
            }

            cout << "Enter grade for student " << studentName << ": ";
            int grade;
            cin >> grade;
            enteredStudents.push_back(make_pair(studentName, grade));
        }

        // Append to homework file
        ofstream homeworkFile("homework.txt", ios::app);
        if (homeworkFile.is_open()) {
            homeworkFile << "Professor: " << this->professor << endl;
            homeworkFile << "Class: " << this->TheNameOfClass << endl;
            homeworkFile << "Homework Name: " << TheNameOfHomeWork << endl;
            homeworkFile << "Homework Text: " << homework << endl;

            // Add student grades for the homework
            for (const auto& student : enteredStudents) {
                homeworkFile << "Student: " << student.first << " Grade: " << student.second << endl;
            }

            homeworkFile << "----------------------------------------" << endl;

            homeworkFile.close();
            cout << "Homework and grades saved successfully." << endl;
        }
        else {
            cerr << "Error: Unable to open homework file for writing." << endl;
        }
    }

    void printHomeworkDetails(const string& professor, const string& className, const string& homeworkName) {
        ifstream homeworkFile("homework.txt");
        string line;
        bool classFound = false;
        bool homeworkFound = false;
        bool readingStudents = false;

        if (homeworkFile.is_open()) {
            while (getline(homeworkFile, line)) {
                if (line == "Professor: " + professor && !classFound) {
                    classFound = true;
                }

                if (classFound && line == "Class: " + className) {
                    homeworkFound = true;
                }

                if (homeworkFound && line == "Homework Name: " + homeworkName) {
                    readingStudents = true;
                    cout << line << endl;
                    continue;
                }

                if (readingStudents) {
                    if (line.find("Student: ") != string::npos) {
                        cout << line << endl;
                    }
                    else if (line.find("Professor: ") != string::npos) {
                        break; // End of this homework section
                    }
                }
            }

            if (!classFound || !homeworkFound) {
                cout << "Error: Class or homework not found." << endl;
            }

            homeworkFile.close();
        }
        else {
            cerr << "Error: Unable to open homework file for reading." << endl;
        }
    }


};




int main() {
    Admin admin("admin_user", "admin_pass", 1);
    admin.displayAdmin();

    // Creating new accounts
    admin.createAccount("prof1", "pass1", 2); // Professor
    admin.createAccount("user1", "pass2", 1); // Student
    admin.createAccount("user2", "pass3", 1);// Student
    admin.createAccount("prof2", "pass11", 2);
    admin.createAccount("user6", "pass6", 1);// Student
    admin.createAccount("user7", "pass7", 1);// Student

    // Editing an account
    admin.editAccount("user1", "pass2", "newuser1", "newpass1", 1);

    // Deleting an account
    admin.deleteAccount("newuser1", "newpass1");

    // Printing all accounts
    admin.printAccounts();
    //cout << "hello world"; 
    // Adding a class
    Darss newClass;
    newClass.addClass("prof1", "pass1", "Math101");
    //newClass.addClass("prof2", "pass11", "Phisics101");
    //newClass.addStudentsToClass("prof1", "Math101"); 
    //newClass.removeStudentsFromClass("prof2", "Phisics101"); 
    //newClass.editStudentGradesInClass("prof1", "Math101");
    newClass.printClassDetails("prof1", "Math101");

    HomeWork Thehomework;
    Thehomework.addHomeWork("prof1", "Math101");
    //Thehomework.addHomeWork("prof1", "Math101");
   // Thehomework.addHomeWork("prof1", "Math101");
    // test for push

    Thehomework.printHomeworkDetails("prof1", "Math101", "taklif1");


    return 0;
}
