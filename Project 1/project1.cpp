//Michael Lucas
//COP2535.DM1
//Bubble & selection sort & linear & binary search comparison
 
#include<iostream>
#include<fstream>
#include<string>

/************************PREPROCESS DIRECTIVE*************************
 * Since this is sequential the #define preprocess directive is used;*
 * In OOP these values would have been static const members of some  *
 * class.                                                            *
 ********************************************************************/
#define STATUS_OK               0       // Program finished as expected.
#define STATUS_PROCESSING       200     // Processing status             
#define STATUS_BAD_FILE         400     // Invalid file contents         
#define STATUS_FILE_NOT_FOUND   404     // random.txt file not found     
#define BUFFER_SIZE             200     // The maximum buffer size.      

/******************************STRUT**********************************
 * search_result                                                     *
 * ----------------------------------------------------------------- *
 * Provides a data structure for the results of a search function.   *
 * ----------------------------------------------------------------- *
 * @param search_method  the name or description of the search       *
 *                       algorithm which produced the results.       *
 * @param subscript      the search value's subscript (index); If not*
 *                       this value must be -1;                      *
 * @param num_comparison the number of comparisons required to find  * 
 *                       to find the value.                          *
 ********************************************************************/
struct search_result {
    std::string search_method;
    int subscript = -1;
    unsigned int num_comparison = 0;
};

/******************************STRUT**********************************
 * sort_result                                                       *
 * ----------------------------------------------------------------- *
 * Provides a data structure for the results of a search function.   *
 * ----------------------------------------------------------------- *
 * @param sort_method   the name or description of the sort          *
 *                      algorithm which produced the results.        *
 * @param num_exchange  the number of exchanges required to sort the *
 *                      number_buffer.                               *
 ********************************************************************/
struct sort_result {
    std::string sort_method;
    unsigned int num_exchange = 0;
};

/****************************TYPEDEF**********************************
 * number_buffer                                                     *
 * ------------------------------------------------------------------*
 * Defined type used to store the numbers readed from the random.txt *
 * file.                                                             *
 ********************************************************************/
typedef int number_buffer[BUFFER_SIZE];

/********************* FUNCTION SIGNATURES **************************/
int file_get_contents(const std::string, number_buffer&, number_buffer&);
sort_result bubble_sort(number_buffer&);
search_result linear_search(const int, const number_buffer&);
sort_result selection_sort(number_buffer &);
search_result binary_search(const int, const number_buffer&);
void sort_result_msg(const sort_result&, const std::string);
void search_result_msg(const int search_value, const search_result&, const number_buffer&);
void error_msg(const std::string, const int);

/*****************************FUNCTION********************************
 * main                                                              *
 * ----------------------------------------------------------------- *
 * Main function reads a file of random numbers into two arrays.     *
 * Sorts one array with a bubble sort & the other                    *
 * with a selection sort. Searchs for the a value of 869 using a     *
 * linear and binary search.                                         *
 * Dispalys results to std::cout                                     *
 * ----------------------------------------------------------------- *
 * @return  exit status code                                         *
 ********************************************************************/
int main()
{ 
    //declare and initialize required variables.
    int status = STATUS_PROCESSING;
    const std::string filename = "./random.txt";
    number_buffer buffer1, buffer2;
    const int search_value = 869;

    //Get the contents of the `filename`
    status = file_get_contents(filename, buffer1, buffer2);
    if(status == STATUS_OK) {
    
        //Bubble Sort
        sort_result sort = bubble_sort(buffer1);
        sort_result_msg(sort, filename);

        //Selection Sort
        sort = selection_sort(buffer2);
        sort_result_msg(sort, filename);

        //Linear Search
        search_result search = linear_search(search_value, buffer1);
        search_result_msg(search_value, search, buffer1);

        //Binary Search
        search = binary_search(search_value, buffer2);
        search_result_msg(search_value, search, buffer2);

    } else {
        error_msg(filename, status);
    }

    system("pause");
    return status;
}

/*****************************FUNCTION********************************
 * file_get_contents                                                 *
 * ----------------------------------------------------------------- *
 * Reads a files contents into an two arrays and returns a status    *
 * code.                                                             *
 * ----------------------------------------------------------------- *
 * @param filename  the full-qualified or relative path of the file  *
 *                  to read.                                         *
 * @param buffer1   the first array to read the files contents into  *
 * @param buffer2   the sechod array to read the files contents into *
 * @return          0 when contents was read successfully;           *
 *                  400 when the file contains bad bad data.         *
 *                  404 when the file is not found                   *
 ********************************************************************/
int file_get_contents(const std::string filename, number_buffer &buffer1, number_buffer &buffer2) 
{
    int status = STATUS_OK;
    std::ifstream filein;
    // open file
    filein.open(filename);
    if(!filein) {
        // unable to open file
        status = STATUS_FILE_NOT_FOUND; 
    } else {
        // read file
        for(int i = 0; i < BUFFER_SIZE; i++) 
        {
            int value;
            filein >> value;
            if(!filein) {
                // encountered some bad data stop reading
                status = STATUS_BAD_FILE; 
                break;
            }
            buffer1[i] = value;
            buffer2[i] = value;
        }
        filein.close(); // be sure to close before we leave.
    }
    return status;
}

/*****************************FUNCTION********************************
 * bubble_sort                                                       *
 * ----------------------------------------------------------------- *
 * Performs a bubble sort on a `number_buffer`.                      *
 * ----------------------------------------------------------------- *
 * @param   &buffer the number ubffer to sort                        *
 * @return  the number of exchenages need to sort the buffer         *
 ********************************************************************/
