
// declare BankAccount class here

#include <string>

class BankAccount {
  private:
    // your code here
    std::string accountNumber = "originalNumber";
    double balance = 0.0;

  public:
    // Геттеры
    std::string getAccountNumber() const;
    double getBalance() const;

    // Сеттеры
    void setAccountNumber(const std::string& newNumber);
    void setBalance(double newBalance);
};
