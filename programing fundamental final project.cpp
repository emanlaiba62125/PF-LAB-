#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>
using namespace std;

const int MAX_RECORDS = 100;
const string USERNAME = "admin";
const string PASSWORD = "1234";

struct FitnessMetrics {
    string date;
    int steps;
    int calories;
    float sleepHours;  
    float weight;     
    int age;           
    float height;      
    string exerciseType;  
};

FitnessMetrics fitnessData[MAX_RECORDS];
int recordCount = 0;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void typeText(const string& text, int delayMs = 50) {
    for (char c : text) {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}

void showWelcomePage() {
    system("cls");
    setColor(12); 
    cout << "==============================================\n";
    setColor(10); 
    cout << "            Welcome to Fitness Tracker         \n";
    setColor(12); 
    cout << "==============================================\n";
    setColor(9);  
    typeText("Your journey to better health starts here!\n", 40);
    setColor(7);  
    cout << "\nPress Enter to continue...\n";
    cin.ignore();
    cin.get();
}

void displayTitle(const string& title) {
    setColor(14); 
    cout << "\n==============================================\n";
    cout << "  " << title << "\n";
    cout << "==============================================\n";
    setColor(7);  
}

bool login() {
    string inputUsername, inputPassword;
    system("cls");
    displayTitle("Login Page");

    setColor(11); 
    cout << "Enter username: ";
    setColor(7); 
    cin >> inputUsername;
    setColor(11); 
    cout << "Enter password: ";
    setColor(7);  
    cin >> inputPassword;

    if (inputUsername == USERNAME && inputPassword == PASSWORD) {
        setColor(10); 
        cout << "\nLogin successful!\n";
        setColor(7);  
        return true;
    } else {
        setColor(12);
        cout << "\nInvalid username or password. Please try again.\n";
        setColor(7);  
        return false;
    }
}

int calculateCalories(int steps, float weight, float height, const string& exerciseType) {
    float baseCalories = (steps * 0.04) + ((weight * height) / 1000);
    
    if (exerciseType == "Running") {
        return baseCalories * 1.2; 
    } else if (exerciseType == "Walking") {
        return baseCalories * 1.1; 
    } else {
        return baseCalories;
    }
}

void logMetrics() {
    system("cls");
    displayTitle("Log Fitness Metrics");

    if (recordCount >= MAX_RECORDS) {
        setColor(12); 
        cout << "Data storage is full. Cannot log more metrics.\n";
        setColor(7);  
        return;
    }

    FitnessMetrics entry;
    setColor(11); 
    cout << "Enter date (YYYY-MM-DD): ";
    setColor(7);  
    cin >> entry.date;

    setColor(11); 
    cout << "Enter steps taken: ";
    setColor(7);  
    cin >> entry.steps;

    setColor(11); 
    cout << "Enter your weight (kg): ";
    setColor(7);  
    cin >> entry.weight;

    setColor(11); 
    cout << "Enter your height (cm): ";
    setColor(7);  
    cin >> entry.height;

    setColor(11); 
    cout << "Enter your age: ";
    setColor(7);  
    cin >> entry.age;

    setColor(11); 
    cout << "Enter sleep hours (hours): ";
    setColor(7);  
    cin >> entry.sleepHours;  

    setColor(11); 
    cout << "Enter exercise type (Walking, Running, etc.): ";
    setColor(7); 
    cin >> entry.exerciseType;


    entry.calories = calculateCalories(entry.steps, entry.weight, entry.height, entry.exerciseType);

    setColor(10);
    cout << "\nMetrics logged successfully!\n";
    fitnessData[recordCount] = entry;
    recordCount++;
    setColor(7);  
}

void viewMetrics() {
    system("cls");
    displayTitle("View Fitness Metrics");

    if (recordCount == 0) {
        setColor(12); 
        cout << "No fitness data available.\n";
        setColor(7);  
        return;
    }

    setColor(9);  
    cout << "\nDate\t\tSteps\tCalories\tSleep Hours\tWeight\tHeight\tAge\tExercise\n";
    cout << "-------------------------------------------------------------------------\n";
    setColor(7);  
    for (int i = 0; i < recordCount; i++) {
        setColor(7);  
        cout << fitnessData[i].date << "\t";
        cout << fitnessData[i].steps << "\t";
        cout << fitnessData[i].calories << "\t\t";
        cout << fitnessData[i].sleepHours << "\t\t";  
        cout << fitnessData[i].weight << "\t";
        cout << fitnessData[i].height << "\t";
        cout << fitnessData[i].age << "\t";
        cout << fitnessData[i].exerciseType << "\n";
    }
}

void updateMetrics() {
    system("cls");
    displayTitle("Update Fitness Metrics");

    string date;
    setColor(11);
    cout << "Enter the date of the entry you want to update (YYYY-MM-DD): ";
    setColor(7);  
    cin >> date;

    for (int i = 0; i < recordCount; i++) {
        if (fitnessData[i].date == date) {
            setColor(11); 
            cout << "Enter new steps taken: ";
            setColor(7);  
            cin >> fitnessData[i].steps;

            setColor(11); 
            cout << "Enter new weight (kg): ";
            setColor(7);
            cin >> fitnessData[i].weight;

            setColor(11); 
            cout << "Enter new height (cm): ";
            setColor(7); 
            cin >> fitnessData[i].height;

            setColor(11); 
            cout << "Enter new age: ";
            setColor(7); 
            cin >> fitnessData[i].age;

            setColor(11); 
            cout << "Enter new sleep hours (hours): ";
            setColor(7);  
            cin >> fitnessData[i].sleepHours;  

            setColor(11); 
            cout << "Enter new exercise type (Walking, Running, etc.): ";
            setColor(7);  
            cin >> fitnessData[i].exerciseType;

    
            fitnessData[i].calories = calculateCalories(fitnessData[i].steps, fitnessData[i].weight, fitnessData[i].height, fitnessData[i].exerciseType);

            setColor(10); 
            cout << "\nMetrics updated successfully!\n";
            setColor(7);  
            return;
        }
    }

    setColor(12); 
    cout << "\nNo entry found for the given date.\n";
    setColor(7);  
}

void deleteMetrics() {
    system("cls");
    displayTitle("Delete Fitness Metrics");

    string date;
    setColor(11);
    cout << "Enter the date of the entry you want to delete (YYYY-MM-DD): ";
    setColor(7);  
    cin >> date;

    for (int i = 0; i < recordCount; i++) {
        if (fitnessData[i].date == date) {
            for (int j = i; j < recordCount - 1; j++) {
                fitnessData[j] = fitnessData[j + 1];
            }
            recordCount--;

            setColor(10); 
            cout << "\nEntry deleted successfully!\n";
            setColor(7);
            return;
        }
    }

    setColor(12);
    cout << "\nNo entry found for the given date.\n";
    setColor(7);  
}

int main() {
    showWelcomePage();

    while (true) {
        if (login()) break;
    }

    int choice;

    while (true) {
        system("cls");
        displayTitle("Main Menu");

        setColor(14); 
        cout << "1. Log Fitness Metrics\n";
        cout << "2. View Fitness Metrics\n";
        cout << "3. Update Fitness Metrics\n";
        cout << "4. Delete Fitness Metrics\n";
        cout << "5. Exit\n";
        setColor(11); 
        cout << "\nEnter your choice: ";
        setColor(7); 
        cin >> choice;

        switch (choice) {
            case 1:
                logMetrics();
                break;
            case 2:
                viewMetrics();
                break;
            case 3:
                updateMetrics();
                break;
            case 4:
                deleteMetrics();
                break;
            case 5:
                system("cls");
                setColor(10); 
                typeText("Thank you for using the Fitness Tracker! Stay healthy!\n", 40);
                setColor(7);
                return 0;
            default:
                setColor(12); 
                cout << "\nInvalid choice. Please try again.\n";
                setColor(7); 
        }

        cout << "\nPress Enter to return to the main menu...";
        cin.ignore();
        cin.get();
    }
}

