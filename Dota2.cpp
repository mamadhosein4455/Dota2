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

};