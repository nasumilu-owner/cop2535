// Michael Lucas
// COP2535.DM1
// Description 
//  1. Reads in a string from the user
//  2. Displays the strings range of characters
//  3. Diplays a character a user inputted position
//      a. If value is out of range raise a BoundsException
//      b. If value is not valid raise a BoundsException
//  4. User inputs '\q' to terminate

#include <iostream>
#include <string>
#include <regex>

/**
 * BCheckString class extends the STL string class to provide an 
 * alternative [] operator. 
 * 
 * This is in lieu of a header (*.h) file.
 * 
 * @see http://www.cplusplus.com/reference/string/string/operator[]/ for details
 */
class BCheckString : public std::string {
        
    private:
        static const int MIN_STRING_LENGTH = 2;             // min string length allowed from input
        void set();                                         // sets this classes string value from user input
        void displayRange();                                // displays the strings range, 0....n characters
        void getChar();                                     // gets a char from user input.
        int validate(const std::string&) const;             // validate member function -- project requirement
        void validate(size_t) const;
    public:
        BCheckString();                                     // default, empty construct -- project requirement
        BCheckString(const std::string&);                   // string copy constructor
        const char& operator[](size_t) const;               // overload the std::string[] operator
        const char& operator[](const std::string&);         // finds the character at std::string position
        const char& at(size_t) const;                       // overload the std::string::at member function to provide the BoundsException feature
        const char& at(const std::string&);                 // finds the character at std::string
        void driver();                                      // driver member function (controller)
        class BoundsException {                             // Bounds Exception - project requirement
            private:
                std::string msg;                            // Bounds Exception message
                // int statusCode;                           
                // operator to output the BoundsException's message
                friend std::ostream& operator<< (std::ostream &os, const BoundsException &ex)
                {
                    os << "Bounds Exception: " << ex.msg << std::endl;               
                    return os;
                }  
            public:
                BoundsException(const std::string& msg);                        // Default BoundsException construct
                static BoundsException createOutOfRange(const size_t);          // static factory member function to create out of range BoundsException
                static BoundsException createInvalidBounds(const std::string&); // static factory member function to create invlid bounds BoundsException
                                     
        };
};

int main () 
{
    system("cls");      // clear terminal (windows only)
    BCheckString str;   //init as empty string
    str.driver();       //do some stuff
    system("pause");    // pause terminal (windows only)
    return 0;
}

/***************************CONSTRUCTOR*******************************
 * BCheckString default construct                                    *
 * ----------------------------------------------------------------- *
 * Constructs an empty BCheckString string, with a zero length of    *
 * characters. This is accomplished by delegating (extending) the    *
 * std::string class.                                                * 
 *                                                                   *
 * @see http://www.cplusplus.com/reference/string/string/string/     *
 *********************************************************************/
BCheckString::BCheckString() : std::string()
{
}

/***************************CONSTRUCTOR*******************************
 * BCheckString copy construct                                       *
 * ----------------------------------------------------------------- *
 * Constructs a BCheckString string by copying the argument `str`.   *
 * This is accomplished by delegating (extending) the std::string    *
 * class.                                                            * 
 *                                                                   *
 * @see http://www.cplusplus.com/reference/string/string/string/     *
 *********************************************************************/
BCheckString::BCheckString(const std::string &str) : std::string(str)
{
}

/************************MEMBER FUNCTION******************************
 * BCheckString::set                                                 *
 * ----------------------------------------------------------------- *
 * Gets a line of input from the user's terminal and sets            *
 * BCheckString value. The value must have                           *
 * BCheckString::MIN_STRING_LENGTH of characters.                    * 
 *                                                                   *
 * Does not support i18n                                             *
 *********************************************************************/
void BCheckString::set()
{
    std::cout << "Enter a string: ";
    std::getline(std::cin, *this);
    while (!std::cin || this->length() < BCheckString::MIN_STRING_LENGTH) 
    {
        std::cout << "Input must have " << BCheckString::MIN_STRING_LENGTH 
                  << " or more characters! Enter a string: ";
        std::getline(std::cin, *this);
    }
}

