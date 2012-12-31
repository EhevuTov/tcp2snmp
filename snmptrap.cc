// Tekno Telecom SNMP Trap
// O.M. Created.  2010

#include <stdio.h>
#include "winsnmp.h"
#include "time.h"
#include "snmptrap.h"

#define ENTERPRISE 1, 3, 6, 1, 4, 1, 3, 1, 36872
// Stub callback function
SNMPAPI_STATUS CALLBACK cbFunc(HSNMP_SESSION hSession, HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam, LPVOID lpClientData)
{
	return SNMPAPI_SUCCESS;
}
void trap::init() {
	hSession		= SNMPAPI_FAILURE;
	hDst			= SNMPAPI_FAILURE;
	hVbl		    = SNMPAPI_FAILURE;
	hPdu			= SNMPAPI_FAILURE;
	hContext		= SNMPAPI_FAILURE;
    
	cB = &cbFunc;
				
	id = 1;

	sysUpTime[0] = 1;
	sysUpTime[1] = 3;
	sysUpTime[2] = 6;
	sysUpTime[3] = 1;
	sysUpTime[4] = 2;
	sysUpTime[5] = 1;
	sysUpTime[6] = 1;
	sysUpTime[7] = 3;
	sysUpTime[8] = 0;

	snmpTrapOid[0]	= 1;
	snmpTrapOid[1]	= 3;
	snmpTrapOid[2]	= 6;
	snmpTrapOid[3]	= 1;
	snmpTrapOid[4]	= 4;
	snmpTrapOid[5]  = 1;
	snmpTrapOid[6]	= 36872;
	snmpTrapOid[7]  = 1;
	snmpTrapOid[8]  = 0;

	// make copies for some reason
	memcpy (snmpTrapOid, trapValue, sizeof (snmpTrapOid)) ;
	memcpy (snmpTrapOid, snmpTrapEnterprise, sizeof(snmpTrapOid));

	smiOID dSysUpTimeName   = {9, sysUpTime};
	smiOID dTrapName        = {9, snmpTrapOid};
	smiOID dEnterpriseName  = {9, snmpTrapEnterprise};

	smiOID		dOID  = {9, snmpTrapEnterprise};
	smiVALUE	valEvent;
	TargetPort = 162;
	snmpSendPort = 162;	 // 162 is default
	SnmpReturnError = 1;					// -1 failed, 1 success     
}

