#include "GrowBoxDefines.h"
//#include "K8055D.h"


class CoolingController {

public:
	CoolingController();	// standard constructor
	virtual ~CoolingController();

	void start();
	void stop();


//private:
//	k8055d  k8055;

};