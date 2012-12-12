#include <iostream.h>
#include <string.h>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <boost/foreach.hpp>

#include "snmptrap.h"
//#include "elem.h"


oid             objid_enterprise[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1 };
oid             objid_sysdescr[] = { 1, 3, 6, 1, 2, 1, 1, 1, 0 };
oid             objid_sysuptime[] = { 1, 3, 6, 1, 2, 1, 1, 3, 0 };
oid             objid_snmptrap[] = { 1, 3, 6, 1, 6, 3, 1, 1, 4, 1, 0 };
oid             objid_mytrap[] = { 1, 3, 6, 1, 6, 3, 1, 1, 34, 0 };
int             inform = 0;

trap::trap(char* data) {
  //tlv tlv = new tlv(data);
  //create list of tlv values
  //tlv.list
  //BOOST_FOREACH(elem e, tlv.list){};
  netsnmp_session session, *ss;
  netsnmp_pdu    *pdu, *response;
  oid             name[MAX_OID_LEN];
  size_t          name_length;
  int             status;
  char           *trap = NULL;
  char           *prognam;
  int             exitval = 0;
  snmp_sess_init(&session);

  session.version       = SNMP_VERSION_1;
  session.retries       = 2;
  char address[]        = "localhost:162";
  char *ptrAddress      = address;
  session.peername      = ptrAddress;
  u_char comm[]         = "public";
  u_char *community     = comm;
  session.community     = community;
  //session.community_len = strlen(session.community);
  session.community_len = 6;

  // set debug tokens
  //debug_register_tokens("transport,tdomain,snmp_sess");
  debug_register_tokens("all");
  snmp_set_do_debugging(1);
  /* windows32 specific initialization (is a noop on unix) */
  SOCK_STARTUP;
  // open snmp session
  ss = snmp_open(&session);
  /*
  ss = snmp_add(&session,
    netsnmp_transport_open_client("snmptrap", session.peername),
    NULL, NULL);
  */
    if (!ss) {
    //snmp_perror("ack");
    snmp_sess_perror("snmptrap", &session);
    //snmp_log(LOG_DEBUG, "Session did not open\n");
    exit(2);
  }
  //snmp_log(LOG_DEBUG, "DEBUG OUTPUT");
  // create the PDU
  //pdu = snmp_pdu_create(1);
  pdu = snmp_pdu_create(SNMP_MSG_TRAP);
  if ( !pdu ) {
    fprintf(stderr, "Failed to create trap PDU\n");
    snmp_perror("pdu error");
    SOCK_CLEANUP;
    exit(1);
  }

  pdu->enterprise = (oid *) malloc(sizeof(objid_enterprise));
  memcpy(pdu->enterprise, objid_enterprise, sizeof(objid_enterprise));
  pdu->enterprise_length = sizeof(objid_enterprise) / sizeof(oid);

  /*
  pdu->specific_type = (oid *) malloc(sizeof(objid_snmptrap));
  memcpy(pdu->specific_type, objid_snmptrap, sizeof(objid_snmptrap));
  */
  pdu->specific_type = 8;

  /*
  pdu->trap_type = (oid *) malloc(sizeof(objid_snmptrap));
  memcpy(pdu->trap_type, objid_snmptrap, sizeof(objid_snmptrap));
  //pdu->enterprise_length = sizeof(objid_enterprise) / sizeof(oid);
  */
  pdu->trap_type = 124;

  // add variables to the PDU
  // int snmp_add_var (netsnmp_pdu *pdu, const oid *name, 
  // size_t name_length, char type, const char *value)

  // make singature string compare
  // Event Type: 0=Clear, 1=Minor, 2=Major, 3=NoData
  if(snmp_add_var(pdu, objid_mytrap, OID_LENGTH(objid_mytrap), 'i', data+6)){
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };
  // TeknoID
  if(snmp_add_var(pdu, objid_mytrap, OID_LENGTH(objid_mytrap), 'i', data+8)){
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };
  // LinkSet
  if(snmp_add_var(pdu, objid_mytrap, OID_LENGTH(objid_mytrap), 's', data+14)){
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };
  // LinkQualifier
  if(snmp_add_var(pdu, objid_mytrap, OID_LENGTH(objid_mytrap), 's', data+32)){
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };
  // Originating CLLI
  if(snmp_add_var(pdu, objid_mytrap, OID_LENGTH(objid_mytrap), 's', data+88)){
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };
  // Destination CLLI
  if(snmp_add_var(pdu, objid_mytrap, OID_LENGTH(objid_mytrap), 's', data+106)){
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };
  // Threshold Percent
  if(snmp_add_var(pdu, objid_mytrap, OID_LENGTH(objid_mytrap), 'i', data+124)){
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };
  // Occupancy Percent
  if(snmp_add_var(pdu, objid_mytrap, OID_LENGTH(objid_mytrap), 'i', data+128)){
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };

  status = snmp_send(ss, pdu) == 0;
  if (status) {
    snmp_sess_perror(inform ? "snmpinform" : "snmptrap", ss);
  }
  snmp_close(ss);
};
