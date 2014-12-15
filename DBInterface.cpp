
#include "DBInterface.h"

//#include "mysql.h"




void DBInterface::initDBInterface()
{
/*	TRACE0("dbinteface initDBInterface\n");
	interfaceOn = false;
	attemptConnect();  */
}

int DBInterface::isInterfaceOn()
{
//	return interfaceOn;
	return 0;
}

void DBInterface::exitDBInterface()
{	
//	TRACE0("dbinteface exitDBInterface\n");
/*	closeConnect(); */
}

void DBInterface::logValues(float temp, float hum)
{
/*
	if (! interfaceOn ) attemptConnect();

	if (interfaceOn) {

		char buffer [1024];

		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"insert into growdata (temp, hum) values ( %.2f , %.2f )",temp, hum);

	//	TRACE1("logValues %s \n",buffer);

		if (mysql_real_query(&mysql,buffer,strlen(buffer)) == 0){
//			TRACE0("record Added\n");
		} else {
			TRACE1("add failed %s \n",mysql_error(&mysql));
			closeConnect();
		}
	}
*/
}

void DBInterface::closeConnect() {
/*	mysql_close(&mysql);	
	interfaceOn = false;
	TRACE0("dbinteface close\n");
	*/
}

void DBInterface::attemptConnect()
{ 
/*	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql,"mirabella","grower","grower","growdb",0,NULL,0)) {
		interfaceOn = false;
		TRACE0("mysql connect failed\n");

	} else {
		interfaceOn = true;
//		TRACE0("mysql connect ok\n");
	}
	*/
}