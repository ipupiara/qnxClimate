/* soapH.h
   Generated by gSOAP 2.7.9a from getStates.h
   Copyright(C) 2000-2006, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/
#include "stdafx.h"

#ifndef soapH_H
#define soapH_H
#include "soapStub.h"
SOAP_FMAC3 int SOAP_FMAC4 soap_ignore_element(struct soap*);
#ifndef WITH_NOIDREF
SOAP_FMAC3 int SOAP_FMAC4 soap_putindependent(struct soap*);
SOAP_FMAC3 int SOAP_FMAC4 soap_getindependent(struct soap*);
SOAP_FMAC3 void SOAP_FMAC4 soap_markelement(struct soap*, const void*, int);
SOAP_FMAC3 int SOAP_FMAC4 soap_putelement(struct soap*, const void*, const char*, int, int);
SOAP_FMAC3 void * SOAP_FMAC4 soap_getelement(struct soap*, int*);
#endif

SOAP_FMAC3 void * SOAP_FMAC4 soap_instantiate(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_fdelete(struct soap_clist*);
SOAP_FMAC3 void* SOAP_FMAC4 soap_class_id_enter(struct soap*, const char*, void*, int, size_t, const char*, const char*);

#ifndef SOAP_TYPE_byte
#define SOAP_TYPE_byte (2)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_byte(struct soap*, char *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_byte(struct soap*, const char *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_byte(struct soap*, const char*, int, const char *, const char*);
SOAP_FMAC3 char * SOAP_FMAC4 soap_get_byte(struct soap*, char *, const char*, const char*);
SOAP_FMAC3 char * SOAP_FMAC4 soap_in_byte(struct soap*, const char*, char *, const char*);

#ifndef SOAP_TYPE_int
#define SOAP_TYPE_int (1)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_int(struct soap*, int *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_int(struct soap*, const int *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_int(struct soap*, const char*, int, const int *, const char*);
SOAP_FMAC3 int * SOAP_FMAC4 soap_get_int(struct soap*, int *, const char*, const char*);
SOAP_FMAC3 int * SOAP_FMAC4 soap_in_int(struct soap*, const char*, int *, const char*);

#ifndef SOAP_TYPE_xsd__int
#define SOAP_TYPE_xsd__int (10)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_xsd__int(struct soap*, long *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_xsd__int(struct soap*, const long *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_xsd__int(struct soap*, const char*, int, const long *, const char*);
SOAP_FMAC3 long * SOAP_FMAC4 soap_get_xsd__int(struct soap*, long *, const char*, const char*);
SOAP_FMAC3 long * SOAP_FMAC4 soap_in_xsd__int(struct soap*, const char*, long *, const char*);

#ifndef SOAP_TYPE_long
#define SOAP_TYPE_long (9)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_long(struct soap*, long *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_long(struct soap*, const long *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_long(struct soap*, const char*, int, const long *, const char*);
SOAP_FMAC3 long * SOAP_FMAC4 soap_get_long(struct soap*, long *, const char*, const char*);
SOAP_FMAC3 long * SOAP_FMAC4 soap_in_long(struct soap*, const char*, long *, const char*);

#ifndef SOAP_TYPE_xsd__float
#define SOAP_TYPE_xsd__float (8)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_xsd__float(struct soap*, float *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_xsd__float(struct soap*, const float *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_xsd__float(struct soap*, const char*, int, const float *, const char*);
SOAP_FMAC3 float * SOAP_FMAC4 soap_get_xsd__float(struct soap*, float *, const char*, const char*);
SOAP_FMAC3 float * SOAP_FMAC4 soap_in_xsd__float(struct soap*, const char*, float *, const char*);

#ifndef SOAP_TYPE_float
#define SOAP_TYPE_float (7)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_float(struct soap*, float *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_float(struct soap*, const float *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_float(struct soap*, const char*, int, const float *, const char*);
SOAP_FMAC3 float * SOAP_FMAC4 soap_get_float(struct soap*, float *, const char*, const char*);
SOAP_FMAC3 float * SOAP_FMAC4 soap_in_float(struct soap*, const char*, float *, const char*);

#ifndef SOAP_TYPE_GrowBoxInfo
#define SOAP_TYPE_GrowBoxInfo (11)
#endif

SOAP_FMAC3 int SOAP_FMAC4 soap_out_GrowBoxInfo(struct soap*, const char*, int, const GrowBoxInfo *, const char*);
SOAP_FMAC3 GrowBoxInfo * SOAP_FMAC4 soap_get_GrowBoxInfo(struct soap*, GrowBoxInfo *, const char*, const char*);
SOAP_FMAC3 GrowBoxInfo * SOAP_FMAC4 soap_in_GrowBoxInfo(struct soap*, const char*, GrowBoxInfo *, const char*);
SOAP_FMAC5 GrowBoxInfo * SOAP_FMAC6 soap_new_GrowBoxInfo(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_GrowBoxInfo(struct soap*, GrowBoxInfo*);
SOAP_FMAC3 GrowBoxInfo * SOAP_FMAC4 soap_instantiate_GrowBoxInfo(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_GrowBoxInfo(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (26)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *);
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Fault(struct soap*, const char*, int, const struct SOAP_ENV__Fault *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_get_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_in_SOAP_ENV__Fault(struct soap*, const char*, struct SOAP_ENV__Fault *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Fault * SOAP_FMAC6 soap_new_SOAP_ENV__Fault(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Fault(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Fault(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (25)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *);
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Reason(struct soap*, const char*, int, const struct SOAP_ENV__Reason *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_get_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_in_SOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Reason * SOAP_FMAC6 soap_new_SOAP_ENV__Reason(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Reason(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Reason(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (24)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *);
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Detail(struct soap*, const char*, int, const struct SOAP_ENV__Detail *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_get_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_in_SOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Detail * SOAP_FMAC6 soap_new_SOAP_ENV__Detail(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Detail(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Detail(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (22)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *);
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Code(struct soap*, const char*, int, const struct SOAP_ENV__Code *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_get_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_in_SOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Code * SOAP_FMAC6 soap_new_SOAP_ENV__Code(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Code(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Code(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (21)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *);
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Header(struct soap*, const char*, int, const struct SOAP_ENV__Header *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_get_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_in_SOAP_ENV__Header(struct soap*, const char*, struct SOAP_ENV__Header *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Header * SOAP_FMAC6 soap_new_SOAP_ENV__Header(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Header(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Header(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef SOAP_TYPE_ns__performAction
#define SOAP_TYPE_ns__performAction (18)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__performAction(struct soap*, const struct ns__performAction *);
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__performAction(struct soap*, struct ns__performAction *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__performAction(struct soap*, const struct ns__performAction *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__performAction(struct soap*, const char*, int, const struct ns__performAction *, const char*);
SOAP_FMAC3 struct ns__performAction * SOAP_FMAC4 soap_get_ns__performAction(struct soap*, struct ns__performAction *, const char*, const char*);
SOAP_FMAC3 struct ns__performAction * SOAP_FMAC4 soap_in_ns__performAction(struct soap*, const char*, struct ns__performAction *, const char*);
SOAP_FMAC5 struct ns__performAction * SOAP_FMAC6 soap_new_ns__performAction(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__performAction(struct soap*, struct ns__performAction*);
SOAP_FMAC3 struct ns__performAction * SOAP_FMAC4 soap_instantiate_ns__performAction(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__performAction(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__performActionResponse
#define SOAP_TYPE_ns__performActionResponse (17)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__performActionResponse(struct soap*, const struct ns__performActionResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__performActionResponse(struct soap*, struct ns__performActionResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__performActionResponse(struct soap*, const struct ns__performActionResponse *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__performActionResponse(struct soap*, const char*, int, const struct ns__performActionResponse *, const char*);
SOAP_FMAC3 struct ns__performActionResponse * SOAP_FMAC4 soap_get_ns__performActionResponse(struct soap*, struct ns__performActionResponse *, const char*, const char*);
SOAP_FMAC3 struct ns__performActionResponse * SOAP_FMAC4 soap_in_ns__performActionResponse(struct soap*, const char*, struct ns__performActionResponse *, const char*);
SOAP_FMAC5 struct ns__performActionResponse * SOAP_FMAC6 soap_new_ns__performActionResponse(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__performActionResponse(struct soap*, struct ns__performActionResponse*);
SOAP_FMAC3 struct ns__performActionResponse * SOAP_FMAC4 soap_instantiate_ns__performActionResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__performActionResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getGrowBoxInfo
#define SOAP_TYPE_ns__getGrowBoxInfo (14)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getGrowBoxInfo(struct soap*, const struct ns__getGrowBoxInfo *);
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getGrowBoxInfo(struct soap*, struct ns__getGrowBoxInfo *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getGrowBoxInfo(struct soap*, const struct ns__getGrowBoxInfo *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getGrowBoxInfo(struct soap*, const char*, int, const struct ns__getGrowBoxInfo *, const char*);
SOAP_FMAC3 struct ns__getGrowBoxInfo * SOAP_FMAC4 soap_get_ns__getGrowBoxInfo(struct soap*, struct ns__getGrowBoxInfo *, const char*, const char*);
SOAP_FMAC3 struct ns__getGrowBoxInfo * SOAP_FMAC4 soap_in_ns__getGrowBoxInfo(struct soap*, const char*, struct ns__getGrowBoxInfo *, const char*);
SOAP_FMAC5 struct ns__getGrowBoxInfo * SOAP_FMAC6 soap_new_ns__getGrowBoxInfo(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getGrowBoxInfo(struct soap*, struct ns__getGrowBoxInfo*);
SOAP_FMAC3 struct ns__getGrowBoxInfo * SOAP_FMAC4 soap_instantiate_ns__getGrowBoxInfo(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getGrowBoxInfo(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason
#define SOAP_TYPE_PointerToSOAP_ENV__Reason (28)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Reason(struct soap*, const char *, int, struct SOAP_ENV__Reason *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason **, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason **, const char*);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail
#define SOAP_TYPE_PointerToSOAP_ENV__Detail (27)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Detail(struct soap*, const char *, int, struct SOAP_ENV__Detail *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail **, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail **, const char*);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code
#define SOAP_TYPE_PointerToSOAP_ENV__Code (23)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Code(struct soap*, const char *, int, struct SOAP_ENV__Code *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code **, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code **, const char*);

#endif

#ifndef SOAP_TYPE_PointerToGrowBoxInfo
#define SOAP_TYPE_PointerToGrowBoxInfo (12)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToGrowBoxInfo(struct soap*, GrowBoxInfo *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToGrowBoxInfo(struct soap*, GrowBoxInfo *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToGrowBoxInfo(struct soap*, const char *, int, GrowBoxInfo *const*, const char *);
SOAP_FMAC3 GrowBoxInfo ** SOAP_FMAC4 soap_get_PointerToGrowBoxInfo(struct soap*, GrowBoxInfo **, const char*, const char*);
SOAP_FMAC3 GrowBoxInfo ** SOAP_FMAC4 soap_in_PointerToGrowBoxInfo(struct soap*, const char*, GrowBoxInfo **, const char*);

#ifndef SOAP_TYPE_xsd__string
#define SOAP_TYPE_xsd__string (6)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_xsd__string(struct soap*, char **);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_xsd__string(struct soap*, char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_xsd__string(struct soap*, char *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_xsd__string(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char ** SOAP_FMAC4 soap_get_xsd__string(struct soap*, char **, const char*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in_xsd__string(struct soap*, const char*, char **, const char*);

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default__QName(struct soap*, char **);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__QName(struct soap*, char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put__QName(struct soap*, char *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__QName(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char ** SOAP_FMAC4 soap_get__QName(struct soap*, char **, const char*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in__QName(struct soap*, const char*, char **, const char*);

#ifndef SOAP_TYPE_string
#define SOAP_TYPE_string (3)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_string(struct soap*, char **);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_string(struct soap*, char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_string(struct soap*, char *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_string(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char ** SOAP_FMAC4 soap_get_string(struct soap*, char **, const char*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in_string(struct soap*, const char*, char **, const char*);

#endif

/* End of soapH.h */
