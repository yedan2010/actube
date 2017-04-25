/*
    This file is part of libcapwap.

    libcapwap is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libcapwap is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "cw/capwap.h"
#include "cw/cipwap.h"

#include "cw/action.h"
#include "cw/capwap_items.h"
#include "cw/strheap.h"
#include "cw/radio.h"
#include "cw/capwap_cisco.h"
#include "cw/capwap80211.h"
#include "cw/capwap80211_items.h"

#include "cw/lwapp_cisco.h"
#include "cw/cw_80211.h"

#include "include/capwap_actions.h"

#include "mod_cisco.h"
#include "cisco.h"

#include "cisco_items.h"

#include "include/cipwap_items.h"


static cw_action_in_t actions_in[] = {


	/* --------------------------------------------------------
	 * Discovery Resquest 
	 */

	/* Message Discovery Request */
	{
		.capwap_state = CW_STATE_DISCOVERY,
		.msg_id = CW_MSG_DISCOVERY_REQUEST,
		.end = cw_in_check_disc_req
	}
	,

	/* Element WTP Descriptor */
	{
		.capwap_state = CW_STATE_DISCOVERY, 
		.msg_id = CW_MSG_DISCOVERY_REQUEST, 
		.elem_id = CW_ELEM_WTP_DESCRIPTOR,
	 	.start = cisco_in_wtp_descriptor, 
		.item_id = "wtp_descriptor", 
		.mand = 1, 
	}
	,

	/* Element Cisco RAD Name */
	{
		.capwap_state = CW_STATE_DISCOVERY, 
		.msg_id = CW_MSG_DISCOVERY_REQUEST, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_RAD_NAME, 
		.start=cw_in_generic2, 
		.item_id = "wtp_name", 
		.min_len=1,
		.max_len=512,
		.mand=1
	}
	,





	/* --------------------------------------------------------
	 * Discovery Resquest 
	 */

	/* WTP Descriptor - Join Request */
	{
		.capwap_state = CW_STATE_JOIN, 
		.msg_id = CW_MSG_JOIN_REQUEST, 
		.elem_id = CW_ELEM_WTP_DESCRIPTOR,
	 	.start = cisco_in_wtp_descriptor, 
		.item_id = "wtp_descriptor", 
		.mand = 1, 
	}
	,

	/* Session ID - Join Request */
	{
		/* Cisco uses 4 byte session ids */
		.capwap_state = CW_STATE_JOIN, 
		.msg_id = CW_MSG_JOIN_REQUEST, 
		.elem_id = CW_ELEM_SESSION_ID,
	 	.start = capwap_in_session_id, 
		.item_id = CW_ITEM_SESSION_ID, 
		.mand = 1, 
		.min_len = 4, 
		.max_len = 16
	}
	,

	/* Local IPv4 Address - Join Request */
	{
		.capwap_state = CW_STATE_JOIN, 
		.msg_id = CW_MSG_JOIN_REQUEST, 
		.elem_id = CW_ELEM_WTP_IPV4_IP_ADDRESS,
		.item_id = CW_ITEM_CAPWAP_LOCAL_IP_ADDRESS,
	 	.start = cw_in_capwap_local_ipv4_address, 
		.mand = 1,
		.min_len = 4, 
		.max_len = 4
	}
	,

	/* Local IPv6 Address - Join Request */
	{
		.capwap_state = CW_STATE_JOIN, 
		.msg_id = CW_MSG_JOIN_REQUEST, 
		.elem_id = CW_ELEM_WTP_IPV6_IP_ADDRESS,
		.item_id = CW_ITEM_CAPWAP_LOCAL_IP_ADDRESS,
	 	.start = cw_in_capwap_local_ipv4_address, 
		.mand = 1,
		.min_len = 16, 
		.max_len = 16
	}
	,

	/* ECN Support - Join Request */
	{
		/* Cisco (using draft 7) does nothing know 
		 * about ECN support, so make it non-mandatory */
		.capwap_state = CW_STATE_JOIN, 
		.msg_id = CW_MSG_JOIN_REQUEST, 
		.elem_id = CW_ELEM_ECN_SUPPORT,
		.item_id = CW_ITEM_ECN_SUPPORT,
	 	.start = cw_in_generic2, 
		.mand = 0, 
		.min_len = 1, 
		.max_len = 1
	}
	,


	/* --------------------------------------------------------
	 * Configuration Status Request 
	 */

			

	/* AC Name - Config Status Request */	
	{
		/* We have to deal with zero-length strings */
		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST,
		.elem_id = CW_ELEM_AC_NAME,
		.item_id = CW_ITEM_AC_NAME,
		.start = cw_in_generic2,
		.min_len = 0,
		.max_len = 512,
		.mand = 1

	}
	,

		

	{
		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_WTP_RADIO_CFG, 
		.start=cisco80211_in_wtp_radio_configuration, 
		.item_id = "cisco_radio_cfg", 
	}
	,


	/* LED State Config */	
	{
		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_AP_LED_STATE_CONFIG, 
		.item_id = CISCO_ITEM_AP_LED_STATE_CONFIG,
		.start = cw_in_generic2

	}
	,

	/* LED Flash Config */	
	{
		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_AP_LED_FLASH_CONFIG, 
		.item_id = CISCO_ITEM_AP_LED_FLASH_CONFIG,
		.start = cw_in_generic2

	}
	,


	
	{
		/* This is Cisco's Vendor specific encapsulation
		 * of LWAPP elements */

		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST,
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_SPAM_VENDOR_SPECIFIC,
		.start = lw_in_vendor_specific,

	}
	,

	/* LWAPP Vendor spec Messages */


	/* Telent SSH */
	{

		.proto = CW_ACTION_PROTO_LWAPP,
		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST,
		.vendor_id = LW_VENDOR_ID_CISCO,
		.elem_id = LW_CISCO_TELNET_SSH,
		.start = cisco_in_telnet_ssh
	}

	,	

	/* AP Mode and Type */
	{

		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST,
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_AP_MODE_AND_TYPE,
		.item_id = CISCO_ITEM_AP_MODE_AND_TYPE,
		.start = cw_in_generic2
	}
	,

	/* Log Facility */
	{

		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST,
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_AP_LOG_FACILITY,
		.item_id = CIPWAP_ITEM_LOG_FACILITY,
		.start = cw_in_generic2
	}
	,

		


	/* Radio Operational State - Run State - Change State Event Req */
	{
		.capwap_state = CW_STATE_RUN, 
		.msg_id= CW_MSG_CHANGE_STATE_EVENT_REQUEST,
		.elem_id = CW_ELEM_RADIO_OPERATIONAL_STATE,
		.item_id = CW_RADIOITEM_OPER_STATE,
		.start = cisco_in_radio_operational_state,
		.min_len=3,
		.max_len=3,
		.mand = 0
	}
	,

	/* Radio Operational State - Configure State - Change State Event Req */
	{
		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id= CW_MSG_CHANGE_STATE_EVENT_REQUEST,
		.elem_id = CW_ELEM_RADIO_OPERATIONAL_STATE,
		.item_id = CW_RADIOITEM_OPER_STATE,
		.start = cisco_in_radio_operational_state, //operational_state,
		.min_len=3,
		.max_len=3,
		.mand = 0
	}
	,



	/* End of list */
	{0, 0}
};


