/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "convert.h"

bool_t
xdr_my_result (XDR *xdrs, my_result *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->data, 255))
		 return FALSE;
	return TRUE;
}
