#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

class Account {
public:
    double balance, id, pin, pincode;
    string actype, name, fname, city;

    void getDetails();
    void showDetails() const;
    bool login();
    void balanceEnquiry() const;
    void withdraw();
    void deposit();
    void transfer();
    void pinChange();

private:
    void saveAccount() const;
    void updateAccount();
    static bool isAccountExist(double accountId);
    static bool isPinMatch(double accountId, double pin);
};

void Account::getDetails() {
    system("clear"); 
    cout << "######################################\n";
    cout << "          NEW ACCOUNT                 \n";
    cout << "--------------------------------------\n";
    cout << "Enter Account holder name: ";
    cin.ignore(); 
    getline(cin, name);
    cout << "Enter Your father's name: ";
    getline(cin, fname);
    cout << "Enter the account type (press c for current/s for saving): ";
    cin >> actype;
    cin.ignore(); 
    cout << "Enter your branch city: ";
    getline(cin, city);
    cout << "Enter pincode: ";
    cin >> pincode;
    cout << "Enter any 5 digit account number: ";
    cin >> id;
    cout << "Enter your 4 digit ATM pin: ";
    cin >> pin;
    cout << "Enter initial amount (more than 500): ";
    
    double amount;
    while (true) {
        cin >> amount;
        if (amount > 500) {
            balance = amount;
            break;
        } else {
            cout << "Amount should be more than 500. Enter again: ";
        }
    }
    
    saveAccount();
}

void Account::showDetails() const {
    system("clear"); 
    cout << "\n\n\n\n\n\n";
    cout << "\t\t\t################################\n";
    cout << "\t\t\t#        ACCOUNT DETAILS        \n";
    cout << "\t\t\t#------------------------------ \n";
    cout << "\t\t\t# Account holder : " << name << endl;
    cout << "\t\t\t# Father's name  : " << fname << endl;
    cout << "\t\t\t# City           : " << city << endl;
    cout << "\t\t\t# Pincode        : " << pincode << endl;
    cout << "\t\t\t# Account type   : " << actype << endl;
    cout << "\t\t\t#------------------------------  \n";
    cout << "\t\t\t################################\n";
}



bool Account::login() {
    system("clear"); 
    double enteredPin, enteredId;
    ifstream fin("details.dat", ios::binary);
    
    if (!fin) {
        cout << "Error opening file!\n";
        return false;
    }
    
    cout << "\n\n\n";
    cout << "\t\t\t############################\n";
    cout << "\t\t\t         ACCOUNT LOGIN      \n";
    cout << "\t\t\t----------------------------\n";
    cout << "\t\t\tEnter your account ID: ";
    cin >> enteredId;
    cout << "\t\t\tEnter your 4 digit PIN: ";
    cin >> enteredPin;
    
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Account))) {
        if (id == enteredId && pin == enteredPin) {
            fin.close();
            return true; // Login successful
        }
    }
    
    fin.close();
    return false; // Login failed
}

void Account::balanceEnquiry() const {
    system("clear"); 
    cout << "\n\n\n";
    cout << "\t\t\t############################\n";
    cout << "\t\t\t#        BALANCE ENQUIRY    \n";
    cout << "\t\t\t# -----------------------\n";
    cout << "\t\t\t# Account ID: " << id << endl;
    cout << "\t\t\t# Account Balance: Rs." << balance << endl;
    cout << "\t\t\t# -----------------------\n";
    cout << "\t\t\t############################\n";
}

void Account::withdraw() {
    system("clear"); 
    double amount;
    cout << "\n\n\n";
    cout << "\t\t\t############################\n";
    cout << "\t\t\t        CASH WITHDRAWAL\n";
    cout << "\t\t\t -----------------------\n";
    cout << "\t\t\t Enter the amount to withdraw: ";
    cin >> amount;
    
    if (amount > balance) {
        cout << "\n\t\t\tWithdrawal not possible\n";
        cout << "\t\t\tYour balance is: Rs." << balance << endl;
    } else {
        balance -= amount;
        cout << "\n\t\t\tUpdated balance: Rs." << balance << endl;
        updateAccount();
    }
}

void Account::deposit() {
    system("clear"); 
    double amount;
    cout << "\n\n\n";
    cout << "\t\t\t##############################\n";
    cout << "\t\t\t      CASH DEPOSIT            \n";
    cout << "\t\t\t-------------------------------\n";
    cout << "\t\t\t Enter the amount to deposit: ";
    cin >> amount;
    
    balance += amount;
    cout << "\t\t\t Transaction Successful\n";
    cout << "\n\t\t\tUpdated balance: Rs." << balance << endl;
    updateAccount();
}

