#include "compare.h"
#include<filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

file_and_name read_file(const std::string& path) {
    const auto & itr = fs::directory_iterator(path);//iterator over the files;
    std::ifstream inputFile;
    inputFile.open(itr->path());//open of files in the path
    char toAdd = 0;
    std::vector<char>file_to_check;//vector of char of the content in the file
    if(!inputFile.is_open()){
        throw std::logic_error("file not opened");
        std::cout << "file not opened";
    }
    while(inputFile.get(toAdd)){
        file_to_check.push_back(toAdd);
    }
    //std::string pathname = path.substr(41);
    //file_and_name result = file_and_name(file_to_check,pathname);
    file_and_name result = file_and_name(file_to_check,itr->path());
    inputFile.close();
    return result;
}


std::vector<std::vector<int>> match(std::vector<char> &first, std::vector<char> &second) {
    std::vector<std::vector<int>> result;//a matrix that consist of 0 and 1
    for(size_t i = 0; i < second.size(); ++i){// have the second vector the row
        std::vector<int>row;//a new row
        for(size_t j = 0; j < first.size(); ++j){//make the first row the column
            if(second[i] == first[j]){//if two char is equal
                row.push_back(1);//push 1 into the row
            }else{
                row.push_back(0);//push 0 into the row
            }
        }
        result.push_back(row);//push the row into the matrix
    }
    return result;
}

std::vector<std::vector<int>> count(const std::vector<std::vector<int>> &match) {
    std::vector<std::vector<int>> result;// a matrix of different number
    std::vector<int>frst_row(match[0].size(),1);//first row is all 1's
    result.push_back(frst_row);//push back the first row which
    for(size_t i = 1; i < match.size(); ++i){//start from the second row and loop
        std::vector<int>row;// a new row
        row.push_back(1);//first one in each row is 1
        for(size_t j = 1; j < match[0].size(); ++j ){//start from the second column and loop
            if(match[i][j] == 0){//if two char is different
                row.push_back(std::max(row[j-1], result[i-1][j]));//make the number be the max number between its upper
                //number and its left number
            }else{
                row.push_back(1 + result[i-1][j-1]);//if two char is the same
                //add the number one to its upper right
            }
        }
        result.push_back(row);//push back the row into the matrix
    }
    return result;
}

std::string backTrack(const std::vector<std::vector<int>> &match, const std::vector<std::vector<int>> &count,
                      const std::vector<char> &file) {
    std::string common = "";//the string of common char to return
    size_t i = match.size() - 1;//the row to loop
    size_t j = match[0].size() - 1;// the column to loop
    while(count[i][j] > 1){//while the count matrix number is not one(since one is the first row and column.
        if(match[i][j] == 1){//if the two char is equal
            common = file[j] + common;//add the char to the string
            i--;//decrement row
            j--;//decrement column
            //which mean get down to the down right
        }else{//if the two are not equal, go to the higher on between its up and left number
            if(count[i][j-1] < count[i-1][j]){//if its uper one is greater that its left one
                i--;//go up
            }else{
                j--;//go down
            }
        }
    }
    return common;
}

void compareFiles( const std::string& file1, const std::string& file2){
    std::vector<char>file_1 = read_file(file1).get_file_to_check();//get the vector of char of file 1
    std::vector<char>file_2 = read_file(file2).get_file_to_check();//get the vector of char of file 2
    std::string file1name = read_file(file1).get_fileName();//get the filename1
    std::string file2name = read_file(file2).get_fileName();//get the filename2

    std::vector<std::vector<int>> mathches = match(file_1,file_2);//get the matching matrix of file1 and file2
    std::string commonString = backTrack(mathches, count(mathches),file_1);
    //get the common string
    std::cout <<"\nParing " << file2name << "-" << file1name << "\n";
    std::cout << "Common Subsequence Length: " << commonString.size() << "\n";
    std::cout << "Overlap: \n" << commonString << "\n";
    std::cout << "----------------";
}

