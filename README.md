C++ ATM System
This project is a simple ATM system implemented in C++. It allows users to create accounts, log in, deposit and withdraw funds, transfer money, change their PIN, and check account details. The system uses file handling to store account data, ensuring that information persists even after restarting the program.

Features
Account Creation: Users can create a new account with an initial deposit.
Login System: Secure login using account ID and PIN.
Deposit & Withdraw: Perform deposits and withdrawals from the account.
Money Transfer: Transfer money between accounts.
PIN Change: Change the ATM PIN for security.
Balance Enquiry: Check the current balance.
Account Details: View account holder details such as name, account type, and balance.
Prerequisites
C++ Compiler: Ensure you have a C++ compiler that supports C++17 or later installed on your system.
Git: Optional, for cloning the repository from GitHub.

Run the Program:
Once compiled, run the program with:
./atm
Usage

After running the program, you will be presented with a menu offering the following options:

Create an Account: Follow the prompts to create a new account.
Login: Log in using your account ID and PIN.
Perform Operations: Once logged in, you can:
Check your account details.
Deposit or withdraw money.
Transfer money to another account.
Change your PIN.
Check your balance.
Admin Access: Admin can view all accounts by entering the admin password.
File Handling
Account Data: The program uses a binary file (details.dat) to store account information persistently. Each operation that modifies account data ensures that the file is updated accordingly.
Troubleshooting
File Not Found: Ensure that the program has read/write permissions for details.dat. The file will be created automatically when the first account is added.
Crashes: If the program crashes, check the input formats and ensure that the file details.dat is not corrupted. You can delete the file and restart the program to reset all data.
Contributing
Contributions are welcome! If you would like to improve the project or fix any issues, follow these steps:



Contact
For any questions or issues, feel free to reach out to the repository maintainer:

Name: Ritik Singh
Email: ritik306singh@gmail.com