trap::trap() {
	init();





	sprintf(trapTargetIP, "127.0.0.1");  //  for debug only !!!
	snmpSendPort = 26;					 //  for debug only !!!
	sprintf(Community, "public");		 //  for debug only !!!
}
trap::trap(char TargetIp[15], char TargetCommunity[100], unsigned int TargetPort, unsigned int snmpSendPort, char trapTargetIP[15], char Community[100], int SnmpReturnError, unsigned char	ContextBuffer[300]) {

	smiOID dSysUpTimeName   = {9, sysUpTime};
	smiOID dTrapName        = {9, snmpTrapOid};
	smiOID dEnterpriseName  = {9, snmpTrapEnterprise};


//	smiVALUE valEnterprise;

	smiOID		dOID  = {9, snmpTrapEnterprise};
	smiVALUE	valEvent;
	memset(trapTargetIP,' ',15);
	sprintf(Community,TargetCommunity);
	snmpSendPort = TargetPort;
/*
for ( int i = 0; i < CharCount; i++)
		trapTargetIP[i] = TargetIp[i];
*/
}

  void TeknoSnmpTrap_Looping(unsigned long EventID, int LinkID, unsigned int ProcessorID,  unsigned int PortID, unsigned long Direction, unsigned int  MessageType, char TextBuffer[255], int TextLength )
  {
	//===============================================
	// Loop Alarm Record Structs as defined in Snmm.h
	#define MaxDigBytes 10  
	/*
	 *  BCD digits structure
	 */
	typedef
	struct { 
		byte  flag;
		byte  nature;
		byte  status;
		byte  numberplan;
		byte  category;
		byte  encoding;
		byte  number[ MaxDigBytes ]; 
	} numberset ;
	//
	typedef
	struct _pointcode
	{ byte netid,
		netcluster,
		netmember,
		filler;      
	} pointcode ;

	typedef
	struct {
	unsigned __int32 Link             ; /* Link								  */
	unsigned __int32 CorrelationSetId ; // Now Correlation Set Id
	byte		Direction			  ; /* 0 Incoming, 1 Outgoing ???         */
	unsigned int  	 ThresholdValue   ; /* Threshold count				  */

	pointcode   MtpOPC			      ; /* MTP Originating Point Code   4     */
	pointcode   MtpDPC			      ; /* MTP Destination Point Code   4     */
	pointcode   STPPointCode          ; /* Local STP Point Code         4     */
	pointcode   SPSTPPointCode        ; /* SP/STP Point Code            4     */

	byte        SCCPcalledaddrind     ; /* called address ind                 */
	byte        SCCPcalledSubsys      ; /* called subsystem num               */
	pointcode   SCCPcalledPC          ; /* called point code                  */
	byte        SCCPcalledTranstype   ; /* called translation                 */
	numberset   SCCPcalledTitleAddr   ; /* called global title addr           */

	byte        SCCPcallingaddrind    ; /* calling address ind                */
	byte        SCCPcallingSubsys     ; /* calling subsystem num              */
	pointcode   SCCPcallingPC         ; /* calling point code                 */
	byte        SCCPcallingTranstype  ; /* calling translation                */
	numberset   SCCPcallingTitleAddr  ; /* calling global title               */

	byte		TranIdOrig[4] 		  ; /* transaction ID originating		  */
	byte		TranIdDest[4]		  ; /* transaction ID destination		  */
	unsigned int		OpCode;
	} LoopAlarmRecord;

	LoopAlarmRecord LAR;

	memcpy(&LAR, TextBuffer, sizeof(LAR)); 

	// Link
	snmpTrapEnterprise[8] = 2;        // 
	valEvent.syntax = SNMP_SYNTAX_INT;
	valEvent.value.uNumber = LAR.Link;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	//CorrelationSetId
	snmpTrapEnterprise[8] = 3;        // 
	valEvent.syntax = SNMP_SYNTAX_INT;
	valEvent.value.uNumber = LAR.CorrelationSetId;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Direction
	snmpTrapEnterprise[8] = 4;        // 
	valEvent.syntax = SNMP_SYNTAX_INT;
	valEvent.value.uNumber = LAR.Direction;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// ThresholdValue
	snmpTrapEnterprise[8] = 5;        // 
	valEvent.syntax = SNMP_SYNTAX_INT;
	valEvent.value.uNumber = LAR.ThresholdValue;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// MtpOPC
	snmpTrapEnterprise[8] = 6;        // 
	valEvent.syntax = SNMP_SYNTAX_UNSIGNED32;
	valEvent.value.uNumber = (LAR.MtpOPC.netid << 24) + (LAR.MtpOPC.netcluster << 16) + (LAR.MtpOPC.netmember << 8) + LAR.MtpOPC.filler;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// MtpDPC
	snmpTrapEnterprise[8] = 7;        // 
	valEvent.syntax = SNMP_SYNTAX_UNSIGNED32;
	valEvent.value.uNumber = (LAR.MtpDPC.netid << 24) + (LAR.MtpDPC.netcluster << 16) + (LAR.MtpDPC.netmember << 8) + LAR.MtpDPC.filler;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);
  }

  //-----------------------------------------------------------------------------------------------------------------------------------------------------
  //-----------------------------------------------------------------------------------------------------------------------------------------------------

  void TeknoSnmpTrap_ILM(unsigned long EventID, int LinkID, unsigned int ProcessorID,  unsigned int PortID, unsigned long Direction, unsigned int  MessageType, char TextBuffer[255], int TextLength )
  {
	// Event ID
	snmpTrapEnterprise[8] = 2;
	valEvent.syntax =SNMP_SYNTAX_INT32;
	valEvent.value.uNumber = EventID;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// SSG ID, 8 octets - set to NULL
	snmpTrapEnterprise[8] = 3;
	for (int i=0; i<8; i++) ContextBuffer[i] = NULL;
	valEvent.syntax = SNMP_SYNTAX_OCTETS;
	valEvent.value.string.len = 8;
	valEvent.value.string.ptr = &ContextBuffer[0];
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Adjucnt device ID
	snmpTrapEnterprise[8] = 4;
	valEvent.syntax = SNMP_SYNTAX_INT32;
	valEvent.value.uNumber = 0;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Version - fixed at 1
	snmpTrapEnterprise[8] = 5;
	ContextBuffer[0] = '1';	ContextBuffer[1] = NULL;
	valEvent.syntax = SNMP_SYNTAX_OCTETS;
	valEvent.value.string.len = 1;
	valEvent.value.string.ptr = &ContextBuffer[0];
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// SSG Class - fixed at 1
	snmpTrapEnterprise[8] = 6;
	ContextBuffer[0] = '1';	ContextBuffer[1] = NULL;
	valEvent.syntax = SNMP_SYNTAX_OCTETS;
	valEvent.value.string.len = 1;
	valEvent.value.string.ptr = &ContextBuffer[0];
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Adjunct Device ID 
	snmpTrapEnterprise[8] = 7;
	ContextBuffer[0] = '0';	ContextBuffer[1] = NULL;
	valEvent.syntax = SNMP_SYNTAX_OCTETS;
	valEvent.value.string.len = 1;
	valEvent.value.string.ptr = &ContextBuffer[0];
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Link ID
	snmpTrapEnterprise[8] = 8;
	valEvent.syntax =SNMP_SYNTAX_INT32;
	valEvent.value.uNumber = LinkID;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Processor ID
	snmpTrapEnterprise[8] = 9;
	valEvent.syntax =SNMP_SYNTAX_INT32;
	valEvent.value.uNumber = ProcessorID;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Port ID
	snmpTrapEnterprise[8] = 10;
	valEvent.syntax =SNMP_SYNTAX_INT32;
	valEvent.value.uNumber = PortID;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Direction - fixed at 0
	snmpTrapEnterprise[8] = 11;
	valEvent.syntax =SNMP_SYNTAX_INT32;
	valEvent.value.uNumber = 0;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Message Type
	snmpTrapEnterprise[8] = 12;
	valEvent.syntax =SNMP_SYNTAX_INT32;
	valEvent.value.uNumber = MessageType;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	// Alarm string
	snmpTrapEnterprise[8] = 13;
	valEvent.value.string.len = TextLength;
	valEvent.value.string.ptr = (unsigned char*)&TextBuffer[0];
	valEvent.syntax = SNMP_SYNTAX_OCTETS;
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);
  }


