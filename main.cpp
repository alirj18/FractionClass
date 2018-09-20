#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> //rand()
#include <ctime>   //time(0)
#include <regex>

using namespace std;


class Fraction
{
    
    friend ostream& operator<<(ostream&, const Fraction&);
    friend istream& operator>>(istream&, Fraction&);
    
public:
    Fraction(const Fraction&);
    Fraction();
    Fraction(int, int);
    Fraction(int, int, int);
    void setWholeNum(int);
    void setNum(int);
    void setDenom(int);
    int getWholeNum() const { return wholeNum; };
    int getNumerator() const { return num; };
    int getDenominator() const { return denom; };
    string toFracStr() const;
    Fraction operator+(const Fraction&) const;
    Fraction operator*(const Fraction&) const;
    bool operator==(const Fraction&) const;
    const Fraction& operator=(const Fraction&);
    int gcd(int, int) const;
    ~Fraction();
    
private:
    int num, denom, wholeNum;
};

void getValidDenom(int&);
void printTable(int, Fraction**);
Fraction** createTable(int);
void destroyTable(int, Fraction**);



int main() {
    
    int denominator = 0;
    string loop = "";
    
    do {
        
        
        getValidDenom(denominator);
        
        
        Fraction ** table = createTable(denominator);
        
        
        printTable(denominator, table);
        
        
        std::cout << "\nType 1 to repeat. Type anything else to quit.\n";
        std::cin >> loop;
        std::cout << "\n";
        
        
        destroyTable(denominator, table);
        
    } while (loop == to_string(1));
    
}

/*
 Test Data
 
 Please enter a valid denominator.
 0
 
 Please enter a valid denominator.
 -1
 
 Please enter a valid denominator.
 10
 
 [_]      [0]       [1]       [2]       [3]       [4]       [5]       [6]       [7]       [8]       [9]
 [0]     0/10      1/10      2/10      3/10      4/10      5/10      6/10      7/10      8/10      9/10
 [1]     1/10     1/100      1/50     3/100      1/25      1/20      3/50     7/100      2/25     9/100
 [2]     2/10      1/50      1/25      3/50      2/25      1/10      3/25      7/50      4/25      9/50
 [3]     3/10     3/100      3/50     9/100      3/25      3/20      9/50    21/100      6/25    27/100
 [4]     4/10      1/25      2/25      3/25      4/25       1/5      6/25      7/25      8/25      9/25
 [5]     5/10      1/20      1/10      3/20       1/5       1/4      3/10      7/20       2/5      9/20
 [6]     6/10      3/50      3/25      9/50      6/25      3/10      9/25     21/50     12/25     27/50
 [7]     7/10     7/100      7/50    21/100      7/25      7/20     21/50    49/100     14/25    63/100
 [8]     8/10      2/25      4/25      6/25      8/25       2/5     12/25     14/25     16/25     18/25
 [9]     9/10     9/100      9/50    27/100      9/25      9/20     27/50    63/100     18/25    81/100
 
 Type 1 to repeat. Type anything else to quit.
 1
 
 Please enter a valid denominator.
 -7
 
 Please enter a valid denominator.
 no
 
 Please enter a valid denominator.
 7
 
 [_]     [0]      [1]      [2]      [3]      [4]      [5]      [6]
 [0]     0/7      1/7      2/7      3/7      4/7      5/7      6/7
 [1]     1/7     1/49     2/49     3/49     4/49     5/49     6/49
 [2]     2/7     2/49     4/49     6/49     8/49    10/49    12/49
 [3]     3/7     3/49     6/49     9/49    12/49    15/49    18/49
 [4]     4/7     4/49     8/49    12/49    16/49    20/49    24/49
 [5]     5/7     5/49    10/49    15/49    20/49    25/49    30/49
 [6]     6/7     6/49    12/49    18/49    24/49    30/49    36/49
 
 Type 1 to repeat. Type anything else to quit.
 quit
 
 Press any key to continue...
 
 */





