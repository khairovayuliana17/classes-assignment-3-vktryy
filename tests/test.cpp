#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "account.h"
#include <sstream>
#include <cstdio>

class OutputCapture {
    std::stringstream buffer;
    std::streambuf* oldStdout;

  public:
    OutputCapture() : oldStdout(std::cout.rdbuf(buffer.rdbuf())) {}
    ~OutputCapture() { std::cout.rdbuf(oldStdout); }
    std::string getOutput() { return buffer.str(); }
    void clear() { buffer.str(""); }
};

TEST_CASE("Type checks for BankAccount fields") {
    SECTION("Check field types") {
        static_assert(
            std::is_same_v<decltype(BankAccount{}.getAccountNumber()), std::string>,
            "accountNumber field should be std::string");

        static_assert(
            std::is_same_v<decltype(BankAccount{}.getBalance()), double>,
            "balance field should be double");
    }
}

TEST_CASE("BankAccount initialization", "[BankAccount]") {
    BankAccount account;

    SECTION("Default values") {
        REQUIRE(account.getAccountNumber() == "originalNumber");
        REQUIRE(account.getBalance() == Approx(0.0));
    }
}

TEST_CASE("BankAccount account number", "[BankAccount]") {
    BankAccount account;

    SECTION("Valid account number change") {
        account.setAccountNumber("1234567890123456");
        REQUIRE(account.getAccountNumber() == "1234567890123456");
    }

    SECTION("Too short account number") {
        account.setAccountNumber("123");
        REQUIRE(account.getAccountNumber() == "originalNumber");
    }

    SECTION("Too long account number") {
        account.setAccountNumber("12345678901234567890");
        REQUIRE(account.getAccountNumber() == "originalNumber");
    }

    SECTION("Account number with letters") {
        account.setAccountNumber("123456789012abc");
        REQUIRE(account.getAccountNumber() == "originalNumber");
    }
}

TEST_CASE("BankAccount balance", "[BankAccount]") {
    BankAccount account;

    SECTION("Valid balance change") {
        account.setBalance(100.50);
        REQUIRE(account.getBalance() == Approx(100.50));
    }

    SECTION("Negative balance attempt") {
        account.setBalance(-50.0);
        REQUIRE(account.getBalance() == Approx(0.0));
    }

    SECTION("Multiple valid changes") {
        account.setBalance(100.0);
        account.setBalance(200.0);
        REQUIRE(account.getBalance() == Approx(200.0));
    }

    SECTION("Zero balance") {
        account.setBalance(0.0);
        REQUIRE(account.getBalance() == Approx(0.0));
    }
}

TEST_CASE("BankAccount output messages", "[BankAccount][output]") {
    BankAccount account;
    OutputCapture capture;

    SECTION("Successful account number change") {
        account.setAccountNumber("1234567890123456");
        REQUIRE(capture.getOutput() == "Счет изменен: 1234567890123456\n");
    }

    SECTION("Invalid account number (too short)") {
        account.setAccountNumber("123");
        REQUIRE(capture.getOutput() == "Ошибка: номер счета должен содержать 16 цифр!\n");
    }

    SECTION("Invalid account number (non-digits)") {
        account.setAccountNumber("123456789012abc");
        REQUIRE(capture.getOutput() == "Ошибка: номер счета должен содержать 16 цифр!\n");
    }

    SECTION("Successful balance change") {
        account.setBalance(100.17);
        REQUIRE(capture.getOutput() == "Баланс изменен: 100.17\n");
    }

    SECTION("Negative balance attempt") {
        account.setBalance(-50.0);
        REQUIRE(capture.getOutput() == "Ошибка: баланс не может быть отрицательным!\n");
    }
}
