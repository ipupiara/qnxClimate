//gsoap ns service name:	states
//gsoap ns service style:	rpc
//gsoap ns service encoding:	encoded
//gsoap ns service namespace:	urn:xmethods-delayed-quotes
//gsoap ns service location:	http://services.xmethods.net/soap

//gsoap ns service method-action: getStates ""

typedef char *xsd__string; 
typedef float xsd__float; 
typedef long xsd__int; 

class GrowBoxInfo  {
public:
	xsd__int  HygroCnt;
	xsd__float  Temperature;
	xsd__float   Humidity;
	xsd__string		State;
};


int ns__getGrowBoxInfo( GrowBoxInfo * Result);

int ns__performAction(xsd__int  actionCode, xsd__int&  return_Code);


