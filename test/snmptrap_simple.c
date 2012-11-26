//#include <cstdlib>
//#include <iostream>
//#include <boost/bind.hpp>
//#include <boost/asio.hpp>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "snmptrap_simple.h"

//using boost::asio::ip::tcp;

int main (int argc, char **argv) {
  oid             objid_enterprise[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1 };
  oid             objid_sysdescr[] = { 1, 3, 6, 1, 2, 1, 1, 1, 0 };
  oid             objid_sysuptime[] = { 1, 3, 6, 1, 2, 1, 1, 3, 0 };
  oid             objid_snmptrap[] = { 1, 3, 6, 1, 6, 3, 1, 1, 4, 1, 0 };
//  int             inform = 0;

  netsnmp_session session, *ss;
  netsnmp_pdu    *pdu, *response;
  oid             name[MAX_OID_LEN];
  size_t          name_length;
  int             arg;
  int             status;
  char           *trap = NULL;
  char           *prognam;
  int             exitval = 0;

  //session.version     = 2;
  session.version       = SNMP_VERSION_1;
  session.retries       = 2;
  char address[]        = "127.0.0.1";
  char *ptrAddress      = address;
  session.peername      = ptrAddress;
  u_char comm[]         = "public";
  const u_char *community = comm;
  session.community     = community;
  session.community_len = strlen(session.community);

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
    snmp_perror("ack");
    snmp_sess_perror("snmptrap", &session);
    snmp_log(LOG_DEBUG, "Session did not open\n");
    exit(2);
  }
  snmp_log(LOG_DEBUG, "DEBUG OUTPUT");
  // create the PDU
  //pdu = snmp_pdu_create(1);
  pdu = snmp_pdu_create(SNMP_MSG_TRAP);
  if ( !pdu ) {
      fprintf(stderr, "Failed to create trap PDU\n");
      SOCK_CLEANUP;
      exit(1);
  }

  // add variables to the PDU
/*
  snmp_add_var (pdu, name, name_length, argv[arg - 2][0],
    argv[arg - 1]) != 0) {
*/
  // int snmp_add_var (netsnmp_pdu *pdu, const oid *name, 
  // size_t name_length, char type, const char *value)
  char *value;
  *value = '42';
  if(snmp_add_var (pdu, name, name_length, 'i', value)){
    //void snmp_perror(const char *prog_string)
    snmp_perror("add variable");
    SOCK_CLEANUP;
    exit(1);
  };

  send_trap_to_sess (&session, pdu);
/*
  status = snmp_send(ss, pdu) == 0;
  if (status) {
    snmp_sess_perror(inform ? "snmpinform" : "snmptrap", ss);
  }
*/
  return 0;
}
