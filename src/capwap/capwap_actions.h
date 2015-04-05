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

#ifndef __CAPWAP_ACTIONS_H
#define __CAPWAP_ACTIONS_H


#include "capwap.h"
#include "capwap_items.h"


#define CW_ACTION_IN_LOCATION_DATA 	\
	CW_ELEM_LOCATION_DATA, 		/* Element ID*/			\
	cw_in_generic, 0,		/* start/end callback */	\
	CW_ITEMTYPE_STR, 		/* Type of element */		\
	CW_ITEM_LOCATION_DATA,		/* ID to use store */		\
	1, 1024				/* min/max length */


#define CW_ACTION_IN_WTP_NAME	 	\
	CW_ELEM_WTP_NAME, 		/* Element ID*/			\
	cw_in_generic, 0,		/* start/end callback */	\
	CW_ITEMTYPE_STR, 		/* Type of element */		\
	CW_ITEM_WTP_NAME,		/* ID to use store */		\
	1, 1024				/* min/max length */

#define CW_ACTION_IN_SESSION_ID	 	\
	CW_ELEM_SESSION_ID, 		/* Element ID*/			\
	cw_in_generic, 0,		/* start/end callback */	\
	CW_ITEMTYPE_BSTR, 		/* Type of element */		\
	CW_ITEM_SESSION_ID,		/* ID to use store */		\
	16, 16				/* min/max length */

#define CW_ACTION_IN_WTP_FRAME_TUNNEL_MODE	 	\
	CW_ELEM_WTP_FRAME_TUNNEL_MODE,	/* Element ID*/			\
	cw_in_generic, 0,		/* start/end callback */	\
	CW_ITEMTYPE_BYTE, 		/* Type of element */		\
	CW_ITEM_WTP_FRAME_TUNNEL_MODE,	/* ID to use store */		\
	1, 1				/* min/max length */


#define CW_ACTION_IN_WTP_MAC_TYPE	 	\
	CW_ELEM_WTP_MAC_TYPE,		/* Element ID*/			\
	cw_in_generic, 0,		/* start/end callback */	\
	CW_ITEMTYPE_BYTE, 		/* Type of element */		\
	CW_ITEM_WTP_MAC_TYPE,		/* ID to use store */		\
	1, 1				/* min/max length */

#define CW_ACTION_IN_VENDOR_SPECIFIC_PAYLOAD	\
	CW_ELEM_VENDOR_SPECIFIC_PAYLOAD,	/* Element ID */	\
	cw_in_vendor_specific_payload, 0	/* start/end callback*/	\


#define CW_ACTION_IN_WTP_BOARD_DATA	\
	CW_ELEM_WTP_BOARD_DATA,		/* Element ID */		\
	cw_in_wtp_board_data, 0		/* start/end callback */	\

#define CW_ACTION_IN_WTP_DESCRIPTOR	\
	CW_ELEM_WTP_DESCRIPTOR,		/* Element ID */		\
	cw_in_wtp_descriptor, 0		/* start/end callback */	\
	

#endif
