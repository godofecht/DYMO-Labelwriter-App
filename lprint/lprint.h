//
// Header file for LPrint, a Label Printer Application
//
// Copyright © 2019-2023 by Michael R Sweet.
//
// Licensed under Apache License v2.0.  See the file "LICENSE" for more
// information.
//

#ifndef LPRINT_H
#  define LPRINT_H

//
// Include necessary headers...
//

#  include "config.h"
#  include <pappl/pappl.h>
#  include <math.h>


//
// Debug macro...
//

#  ifdef DEBUG
#    define LPRINT_DEBUG(...) fprintf(stderr, __VA_ARGS__)
#  else
#    define LPRINT_DEBUG(...)
#  endif // DEBUG


//
// Function annotations...
//

#  if defined(__GNUC__) || defined(__has_extension)
#    define LPRINT_FORMAT(a,b)	__attribute__ ((__format__(__printf__, a,b)))
#    define LPRINT_NONNULL(...)	__attribute__ ((nonnull(__VA_ARGS__)))
#    define LPRINT_NORETURN	__attribute__ ((noreturn))
#  else
#    define LPRINT_FORMAT(a,b)
#    define LPRINT_NONNULL(...)
#    define LPRINT_NORETURN
#  endif // __GNUC__ || __has_extension


//
// The CUPS API is changed in CUPS v3...
//

#  if CUPS_VERSION_MAJOR < 3
#    define CUPS_ENCODING_ISO8859_1	CUPS_ISO8859_1
#    define CUPS_ENCODING_JIS_X0213	CUPS_JIS_X0213
#    define cups_len_t int
#    define cups_page_header_t cups_page_header2_t
#    define cupsArrayNew cupsArrayNew3
#    define cupsArrayGetCount cupsArrayCount
#    define cupsArrayGetElement(a,n) cupsArrayIndex(a,(int)n)
#    define cupsArrayGetFirst cupsArrayFirst
#    define cupsArrayGetLast cupsArrayLast
#    define cupsArrayGetNext cupsArrayNext
#    define cupsArrayGetPrev cupsArrayPrev
#    define cupsGetUser cupsUser
#    define cupsLangGetName(lang)	lang->language
#    define cupsRasterReadHeader cupsRasterReadHeader2
#    define cupsRasterWriteHeader cupsRasterWriteHeader2
#    define cupsTempFd(prefix,suffix,buffer,bufsize) cupsTempFd(buffer,bufsize)
#    define httpAddrConnect httpAddrConnect2
#    define httpAddrGetFamily httpAddrFamily
#    define httpAddrGetLength httpAddrLength
#    define httpAddrGetString httpAddrString
#    define httpAddrIsLocalhost httpAddrLocalhost
#    define httpConnect httpConnect2
#    define httpDecode64(out,outlen,in,end) httpDecode64_2(out,outlen,in)
#    define httpEncode64(out,outlen,in,inlen,url) httpEncode64_2(out,outlen,in,inlen)
#    define httpGetDateString httpGetDateString2
#    define httpRead httpRead2
#    define httpReconnect httpReconnect2
#    define httpSetEncryption(http,e) (httpEncryption(http,e)>=0)
#    define httpStatusString httpStatus
#    define httpWrite httpWrite2
#    define httpWriteResponse(http,code) (httpWriteResponse(http,code) == 0)
#    define ippGetFirstAttribute ippFirstAttribute
#    define ippGetNextAttribute ippNextAttribute
#    define IPP_NUM_CAST (int)
typedef cups_array_func_t cups_array_cb_t;
typedef cups_acopy_func_t cups_acopy_cb_t;
typedef cups_afree_func_t cups_afree_cb_t;
typedef cups_raster_iocb_t cups_raster_cb_t;
typedef ipp_copycb_t ipp_copy_cb_t;
#    if CUPS_VERSION_MINOR < 3
#      define HTTP_STATUS_FOUND (http_status_t)302
#    endif // CUPS_VERSION_MINOR < 3
#  else
#    define cups_len_t size_t
#    define cups_utf8_t char
#    define IPP_NUM_CAST (size_t)
#  endif // CUPS_VERSION_MAJOR < 3


