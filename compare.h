//
// Created by Zhenyuxi Ji on 2022/4/11.
//

#ifndef HW3_SUPP_COMPARE_H
#define HW3_SUPP_COMPARE_H
#include<filesystem>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * method to give the name and the vector of Char of the file
 */
class file_and_name{
private:
    std::vector<char> file_to_check;
    std::string fileName;
public:
    const std::vector<char> get_file_to_check()const{
        return file_to_check;
    }
    const std::string get_fileName()const {
        return fileName;
    }
    file_and_name(std::vector<char> _file_to_check, std::string _fileName):fileName(_fileName)
            , file_to_check(_file_to_check){}
};

/**
 * Function that takes in a path name (Alice, Bob...) and then scan files in that directory
 * convert each of the files in the directory to vector of Char
 * @param path path name (Alice, Bob...)
 * @return the name and the vector of char of the file
 */
file_and_name read_file(const std::string& path) ;

/**
 * Function that compare if each of the char in two vector of char is the same
 * if same put in 1, if not put in 0
 * @param first first vector of char(a file)
 * @param second second vector of char(a file)
 * @return a matrix of 0 and 1
 */
std::vector<std::vector<int>> match(std::vector<char> &first, std::vector<char> &second);

/**
 * Function that count how many chars are equal
 * @param match the 0 and 1 matrix
 * @return a matrix with different numbers
 */
std::vector<std::vector<int>> count(const std::vector<std::vector<int>> &match);

/**
 * Function that takes in the 0 and 1 matrix and the count matrix and a file(in order to get the char in to a string)
 * generate the string of common char of two files
 * @param match 0 and 1 matrix
 * @param count count matrix
 * @param file a file(in order to get the char in to a string)
 * @return
 */
std::string backTrack(const std::vector<std::vector<int>> &match, const std::vector<std::vector<int>> &count,
                      const std::vector<char> &file);
/**
 * Function that loop through each of the directories and compare two files
 * @param file1 file1 to compare
 * @param file2 file2 to compare
 */
void compareFiles( const std::string& file1, const std::string& file2);

#endif //HW3_SUPP_COMPARE_H

