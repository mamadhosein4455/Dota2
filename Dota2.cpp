#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>


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