/************************MEMBER FUNCTION******************************
 * BCheckString::displayRange                                        *
 * ----------------------------------------------------------------- *
 * Displays the BCheckString valid range. Note the BCheckString's    *
 * first character is subscripted by 0 (not 1).                      * 
 *                                                                   *
 * Does not support i18n                                             *
 *********************************************************************/
void BCheckString::displayRange()
{
    std::cout << std::endl << "Legitimate string positions are: 0 - " 
              << this->length() -1 << std::endl;
}

/************************MEMBER FUNCTION******************************
 * BCheckString::validate                                            *
 * ----------------------------------------------------------------- *
 * Valiates that parameter `pos` is a valid string subscript.        * 
 * ----------------------------------------------------------------- *
 * @param &pos - the string subscript to validate                    *
 * @return int - the validate subscript as an integer.               *
 * @throws BoundsException - when the subscript is invalid or out of *
 *                           range.                                  *
 *********************************************************************/
int BCheckString::validate(const std::string &pos) const
{
    std::regex pattern{"\\d+"};
    int offset;
    //int length = this->length();
    if(std::regex_match(pos, pattern)) 
    {   
        offset = std::stoi(pos);
        this->validate(offset);
    } else {
        throw BCheckString::BoundsException::createInvalidBounds(pos);
    }
    return offset;
}

/************************MEMBER FUNCTION******************************
 * BCheckString::validate                                            *
 * ----------------------------------------------------------------- *
 * Valiates that parameter `pos` is a valid string subscript.        * 
 * ----------------------------------------------------------------- *
 * @param &pos - the integer subscript to validate                   *
 * @throws BoundsException - when the subscript is out of range      *
 *********************************************************************/
void BCheckString::validate(size_t pos) const
{
    if(pos < 0 || pos >= this->length())
    {
        throw BCheckString::BoundsException::createOutOfRange(pos);
    }
}

/************************MEMBER FUNCTION******************************
 * BCheckString::getChar                                             *
 * ----------------------------------------------------------------- *
 * Gets an offset or \q from the user and displays the BCheckString  *
 * character at the inputed position. Becuase BCheckString preservse *
 * spaces any space character is displayed using the string [Space]. *
 * If the inputed value is invalid it will display a message         *
 * and ask again.                                                    *             
 *                                                                   *
 * The user may terminate the program cleanly by inputing \q         *
 * Does not support i18n                                             *
 *********************************************************************/
void BCheckString::getChar() 
{
    std::string position;
    char c;
    do 
    {
        std::cout << std::endl << "Enter an positive integer describing "
                  << "a position inside or outside the string or \\q to "
                  << "quit: ";
        std::getline(std::cin, position);
        if(position != "\\q") {
            try 
            {
                c = (*this)[position];
                std::string value;
                if(c == 32) {
                    value = "[Space]";
                } else {
                    value = c;
                }
                std::cout << std::endl << "The character a position " 
                          << position << " is " <<  value << std::endl;
            }
            catch (const BoundsException ex)
            {
                std::cout << ex;
            }
        }
        
    } while (std::cin && position != "\\q");
}

/************************MEMBER FUNCTION******************************
 * BCheckString::operator[]                                          *
 * ----------------------------------------------------------------- *
 * Gets the reference to the character a position `pos`.             *
 * ----------------------------------------------------------------- *
 * @param pos   The position of the character to obtain.             *
 * @return      The character at the specified position.             *
 * @throws      BoundsException when the parameter `pos` is out of   *
 *              range.                                               *
 *                                                                   *
 * @see http://www.cplusplus.com/reference/string/string/operator[]/ *
 *********************************************************************/
const char& BCheckString::operator[](size_t pos) const
{
    this->validate(pos);
    return std::string::operator[](pos);
}

/************************MEMBER FUNCTION******************************
 * BCheckString::operator[]                                          *
 * ----------------------------------------------------------------- *
 * Gets the reference to the character a position `pos`.             *
 * ----------------------------------------------------------------- *
 * @param pos   The position of the character to obtain as a string. *
 * @return      The character at the specified position.             *
 * @throws      BoundsException when the parameter `pos` is out of   *
 *              range or invalid.                                    *
 *********************************************************************/
