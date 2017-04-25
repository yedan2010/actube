
#include "cw.h"
#include "capwap_items.h"

#include "dbg.h"
#include "log.h"


int cw_out_generic(struct conn *conn, struct cw_action_out *a, uint8_t * dst)	
{


	/* Get the item to put */
	struct mbag_item *item = NULL;
	if (a->get) {
		item = a->get(conn, a);
	}


	/* Size for msg elem header depends on 
	   vendor specific payload */
	int start = a->vendor_id ? 10 : 4;


	int len;
	if (!item) {
		const char *vendor="";
		if ( a->vendor_id ) {
			vendor=cw_strvendor(a->vendor_id);
		}
		if (a->mand) {
			cw_log(LOG_ERR,
			       "Can't put mandatory element %s %d - (%s) into %s. No value for '%s' found.",
				vendor,
			       a->elem_id, cw_strelemp(conn->actions, a->elem_id)
			       , cw_strmsg(a->msg_id)
			       , a->item_id
			    );
		}
		else{
			cw_dbg(DBG_WARN,"No output for element %s%d -(%s) in %s. Item %s not found.",
				vendor,
			       a->elem_id, cw_strelemp(conn->actions, a->elem_id)
			       , cw_strmsg(a->msg_id),a->item_id);

		}
		return 0;
	} else {
		len = cw_put_mbag_item(dst + start, item);
	}


	if (a->vendor_id)
		return len + cw_put_elem_vendor_hdr(dst, a->vendor_id, a->elem_id, len);

	return len + cw_put_elem_hdr(dst, a->elem_id, len);
}




