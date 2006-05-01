#include "ddjvuapi.h"
#include <stdio.h>


int main()
{
	ddjvu_context_t  *d_context = ddjvu_context_create("Evince");;
	ddjvu_document_t *doc;

	doc = ddjvu_document_create_by_filename( d_context, "D:\\Projects\\libdjvu\\doc\\djvu2spec.djvu", TRUE );
	//doc = ddjvu_document_create( d_context, "file://../doc/djvu2spec.djvu", FALSE );	

	if (!doc) {
		printf( "ddjvu_document_create_by_filename error!\n" );
		return 0;
	}

	while (!ddjvu_document_decoding_done(doc)) {
		    ddjvu_message_wait(d_context);
		    ddjvu_message_pop(d_context);	
	}
		
    ddjvu_pageinfo_t info = { 0 };
	
    ddjvu_status_t r = DDJVU_JOB_NOTSTARTED;
	while ( r < DDJVU_JOB_OK ) {
        r = ddjvu_document_get_pageinfo( doc, 0, &info );
        ddjvu_message_wait( d_context );
        ddjvu_message_pop( d_context );	
	}
	
	printf( "OK!\n" );
	
	return 0;
}