static cw_action_out_t actions_out[]={

	/* --------------------------------------------------------
	 * Discovery Response 
	 */


	/* Cisco AP Timesync - Discovery Request
	 * Important to get the WTP a DTLS connection established
	 */
	{
		.msg_id = CW_MSG_DISCOVERY_RESPONSE, 
		.item_id = CW_ITEM_AC_TIMESTAMP, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id  = CW_CISCO_AP_TIMESYNC,
		.out = cisco_out_ap_timesync,
		.mand = 1
	}
	,
	/* AC Descriptor - Discovery Response */
	{
		.msg_id = CW_MSG_DISCOVERY_RESPONSE, 
		.item_id = CW_ITEM_AC_DESCRIPTOR,
		.elem_id = CW_ELEM_AC_DESCRIPTOR, 
		.out = cisco_out_ac_descriptor,
		.mand = 1
	}
	,


	/* AC Descriptor - Join Response */
	{
		.msg_id = CW_MSG_JOIN_RESPONSE, 
		.item_id = CW_ITEM_AC_DESCRIPTOR,
		.elem_id = CW_ELEM_AC_DESCRIPTOR, 
		.out = cisco_out_ac_descriptor,
		.mand = 1
	}
	,



	/* ECN Support - Join Response */
	{
		.msg_id = CW_MSG_JOIN_RESPONSE, 
		.elem_id  = CW_ELEM_ECN_SUPPORT,
		.item_id = CW_ITEM_ECN_SUPPORT
	}
	,

	/* --------------------------------------------------------
	 * Echo Response 
	 */
	/* AP Time Sync - Echo Response */
	{
		.msg_id = CW_MSG_ECHO_RESPONSE, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.item_id = CW_ITEM_AC_TIMESTAMP, 
		.elem_id  = CW_CISCO_AP_TIMESYNC,
		.out = cisco_out_ap_timesync,
		.mand = 1
	}
	,

	/* --------------------------------------------------------
	 * Configuration Status Response
	 */
	/* Manager IP Address */
	{
		.msg_id = CW_MSG_CONFIGURATION_STATUS_RESPONSE, 
		.out = cisco_out_manager_ip_addr,
		.mand = 1
	}
	,


	/* --------------------------------------------------------
	 * Configuration Update Request - Out
	 */

	{
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST, 
		.out = cisco_out_telnet_ssh,
	}
	,

	{
		/* Cisco's APs complain about msg elements of type
		  45 (WTP Name). So it ist silenced here.
		  But the method here used to silence the element
		  isn't effective. TODO: There shuld be a way to remove
		  or replace such elemenns */
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST, 
		.item_id = CW_ITEM_WTP_NAME, 
		.elem_id = CW_ELEM_WTP_NAME,
	}
	,

	/* WTP Name */
	{
		
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST, 
		.item_id = CW_ITEM_WTP_NAME, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_RAD_NAME,
		.out=cw_out_generic, 
		.get = cw_out_get_outgoing
	}
	,

	/* Radio Operational State  - OUT */
	{
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST,
		.elem_id = CW_ELEM_RADIO_OPERATIONAL_STATE,
		.item_id = CW_RADIOITEM_OPER_STATE,
	 	.out = cisco_out_radio_operational_state,
		.mand = 0
	}
	,

	/* LED State Config -  OUT */
	{
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST,
		.vendor_id = CW_VENDOR_ID_CISCO, 
		.elem_id = CW_CISCO_AP_LED_STATE_CONFIG,
		.item_id = CISCO_ITEM_AP_LED_STATE_CONFIG,
	 	.out = cw_out_generic, 
		.get = cw_out_get_outgoing,
		.mand = 0
	}
	,


	/* LED Flash Config -  OUT */
	{
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST,
		.vendor_id = CW_VENDOR_ID_CISCO, 
		.elem_id = CW_CISCO_AP_LED_FLASH_CONFIG,
		.item_id = CISCO_ITEM_AP_LED_FLASH_CONFIG,
	 	.out = cw_out_generic, 
		.get = cw_out_get_outgoing,
		.mand = 0
	}
	,

	/* AP Mode and Type -  OUT */
	{
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST,
		.vendor_id = CW_VENDOR_ID_CISCO, 
		.elem_id = CW_CISCO_AP_MODE_AND_TYPE,
		.item_id = CISCO_ITEM_AP_MODE_AND_TYPE,
	 	.out = cw_out_generic, 
		.get = cw_out_get_outgoing,
	}
	,

	
	/* Cisco WTP Admin state -  OUT */
	{
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST,
		.vendor_id = CW_VENDOR_ID_CISCO, 
//		.elem_id = CW_CISCO_AP_MODE_AND_TYPE,
		.item_id = CISCO_ITEM_WTP_ADMIN_STATE,
	 	.out = cisco_out_wtp_administrative_state, 
//		.get = cw_out_get_outgoming,
	}
	,



	{0,0}

};

