#ifndef __CISCO_H
#define __CISCO_H

#include "cw/conn.h"
#include "cw/action.h"

extern int cisco_out_ap_timesync(struct conn *conn, struct cw_action_out *a,
				 uint8_t * dst);
extern int cisco_in_wtp_descriptor(struct conn *conn, struct cw_action_in *a,
				   uint8_t * data, int len, struct sockaddr *from);
extern int cisco_out_ac_descriptor(struct conn *conn, struct cw_action_out *a,
				   uint8_t * dst);
extern int cisco_out_wtp_descriptor(struct conn *conn, struct cw_action_out *a,
				    uint8_t * dst);
extern int cisco_out_board_data_options(struct conn *conn, struct cw_action_out *a,
				    uint8_t * dst);



extern int cisco_in_ac_descriptor(struct conn *conn, struct cw_action_in *a,
				  uint8_t * data, int len, struct sockaddr *from);

extern int cisco_in_radio_administrative_state(struct conn *conn,
						   struct cw_action_in *a, uint8_t * data,
						   int len, struct sockaddr *from);
int cisco_in_spam_vendor_specific(struct conn *conn, struct cw_action_in *a, uint8_t * data, int len,
		  struct sockaddr *from);

int cisco_in_telnet_ssh(struct conn *conn, struct cw_action_in *a, uint8_t * data, int len,
		  struct sockaddr *from);

int cisco_out_telnet_ssh(struct conn *conn,struct cw_action_out * a,uint8_t *dst);

int cisco_out_radio_administrative_states(struct conn *conn, struct cw_action_out *a, uint8_t * dst);

int cisco80211_in_mac_operation(struct conn *conn, struct cw_action_in *a, uint8_t * data,
		                         int len, struct sockaddr *from);

int cisco80211_in_wtp_radio_configuration(struct conn *conn, struct cw_action_in *a, uint8_t * data,
			 int len, struct sockaddr *from);
int cisco80211_out_wtp_radio_configuration(struct conn *conn, struct cw_action_out *a, uint8_t * dst);

int cisco_out_manager_ip_addr(struct conn *conn,struct cw_action_out * a,uint8_t *dst) ;
int cisco_out_ac_ipv4_list(struct conn *conn, struct cw_action_out *a, uint8_t * dst);

int cisco_in_add_wlan(struct conn *conn, struct cw_action_in *a, uint8_t * data, int len,
		  struct sockaddr *from);

int cisco_out_wtp_administrative_state(struct conn *conn, struct cw_action_out *a, uint8_t * dst);
int cisco_out_wtp_operational_state(struct conn *conn, struct cw_action_out *a, uint8_t * dst);
int cisco_out_radio_operational_state(struct conn *conn, struct cw_action_out *a, uint8_t * dst);
int cisco_in_radio_operational_state(struct conn *conn, struct cw_action_in *a, uint8_t * data,
			int len, struct sockaddr *from);

#endif
