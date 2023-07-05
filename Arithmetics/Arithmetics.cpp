#include <iostream>
#include <cmath>

int main()
{
    // Examples of variables and math operations
    int numApples = 0;
    std::cout << "Enter number of apples: ";
    std::cin >> numApples;

    int sum = numApples + 3;
    std::cout << "Sum: " << sum << "\n";

    int difference = numApples - 3;
    std::cout << "Difference: " << difference << "\n";

    int multiply = numApples * 3;
    std::cout << "Multiply: " << multiply << "\n";

    int division = numApples / 3;
    unsigned int remainder = numApples % 3;
    std::cout << "Division: " << division << "\n";
    std::cout << "Remainder: " << remainder << "\n";

    double exactDivision = (double)numApples / 3;
    std::cout << "Exact division: " << exactDivision << "\n";

    bool isEven = numApples % 2 == 0;
    std::cout << "Is even: " << isEven << "\n";
    std::string evenessString = isEven ? "even" : "odd";
    std::cout << numApples << " is " << evenessString << "\n";

    double a = 0.;
    double b = 0.;
    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter b: ";
    std::cin >> b;
    double c = sqrt(a * a + b * b);
    std::cout << "c = " << c << "\n";

    float farenheits = 0.f;
    std::cout << "Enter temperature in farenheits: ";
    std ::cin >> farenheits;
    float celsius = (farenheits - 32) * 5 / 9;
    std::cout << "Temperature in celsius: " << celsius << "\n";

    // Student exercise: calculate farenheihts from celsius
    std::cout << "Enter temperature in celsius: ";
    std::cin >> celsius;
    farenheits = celsius * 9 / 5 + 32;
    std::cout << "Temperature in farenheits: " << farenheits << "\n";

}