sort_result bubble_sort(number_buffer &buffer)
{
    sort_result result{"Bubble"};
    for(int i = 0; i < BUFFER_SIZE - 1; i++) 
    {
        for(int j = 0; j < BUFFER_SIZE - i - 1; j++) 
        {
            if(buffer[j+1] < buffer[j]) {
                std::swap(buffer[j+1], buffer[j]);
                result.num_exchange++;
            }
        }
        if(result.num_exchange == 0) {
            break; //everything is in order here
        }
    }
    return result;
}

/*****************************FUNCTION********************************
 * linear_search                                                     *
 * ----------------------------------------------------------------- *
 * Searchs for the value `search_value` in `number_buffer` using a   *
 * linear search algorithm.                                          *
 * ----------------------------------------------------------------- *
 * @param   search_value the value to search for                     *
 * @param   &buffer      the number ubffer to search                 *
 * @return  a search_result containing the search results            *
 ********************************************************************/
search_result linear_search(const int search_value, const number_buffer &buffer) 
{
    search_result result{"Linear"};
    for(int i = 0; i < BUFFER_SIZE; i++) 
    {
        result.num_comparison++;
        if(buffer[i] == search_value) {
            result.subscript = i;
            break; //found it we are done here
        }
    }
    return result;
}

/*****************************FUNCTION********************************
 * selection_sort                                                    *
 * ----------------------------------------------------------------- *
 * Performs a selection sort on a `number_buffer`.                   *
 * ----------------------------------------------------------------- *
 * @param   &buffer the number ubffer to sort                        *
 * @return  the number of exchenages need to sort the buffer         *
 ********************************************************************/
sort_result selection_sort(number_buffer &buffer) 
{
    sort_result result{"Selecton"};
    for(int i = 0; i < BUFFER_SIZE - 1; i++) 
    {
        int index = i;
        for(int j = i + 1;j < BUFFER_SIZE; j++) 
        {
            if(buffer[j] < buffer[index]) {
                index = j;
            }
        }
        if(index != i) {
            std::swap(buffer[index], buffer[i]);
            result.num_exchange++;
        }
    }
    return result;
}

/*****************************FUNCTION********************************
 * binary_search                                                     *
 * ----------------------------------------------------------------- *
 * Searchs for the value `search_value` in `number_buffer` using a   *
 * binary search algorithm.                                          *
 * ----------------------------------------------------------------- *
 * @param   search_value the value to search for                     *
 * @param   &buffer      the number buffer to search                 *
 * @return  a search_result containing the search results            *
 ********************************************************************/
search_result binary_search(const int search_value, const number_buffer &buffer) 
{
    search_result result{"Binary"};
    int lower_bound = 1;
    int upper_bound = BUFFER_SIZE;
    while(result.subscript == -1) 
    {
        result.num_comparison++;
        if(upper_bound < lower_bound) {
            break; // value not found
        }
        int offset = lower_bound + (upper_bound - lower_bound) / 2;
        if(buffer[offset] < search_value) {
            lower_bound = offset + 1;
        } else if(buffer[offset] == search_value) {
            result.subscript = offset;
        } else {
            upper_bound = offset -1;
        }
    }
    return result;
}

/*****************************FUNCTION********************************
 * sort_result_msg                                                   *
 * ----------------------------------------------------------------- *
 * Utility function for outputting a sort_result.                    *
 * Does not support i18n                                             *
 * Does not support pluralization                                    *
 * ----------------------------------------------------------------- *
 * @param search_value  the search value                             *
 * @param filename      the fully-qualified or relative path of the  *
 *                      random number file                           *
 *********************************************************************/
void sort_result_msg(const sort_result &result, const std::string filename)
{
        std::cout << result.sort_method << " sort used " 
            << result.num_exchange << " exchanges to sort the integer "
            << "values found in " << filename << "." << std::endl;
}

/*****************************FUNCTION********************************
 * search_result_msg                                                 *
 * ----------------------------------------------------------------- *
 * Utility function for outputing a search_result.                  *
 * Does not support i18n                                             *
 * Does not support pluralization                                    *
 * ----------------------------------------------------------------- *
 * @param search_value  the search value                             *
 * @param &result       the results of the serarch                   *
 * @param &buffer       the number_buffer searched                   *
 ********************************************************************/
void search_result_msg(const int search_value, const search_result &result, const number_buffer &buffer) 
{
        if(result.subscript == -1) {
            std::cout << "Unable to find value " << search_value << "!" << std::endl;
        } else {
            std::cout << result.search_method << " search took " << result.num_comparison 
                << " comparisons to find the value " << buffer[result.subscript]
                << " at subscript " << result.subscript << std::endl;
        }
}

/*****************************FUNCTION********************************
 * error_msg                                                         *
 * ----------------------------------------------------------------- *
 * Utility function for outputing an error messages.                *
 * Does not support i18n                                             *
 * ----------------------------------------------------------------- *
 * @param filename  the fully-qualified or relative path of the      *
 *                  random number file                               *
 * @param status    the error code                                   *
 ********************************************************************/
void error_msg(const std::string filename, const int status)
{
    if(status == STATUS_BAD_FILE) {
        std::cout << "Please check the " << filename 
            << " file it contains invalid data." << std::endl;
    } else if (status == STATUS_FILE_NOT_FOUND) {
        std::cout << "File " << filename 
            << " not found! Please check the file path to ensure "
            << "it is in the programs working directory!" << std::endl;
    } else {
        std::cout << "Error: " << status << std::endl;
    }
}