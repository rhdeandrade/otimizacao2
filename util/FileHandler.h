/*
 * FileHandler.h
 *
 *  Created on: 10/10/2013
 *      Author: raphael
 */

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class FileHandler {
public:
	FileHandler();
	std::vector<string> open_file(string file_name);
};

#endif /* FILEHANDLER_H_ */
