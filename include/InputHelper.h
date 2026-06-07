#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <string>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;

class InputHelper
{
public:
    // Menu selection (numbered options)
    static int selectFromMenu(const vector<string> &options, const string &prompt = "");

    // Validation functions
    static bool validateStudentId(const string &id);
    static bool validateName(const string &name);
    static bool validateEmail(const string &email);
    static bool validatePassword(const string &password);
    static bool validateVehicleId(const string &id);
    static bool validateModelName(const string &model);
    static bool validateCapacity(const string &capacityStr, int &capacity);
    static bool validateCapacity(int capacity);
    static bool validateRouteId(const string &id);
    static bool validateRouteName(const string &name);
    static bool validateDistance(const string &distStr, double &distance);
    static bool validateDistance(double distance);

    // Safe input functions with validation
    static string getValidatedInput(const string &prompt, bool (*validator)(const string &));
    static string getStudentId(const string &prompt = "Enter Student ID: ");
    static string getName(const string &prompt = "Enter Name: ");
    static string getEmail(const string &prompt = "Enter Email: ");
    static string getPassword(const string &prompt = "Enter Password: ");
    static int getCapacity(const string &prompt = "Enter Capacity (5-100): ");
    static double getDistance(const string &prompt = "Enter Distance (km): ");
    static string getVehicleId(const string &prompt = "Enter Vehicle ID: ");
    static string getModelName(const string &prompt = "Enter Model Name: ");
    static string getRouteId(const string &prompt = "Enter Route ID: ");
    static string getRouteName(const string &prompt = "Enter Route Name: ");

    // Year selection menu (1-4)
    static int selectYear();

    // Vehicle type selection
    static string selectVehicleType();

    // Boolean option selection
    static bool selectYesNo(const string &prompt);

    // Helper to trim whitespace
    static string trim(const string &str);

private:
    // Regex patterns
    static const regex STUDENT_ID_REGEX;      // S#### (S + 4+ digits)
    static const regex NAME_REGEX;             // Letters and spaces only
    static const regex EMAIL_REGEX;            // Standard email format
    static const regex PASSWORD_REGEX;         // 6+ alphanumeric characters
    static const regex VEHICLE_ID_REGEX;       // 2-4 letters + 3+ digits (e.g., BUS001, VAN123)
    static const regex MODEL_NAME_REGEX;       // Alphanumeric + hyphens/spaces
    static const regex ROUTE_ID_REGEX;         // Letter + 3+ digits (e.g., R001, A100)
    static const regex ROUTE_NAME_REGEX;       // 3+ chars, alphanumeric + hyphens/spaces
    static const regex DISTANCE_REGEX;         // Decimal numbers up to 2 places
    static const regex CAPACITY_REGEX;         // Positive integers
};

#endif // INPUTHELPER_H
