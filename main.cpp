#include <iostream>
#include<vector>
#include "compare.h"

namespace fs = std::filesystem;

int main(int arc, char**arv) {
    if(arc != 2){
        throw std::logic_error("can not compile");
    }
    const fs::path path{arv[1]};//the path of the folder
    std::vector<std::string>submissions;//vector of the path name of each submission
    for(const auto &submission:fs::directory_iterator(path)) {//loop through the files in the folder
        if (fs::is_directory(submission.path())) {//if the path name is a directory
            submissions.push_back(submission.path());//push it back in the vector of path name

        }
    }
    std::size_t numberOfSubmission = submissions.size();//the number of directories of submissions
    std::string file1 = " ";
    std::string file2 = " ";

    for(std::size_t i = 0; i < numberOfSubmission; ++i){
        file1 = submissions[i];//the path name of the first file
        for(std::size_t j = i + 1; j < numberOfSubmission; ++j){
            file2 = submissions[j];//the path name of the second file
            compareFiles(file1, file2);//call compareFiles function
        }
    }
    return 0;
}

