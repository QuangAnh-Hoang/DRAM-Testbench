#/*
#Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
#SPDX-License-Identifier: X11
#*/

#include <stdint.h>

//#include "cmdlineparser.h"
#include <iostream>
#include <cstring>

#include "MemoryController.h"

#define ARRAY_LENGTH 64

int main(int argc, char** argv) {
	srand(time(NULL));
	MemoryController* memCtrl = MemoryController::getInstance();

	uint16_t inArr[ARRAY_LENGTH];
	uint16_t outArr[ARRAY_LENGTH];

	for ( int i = 0; i < ARRAY_LENGTH; i++ ) {
		inArr[i] = i;
	}
	
	for ( int i = 0; i < ARRAY_LENGTH; i++ ) {
		if ((i % BURST_LENGTH) == 0) {
			memCtrl->write(i, &inArr[i], BURST_LENGTH);
			memCtrl->read(i);
		}
	}

	memCtrl->ifc->flush();

	for (int i = 0; i < ARRAY_LENGTH; i++) {
		outArr[i] = memCtrl->getMemoryResp(i);
		std::cout << "Recv " << i << " = " << outArr[i] << std::endl;		
	}

	std::cout << "Result array: [";
	for ( int i = 0; i < ARRAY_LENGTH; i++ ) {
		std::cout << outArr[i] << ", ";
	}
	std::cout << "]" << std::endl;

    return 0;
}