static cw_action_in_t actions80211_in[] = {
	/* --------------------------------------------------------
	 * Discovery Resquest 
	 */

	/* 802.11 Radio Information - Discovery Request */
	{
		/* Cisco doe't sned this message element in discovery request,
		   so make it non-mandatory */

		.capwap_state = CW_STATE_DISCOVERY, 
		.msg_id = CW_MSG_DISCOVERY_REQUEST, 
		.elem_id = CW_ELEM80211_WTP_RADIO_INFORMATION,
		.item_id = CW_RADIOITEM80211_WTP_RADIO_INFORMATION,
	 	.start = cw_in_radio_generic, 
		.mand = 0, 
		.min_len = 5, 
		.max_len = 5
	}
	,

	/* --------------------------------------------------------
	 * Configuration Status Resquest - IN
	 */
	/* Supported Rates - Configruati Status Request */	
	{
		.capwap_state = CW_STATE_CONFIGURE, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST, 
		.elem_id = CW_CISCO_SUPPORTED_RATES,
		.item_id = CW_RADIOITEM80211_SUPPORTED_RATES,
	 	.start = cw_in_radio_generic, 
		.mand = 0, 
		.min_len = 5, 
		.max_len = 5
		
	}

	,

	/* MAC Operation - Configruation Status Request */	
	{
		.capwap_state = CW_STATE_CONFIGURE, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST, 
		.elem_id = CW_CISCO_MAC_OPERATION,
		.item_id = "mac operation",
	 	.start = cisco80211_in_mac_operation, 
		.mand = 0, 
		.min_len = 5, 
		.max_len = 5
		
	}

	,


	/*  Radio Admin State (IN) - Config Status Request */
	{
		.capwap_state = CW_STATE_CONFIGURE, 
		.msg_id = CW_MSG_CONFIGURATION_STATUS_REQUEST,
		.elem_id = CW_ELEM_RADIO_ADMINISTRATIVE_STATE,
		.item_id = CW_RADIOITEM_ADMIN_STATE,
		.start = cisco_in_radio_administrative_state,
		.mand = 1
	}
	,

		

	{0,0}


};



