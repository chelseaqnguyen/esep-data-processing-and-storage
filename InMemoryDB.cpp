#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <cctype> // For isdigit function

class InMemoryDB {
private:
    std::unordered_map<std::string, int> mainState;
    std::unordered_map<std::string, int> transactionState;
    bool inTransaction;

public:
    InMemoryDB() : inTransaction(false) {}

    int getValue(const std::string& key) {
        if (transactionState.find(key) != transactionState.end()) {
            return transactionState[key];
        } else {
            return mainState[key];
        }
    }

    void putValue(const std::string& key, const std::string& value) {
        if (!inTransaction) {
            throw std::logic_error("Transaction not in progress");
        }

        // Validate if the value is an integer
        for (char c : value) {
            if (!std::isdigit(c)) {
                throw std::invalid_argument("Invalid value. Must be an integer.");
            }
        }

        transactionState[key] = std::stoi(value);
    }

    void beginTransaction() {
        if (inTransaction) {
            throw std::logic_error("Transaction is already in progress");
        }
        inTransaction = true;
        transactionState = mainState;
    }

    void commitTransaction() {
        if (!inTransaction) {
            throw std::logic_error("No transaction to commit");
        }
        mainState = transactionState;
        transactionState.clear();
        inTransaction = false;
    }

    void rollbackTransaction() {
        if (!inTransaction) {
            throw std::logic_error("No ongoing transaction to rollback");
        }
        transactionState.clear();
        inTransaction = false;
    }
};

int main() {
    InMemoryDB inMemoryDB;

    std::cout << "In-Memory Key-Value Database\n";

    while (true) {
        std::cout << "\nEnter a command (put, get, begin, commit, rollback, exit): ";
        std::string command;
        std::cin >> command;

        if (command == "put") {
            std::string key, value;
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Enter value: ";
            std::cin >> value;

            try {
                inMemoryDB.putValue(key, value);
                std::cout << "Put successful\n";
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (command == "get") {
            std::string key;
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Value for key '" << key << "': " << inMemoryDB.getValue(key) << std::endl;
        } else if (command == "begin") {
            try {
                inMemoryDB.beginTransaction();
                std::cout << "Transaction started\n";
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (command == "commit") {
            try {
                inMemoryDB.commitTransaction();
                std::cout << "Transaction committed\n";
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (command == "rollback") {
            try {
                inMemoryDB.rollbackTransaction();
                std::cout << "Transaction rolled back\n";
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command. Try again.\n";
        }
    }

    return 0;
}
