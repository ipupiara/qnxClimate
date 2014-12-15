#ifndef DBInterface_h
#define DBInterface_h

//#include "mysql.h"


class DBInterface
{
	
public:
	void initDBInterface();
	void exitDBInterface();
	void logValues(float temp, float hum);
	int isInterfaceOn();
private:
//	MYSQL mysql;

//	bool interfaceOn;
	
	void attemptConnect();
	void closeConnect();
};
#endif

