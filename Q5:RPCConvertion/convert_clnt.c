/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "convert.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

my_result *
convert_hex_1(int *argp, CLIENT *clnt)
{
	static my_result clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, convert_hex,
		(xdrproc_t) xdr_int, (caddr_t) argp,
		(xdrproc_t) xdr_my_result, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

my_result *
convert_oct_1(int *argp, CLIENT *clnt)
{
	static my_result clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, convert_oct,
		(xdrproc_t) xdr_int, (caddr_t) argp,
		(xdrproc_t) xdr_my_result, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