const char& BCheckString::operator[](const std::string& pos)
{
    return std::string::operator[](this->validate(pos));
}

/************************MEMBER FUNCTION******************************
 * BCheckString::at                                                  *
 * ----------------------------------------------------------------- *
 * Gets the reference to the character a position `pos`.             *
 * ----------------------------------------------------------------- *
 * @param pos   The position of the character to obtain.             *
 * @return      The character at the specified position.             *
 * @throws      BoundsException when the parameter `pos` is out of   *
 *              range.                                               *
 *                                                                   *
 * @see http://www.cplusplus.com/reference/string/string/at/         *
 *********************************************************************/
const char& BCheckString::at(size_t pos) const
{
    //delegate to the BCheckString[size_t pos] operator
    return (*this)[pos];
}

/************************MEMBER FUNCTION******************************
 * BCheckString::at                                                  *
 * ----------------------------------------------------------------- *
 * Gets the reference to the character a position `pos`.             *
 * ----------------------------------------------------------------- *
 * @param pos   The position of the character to obtain as a string. *
 * @return      The character at the specified position.             *
 * @throws      BoundsException when the parameter `pos` is out of   *
 *              range or invalid.                                    *
 *********************************************************************/
const char& BCheckString::at(const std::string &pos)
{
    //delegate to the BCheckString[const std::string &pos] operator
    return (*this)[pos]; 
}

/************************MEMBER FUNCTION******************************
 * BCheckString::driver                                              *
 * ----------------------------------------------------------------- *
 * The applications controller member function.                      *
 * ----------------------------------------------------------------- *
 * 1. Outputs the programs title message.                            *
 * 2. Calls member function BChekcString::set                        *
 * 3. Displays BCheckString's range                                  *
 * 4. Asks for input to display a charachter.                        *
 * 5. Bids you far well                                              *
 *                                                                   *
 * Does not support i18n                                             *
 *********************************************************************/
void BCheckString::driver() 
{
    std::cout << "This program demonstrates bounds checking on a "
              << "string object." << std::endl;
    this->set(); //set the string value from user input.
    this->displayRange(); // show the range
    this->getChar();
    
    std::cout << "Thank you! Have a great day :-)" << std::endl;
}

/***************************CONSTRUCTOR*******************************
 * BCheckString::BoundsException construct                           *
 * ----------------------------------------------------------------- *
 * The BCheckString::BoundsException class is used to indicate that  *
 * an invalid string subscript (offset) had been requested.          * 
 * ----------------------------------------------------------------- *
 * @param msg - the exception's message suffix                       *
 *********************************************************************/
BCheckString::BoundsException::BoundsException(const std::string& msg) 
{
    this->msg = msg;
}

/*********************STATIC MEMBER FUNCTION**************************
 * BCheckString::BoundsException::createOutOfRange                   *
 * ----------------------------------------------------------------- *
 * Static factory member function for creating a                     *
 * BCheckString::BoundsException which indicates that the an out of  *
 * range offset had been requested.                                  *
 * ----------------------------------------------------------------- *
 * @param invalidOffset - the invalid offset requested               *
 * @return BCheckString::BoundsException                             *
 *                                                                   *
 * Does not support i18n                                             *
 *********************************************************************/
BCheckString::BoundsException BCheckString::BoundsException::createOutOfRange(const size_t invalidOffset)
{
    BCheckString::BoundsException ex{std::to_string(invalidOffset) + " is out of range"};
    return ex;
}

/*********************STATIC MEMBER FUNCTION**************************
 * BCheckString::BoundsException::createInvalidBounds                *
 * ----------------------------------------------------------------- *
 * Static factory member function for creating a                     *
 * BCheckString::BoundsException which indicates that the an invalid *
 * offset had been requested.                                        *
 * ----------------------------------------------------------------- *
 * @param invalidOffset - the invalid offset requested               *
 * @return BCheckString::BoundsException                             *
 *                                                                   *
 * Does not support i18n                                             *
 *********************************************************************/
BCheckString::BoundsException BCheckString::BoundsException::createInvalidBounds(const std::string &invlaidOffset)
{
    BCheckString::BoundsException ex{invlaidOffset + " is an invalid bounds"};
    return ex;
}