Fraction::Fraction(const Fraction & fr) {
    //std::cout << "Copy constructor reassigning values.\n";
    (*this) = fr;
}
Fraction::Fraction() : wholeNum(0), num(0), denom(1) {}                                                    //Initializes the member variables to valid values
//Fraction::Fraction(int n, int d) : wholeNum(0), num(abs(n)), denom(d == 0 ? 1 : abs(d)) {}                //Initializes the numerator and denominator to the values passed during the object's declaration
Fraction::Fraction(int n, int d) : wholeNum(0) {
    setNum(n);
    setDenom(d);
}
//Fraction::Fraction(int x, int n, int d) : wholeNum(abs(x)), num(abs(n)), denom(d == 0 ? 1 : abs(d)) {}    //Initializes all the member variables to the values passed during the object's declaration
Fraction::Fraction(int x, int n, int d) {
    setWholeNum(x);
    setNum(n);
    setDenom(d);
}
string Fraction::toFracStr() const {
    return (wholeNum == 0 ? "" : to_string(wholeNum) + " ") + to_string(num) + "/" + to_string(denom);    //Prints the values of the member variables of the class
}
void Fraction::setWholeNum(int x) {
    if (x < 0) {                                                                                        //Checks if the whole number is greater than or equal to zero
        std::cout << "Whole number is not positive! Setting whole number equal to absolute value of " << x << ".\n";
    }
    wholeNum = abs(x);
}
void Fraction::setNum(int n) {
    if (n < 0) {                                                                                        //Checks if the numerator is greater than or equal to zero
        std::cout << "Numerator is not positive! Setting numerator equal to absolute value of " << n << ".\n";
    }
    num = abs(n);
}
void Fraction::setDenom(int d) {
    if (d <= 0) {                                                                                        //Checks if the denominator is greater than zero
        std::cout << (d == 0 ? "Denominator can't be 0! Setting denominator equal to 1" : "Denominator is not positive! Setting denominator equal to absolute value of " + to_string(d)) << ".\n";
    }
    denom = (d == 0 ? 1 : abs(d));
}
Fraction Fraction::operator+(const Fraction& obj) const {
    //Calculates the sum of both numerators after the mixed fractions are converted to improper fractions
    int numeratorSum = (((wholeNum*denom) + num) * obj.denom) + (((obj.wholeNum*obj.denom) + obj.num) * denom);
    //Calculates the common denominator of both fractions
    int commonDenominator = denom * obj.denom;
    //Simplifies the numerator and denominator
    int greatestCommonDiv = gcd(abs(numeratorSum), abs(commonDenominator));
    numeratorSum /= greatestCommonDiv;
    commonDenominator /= greatestCommonDiv;
    //Returns a simplified mixed fraction.
    return Fraction(numeratorSum / commonDenominator, (numeratorSum < commonDenominator ? numeratorSum : numeratorSum % commonDenominator), commonDenominator);
}
Fraction Fraction::operator*(const Fraction& obj) const {
    //Calculates the product of both numerators after the mixed fractions are converted to improper fractions
    int numeratorProduct = ((wholeNum*denom) + num) * ((obj.wholeNum*obj.denom) + obj.num);
    //Calculates the common denominator of both fractions
    int commonDenominator = denom * obj.denom;
    //Simplifies the numerator and denominator
    int greatestCommonDiv = gcd(abs(numeratorProduct), abs(commonDenominator));
    numeratorProduct /= greatestCommonDiv;
    commonDenominator /= greatestCommonDiv;
    //Returns a simplified mixed fraction
    return Fraction(numeratorProduct / commonDenominator, (numeratorProduct < commonDenominator ? numeratorProduct : numeratorProduct % commonDenominator), commonDenominator);
}
bool Fraction::operator==(const Fraction& obj) const {
    //Checks if the fractions are mathematically equivalent. For example, the comparison 5/6 == 10/12 will return true
    return ((wholeNum*denom) + num)*obj.denom == ((obj.wholeNum*obj.denom) + obj.num)*denom;
}
const Fraction& Fraction::operator=(const Fraction& obj) {
    if (this != &obj) { //Prevents self-assignment
        wholeNum = obj.wholeNum;
        num = obj.num;
        denom = obj.denom;
    }
    return *this;
}
int Fraction::gcd(int a, int b) const {    //Gets the greatest common divisor of two numbers to help with simplifying
    return b == 0 ? a : gcd(b, a % b);
}
ostream& operator<<(ostream& o, const Fraction& obj) {
    o << obj.toFracStr();
    return o;
}
istream& operator>>(istream& i, Fraction& obj) {
    i >> obj.wholeNum >> obj.num >> obj.denom;
    if (obj.wholeNum < 0) {
        std::cout << "\nSetting whole number equal to " << -1 * obj.wholeNum << "\n";
        obj.wholeNum = -1 * obj.wholeNum;
    }
    if (obj.num < 0) {
        std::cout << "\nSetting numerator equal to " << -1 * obj.num << "\n";
        obj.num = -1 * obj.num;
    }
    if (obj.denom < 0) {
        std::cout << "\nSetting denominator equal to " << -1 * obj.denom << "\n";
        obj.denom = -1 * obj.denom;
    }
    if (obj.denom == 0) {
        std::cout << "\nSetting denominator equal to 1\n";
        obj.denom = 1;
    }
    return i;
}
Fraction::~Fraction() {
    //std::cout << "\nIn destructor!\n\nSetting whole number equal to 0.\nSetting numerator equal to 0.\nSetting denominator equal to 1.\n\n";
    wholeNum = 0;
    num = 0;
    denom = 1;
}
void getValidDenom(int& d) {
    string input = "";
    // Checks for valid input (positive and nonzero denominators only)
    while (!regex_match(input, regex("([1-9])([0-9])*"))) {
        cout << "Please enter a valid denominator.\n";
        cin >> input;
        cout << "\n";
    }
    d = stoi(input);
}

