#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string str = "0,1,2,3,4,5,6";
    std::istringstream ss(str);
    std::string deger;
    while (std::getline(ss, deger, ',')) {
        std::cout << deger << std::endl;
    }
    return 0;
}
