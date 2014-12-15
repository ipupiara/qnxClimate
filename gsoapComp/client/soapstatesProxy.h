/* soapstatesProxy.h
   Generated by gSOAP 2.7.9a from getStates.h
   Copyright(C) 2000-2006, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapstates_H
#define soapstates_H
#include "soapH.h"
class states
{   public:
	struct soap *soap;
	const char *endpoint;
	states()
	{ soap = soap_new(); endpoint = "http://services.xmethods.net/soap"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:xmethods-delayed-quotes", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	virtual ~states() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	virtual int ns__getGrowBoxInfo(GrowBoxInfo *Result) { return soap ? soap_call_ns__getGrowBoxInfo(soap, endpoint, NULL, Result) : SOAP_EOM; };
	virtual int ns__performAction(long actionCode, long &return_Code) { return soap ? soap_call_ns__performAction(soap, endpoint, NULL, actionCode, return_Code) : SOAP_EOM; };
};
#endif
