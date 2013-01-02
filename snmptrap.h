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
	
	typedef struct pdu {
	  char signature[6];
	  char eventType[2];
	  char teknoID[6];
	  char linkSet[18];
	  char linkQual[56];
	  char origin[18];
	  char destin[18];
	  char threshold[4];
	  char occupancy[4];
	  char direction[1];
	  char padding[27];
	} pdu;

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
	smiOID	dOID;

	smiVALUE valSysUpTime;
	smiVALUE valTrap;
	smiVALUE valEvent;

	void init();
	void TeknoSnmpTrap_Looping(unsigned long EventID, int LinkID, unsigned int ProcessorID,  unsigned int PortID, unsigned long Direction, unsigned int  MessageType, char TextBuffer[255], int TextLength);
	void TeknoSnmpTrap_ILM(unsigned long EventID, int LinkID, unsigned int ProcessorID,  unsigned int PortID, unsigned long Direction, unsigned int  MessageType, char TextBuffer[255], int TextLength);
	void pduPackAdmin(char *data);
  public:
    trap();
	trap(char TargetIp[15], char TargetCommunity[100], unsigned int	TargetPort,	unsigned int snmpSendPort, char trapTargetIP[15], char Community[100], int SnmpReturnError, char TextBuffer[255], unsigned char ContextBuffer[300]);
	int sendTrap(char* data, unsigned long EventID, int LinkID, unsigned int ProcessorID,  unsigned int PortID, unsigned long Direction, unsigned int  MessageType, char TextBuffer[255], int TextLength);
	int sendTrap(char* data);
};