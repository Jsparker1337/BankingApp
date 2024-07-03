
#include <iostream>
#include <string>
#include <vector>
#include <functional>



    class BankAccount {
    public:

        class Transaction {
        public:
            enum class Type { DEPOSIT, WITHDRAWAL };

            Transaction(Type t, double amt) : type(t), amount(amt), timestamp(time(nullptr)) {}

            void display() const {
                std::cout << "Type: " << (type == Type::DEPOSIT ? "Deposit" : "Withdrawal");
                std::cout << ", Amount: $" << amount << std::endl;

            }
        private:
            Type type;
            double amount;
            std::time_t timestamp;
        };


        BankAccount(const std::string& holder, double initialBalance, const std::string& user, const std::string& pass) {
            accountHolder = holder;
            balance = initialBalance;
            username = user;
            password = pass;
        }

        bool authenticate(const std::string& user, const std::string& pass) {
            return (user == username && pass == password);
        }

        void deposit(double amount) {
            if (amount > 0) {
                balance += amount;
                transactions.emplace_back(Transaction::Type::DEPOSIT, amount);
                std::cout << "Deposited $" << amount << ". New balance: $" << balance << std::endl;
            }
            else {
                std::cout << "Invalid deposit amount." << std::endl;
            }
        }

        void withdraw(double amount) {
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                transactions.emplace_back(Transaction::Type::WITHDRAWAL, amount);
                std::cout << "Withdrawn $" << amount << ". New balance: $" << balance << std::endl;
            }
            else {
                std::cout << "Insufficient funds or invalid withdrawal amount." << std::endl;
            }
        }

        void displayBalance() {
            std::cout << "Account holder: " << accountHolder << std::endl;
            std::cout << "Current balance: $" << balance << std::endl;
        }

        void displayTransactionHistory() const {
            std::cout << "\nTransaction History:\n";
            for (const auto& txn : transactions) {
                txn.display();
            }
        }


    private:
        std::string accountHolder;
        double balance;
        std::string username;
        std::string password;
        std::vector<Transaction> transactions;

};




void menu(BankAccount& Account) {
    int choice;
    double amount;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Deposit\n";
        std::cout << "2. Withdraw\n";
        std::cout << "3. Display balance\n";
        std::cout << "4. Display transaction history\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter deposit amount: $";
            std::cin >> amount;
            Account.deposit(amount);
            break;
        case 2:
            std::cout << "Enter withdrawal amount: $";
            std::cin >> amount;
            Account.withdraw(amount);
            break;
        case 3:
            Account.displayBalance();
            break;
        case 4:
            Account.displayTransactionHistory();
            break;
        case 5:
            std::cout << "Thank you for using our banking program!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void login(BankAccount Account) {

    std::string enteredUser, enteredPass;
    std::cout << "Enter username: ";
    std::cin >> enteredUser;
    std::cout << "Enter password: ";
    std::cin >> enteredPass;
    std::hash<std::string> hasher;
    size_t hashValue = hasher(enteredPass);

    if (Account.authenticate(enteredUser, enteredPass)) {
        menu(Account);
    }
    else {
        std::cout << "Authentication failed. Exiting program.\n";
    }

}


int main() {

    BankAccount myAccount("John Doe", 1000.0, "myuser", "mypassword");
    login(myAccount);

}