extern int cisco_out_capwap_up(struct conn *conn, struct cw_action_out *a, uint8_t * dst);

static cw_action_out_t actions80211_out[]={

	{
		.msg_id = CW_MSG_CONFIGURATION_UPDATE_REQUEST, 
		.vendor_id = CW_VENDOR_ID_CISCO,
		.elem_id = CW_CISCO_WTP_RADIO_CFG,
		.out = cisco80211_out_wtp_radio_configuration,
	}
	,
	{
		.msg_id = CW_MSG_CONFIGURATION_STATUS_RESPONSE, 
		.out = cisco_out_capwap_up,
	}
	,



	{0,0}
};


#include "cw/item.h"

static struct cw_itemdef _capwap_itemdefs[] = {

	{"wtp_name_cisco",CW_ITEM_NONE,MBAG_STR},

	/*	{"wtp_mac_type",CW_ITEM_NONE,MBAG_BYTE},
	{"discovery_type",CW_ITEM_NONE,MBAG_BYTE},
	{"wtp_frame_tunnel_mode",CW_ITEM_NONE,MBAG_BYTE},
*/	{CW_ITEM_NONE}

};


#include "../modload.h"

int cisco_register_actions_ac(struct cw_actiondef *def)
{

	int rc;
	rc = cw_actionlist_in_register_actions(def->in, actions_in);
	rc += cw_actionlist_out_register_actions(def->out, actions_out);

	rc += cw_strheap_register_strings(def->strmsg, capwap_strings_msg);
	rc += cw_strheap_register_strings(def->strelem, cipwap_strings_elem);

	rc += cw_itemdefheap_register(def->items, _capwap_itemdefs);
//	rc += cw_itemdefheap_register(def->radioitems, cisco_radioitemdefs);

	intavltree_add(def->wbids, 0);



	return rc;
}



int cisco_register_actions80211_ac(struct cw_actiondef *def)
{

	int rc;
	rc=0;
	rc = cw_actionlist_in_register_actions(def->in, actions80211_in);
	rc += cw_actionlist_out_register_actions(def->out, actions80211_out);
	rc += cw_itemdefheap_register(def->items, cisco_itemdefs);
	rc += cw_itemdefheap_register(def->radioitems, cisco_radioitemdefs);
	

/*	rc += cw_strheap_register_strings(def->strmsg, capwap_strings_msg);
	rc += cw_strheap_register_strings(def->strelem, cipwap_strings_elem);

	rc += cw_itemdefheap_register(def->radioitems, capwap_radioitemdefs);

	intavltree_add(def->wbids, 0);
*/


	return rc;
}