// Called from TeknoSnmp.cs  
  int trap::sendTrap(char* data, unsigned long EventID, int LinkID, unsigned int ProcessorID,  unsigned int PortID, unsigned long Direction, unsigned int  MessageType, char TextBuffer[255], int TextLength )
  {
	lStat = SnmpStartup(&lStat, &lStat, &lStat, &lStat, &lStat);
	if (lStat == SNMPAPI_FAILURE)
		return -1;
		
	hSession = SnmpCreateSession(NULL, 0, cB, NULL);
	if (hSession == SNMPAPI_FAILURE)
		return -1;

	lStat = SnmpSetTranslateMode(SNMPAPI_UNTRANSLATED_V2);
	hDst = SnmpStrToEntity(hSession, trapTargetIP);
	lStat = SnmpSetPort(hDst, snmpSendPort);

	int length = sprintf_s( (char*)ContextBuffer,sizeof(ContextBuffer), Community) ;
	dContext.ptr = &ContextBuffer[0];
	dContext.len = length;
	hContext = SnmpStrToContext(hSession, &dContext);
	hVbl = SnmpCreateVbl(hSession, NULL, NULL);

	valSysUpTime.syntax = SNMP_SYNTAX_TIMETICKS;
	valSysUpTime.value.uNumber = GetTickCount() / 10;
	lStat = SnmpSetVb(hVbl, 0, &dSysUpTimeName, &valSysUpTime);

	valTrap.syntax = SNMP_SYNTAX_OID;
	valTrap.value.oid.len = 8;
	valTrap.value.oid.ptr = trapValue;
	lStat = SnmpSetVb(hVbl, 0, &dTrapName, &valTrap);

	/*
	valEnterprise.syntax = SNMP_SYNTAX_OID;
	valEnterprise.value.oid.len = 7;
	valEnterprise.value.oid.ptr = enterpriseValue;
	lStat = SnmpSetVb(hVbl, 0, &dEnterpriseName, &valEnterprise);
	*/

	// TimeStamp
	snmpTrapEnterprise[8] = 1;
	valEvent.syntax =SNMP_SYNTAX_TIMETICKS;
	valEvent.value.uNumber = (long)time (NULL);
	lStat = SnmpSetVb(hVbl, 0, &dOID, &valEvent);

	if (EventID == 9)
		TeknoSnmpTrap_Looping(EventID, LinkID, ProcessorID, PortID, Direction, MessageType, TextBuffer, TextLength );
	else
		TeknoSnmpTrap_ILM(EventID, LinkID, ProcessorID, PortID, Direction, MessageType, TextBuffer, TextLength );

	//lStat = SnmpCountVbl(hVbl);  // count of vb - not needed

	hPdu = SnmpCreatePdu(hSession, SNMP_PDU_TRAP, 1, 0, 0, hVbl);
	lStat = SnmpSetPduData(hPdu, NULL, &id, NULL, NULL, NULL);
	lStat = SnmpSendMsg(hSession, NULL, hDst, hContext, hPdu);
	if (lStat != SNMPAPI_SUCCESS)
	{
		//SNMPAPI_STATUS err = SnmpGetLastError(hSession);
		SnmpReturnError = -1;
	}

	// Cleanup
	if (hContext != SNMPAPI_FAILURE)
	{
		lStat = SnmpFreeContext(hContext);
		hContext = SNMPAPI_FAILURE;
	}
	if (hDst != SNMPAPI_FAILURE)
	{
		lStat = SnmpFreeEntity(hDst);
		hDst = SNMPAPI_FAILURE;
	}
	if (hPdu != SNMPAPI_FAILURE)
	{
		lStat = SnmpFreePdu(hPdu);
		hPdu = SNMPAPI_FAILURE;
	}
	if (hVbl != SNMPAPI_FAILURE)
	{
		lStat = SnmpFreeVbl(hVbl);
		hVbl = SNMPAPI_FAILURE;
	}
	if (hSession != SNMPAPI_FAILURE)
	{
		lStat = SnmpClose(hSession);
		hSession = SNMPAPI_FAILURE;
	}
	lStat = SnmpCleanup();

	return(SnmpReturnError);
  }

}