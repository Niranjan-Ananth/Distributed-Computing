/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "convert.h"

my_result *
convert_hex_1_svc(int *argp, struct svc_req *rqstp)
{
	static my_result  result;

	int n = *argp;
	static char buffer[255];
	snprintf(buffer, 255, "%x", n);
	result.data = buffer;
	printf("Hexadecimal: %s\n", buffer);
	return &result;
}

my_result *
convert_oct_1_svc(int *argp, struct svc_req *rqstp)
{
	static my_result  result;

	int n = *argp;
	static char buffer[255];
	snprintf(buffer, 255, "%o", n);
	result.data = buffer;
	printf("Octal: %s\n\n", buffer);
	return &result;
}
