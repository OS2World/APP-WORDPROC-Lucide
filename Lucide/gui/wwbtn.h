#ifndef __WWBTN_H
#define __WWBTN_H

/*
 *  wwbtn interface.
 *  by Eugene Romanenko
 *
 *  This code is in the public domain and has no copyright.
 */


#define UBTNTYPE_RADIOBUTTON    1
#define UBTNTYPE_CHECKBOX       2

#ifdef __cplusplus
extern "C" {
#endif

void UButtonJob( HWND owner, MPARAM mp1, MPARAM mp2, 
                 int buttonType, PUSHORT group );

void toWordWrapLabel( HWND hwnd );

#ifdef __cplusplus
}
#endif

#endif // __WWBTN_H
