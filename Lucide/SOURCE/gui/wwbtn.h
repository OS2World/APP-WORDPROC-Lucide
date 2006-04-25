#ifndef __WWBTN_H
#define __WWBTN_H

/*
 *
 *  Copyrights? Public domain, nah!
 *
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
