#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to display the main menu interface
void displayInterface() {
    cout << " \t           AAA                              RRRRRRRRRRRRRR                               SSSSS\n";
    cout << " \t          AAAAA                             RRR        RRRRR                          SS      SS\n";
    cout << " \t        AA     AA                           RR           RRRRR                      SSS        SSS\n";
    cout << " \t       AA       AA                          RR             RRR                     SS\n";
    cout << " \t      AA         AA                         RR            RRR                       SSSS\n";
    cout << " \t     AAAAAAAAAAAAAAA                        RRRRRRRRRRRRRRR                             SSSS\n";
    cout << " \t    AA             AA                       RR             RR                              SSSS\n";
    cout << " \t   AA               AA                      RR               RR                                 SSS\n";
    cout << " \t  AA                 AA                     RR                RR                    SSS          SSS\n";
    cout << "\t AA                   AA                    RR                 RR                     SSSS      SSS\n";
    cout << "\tAA                     AA                   RR                  RR                        SSSSS\n";
    cout << "\t\t\t\t\n";
    cout << "\t\t\t\t                 ARMY RECRUITMENT SYSTEM\n";
    cout << "\t\t\t\t                  SERVE YOUR MOTHERLAND!\n";
    cout << "\t\t\t\t\n";
    cout << "\t\t\t\t\n";
    cout << " \t\t         ______________________________________________________________________\n";
    cout << " \t\t        |                                                                      |\n";
    cout << " \t\t        | 1- RECRUITER                                                         |\n";
    cout << " \t\t        | 2- CANDIDATE                                                         |\n";
    cout << " \t\t        | 3- EXIT                                                              |\n";
    cout << " \t\t        |______________________________________________________________________|\n";
}

// Function to check recruiter password
bool checkPassword() {
    string password;
    int attempt = 0;
    while (attempt < 3) {
        cout << "Enter recruiter password: ";
        cin >> password;
        if (password == "recruiter123") {
            return true;
        } else {
            cout << "Incorrect password. Try again.\n";
            attempt++;
        }
    }
    cout << "Incorrect password entered multiple times. Access denied.\n";
    return false;
}

// Function to save candidates' data to a file
void saveCandidates(float height[], float weight[], int systolic[], int diastolic[], float sugar[], int count) {
    ofstream outFile("candidates.txt");
    outFile << count << endl;
    for (int i = 0; i < count; i++) {
        outFile << height[i] << " " << weight[i] << " " << systolic[i] << " " << diastolic[i] << " " << sugar[i] << endl;
    }
    outFile.close();
}

// Function to load candidates' data from a file
void loadCandidates(float height[], float weight[], int systolic[], int diastolic[], float sugar[], int &count) {
    ifstream inFile("candidates.txt");
    if (inFile.is_open()) {
        inFile >> count;
        for (int i = 0; i < count; i++) {
            inFile >> height[i] >> weight[i] >> systolic[i] >> diastolic[i] >> sugar[i];
        }
        inFile.close();
    }
}

// Function to check eligibility criteria for the army
bool checkEligibility(float height, float weight, int systolic, int diastolic, float sugar) {
    if (height >= 140 && height <= 200 && weight >= 120 && weight <= 180 && systolic >= 120 && systolic <= 140 && diastolic >= 80 && diastolic <= 100 && sugar >= 1 && sugar <= 7) {
        return true;
    } else {
        return false;
    }
}

// Function to view all registered candidates
void viewCandidates(float height[], float weight[], int systolic[], int diastolic[], float sugar[], int count) {
    if (count == 0) {
        cout << "No candidates available.\n";
        return;
    }

    cout << "\nRegistered Candidates List:\n";
    for (int i = 0; i < count; i++) {
        cout << "\nCandidate " << i + 1 << " Details:\n";
        cout << "Height: " << height[i] << " inches\n";
        cout << "Weight: " << weight[i] << " pounds\n";
        cout << "Blood Pressure: " << systolic[i] << "/" << diastolic[i] << " mmHg\n";
        cout << "Blood Sugar Level: " << sugar[i] << "%\n";
        if (checkEligibility(height[i], weight[i], systolic[i], diastolic[i], sugar[i])) {
            cout << "Eligible for army.\n";
        } else {
            cout << "Not eligible for army.\n";
        }
    }
}