void Account::transfer() {
    system("clear"); 
    double amount, beneficiaryId;
    cout << "\n\n\n";
    cout << "\t\t\t##############################\n";
    cout << "\t\t\t      CASH TRANSFER           \n";
    cout << "\t\t\t-------------------------------\n";
    cout << "\t\t\t Enter the beneficiary account ID: ";
    cin >> beneficiaryId;
    cout << "\t\t\t Enter the amount to transfer: ";
    cin >> amount;
    
    if (amount > balance) {
        cout << "\t\t\t Insufficient balance.\n";
        return;
    }

    bool foundBeneficiary = false;
    ifstream fin("details.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary | ios::app);
    
    if (!fin || !fout) {
        cout << "Error opening file!\n";
        return;
    }
    
    Account temp;
    while (fin.read(reinterpret_cast<char*>(&temp), sizeof(Account))) {
        if (temp.id == beneficiaryId) {
            temp.balance += amount;
            foundBeneficiary = true;
        }
        fout.write(reinterpret_cast<char*>(&temp), sizeof(Account));
    }

    if (foundBeneficiary) {
        balance -= amount;
        cout << "\t\t\t Transaction Successful\n";
    } else {
        cout << "\t\t\t Beneficiary account not found\n";
    }
    
    fin.close();
    fout.close();
    
    remove("details.dat");
    rename("temp.dat", "details.dat");
    
    updateAccount();
}

void Account::pinChange() {
    system("clear"); 
    int newPin, verifyPin;
    cout << "\n\n\n";
    cout << "\t\t\t##############################\n";
    cout << "\t\t\t      PIN CHANGE            \n";
    cout << "\t\t\t-------------------------------\n";
    cout << "\t\t\t Enter new 4 digit PIN: ";
    cin >> newPin;
    cout << "\t\t\t Re-enter new 4 digit PIN: ";
    cin >> verifyPin;
    
    if (newPin == verifyPin) {
        pin = newPin;
        updateAccount();
        cout << "\t\t\t PIN changed successfully\n";
    } else {
        cout << "\t\t\t Pins do not match. Try again.\n";
    }
}

void Account::saveAccount() const {
    ofstream fout("details.dat", ios::binary | ios::app);
    
    if (!fout) {
        cout << "Error opening file!\n";
        return;
    }
    
    fout.write(reinterpret_cast<const char*>(this), sizeof(Account));
    fout.close();
}

void Account::updateAccount() {
    ifstream fin("details.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);
    
    if (!fin || !fout) {
        cout << "Error opening file!\n";
        return;
    }
    
    Account temp;
    while (fin.read(reinterpret_cast<char*>(&temp), sizeof(Account))) {
        if (temp.id == id) {
            fout.write(reinterpret_cast<const char*>(this), sizeof(Account));
        } else {
            fout.write(reinterpret_cast<const char*>(&temp), sizeof(Account));
        }
    }
    
    fin.close();
    fout.close();
    
    remove("details.dat");
    rename("temp.dat", "details.dat");
}

bool Account::isAccountExist(double accountId) {
    ifstream fin("details.dat", ios::binary);
    
    if (!fin) {
        return false;
    }
    
    Account temp;
    while (fin.read(reinterpret_cast<char*>(&temp), sizeof(Account))) {
        if (temp.id == accountId) {
            fin.close();
            return true;
        }
    }
    
    fin.close();
    return false;
}

bool Account::isPinMatch(double accountId, double pin) {
    ifstream fin("details.dat", ios::binary);
    
    if (!fin) {
        return false;
    }
    
    Account temp;
    while (fin.read(reinterpret_cast<char*>(&temp), sizeof(Account))) {
        if (temp.id == accountId && temp.pin == pin) {
            fin.close();
            return true;
        }
    }
    
    fin.close();
    return false;
}

int main() {
    Account a;
    int choice;

    while (true) {
        system("clear"); // Use system("cls") on Windows
        cout << "\n\n\n";
        cout << "\t\t\t###############################\n";
        cout << "\t\t\t#         ATM SYSTEM           #\n";
        cout << "\t\t\t#   1. Create Account          #\n";
        cout << "\t\t\t#   2. Login                   #\n";
        cout << "\t\t\t#   3. Exit                    #\n";
        cout << "\t\t\t###############################\n";
        cout << "\n\n\n\t\t\tEnter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            a.getDetails();
            break;
        case 2:
            if (a.login()) {
                int operationChoice;
                do {
                    system("clear"); 
                    cout << "\n\n\n";
                    cout << "\t\t\t###############################";
                    cout << "\n\t\t\t#         MAIN MENU           #";
                    cout << "\n\t\t\t#   1. Show Details           #";
                    cout << "\n\t\t\t#   2. Balance Enquiry        #";
                    cout << "\n\t\t\t#   3. Deposit                #";
                    cout << "\n\t\t\t#   4. Withdraw               #";
                    cout << "\n\t\t\t#   5. Change PIN             #";
                    cout << "\n\t\t\t#   6. Transfer               #";
                    cout << "\n\t\t\t#   7. Exit                   #";
                    cout << "\n\t\t\t###############################";
                    cout << "\n\n\n\t\t\tEnter your choice: ";
                    cin >> operationChoice;

                    switch (operationChoice) {
                    case 1:
                        a.showDetails();
                        break;
                    case 2:
                        a.balanceEnquiry();
                        break;
                    case 3:
                        a.deposit();
                        break;
                    case 4:
                        a.withdraw();
                        break;
                    case 5:
                        a.pinChange();
                        break;
                    case 6:
                        a.transfer();
                        break;
                    case 7:
                        cout << "\t\t\tThank you for using the ATM. Goodbye!\n";
                        break;
                    default:
                        cout << "\t\t\tInvalid choice. Please try again.\n";
                        break;
                    }

                    if (operationChoice != 7) {
                        cout << "\n\n\t\t\tPress 0 to go back to the menu or any other key to exit: ";
                        int backToMenu;
                        cin >> backToMenu;
                        if (backToMenu != 0) {
                            operationChoice = 7; 
                        }
                    }

                } while (operationChoice != 7);
            } else {
                cout << "\t\t\tInvalid ID or PIN. Returning to main menu.\n";
                system("pause");
            }
            break;
        case 3:
            cout << "\t\t\tExiting. Goodbye!\n";
            return 0;
        default:
            cout << "\t\t\tInvalid choice. Please try again.\n";
            system("pause");
        }
    }

    return 0;
}
