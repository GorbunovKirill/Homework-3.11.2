#include <iostream>
#include <string>
#include <algorithm>

class big_integer {
public:
  
    big_integer() = default;

    big_integer(const std::string& number) : number_(number) {}

    big_integer(const big_integer& other) : number_(other.number_) {}

    big_integer(big_integer&& other) noexcept : number_(std::move(other.number_)) {}

    big_integer& operator=(const big_integer& other) {
        if (this != &other) {
            number_ = other.number_;
        }
        return *this;
    }

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            number_ = std::move(other.number_);
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        std::string result;
        auto it1 = number_.rbegin();
        auto it2 = other.number_.rbegin();
        int carry = 0;

        while (it1 != number_.rend() || it2 != other.number_.rend() || carry) 
        
        {
            int digit1 = (it1 != number_.rend()) ? *it1 - '0' : 0;
            int digit2 = (it2 != other.number_.rend()) ? *it2 - '0' : 0;

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');

            if (it1 != number_.rend()) ++it1;
            if (it2 != other.number_.rend()) ++it2;
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    big_integer operator*(int num) const {
        std::string result;
        int carry = 0;

        for (auto it = number_.rbegin(); it != number_.rend(); ++it) {
            int digit = *it - '0';
            int product = digit * num + carry;
            carry = product / 10;
            result.push_back((product % 10) + '0');
        }

        while (carry) {
            result.push_back((carry % 10) + '0');
            carry /= 10;
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

  
    friend std::ostream& operator<<(std::ostream& os, const big_integer& bi) {
        os << bi.number_;
        return os;
    }

private:
    std::string number_;
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout <<"sum: "<< result << std::endl;

    auto number3 = big_integer("12345");
    auto result2 = number3 * 9;
    std::cout <<"multipl: "<< result2 << std::endl;

    return 0;
}
