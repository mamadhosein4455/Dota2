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
