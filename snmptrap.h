#include <WinSnmp.h>

class trap {
	private:
	char			TargetIp[15];
	char			TargetCommuity[100];
	unsigned int	TargetPort;
	unsigned int	snmpSendPort;	 // 162 is default
	char			trapTargetIP[15];
	char			Community[100];
	int				SnmpReturnError;					// -1 failed, 1 success
	unsigned char	ContextBuffer[300];
	
	HSNMP_SESSION hSession;
	HSNMP_ENTITY hDst;
	HSNMP_VBL hVbl;
	HSNMP_PDU hPdu;
	HSNMP_CONTEXT hContext;

	SNMPAPI_CALLBACK cB;

	smiOCTETS dContext;					
	smiINT32  id;
	smiUINT32 lStat;

	const smiUINT32 sysUpTime[9];
	const smiUINT32 snmpTrapOid[9]  = {1,3,6,1,4,1,36872,1,0};
  smiUINT32 trapValue[9]          = {1,3,6,1,4,1,36872,1,0};
	smiUINT32 snmpTrapEnterprise[9] = {1,3,6,1,4,1,36872,1,0};

	smiOID dSysUpTimeName;
	smiOID dTrapName;
	smiOID dEnterpriseName;

	smiVALUE valSysUpTime;
	smiVALUE valTrap;

	void init();

  public:
  trap(char* data);
	trap(char* data, char TargetIp[15], char TargetCommunity[100], unsigned int	TargetPort,	unsigned int snmpSendPort, char trapTargetIP[15], char Community[100], int SnmpReturnError, unsigned char	ContextBuffer[300]);
	int sendTrap(unsigned long EventID, int LinkID, unsigned int ProcessorID,  unsigned int PortID, unsigned long Direction, unsigned int  MessageType, char TextBuffer[255], int TextLength );

};