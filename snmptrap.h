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

	smiUINT32 sysUpTime[9];
	smiUINT32 snmpTrapOid[9];
    smiUINT32 trapValue[9];
	smiUINT32 snmpTrapEnterprise[9];

	smiOID dSysUpTimeName;
	smiOID dTrapName;
	smiOID dEnterpriseName;

	smiVALUE valSysUpTime;
	smiVALUE valTrap;
	smiVALUE valEvent;

	void init();

  public:
  trap();
	trap(char TargetIp[15], char TargetCommunity[100], unsigned int	TargetPort,	unsigned int snmpSendPort, char trapTargetIP[15], char Community[100], int SnmpReturnError, unsigned char	ContextBuffer[300]);
	int sendTrap(char* data, unsigned long EventID, int LinkID, unsigned int ProcessorID,  unsigned int PortID, unsigned long Direction, unsigned int  MessageType, char TextBuffer[255], int TextLength );

};