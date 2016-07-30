/*
 * Behavior.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_
#include <vector>
#include "../Robot.h"
using namespace std;

class Behavior {
	vector<Behavior*> _behVect;
protected:
	Robot* _robot;
	int _behSize = 0;
public:
	Behavior(Robot* robot);
	virtual ~Behavior();
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	void addBeh(Behavior* next)
	{
		_behVect.push_back(next);
		_behSize++;
	}
	Behavior* selectNext()
	{
		int i;
		for(i=0;i<_behSize;i++)
			if(_behVect[i]->startCond())
				return _behVect[i];

		return NULL;
	}

};

#endif /* BEHAVIOR_H_ */
