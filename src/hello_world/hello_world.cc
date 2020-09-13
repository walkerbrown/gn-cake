#include <iostream>

int main()
{
    std::cout << "Hello, world." << std::endl;

    auto t = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&t));
}