// Function to remove a candidate from the list
void removeCandidate(float height[], float weight[], int systolic[], int diastolic[], float sugar[], int &count) {
    if (count == 0) {
        cout << "No candidates to remove.\n";
        return;
    }
    int idx;
    cout << "Enter candidate number to remove: ";
    cin >> idx;
    if (idx > 0 && idx <= count) {
        for (int i = idx - 1; i < count - 1; i++) {
            height[i] = height[i + 1];
            weight[i] = weight[i + 1];
            systolic[i] = systolic[i + 1];
            diastolic[i] = diastolic[i + 1];
            sugar[i] = sugar[i + 1];
        }
        count--;
        saveCandidates(height, weight, systolic, diastolic, sugar, count);
        cout << "Candidate removed successfully.\n";
    } else {
        cout << "Invalid candidate number.\n";
    }
}

// Recruiter's menu to manage candidates
void recruiterMenu(float height[], float weight[], int systolic[], int diastolic[], float sugar[], int &count) {
    int choice;
    do {
        cout << "\nRecruiter Menu:\n";
        cout << "1. View all candidates\n";
        cout << "2. Remove a candidate\n";
        cout << "3. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                viewCandidates(height, weight, systolic, diastolic, sugar, count);
                break;
            case 2:
                removeCandidate(height, weight, systolic, diastolic, sugar, count);
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice. Please choose a valid option.\n";
        }
    } while (choice != 3);
}

