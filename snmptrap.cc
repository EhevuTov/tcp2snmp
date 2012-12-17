#include <iostream>
#include <string.h>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <boost/foreach.hpp>

#include "snmptrap.h"

#define BOOST_LIB_DIAGNOSTIC

#define ENTERPRISE 1, 3, 6, 1, 4, 1, 3, 1, 36872
#define SUFFIX 1, 1
#define OID_EVENT ENTERPRISE ## 1
oid             objid_event[] = { ENTERPRISE };
#define OID_TEKNOID 2
#define OID_LINKSET 3
#define OID_LINKQUALIFIER 4
#define OID_ORIGINCLLI 5
#define OID_DESTINCLLI 6
#define OID_THRESHOLD 7
#define OID_OCCUPANCY 8

oid             objid_enterprise[] = { ENTERPRISE };
oid             objid_trap1[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 1 };
oid             objid_trap2[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 2 };
oid             objid_trap3[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 3 };
oid             objid_trap4[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 4 };
oid             objid_trap5[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 5 };
oid             objid_trap6[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 6 };
oid             objid_trap7[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 7 };
oid             objid_trap8[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 8 };
oid             objid_trap9[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1, 36872, 9 };
int             inform = 0;

trap::trap(char* data) {
  //tlv tlv = new tlv(data);
  //create list of tlv values
  //tlv.list
  //BOOST_FOREACH(elem e, tlv.list){};
  netsnmp_session session, *ss;
  netsnmp_pdu    *pdu;
  oid             name[MAX_OID_LEN];
  size_t          name_length;
  int             status;
  int             exitval = 0;
  snmp_sess_init(&session);

  session.version       = SNMP_VERSION_1;
  session.retries       = 2;
  char address[]        = "192.168.1.174:162";
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
  if(snmp_add_var(pdu, objid_trap1, OID_LENGTH(objid_trap1), 'i', data+6)){
    snmp_perror("add variable1");
    snmp_perror(data+6);
    SOCK_CLEANUP;
    exit(1);
  };
  // TeknoID
  if(snmp_add_var(pdu, objid_trap2, OID_LENGTH(objid_trap2), 'i', data+8)){
    snmp_perror("add variable2");
    snmp_perror(data+8);
    SOCK_CLEANUP;
    exit(1);
  };
  // LinkSet
  if(snmp_add_var(pdu, objid_trap3, OID_LENGTH(objid_trap3), 's', data+14)){
    snmp_perror("add variable3");
    snmp_perror(data+14);
    SOCK_CLEANUP;
    exit(1);
  };
  // LinkQualifier
  if(snmp_add_var(pdu, objid_trap4, OID_LENGTH(objid_trap4), 's', data+32)){
    snmp_perror("add variable4");
    snmp_perror(data+32);
    SOCK_CLEANUP;
    exit(1);
  };
  // Originating CLLI
  if(snmp_add_var(pdu, objid_trap5, OID_LENGTH(objid_trap5), 's', data+88)){
    snmp_perror("add variable5");
    snmp_perror(data+88);
    SOCK_CLEANUP;
    exit(1);
  };
  // Destination CLLI
  if(snmp_add_var(pdu, objid_trap6, OID_LENGTH(objid_trap6), 's', data+106)){
    snmp_perror("add variable6");
    snmp_perror(data+106);
    SOCK_CLEANUP;
    exit(1);
  };
  // Threshold Percent
  if(snmp_add_var(pdu, objid_trap7, OID_LENGTH(objid_trap7), 'i', data+124)){
    snmp_perror("add variable7");
    snmp_perror(data+124);
    SOCK_CLEANUP;
    exit(1);
  };
  // Occupancy Percent
  if(snmp_add_var(pdu, objid_trap8, OID_LENGTH(objid_trap8), 'i', data+128)){
    snmp_perror("add variable8");
    snmp_perror(data+128);
    SOCK_CLEANUP;
    exit(1);
  };
  // Link Direction: 0=To, 1=From
  if(snmp_add_var(pdu, objid_trap9, OID_LENGTH(objid_trap9), 'i', data+132)){
    snmp_perror("add variable9");
    snmp_perror(data+132);
    SOCK_CLEANUP;
    exit(1);
  };

  status = snmp_send(ss, pdu) == 0;
  if (status) {
    snmp_sess_perror(inform ? "snmpinform" : "snmptrap", ss);
  }
  snmp_close(ss);
};
