

#include "account.h"

// your code here (getters and setters)

#include <iostream>

std::string BankAccount::getAccountNumber() const { return accountNumber; }

double BankAccount::getBalance() const { return balance; }

void BankAccount::setAccountNumber(const std::string& newNumber) {
    if (newNumber.length() != 16) {
        std::cout << "Ошибка: номер счета должен содержать 16 цифр!" << std::endl;
        return;
    }

    for (char c : newNumber) {
        if (!isdigit(c)) {
            std::cout << "Ошибка: номер счета должен содержать 16 цифр!" << std::endl;
            return;
        }
    }

    accountNumber = newNumber;
    std::cout << "Счет изменен: " << accountNumber << std::endl;
}

void BankAccount::setBalance(double newBalance) {
    if (newBalance < 0) {
        std::cout << "Ошибка: баланс не может быть отрицательным!" << std::endl;
        return;
    }

    balance = newBalance;
    std::cout << "Баланс изменен: " << balance << std::endl;
}