// Candidate's interface to register and view details
void candidateInterface(float height[], float weight[], int systolic[], int diastolic[], float sugar[], int &count) {
    int candidateChoice;

    do {
        cout << "\nCandidate Menu:\n";
        cout << "1. Register as a new candidate\n";
        cout << "2. View existing candidates\n";
        cout << "3. Update existing candidate details\n";
        cout << "4. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> candidateChoice;

        if (candidateChoice == 1) {
            // Register new candidate
            if (count >= 20) {
                cout << "No more candidates can be added. Maximum limit reached.\n";
                break;
            }

            // Input and validate height
            cout << "Enter Height (in inches): ";
            cin >> height[count];
            while (height[count] < 140 || height[count] > 200) {
                cout << "Invalid height! Please enter a valid height (140-200 inches): ";
                cin >> height[count];
            }

            // Input and validate weight
            cout << "Enter Weight (in pounds): ";
            cin >> weight[count];
            while (weight[count] < 120 || weight[count] > 180) {
                cout << "Invalid weight! Please enter a valid weight (120-180 pounds): ";
                cin >> weight[count];
            }

            // Input and validate systolic pressure
            cout << "Enter Systolic Blood Pressure (e.g., 120): ";
            cin >> systolic[count];
            while (systolic[count] < 120 || systolic[count] > 140) {
                cout << "Invalid systolic pressure! Please enter a valid systolic pressure (120-140): ";
                cin >> systolic[count];
            }

            // Input and validate diastolic pressure
            cout << "Enter Diastolic Blood Pressure (e.g., 80): ";
            cin >> diastolic[count];
            while (diastolic[count] < 80 || diastolic[count] > 100) {
                cout << "Invalid diastolic pressure! Please enter a valid diastolic pressure (80-100): ";
                cin >> diastolic[count];
            }

            // Input and validate sugar level
            cout << "Enter Blood Sugar Level (in %): ";
            cin >> sugar[count];
            while (sugar[count] < 1 || sugar[count] > 7) {
                cout << "Invalid blood sugar level! Please enter a valid sugar level (1-7%): ";
                cin >> sugar[count];
            }

            // Check eligibility
            if (checkEligibility(height[count], weight[count], systolic[count], diastolic[count], sugar[count])) {
                count++;
                saveCandidates(height, weight, systolic, diastolic, sugar, count);
                cout << "Candidate registered successfully. Your candidate number is " << count << ".\n";
            } else {
                cout << "Candidate does not meet the eligibility criteria and cannot be registered.\n";
            }
        } 
        else if (candidateChoice == 2) {
            viewCandidates(height, weight, systolic, diastolic, sugar, count);
        }
        else if (candidateChoice == 3) {
            // Update existing candidate details
            if (count == 0) {
                cout << "No candidates registered yet.\n";
                continue;
            }

            int candidateNumber;
            cout << "Enter your candidate number (1-" << count << "): ";
            cin >> candidateNumber;

            if (candidateNumber < 1 || candidateNumber > count) {
                cout << "Invalid candidate number.\n";
                continue;
            }

            int idx = candidateNumber - 1;

            // Input and validate height
            cout << "Enter Height (in inches): ";
            cin >> height[idx];
            while (height[idx] < 140 || height[idx] > 200) {
                cout << "Invalid height! Please enter a valid height (140-200 inches): ";
                cin >> height[idx];
            }

            // Input and validate weight
            cout << "Enter Weight (in pounds): ";
            cin >> weight[idx];
            while (weight[idx] < 120 || weight[idx] > 180) {
                cout << "Invalid weight! Please enter a valid weight (120-180 pounds): ";
                cin >> weight[idx];
            }

            // Input and validate systolic pressure
            cout << "Enter Systolic Blood Pressure (e.g., 120): ";
            cin >> systolic[idx];
            while (systolic[idx] < 120 || systolic[idx] > 140) {
                cout << "Invalid systolic pressure! Please enter a valid systolic pressure (120-140): ";
                cin >> systolic[idx];
            }

            // Input and validate diastolic pressure
            cout << "Enter Diastolic Blood Pressure (e.g., 80): ";
            cin >> diastolic[idx];
            while (diastolic[idx] < 80 || diastolic[idx] > 100) {
                cout << "Invalid diastolic pressure! Please enter a valid diastolic pressure (80-100): ";
                cin >> diastolic[idx];
            }

            // Input and validate sugar level
            cout << "Enter Blood Sugar Level (in %): ";
            cin >> sugar[idx];
            while (sugar[idx] < 1 || sugar[idx] > 7) {
                cout << "Invalid blood sugar level! Please enter a valid sugar level (1-7%): ";
                cin >> sugar[idx];
            }

            // Check eligibility
            if (checkEligibility(height[idx], weight[idx], systolic[idx], diastolic[idx], sugar[idx])) {
                saveCandidates(height, weight, systolic, diastolic, sugar, count);
                cout << "Candidate details updated successfully.\n";
            } else {
                cout << "Updated details do not meet the eligibility criteria.\n";
            }
        }
        else if (candidateChoice != 4) {
            cout << "Invalid choice. Please choose a valid option.\n";
        }

    } while (candidateChoice != 4);
}

// Main function to run the program
int main() {
    float height[20], weight[20], sugar[20];
    int systolic[20], diastolic[20], count = 0;
    int mainChoice;

    loadCandidates(height, weight, systolic, diastolic, sugar, count);

    do {
        displayInterface();
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            if (checkPassword()) {
                recruiterMenu(height, weight, systolic, diastolic, sugar, count);
            } else {
                cout << "Access denied to recruiter.\n";
            }
        } else if (mainChoice == 2) {
            candidateInterface(height, weight, systolic, diastolic, sugar, count);
        } else if (mainChoice == 3) {
            cout << "Exiting program.\n";
        } else {
            cout << "Invalid choice. Please choose a valid option.\n";
        }
    } while (mainChoice != 3);

    return 0;
}