void printTable(int size, Fraction** table) {
    // Formatting variables
    int maxLength = (Fraction(size - 1, size)*Fraction(size - 1, size)).toFracStr().length();
    int spaces = 3;
    // Enumerates the table
    for (int i = 0; i < size + 1; i++) {
        cout.width(i == 0 || i == 1 ? maxLength + spaces : maxLength + spaces + 1);
        cout << right << "[" + (i == 0 ? "_" : to_string(i - 1)) + "]";
    }
    cout << "\n";
    // Prints out all fractions
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == 0) {
                cout.width(maxLength + spaces);
                cout << right << "[" + to_string(i) + "]";
            }
            cout.width(maxLength + spaces);
            cout << right << table[i][j] << " ";
        }
        cout << "\n";
    }
}

Fraction** createTable(int size) {
    // Dynamically creates a square (size x size) table and checks for successful memory allocation
    Fraction ** table = new (nothrow)Fraction*[size];        // rows = size
    if (table == nullptr) {
        cout << "Memory allocation failure (1). Terminating program...\n\n";
        exit(1);
    }
    for (int i = 0; i < size; i++) {                        // columns = size
        table[i] = new (nothrow)Fraction[size];
        if (table[i] == nullptr) {
            cout << "Memory allocation failure (2). Terminating program...\n\n";
            exit(1);
        }
    }
    // Initializes the fraction table
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            table[i][j] = (i == 0 ? Fraction(j, size) : j == 0 ? Fraction(i, size) : Fraction(i, size)*Fraction(j, size));
        }
    }
    return table;
}

void destroyTable(int size, Fraction** table) {
    // Deallocates all allocated memory
    for (int i = 0; i < size; i++) {
        delete[] table[i];
    }
    delete[] table;
}





