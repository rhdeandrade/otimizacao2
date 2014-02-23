/*
 * HillClimbing.cpp
 *
 *  Created on: 20/02/2014
 *      Author: raphael
 */


#ifndef HILLCLIMBING_CPP_
#define HILLCLIMBING_CPP_


#include "HillClimbing.h"

HillClimbing::HillClimbing(PlanoProducao s, int m, int mp) {

	this->currentState = s;
	this->maximumIterationsNumber = m;
	this->maximumPerturbationNumberForIteration = mp;

}

PlanoProducao HillClimbing::execute(int atomicOperationId) {

	int counter = 1;

	while(1) {
		this->perturbation(atomicOperationId, counter);

		if (this->stopMainLoop(counter)) {
			break;
		}

		counter++;
	}

	return this->currentState;
}

void HillClimbing::perturbation(int atomicOperationId, int counter) {
	this->nextState(this->currentState);

	for(int i; i < this->maximumPerturbationNumberForIteration; i++) {
		this->nextState.perturbation(atomicOperationId, counter);

		if (this->changeCurrentState()) {
			this->currentState(this->nextState);
		}
		counter++;
	}


}

bool HillClimbing::changeCurrentState() {
	long double cost1 = this->currentState().objectiveFunctionValue();
	long double cost2 = this->nextState().objectiveFunctionValue();

	if (cost1 > cost2) {
		return true;
	}

	return false;
}

bool HillClimbing::stopMainLoop(int iteration) {
	if (iteration > this->maximumIterationsNumber) {
		return true;
	}

	return false;
}

#endif