//
// Constants...
//

#  define LPRINT_TESTPAGE_MIMETYPE	"application/vnd.lprint-test"
#  define LPRINT_TESTPAGE_HEADER	"T*E*S*T*P*A*G*E*"

#  define LPRINT_EPL2_MIMETYPE		"application/vnd.eltron-epl"
#  define LPRINT_ZPL_MIMETYPE		"application/vnd.zebra-zpl"


//
// Types...
//

enum
{
  LPRINT_REPEAT_H = 0x01,
  LPRINT_REPEAT_V = 0x02,
  LPRINT_REPEAT_ALL = 0x03
};

typedef struct lprint_pixel_s		// Pixel for dithering
{
  unsigned char	repeat,			// Repetition flags
		value;			// Value
} lprint_pixel_t;

typedef struct lprint_dither_s		// Dithering state
{
  pappl_dither_t dither;		// Dither matrix to use
  lprint_pixel_t *input[4];		// Input lines for dithering (only 3 are needed, 4 makes it easier for ring buffer)
  unsigned	in_width,		// Width in pixels
		in_height,		// Height in lines
		in_left,		// Left (starting) pixel
		in_top,			// Top-most pixel
		in_bottom;		// Bottom-most pixel
  unsigned char	in_bpp,			// Input bits per pixel (1 or 8)
		in_white;		// Input white pixel value (0 or 255)
  unsigned char	*output,		// Output bitmap
		out_white;		// Output white pixel value (0 or 255)
  unsigned	out_width;		// Output width in bytes
} lprint_dither_t;


//
// Functions...
//

extern bool	lprintDitherAlloc(lprint_dither_t *dither, pappl_job_t *job, pappl_pr_options_t *options, cups_cspace_t out_cspace, double out_gamma);
extern void	lprintDitherFree(lprint_dither_t *dither);
extern bool	lprintDitherLine(lprint_dither_t *dither, unsigned y, const unsigned char *line);

extern bool	lprintDYMO(pappl_system_t *system, const char *driver_name, const char *device_uri, const char *device_id, pappl_pr_driver_data_t *data, ipp_t **attrs, void *cbdata);
extern bool	lprintEPL2(pappl_system_t *system, const char *driver_name, const char *device_uri, const char *device_id, pappl_pr_driver_data_t *data, ipp_t **attrs, void *cbdata);
extern bool	lprintTestFilterCB(pappl_job_t *job, pappl_device_t *device, void *data);
extern const char *lprintTestPageCB(pappl_printer_t *printer, char *buffer, size_t bufsize);
extern bool	lprintZPL(pappl_system_t *system, const char *driver_name, const char *device_uri, const char *device_id, pappl_pr_driver_data_t *data, ipp_t **attrs, void *cbdata);
extern void	lprintZPLQueryDriver(pappl_system_t *system, const char *device_uri, char *name, size_t namesize);

// Future planned drivers that are not yet implemented
//extern bool	lprintCPCL(pappl_system_t *system, const char *driver_name, const char *device_uri, const char *device_id, pappl_pr_driver_data_t *driver_data, ipp_t **driver_attrs, void *data);
//extern bool	lprintEPL1(pappl_system_t *system, const char *driver_name, const char *device_uri, const char *device_id, pappl_pr_driver_data_t *driver_data, ipp_t **driver_attrs, void *data);
//extern bool	lprintFGL(pappl_system_t *system, const char *driver_name, const char *device_uri, const char *device_id, pappl_pr_driver_data_t *driver_data, ipp_t **driver_attrs, void *data);
//extern bool	lprintPCL(pappl_system_t *system, const char *driver_name, const char *device_uri, const char *device_id, pappl_pr_driver_data_t *driver_data, ipp_t **driver_attrs, void *data);


#endif // !LPRINT_H
