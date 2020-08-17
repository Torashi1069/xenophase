#include <libgrf.h>
#include <stdio.h>
#include <string.h>


bool test_1_codepage()
{
	if( utf8_to_euc_kr("a") == NULL )
	{
		printf("warning: codepage conversion functionality disabled\n");
		return false;
	}

	const char* str_euckr = "\xC0\xAF\xC0\xFA\xC0\xCE\xC5\xCD\xC6\xE4\xC0\xCC\xBD\xBA";
	const char* str_utf8  = "\xEC\x9C\xA0\xEC\xA0\x80\xEC\x9D\xB8\xED\x84\xB0\xED\x8E\x98\xEC\x9D\xB4\xEC\x8A\xA4";
	const char* test_euckr_utf8 = euc_kr_to_utf8(str_euckr);
	if( test_euckr_utf8 == NULL || strcmp(test_euckr_utf8, str_utf8) != 0 )
		printf("warning: euc_kr_to_utf8 fail\n");
	const char* test_utf8_euckr = utf8_to_euc_kr(str_utf8);
	if( test_utf8_euckr == NULL || strcmp(test_utf8_euckr, str_euckr) != 0 )
		printf("warning: utf8_to_euc_kr fail\n");

	return true;
}


bool test_2_create()
{
	grf_handle h = grf_new("libgrf_test.grf");
	if( h == NULL )
	{
		printf("error: grf_new, h == NULL\n");
		return false;
	}

	grf_file_add(h, "test.txt", (void*)"omg omg omg\n", 12);
	grf_save(h);

	grf_free(h);
	return true;
}


bool test_3_load()
{
	char buf[256] = "";
	grf_handle h = grf_load("libgrf_test.grf");
	if( h == NULL )
	{
		printf("error: grf_load, h == NULL\n");
		return false;
	}

	grf_node n = grf_get_file(h, "test.txt");
	if( n == NULL )
	{
		printf("error: grf_get_file, n == NULL\n");
		grf_free(h);
		return false;
	}

	grf_file_get_contents(n, buf);
	if( strcmp(buf, "omg omg omg\n") != 0 )
	{
		printf("error: grf_file_get_contents, data doesn't match\n");
		grf_free(h);
		return false;
	}

	grf_free(h);
	return true;
}


int main(void)
{
	test_1_codepage();
	test_2_create();
	test_3_load();

	// cleanup
	remove("libgrf_test.grf");

	return 0;
}
