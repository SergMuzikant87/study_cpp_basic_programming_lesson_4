#include "address.h"
#include <iostream>
#include <string>
#include <clocale>

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "Russian");

    #define INPUT_FILE_PATH_INDEX 1
    #define OUTPUT_FILE_PATH_INDEX 2
    const char * input_file_path = "data/in.txt";
    const char * output_file_path = "data/out.txt";
    if(argc > INPUT_FILE_PATH_INDEX)
    {
        input_file_path = argv[INPUT_FILE_PATH_INDEX];
    }
    if(argc > OUTPUT_FILE_PATH_INDEX)
    {
        output_file_path = argv[OUTPUT_FILE_PATH_INDEX];
    }

    int status = 0;
    Addresses addresses(input_file_path, &status);
    if(status != 0)
    {
        std::cout << "Ошибка чтения файла. Код ошибки: " << status << "\n"; 
        return -1;
    }

    addresses.sort();
    if((status = addresses.output(output_file_path)) != 0)
    {
        std::cout << "Ошибка вывода в файл файла. Код ошибки: " << status << "\n"; 
        return -1;
    }
    return 0;
}