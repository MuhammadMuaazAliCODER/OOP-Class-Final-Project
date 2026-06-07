#include "../include/InputHelper.h"
#include <iostream>
#include <cctype>
using namespace std;

// Static member initialization - Regex patterns
const regex InputHelper::STUDENT_ID_REGEX("^S\\d{4,}$");
const regex InputHelper::NAME_REGEX("^[A-Za-z\\s]+$");
const regex InputHelper::EMAIL_REGEX("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
const regex InputHelper::PASSWORD_REGEX("^[a-zA-Z0-9]{6,}$");
const regex InputHelper::VEHICLE_ID_REGEX("^[A-Z]{2,4}\\d{3,}$");  // 2-4 letters + 3+ digits: BUS001, VAN123
const regex InputHelper::MODEL_NAME_REGEX("^[A-Za-z0-9\\s\\-]{2,}$");
const regex InputHelper::ROUTE_ID_REGEX("^[A-Z]\\d{3,}$");
const regex InputHelper::ROUTE_NAME_REGEX("^[A-Za-z0-9\\s\\-]{3,}$");
const regex InputHelper::DISTANCE_REGEX("^\\d+(\\.\\d{1,2})?$");
const regex InputHelper::CAPACITY_REGEX("^\\d+$");

string InputHelper::trim(const string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == string::npos)
        return "";
    return str.substr(start, end - start + 1);
}

int InputHelper::selectFromMenu(const vector<string> &options, const string &prompt)
{
    if (options.empty())
    {
        cout << "Error: No options available." << endl;
        return -1;
    }

    if (!prompt.empty())
    {
        cout << "\n" << prompt << endl;
    }

    for (size_t i = 0; i < options.size(); ++i)
    {
        cout << (i + 1) << ". " << options[i] << endl;
    }

    int choice;
    while (true)
    {
        cout << "Select option (1-" << options.size() << "): ";
        if (cin >> choice && choice >= 1 && choice <= (int)options.size())
        {
            cin.ignore();
            return choice - 1; // Return 0-based index
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid selection. Please try again." << endl;
    }
}

bool InputHelper::validateStudentId(const string &id)
{
    return regex_match(id, STUDENT_ID_REGEX) && id.length() <= 10;
}

bool InputHelper::validateName(const string &name)
{
    string trimmed = trim(name);
    return regex_match(trimmed, NAME_REGEX) && trimmed.length() >= 2 && trimmed.length() <= 50;
}

bool InputHelper::validateEmail(const string &email)
{
    return regex_match(email, EMAIL_REGEX) && email.length() <= 100;
}

bool InputHelper::validatePassword(const string &password)
{
    return regex_match(password, PASSWORD_REGEX);
}

bool InputHelper::validateVehicleId(const string &id)
{
    return regex_match(id, VEHICLE_ID_REGEX);
}

bool InputHelper::validateModelName(const string &model)
{
    string trimmed = trim(model);
    return regex_match(trimmed, MODEL_NAME_REGEX) && trimmed.length() >= 2 && trimmed.length() <= 50;
}

bool InputHelper::validateCapacity(const string &capacityStr, int &capacity)
{
    if (!regex_match(capacityStr, CAPACITY_REGEX))
        return false;
    try
    {
        capacity = stoi(capacityStr);
        return capacity >= 5 && capacity <= 100;
    }
    catch (...)
    {
        return false;
    }
}

bool InputHelper::validateCapacity(int capacity)
{
    return capacity >= 5 && capacity <= 100;
}

bool InputHelper::validateRouteId(const string &id)
{
    return regex_match(id, ROUTE_ID_REGEX);
}

bool InputHelper::validateRouteName(const string &name)
{
    string trimmed = trim(name);
    return regex_match(trimmed, ROUTE_NAME_REGEX) && trimmed.length() >= 3 && trimmed.length() <= 50;
}

bool InputHelper::validateDistance(const string &distStr, double &distance)
{
    if (!regex_match(distStr, DISTANCE_REGEX))
        return false;
    try
    {
        distance = stod(distStr);
        return distance > 0 && distance <= 500;
    }
    catch (...)
    {
        return false;
    }
}

bool InputHelper::validateDistance(double distance)
{
    return distance > 0 && distance <= 500;
}

string InputHelper::getValidatedInput(const string &prompt, bool (*validator)(const string &))
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        if (input.empty())
        {
            cout << "Input cannot be empty. Please try again." << endl;
            continue;
        }

        if (validator(input))
        {
            return input;
        }
        cout << "Invalid input. Please check the format and try again." << endl;
        cout << "For help, refer to info.txt for valid formats." << endl;
    }
}

string InputHelper::getStudentId(const string &prompt)
{
    return getValidatedInput(prompt, validateStudentId);
}

string InputHelper::getName(const string &prompt)
{
    return getValidatedInput(prompt, validateName);
}

string InputHelper::getEmail(const string &prompt)
{
    return getValidatedInput(prompt, validateEmail);
}

string InputHelper::getPassword(const string &prompt)
{
    return getValidatedInput(prompt, validatePassword);
}

string InputHelper::getVehicleId(const string &prompt)
{
    return getValidatedInput(prompt, validateVehicleId);
}

string InputHelper::getModelName(const string &prompt)
{
    return getValidatedInput(prompt, validateModelName);
}

int InputHelper::getCapacity(const string &prompt)
{
    string input;
    int capacity;
    while (true)
    {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        if (validateCapacity(input, capacity))
        {
            return capacity;
        }
        cout << "Invalid capacity. Please enter a number between 5 and 100." << endl;
    }
}

string InputHelper::getRouteId(const string &prompt)
{
    return getValidatedInput(prompt, validateRouteId);
}

string InputHelper::getRouteName(const string &prompt)
{
    return getValidatedInput(prompt, validateRouteName);
}

double InputHelper::getDistance(const string &prompt)
{
    string input;
    double distance;
    while (true)
    {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        if (validateDistance(input, distance))
        {
            return distance;
        }
        cout << "Invalid distance. Please enter a number between 1 and 500 km (up to 2 decimal places)." << endl;
    }
}

int InputHelper::selectYear()
{
    vector<string> years = {"1st Year", "2nd Year", "3rd Year", "4th Year"};
    int index = selectFromMenu(years, "Select Your Academic Year:");
    return index + 1; // Return 1, 2, 3, or 4
}

string InputHelper::selectVehicleType()
{
    vector<string> types = {"Bus", "Van"};
    int index = selectFromMenu(types, "Select Vehicle Type:");
    return types[index];
}

bool InputHelper::selectYesNo(const string &prompt)
{
    vector<string> options = {"Yes", "No"};
    int index = selectFromMenu(options, prompt);
    return index == 0; // 0 = Yes, 1 = No
}
