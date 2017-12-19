struct my_result{string data<255>;};
program CONVERT{
	version CONVERT_1{
		my_result convert_hex(int) = 1;
		my_result convert_oct(int) = 2;
	}=1;
}=0x2fffffff;
