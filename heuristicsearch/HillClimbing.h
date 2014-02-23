/*
 * HillClimbing.h
 *
 *  Created on: 20/02/2014
 *      Author: raphael
 */

#ifndef HILLCLIMBING_H_
#define HILLCLIMBING_H_

class HillClimbing {
public:
	HillClimbing(PlanoProducao s, int m, int mp);

	PlanoProducao currentState;
	PlanoProducao nextState;

	int maximumIterationsNumber;
	int maximumPerturbationNumberForIteration;

	PlanoProducao execute(int atomicOperationId);
	void perturbation(int atomicOperationId, int counter);
	bool stopMainLoop(int iteration);
	bool changeCurrentState();


};

#endif /* HILLCLIMBING_H_ */
