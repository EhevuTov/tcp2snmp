#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#ifdef __cplusplus
extern "C" {
#endif

oid             objid_enterprise[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1 };
oid             objid_sysdescr[] = { 1, 3, 6, 1, 2, 1, 1, 1, 0 };
oid             objid_sysuptime[] = { 1, 3, 6, 1, 2, 1, 1, 3, 0 };
oid             objid_snmptrap[] = { 1, 3, 6, 1, 6, 3, 1, 1, 4, 1, 0 };
oid             objid_mytrap[] = { 1, 3, 6, 1, 6, 3, 1, 1, 34, 0 };
int             inform = 0;

/* prototypes for the example */
//void init_snmptrap_simple(void);
//SNMPAlarmCallback send_snmptrap_simple;


#ifdef __cplusplus
}
#endif

#endif /* NOTIFICATION_H */
