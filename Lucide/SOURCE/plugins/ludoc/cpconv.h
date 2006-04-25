#ifndef __cpconv_h
#define __cpconv_h

#ifndef APIENTRY
#define APIENTRY _System
#endif

#ifdef __cplusplus
extern "C" {
#endif

long APIENTRY cnvUniToUTF8( const char **in, unsigned *in_left,
                            char **out, unsigned *out_left );
long APIENTRY cnvUniBEToUTF8( const char **in, unsigned *in_left,
                              char **out, unsigned *out_left );
long APIENTRY cnvUTF8ToUni( const char **in, unsigned *in_left,
                            char **out, unsigned *out_left );
long APIENTRY cnvUTF8ToSys( const char **in, unsigned *in_left,
                            char **out, unsigned *out_left );
long APIENTRY cnvUniBEToSys( const char **in, unsigned *in_left,
                             char **out, unsigned *out_left );
long APIENTRY cnvUniToSys( const char **in, unsigned *in_left,
                           char **out, unsigned *out_left );
long APIENTRY cnvSysToUCS2( const char **in, unsigned *in_left,
                            char **out, unsigned *out_left );
                            
#ifdef __cplusplus
}
#endif

#endif // __cpconv_h
