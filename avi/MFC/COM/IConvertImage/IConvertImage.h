/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Oct 24 16:01:31 2003
 */
/* Compiler settings for E:\Users\FunRoger\ExtrimYUV\IConvertImage\IConvertImage.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __IConvertImage_h__
#define __IConvertImage_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IConvertImage_FWD_DEFINED__
#define __IConvertImage_FWD_DEFINED__
typedef interface IConvertImage IConvertImage;
#endif 	/* __IConvertImage_FWD_DEFINED__ */


#ifndef __IConvertImageYUVPlanar_FWD_DEFINED__
#define __IConvertImageYUVPlanar_FWD_DEFINED__
typedef interface IConvertImageYUVPlanar IConvertImageYUVPlanar;
#endif 	/* __IConvertImageYUVPlanar_FWD_DEFINED__ */


#ifndef __IConvertImageGamma_FWD_DEFINED__
#define __IConvertImageGamma_FWD_DEFINED__
typedef interface IConvertImageGamma IConvertImageGamma;
#endif 	/* __IConvertImageGamma_FWD_DEFINED__ */


#ifndef __IStretchImage_FWD_DEFINED__
#define __IStretchImage_FWD_DEFINED__
typedef interface IStretchImage IStretchImage;
#endif 	/* __IStretchImage_FWD_DEFINED__ */


#ifndef __ICopyMemory_FWD_DEFINED__
#define __ICopyMemory_FWD_DEFINED__
typedef interface ICopyMemory ICopyMemory;
#endif 	/* __ICopyMemory_FWD_DEFINED__ */


#ifndef __ITitleMixer_FWD_DEFINED__
#define __ITitleMixer_FWD_DEFINED__
typedef interface ITitleMixer ITitleMixer;
#endif 	/* __ITitleMixer_FWD_DEFINED__ */


#ifndef __IY16ARLECompressor_FWD_DEFINED__
#define __IY16ARLECompressor_FWD_DEFINED__
typedef interface IY16ARLECompressor IY16ARLECompressor;
#endif 	/* __IY16ARLECompressor_FWD_DEFINED__ */


#ifndef __IDeinterlaceMaker_FWD_DEFINED__
#define __IDeinterlaceMaker_FWD_DEFINED__
typedef interface IDeinterlaceMaker IDeinterlaceMaker;
#endif 	/* __IDeinterlaceMaker_FWD_DEFINED__ */


#ifndef __ConvertImage_FWD_DEFINED__
#define __ConvertImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConvertImage ConvertImage;
#else
typedef struct ConvertImage ConvertImage;
#endif /* __cplusplus */

#endif 	/* __ConvertImage_FWD_DEFINED__ */


#ifndef __StretchImage_FWD_DEFINED__
#define __StretchImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class StretchImage StretchImage;
#else
typedef struct StretchImage StretchImage;
#endif /* __cplusplus */

#endif 	/* __StretchImage_FWD_DEFINED__ */


#ifndef __CopyMemory_FWD_DEFINED__
#define __CopyMemory_FWD_DEFINED__

#ifdef __cplusplus
typedef class CopyMemory CopyMemory;
#else
typedef struct CopyMemory CopyMemory;
#endif /* __cplusplus */

#endif 	/* __CopyMemory_FWD_DEFINED__ */


#ifndef __TitleMixer_FWD_DEFINED__
#define __TitleMixer_FWD_DEFINED__

#ifdef __cplusplus
typedef class TitleMixer TitleMixer;
#else
typedef struct TitleMixer TitleMixer;
#endif /* __cplusplus */

#endif 	/* __TitleMixer_FWD_DEFINED__ */


#ifndef __Y16ARLECompressor_FWD_DEFINED__
#define __Y16ARLECompressor_FWD_DEFINED__

#ifdef __cplusplus
typedef class Y16ARLECompressor Y16ARLECompressor;
#else
typedef struct Y16ARLECompressor Y16ARLECompressor;
#endif /* __cplusplus */

#endif 	/* __Y16ARLECompressor_FWD_DEFINED__ */


#ifndef __DeinterlaceMaker_FWD_DEFINED__
#define __DeinterlaceMaker_FWD_DEFINED__

#ifdef __cplusplus
typedef class DeinterlaceMaker DeinterlaceMaker;
#else
typedef struct DeinterlaceMaker DeinterlaceMaker;
#endif /* __cplusplus */

#endif 	/* __DeinterlaceMaker_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "ImageFormats.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IConvertImage_INTERFACE_DEFINED__
#define __IConvertImage_INTERFACE_DEFINED__

/* interface IConvertImage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IConvertImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7F399F71-B8E5-4AAC-97D2-92991D677866")
    IConvertImage : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertImage( 
            /* [in] */ unsigned char __RPC_FAR *lpvDst,
            /* [in] */ unsigned char __RPC_FAR *lpvSrc,
            /* [in] */ int iWidth,
            /* [in] */ int iHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int iTypeDst,
            /* [in] */ int iTypeSrc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConvertImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConvertImage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConvertImage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConvertImage __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertImage )( 
            IConvertImage __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *lpvDst,
            /* [in] */ unsigned char __RPC_FAR *lpvSrc,
            /* [in] */ int iWidth,
            /* [in] */ int iHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int iTypeDst,
            /* [in] */ int iTypeSrc);
        
        END_INTERFACE
    } IConvertImageVtbl;

    interface IConvertImage
    {
        CONST_VTBL struct IConvertImageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConvertImage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConvertImage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConvertImage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConvertImage_ConvertImage(This,lpvDst,lpvSrc,iWidth,iHeight,iStrideDst,iStrideSrc,iTypeDst,iTypeSrc)	\
    (This)->lpVtbl -> ConvertImage(This,lpvDst,lpvSrc,iWidth,iHeight,iStrideDst,iStrideSrc,iTypeDst,iTypeSrc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConvertImage_ConvertImage_Proxy( 
    IConvertImage __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *lpvDst,
    /* [in] */ unsigned char __RPC_FAR *lpvSrc,
    /* [in] */ int iWidth,
    /* [in] */ int iHeight,
    /* [in] */ int iStrideDst,
    /* [in] */ int iStrideSrc,
    /* [in] */ int iTypeDst,
    /* [in] */ int iTypeSrc);


void __RPC_STUB IConvertImage_ConvertImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConvertImage_INTERFACE_DEFINED__ */


#ifndef __IConvertImageYUVPlanar_INTERFACE_DEFINED__
#define __IConvertImageYUVPlanar_INTERFACE_DEFINED__

/* interface IConvertImageYUVPlanar */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IConvertImageYUVPlanar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EBC3AE44-0A7C-4ba5-AF5D-9EA475C2DC11")
    IConvertImageYUVPlanar : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertYUVPlanarToImage( 
            /* [in] */ unsigned char __RPC_FAR *lpvDst,
            /* [in] */ unsigned char __RPC_FAR *lpvSrcY,
            /* [in] */ unsigned char __RPC_FAR *lpvSrcU,
            /* [in] */ unsigned char __RPC_FAR *lpvSrcV,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrcY,
            /* [in] */ int iStrideSrcU,
            /* [in] */ int iStrideSrcV,
            /* [in] */ int nFormat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertImageToYUVPlanar( 
            /* [in] */ unsigned char __RPC_FAR *lpvDstY,
            /* [in] */ unsigned char __RPC_FAR *lpvDstU,
            /* [in] */ unsigned char __RPC_FAR *lpvDstV,
            /* [in] */ unsigned char __RPC_FAR *lpvSrc,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDstY,
            /* [in] */ int iStrideDstU,
            /* [in] */ int iStrideDstV,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nFormat) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConvertImageYUVPlanarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConvertImageYUVPlanar __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConvertImageYUVPlanar __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConvertImageYUVPlanar __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertYUVPlanarToImage )( 
            IConvertImageYUVPlanar __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *lpvDst,
            /* [in] */ unsigned char __RPC_FAR *lpvSrcY,
            /* [in] */ unsigned char __RPC_FAR *lpvSrcU,
            /* [in] */ unsigned char __RPC_FAR *lpvSrcV,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrcY,
            /* [in] */ int iStrideSrcU,
            /* [in] */ int iStrideSrcV,
            /* [in] */ int nFormat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertImageToYUVPlanar )( 
            IConvertImageYUVPlanar __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *lpvDstY,
            /* [in] */ unsigned char __RPC_FAR *lpvDstU,
            /* [in] */ unsigned char __RPC_FAR *lpvDstV,
            /* [in] */ unsigned char __RPC_FAR *lpvSrc,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDstY,
            /* [in] */ int iStrideDstU,
            /* [in] */ int iStrideDstV,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nFormat);
        
        END_INTERFACE
    } IConvertImageYUVPlanarVtbl;

    interface IConvertImageYUVPlanar
    {
        CONST_VTBL struct IConvertImageYUVPlanarVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConvertImageYUVPlanar_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConvertImageYUVPlanar_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConvertImageYUVPlanar_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConvertImageYUVPlanar_ConvertYUVPlanarToImage(This,lpvDst,lpvSrcY,lpvSrcU,lpvSrcV,nWidth,nHeight,iStrideDst,iStrideSrcY,iStrideSrcU,iStrideSrcV,nFormat)	\
    (This)->lpVtbl -> ConvertYUVPlanarToImage(This,lpvDst,lpvSrcY,lpvSrcU,lpvSrcV,nWidth,nHeight,iStrideDst,iStrideSrcY,iStrideSrcU,iStrideSrcV,nFormat)

#define IConvertImageYUVPlanar_ConvertImageToYUVPlanar(This,lpvDstY,lpvDstU,lpvDstV,lpvSrc,nWidth,nHeight,iStrideDstY,iStrideDstU,iStrideDstV,iStrideSrc,nFormat)	\
    (This)->lpVtbl -> ConvertImageToYUVPlanar(This,lpvDstY,lpvDstU,lpvDstV,lpvSrc,nWidth,nHeight,iStrideDstY,iStrideDstU,iStrideDstV,iStrideSrc,nFormat)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConvertImageYUVPlanar_ConvertYUVPlanarToImage_Proxy( 
    IConvertImageYUVPlanar __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *lpvDst,
    /* [in] */ unsigned char __RPC_FAR *lpvSrcY,
    /* [in] */ unsigned char __RPC_FAR *lpvSrcU,
    /* [in] */ unsigned char __RPC_FAR *lpvSrcV,
    /* [in] */ unsigned int nWidth,
    /* [in] */ unsigned int nHeight,
    /* [in] */ int iStrideDst,
    /* [in] */ int iStrideSrcY,
    /* [in] */ int iStrideSrcU,
    /* [in] */ int iStrideSrcV,
    /* [in] */ int nFormat);


void __RPC_STUB IConvertImageYUVPlanar_ConvertYUVPlanarToImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConvertImageYUVPlanar_ConvertImageToYUVPlanar_Proxy( 
    IConvertImageYUVPlanar __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *lpvDstY,
    /* [in] */ unsigned char __RPC_FAR *lpvDstU,
    /* [in] */ unsigned char __RPC_FAR *lpvDstV,
    /* [in] */ unsigned char __RPC_FAR *lpvSrc,
    /* [in] */ unsigned int nWidth,
    /* [in] */ unsigned int nHeight,
    /* [in] */ int iStrideDstY,
    /* [in] */ int iStrideDstU,
    /* [in] */ int iStrideDstV,
    /* [in] */ int iStrideSrc,
    /* [in] */ int nFormat);


void __RPC_STUB IConvertImageYUVPlanar_ConvertImageToYUVPlanar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConvertImageYUVPlanar_INTERFACE_DEFINED__ */


#ifndef __IConvertImageGamma_INTERFACE_DEFINED__
#define __IConvertImageGamma_INTERFACE_DEFINED__

/* interface IConvertImageGamma */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IConvertImageGamma;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D3A57963-280A-4bca-881E-DDCBF832EF61")
    IConvertImageGamma : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConvertImageGamma( 
            /* [in] */ unsigned char __RPC_FAR *lpvDst,
            /* [in] */ unsigned char __RPC_FAR *lpvSrc,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nFormatDst,
            /* [in] */ int nFormatSrc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGammaPal( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGammaNtsc( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGamma( 
            /* [in] */ double dGamma) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConvertImageGammaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConvertImageGamma __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConvertImageGamma __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConvertImageGamma __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertImageGamma )( 
            IConvertImageGamma __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *lpvDst,
            /* [in] */ unsigned char __RPC_FAR *lpvSrc,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nFormatDst,
            /* [in] */ int nFormatSrc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGammaPal )( 
            IConvertImageGamma __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGammaNtsc )( 
            IConvertImageGamma __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGamma )( 
            IConvertImageGamma __RPC_FAR * This,
            /* [in] */ double dGamma);
        
        END_INTERFACE
    } IConvertImageGammaVtbl;

    interface IConvertImageGamma
    {
        CONST_VTBL struct IConvertImageGammaVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConvertImageGamma_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConvertImageGamma_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConvertImageGamma_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConvertImageGamma_ConvertImageGamma(This,lpvDst,lpvSrc,nWidth,nHeight,iStrideDst,iStrideSrc,nFormatDst,nFormatSrc)	\
    (This)->lpVtbl -> ConvertImageGamma(This,lpvDst,lpvSrc,nWidth,nHeight,iStrideDst,iStrideSrc,nFormatDst,nFormatSrc)

#define IConvertImageGamma_SetGammaPal(This)	\
    (This)->lpVtbl -> SetGammaPal(This)

#define IConvertImageGamma_SetGammaNtsc(This)	\
    (This)->lpVtbl -> SetGammaNtsc(This)

#define IConvertImageGamma_SetGamma(This,dGamma)	\
    (This)->lpVtbl -> SetGamma(This,dGamma)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConvertImageGamma_ConvertImageGamma_Proxy( 
    IConvertImageGamma __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *lpvDst,
    /* [in] */ unsigned char __RPC_FAR *lpvSrc,
    /* [in] */ unsigned int nWidth,
    /* [in] */ unsigned int nHeight,
    /* [in] */ int iStrideDst,
    /* [in] */ int iStrideSrc,
    /* [in] */ int nFormatDst,
    /* [in] */ int nFormatSrc);


void __RPC_STUB IConvertImageGamma_ConvertImageGamma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConvertImageGamma_SetGammaPal_Proxy( 
    IConvertImageGamma __RPC_FAR * This);


void __RPC_STUB IConvertImageGamma_SetGammaPal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConvertImageGamma_SetGammaNtsc_Proxy( 
    IConvertImageGamma __RPC_FAR * This);


void __RPC_STUB IConvertImageGamma_SetGammaNtsc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConvertImageGamma_SetGamma_Proxy( 
    IConvertImageGamma __RPC_FAR * This,
    /* [in] */ double dGamma);


void __RPC_STUB IConvertImageGamma_SetGamma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConvertImageGamma_INTERFACE_DEFINED__ */


#ifndef __IStretchImage_INTERFACE_DEFINED__
#define __IStretchImage_INTERFACE_DEFINED__

/* interface IStretchImage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IStretchImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("076F9D3D-D665-41EC-8DAE-71D679F9E118")
    IStretchImage : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StretchImage( 
            /* [in] */ unsigned char __RPC_FAR *lpvDst,
            /* [in] */ unsigned char __RPC_FAR *lpvSrc,
            /* [in] */ unsigned int nWidthDst,
            /* [in] */ unsigned int nHeightDst,
            /* [in] */ unsigned int nWidthSrc,
            /* [in] */ unsigned int nHeightSrc,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nFormat) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStretchImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStretchImage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStretchImage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStretchImage __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StretchImage )( 
            IStretchImage __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *lpvDst,
            /* [in] */ unsigned char __RPC_FAR *lpvSrc,
            /* [in] */ unsigned int nWidthDst,
            /* [in] */ unsigned int nHeightDst,
            /* [in] */ unsigned int nWidthSrc,
            /* [in] */ unsigned int nHeightSrc,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nFormat);
        
        END_INTERFACE
    } IStretchImageVtbl;

    interface IStretchImage
    {
        CONST_VTBL struct IStretchImageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStretchImage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStretchImage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStretchImage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStretchImage_StretchImage(This,lpvDst,lpvSrc,nWidthDst,nHeightDst,nWidthSrc,nHeightSrc,iStrideDst,iStrideSrc,nFormat)	\
    (This)->lpVtbl -> StretchImage(This,lpvDst,lpvSrc,nWidthDst,nHeightDst,nWidthSrc,nHeightSrc,iStrideDst,iStrideSrc,nFormat)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStretchImage_StretchImage_Proxy( 
    IStretchImage __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *lpvDst,
    /* [in] */ unsigned char __RPC_FAR *lpvSrc,
    /* [in] */ unsigned int nWidthDst,
    /* [in] */ unsigned int nHeightDst,
    /* [in] */ unsigned int nWidthSrc,
    /* [in] */ unsigned int nHeightSrc,
    /* [in] */ int iStrideDst,
    /* [in] */ int iStrideSrc,
    /* [in] */ int nFormat);


void __RPC_STUB IStretchImage_StretchImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStretchImage_INTERFACE_DEFINED__ */


#ifndef __ICopyMemory_INTERFACE_DEFINED__
#define __ICopyMemory_INTERFACE_DEFINED__

/* interface ICopyMemory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICopyMemory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3EA29A5-5FA1-455A-81B0-BEC10EC6173D")
    ICopyMemory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CopyMemoryFast( 
            /* [in] */ unsigned char __RPC_FAR *lpbDestination,
            /* [in] */ unsigned char __RPC_FAR *lpbSource,
            /* [in] */ unsigned int nCountBytes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMemoryByte( 
            /* [in] */ unsigned char __RPC_FAR *lpbDestination,
            /* [in] */ unsigned int nCountBytes,
            /* [in] */ unsigned char bValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMemoryWord( 
            /* [in] */ unsigned short __RPC_FAR *lpwDestination,
            /* [in] */ unsigned int nCountWords,
            /* [in] */ unsigned short wValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMemoryDword( 
            /* [in] */ unsigned int __RPC_FAR *lpnDestination,
            /* [in] */ unsigned int nCountDwords,
            /* [in] */ unsigned int nValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ZeroMemoryFast( 
            /* [in] */ unsigned char __RPC_FAR *lpbDestination,
            /* [in] */ unsigned int nCountBytes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICopyMemoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICopyMemory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICopyMemory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICopyMemory __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyMemoryFast )( 
            ICopyMemory __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *lpbDestination,
            /* [in] */ unsigned char __RPC_FAR *lpbSource,
            /* [in] */ unsigned int nCountBytes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMemoryByte )( 
            ICopyMemory __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *lpbDestination,
            /* [in] */ unsigned int nCountBytes,
            /* [in] */ unsigned char bValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMemoryWord )( 
            ICopyMemory __RPC_FAR * This,
            /* [in] */ unsigned short __RPC_FAR *lpwDestination,
            /* [in] */ unsigned int nCountWords,
            /* [in] */ unsigned short wValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMemoryDword )( 
            ICopyMemory __RPC_FAR * This,
            /* [in] */ unsigned int __RPC_FAR *lpnDestination,
            /* [in] */ unsigned int nCountDwords,
            /* [in] */ unsigned int nValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ZeroMemoryFast )( 
            ICopyMemory __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *lpbDestination,
            /* [in] */ unsigned int nCountBytes);
        
        END_INTERFACE
    } ICopyMemoryVtbl;

    interface ICopyMemory
    {
        CONST_VTBL struct ICopyMemoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICopyMemory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICopyMemory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICopyMemory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICopyMemory_CopyMemoryFast(This,lpbDestination,lpbSource,nCountBytes)	\
    (This)->lpVtbl -> CopyMemoryFast(This,lpbDestination,lpbSource,nCountBytes)

#define ICopyMemory_SetMemoryByte(This,lpbDestination,nCountBytes,bValue)	\
    (This)->lpVtbl -> SetMemoryByte(This,lpbDestination,nCountBytes,bValue)

#define ICopyMemory_SetMemoryWord(This,lpwDestination,nCountWords,wValue)	\
    (This)->lpVtbl -> SetMemoryWord(This,lpwDestination,nCountWords,wValue)

#define ICopyMemory_SetMemoryDword(This,lpnDestination,nCountDwords,nValue)	\
    (This)->lpVtbl -> SetMemoryDword(This,lpnDestination,nCountDwords,nValue)

#define ICopyMemory_ZeroMemoryFast(This,lpbDestination,nCountBytes)	\
    (This)->lpVtbl -> ZeroMemoryFast(This,lpbDestination,nCountBytes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICopyMemory_CopyMemoryFast_Proxy( 
    ICopyMemory __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *lpbDestination,
    /* [in] */ unsigned char __RPC_FAR *lpbSource,
    /* [in] */ unsigned int nCountBytes);


void __RPC_STUB ICopyMemory_CopyMemoryFast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICopyMemory_SetMemoryByte_Proxy( 
    ICopyMemory __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *lpbDestination,
    /* [in] */ unsigned int nCountBytes,
    /* [in] */ unsigned char bValue);


void __RPC_STUB ICopyMemory_SetMemoryByte_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICopyMemory_SetMemoryWord_Proxy( 
    ICopyMemory __RPC_FAR * This,
    /* [in] */ unsigned short __RPC_FAR *lpwDestination,
    /* [in] */ unsigned int nCountWords,
    /* [in] */ unsigned short wValue);


void __RPC_STUB ICopyMemory_SetMemoryWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICopyMemory_SetMemoryDword_Proxy( 
    ICopyMemory __RPC_FAR * This,
    /* [in] */ unsigned int __RPC_FAR *lpnDestination,
    /* [in] */ unsigned int nCountDwords,
    /* [in] */ unsigned int nValue);


void __RPC_STUB ICopyMemory_SetMemoryDword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICopyMemory_ZeroMemoryFast_Proxy( 
    ICopyMemory __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *lpbDestination,
    /* [in] */ unsigned int nCountBytes);


void __RPC_STUB ICopyMemory_ZeroMemoryFast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICopyMemory_INTERFACE_DEFINED__ */


#ifndef __ITitleMixer_INTERFACE_DEFINED__
#define __ITitleMixer_INTERFACE_DEFINED__

/* interface ITitleMixer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITitleMixer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A0ABE85-062D-432A-97C4-080E38CA558B")
    ITitleMixer : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MovTitle( 
            /* [in] */ BYTE __RPC_FAR *lpbDestination,
            /* [in] */ BYTE __RPC_FAR *lpbSource,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nRegionAlpha) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddTitle( 
            /* [in] */ BYTE __RPC_FAR *lpbDestination,
            /* [in] */ BYTE __RPC_FAR *lpbSource,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nRegionAlpha) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CompressToRLE( 
            /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *lpbDestination,
            /* [in] */ BYTE __RPC_FAR *lpbSource,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideSource,
            /* [out][in] */ int __RPC_FAR *__RPC_FAR *lpiCounter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITitleMixerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITitleMixer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITitleMixer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITitleMixer __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MovTitle )( 
            ITitleMixer __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *lpbDestination,
            /* [in] */ BYTE __RPC_FAR *lpbSource,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nRegionAlpha);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTitle )( 
            ITitleMixer __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *lpbDestination,
            /* [in] */ BYTE __RPC_FAR *lpbSource,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideDst,
            /* [in] */ int iStrideSrc,
            /* [in] */ int nRegionAlpha);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CompressToRLE )( 
            ITitleMixer __RPC_FAR * This,
            /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *lpbDestination,
            /* [in] */ BYTE __RPC_FAR *lpbSource,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideSource,
            /* [out][in] */ int __RPC_FAR *__RPC_FAR *lpiCounter);
        
        END_INTERFACE
    } ITitleMixerVtbl;

    interface ITitleMixer
    {
        CONST_VTBL struct ITitleMixerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITitleMixer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITitleMixer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITitleMixer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITitleMixer_MovTitle(This,lpbDestination,lpbSource,nWidth,nHeight,iStrideDst,iStrideSrc,nRegionAlpha)	\
    (This)->lpVtbl -> MovTitle(This,lpbDestination,lpbSource,nWidth,nHeight,iStrideDst,iStrideSrc,nRegionAlpha)

#define ITitleMixer_AddTitle(This,lpbDestination,lpbSource,nWidth,nHeight,iStrideDst,iStrideSrc,nRegionAlpha)	\
    (This)->lpVtbl -> AddTitle(This,lpbDestination,lpbSource,nWidth,nHeight,iStrideDst,iStrideSrc,nRegionAlpha)

#define ITitleMixer_CompressToRLE(This,lpbDestination,lpbSource,nWidth,nHeight,iStrideSource,lpiCounter)	\
    (This)->lpVtbl -> CompressToRLE(This,lpbDestination,lpbSource,nWidth,nHeight,iStrideSource,lpiCounter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITitleMixer_MovTitle_Proxy( 
    ITitleMixer __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *lpbDestination,
    /* [in] */ BYTE __RPC_FAR *lpbSource,
    /* [in] */ unsigned int nWidth,
    /* [in] */ unsigned int nHeight,
    /* [in] */ int iStrideDst,
    /* [in] */ int iStrideSrc,
    /* [in] */ int nRegionAlpha);


void __RPC_STUB ITitleMixer_MovTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITitleMixer_AddTitle_Proxy( 
    ITitleMixer __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *lpbDestination,
    /* [in] */ BYTE __RPC_FAR *lpbSource,
    /* [in] */ unsigned int nWidth,
    /* [in] */ unsigned int nHeight,
    /* [in] */ int iStrideDst,
    /* [in] */ int iStrideSrc,
    /* [in] */ int nRegionAlpha);


void __RPC_STUB ITitleMixer_AddTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITitleMixer_CompressToRLE_Proxy( 
    ITitleMixer __RPC_FAR * This,
    /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *lpbDestination,
    /* [in] */ BYTE __RPC_FAR *lpbSource,
    /* [in] */ unsigned int nWidth,
    /* [in] */ unsigned int nHeight,
    /* [in] */ int iStrideSource,
    /* [out][in] */ int __RPC_FAR *__RPC_FAR *lpiCounter);


void __RPC_STUB ITitleMixer_CompressToRLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITitleMixer_INTERFACE_DEFINED__ */


#ifndef __IY16ARLECompressor_INTERFACE_DEFINED__
#define __IY16ARLECompressor_INTERFACE_DEFINED__

/* interface IY16ARLECompressor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IY16ARLECompressor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F29D605-BC2A-482E-8A44-C32B42517356")
    IY16ARLECompressor : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Compress( 
            /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *lpvDestination,
            /* [in] */ BYTE __RPC_FAR *lpvSource,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideSource,
            /* [out][in] */ int __RPC_FAR *__RPC_FAR *lpiCounter,
            /* [in] */ int nTypeSource) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IY16ARLECompressorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IY16ARLECompressor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IY16ARLECompressor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IY16ARLECompressor __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Compress )( 
            IY16ARLECompressor __RPC_FAR * This,
            /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *lpvDestination,
            /* [in] */ BYTE __RPC_FAR *lpvSource,
            /* [in] */ unsigned int nWidth,
            /* [in] */ unsigned int nHeight,
            /* [in] */ int iStrideSource,
            /* [out][in] */ int __RPC_FAR *__RPC_FAR *lpiCounter,
            /* [in] */ int nTypeSource);
        
        END_INTERFACE
    } IY16ARLECompressorVtbl;

    interface IY16ARLECompressor
    {
        CONST_VTBL struct IY16ARLECompressorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IY16ARLECompressor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IY16ARLECompressor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IY16ARLECompressor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IY16ARLECompressor_Compress(This,lpvDestination,lpvSource,nWidth,nHeight,iStrideSource,lpiCounter,nTypeSource)	\
    (This)->lpVtbl -> Compress(This,lpvDestination,lpvSource,nWidth,nHeight,iStrideSource,lpiCounter,nTypeSource)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IY16ARLECompressor_Compress_Proxy( 
    IY16ARLECompressor __RPC_FAR * This,
    /* [out][in] */ BYTE __RPC_FAR *__RPC_FAR *lpvDestination,
    /* [in] */ BYTE __RPC_FAR *lpvSource,
    /* [in] */ unsigned int nWidth,
    /* [in] */ unsigned int nHeight,
    /* [in] */ int iStrideSource,
    /* [out][in] */ int __RPC_FAR *__RPC_FAR *lpiCounter,
    /* [in] */ int nTypeSource);


void __RPC_STUB IY16ARLECompressor_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IY16ARLECompressor_INTERFACE_DEFINED__ */


#ifndef __IDeinterlaceMaker_INTERFACE_DEFINED__
#define __IDeinterlaceMaker_INTERFACE_DEFINED__

/* interface IDeinterlaceMaker */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDeinterlaceMaker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("323C5C6C-92A6-4024-A80E-03F78EC4105E")
    IDeinterlaceMaker : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RestoreLowerField( 
            /* [in] */ BYTE __RPC_FAR *lpbDest,
            /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
            /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
            /* [in] */ BYTE __RPC_FAR *lpbSrcUpper,
            /* [in] */ DWORD nFieldWidth,
            /* [in] */ DWORD nFieldHeight,
            /* [in] */ int iStrideDest,
            /* [in] */ int iStrideSrc,
            /* [in] */ DWORD Kmin,
            /* [in] */ DWORD Kmax) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RestoreUpperField( 
            /* [in] */ BYTE __RPC_FAR *lpbDest,
            /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
            /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
            /* [in] */ BYTE __RPC_FAR *lpbSrcLower,
            /* [in] */ DWORD nFieldWidth,
            /* [in] */ DWORD nFieldHeight,
            /* [in] */ int iStrideDest,
            /* [in] */ int iStrideSrc,
            /* [in] */ DWORD Kmin,
            /* [in] */ DWORD Kmax) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RestoreLowerFieldAlpha( 
            /* [in] */ BYTE __RPC_FAR *lpbDest,
            /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
            /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
            /* [in] */ BYTE __RPC_FAR *lpbSrcUpper,
            /* [in] */ DWORD nFieldWidth,
            /* [in] */ DWORD nFieldHeight,
            /* [in] */ int iStrideDest,
            /* [in] */ int iStrideSrc,
            /* [in] */ DWORD Kmin,
            /* [in] */ DWORD Kmax) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RestoreUpperFieldAlpha( 
            /* [in] */ BYTE __RPC_FAR *lpbDest,
            /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
            /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
            /* [in] */ BYTE __RPC_FAR *lpbSrcLower,
            /* [in] */ DWORD nFieldWidth,
            /* [in] */ DWORD nFieldHeight,
            /* [in] */ int iStrideDest,
            /* [in] */ int iStrideSrc,
            /* [in] */ DWORD Kmin,
            /* [in] */ DWORD Kmax) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDeinterlaceMakerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDeinterlaceMaker __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDeinterlaceMaker __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDeinterlaceMaker __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreLowerField )( 
            IDeinterlaceMaker __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *lpbDest,
            /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
            /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
            /* [in] */ BYTE __RPC_FAR *lpbSrcUpper,
            /* [in] */ DWORD nFieldWidth,
            /* [in] */ DWORD nFieldHeight,
            /* [in] */ int iStrideDest,
            /* [in] */ int iStrideSrc,
            /* [in] */ DWORD Kmin,
            /* [in] */ DWORD Kmax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreUpperField )( 
            IDeinterlaceMaker __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *lpbDest,
            /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
            /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
            /* [in] */ BYTE __RPC_FAR *lpbSrcLower,
            /* [in] */ DWORD nFieldWidth,
            /* [in] */ DWORD nFieldHeight,
            /* [in] */ int iStrideDest,
            /* [in] */ int iStrideSrc,
            /* [in] */ DWORD Kmin,
            /* [in] */ DWORD Kmax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreLowerFieldAlpha )( 
            IDeinterlaceMaker __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *lpbDest,
            /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
            /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
            /* [in] */ BYTE __RPC_FAR *lpbSrcUpper,
            /* [in] */ DWORD nFieldWidth,
            /* [in] */ DWORD nFieldHeight,
            /* [in] */ int iStrideDest,
            /* [in] */ int iStrideSrc,
            /* [in] */ DWORD Kmin,
            /* [in] */ DWORD Kmax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreUpperFieldAlpha )( 
            IDeinterlaceMaker __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *lpbDest,
            /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
            /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
            /* [in] */ BYTE __RPC_FAR *lpbSrcLower,
            /* [in] */ DWORD nFieldWidth,
            /* [in] */ DWORD nFieldHeight,
            /* [in] */ int iStrideDest,
            /* [in] */ int iStrideSrc,
            /* [in] */ DWORD Kmin,
            /* [in] */ DWORD Kmax);
        
        END_INTERFACE
    } IDeinterlaceMakerVtbl;

    interface IDeinterlaceMaker
    {
        CONST_VTBL struct IDeinterlaceMakerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeinterlaceMaker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDeinterlaceMaker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDeinterlaceMaker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDeinterlaceMaker_RestoreLowerField(This,lpbDest,lpbSrcPrev,lpbSrcNext,lpbSrcUpper,nFieldWidth,nFieldHeight,iStrideDest,iStrideSrc,Kmin,Kmax)	\
    (This)->lpVtbl -> RestoreLowerField(This,lpbDest,lpbSrcPrev,lpbSrcNext,lpbSrcUpper,nFieldWidth,nFieldHeight,iStrideDest,iStrideSrc,Kmin,Kmax)

#define IDeinterlaceMaker_RestoreUpperField(This,lpbDest,lpbSrcPrev,lpbSrcNext,lpbSrcLower,nFieldWidth,nFieldHeight,iStrideDest,iStrideSrc,Kmin,Kmax)	\
    (This)->lpVtbl -> RestoreUpperField(This,lpbDest,lpbSrcPrev,lpbSrcNext,lpbSrcLower,nFieldWidth,nFieldHeight,iStrideDest,iStrideSrc,Kmin,Kmax)

#define IDeinterlaceMaker_RestoreLowerFieldAlpha(This,lpbDest,lpbSrcPrev,lpbSrcNext,lpbSrcUpper,nFieldWidth,nFieldHeight,iStrideDest,iStrideSrc,Kmin,Kmax)	\
    (This)->lpVtbl -> RestoreLowerFieldAlpha(This,lpbDest,lpbSrcPrev,lpbSrcNext,lpbSrcUpper,nFieldWidth,nFieldHeight,iStrideDest,iStrideSrc,Kmin,Kmax)

#define IDeinterlaceMaker_RestoreUpperFieldAlpha(This,lpbDest,lpbSrcPrev,lpbSrcNext,lpbSrcLower,nFieldWidth,nFieldHeight,iStrideDest,iStrideSrc,Kmin,Kmax)	\
    (This)->lpVtbl -> RestoreUpperFieldAlpha(This,lpbDest,lpbSrcPrev,lpbSrcNext,lpbSrcLower,nFieldWidth,nFieldHeight,iStrideDest,iStrideSrc,Kmin,Kmax)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDeinterlaceMaker_RestoreLowerField_Proxy( 
    IDeinterlaceMaker __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *lpbDest,
    /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
    /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
    /* [in] */ BYTE __RPC_FAR *lpbSrcUpper,
    /* [in] */ DWORD nFieldWidth,
    /* [in] */ DWORD nFieldHeight,
    /* [in] */ int iStrideDest,
    /* [in] */ int iStrideSrc,
    /* [in] */ DWORD Kmin,
    /* [in] */ DWORD Kmax);


void __RPC_STUB IDeinterlaceMaker_RestoreLowerField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDeinterlaceMaker_RestoreUpperField_Proxy( 
    IDeinterlaceMaker __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *lpbDest,
    /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
    /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
    /* [in] */ BYTE __RPC_FAR *lpbSrcLower,
    /* [in] */ DWORD nFieldWidth,
    /* [in] */ DWORD nFieldHeight,
    /* [in] */ int iStrideDest,
    /* [in] */ int iStrideSrc,
    /* [in] */ DWORD Kmin,
    /* [in] */ DWORD Kmax);


void __RPC_STUB IDeinterlaceMaker_RestoreUpperField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDeinterlaceMaker_RestoreLowerFieldAlpha_Proxy( 
    IDeinterlaceMaker __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *lpbDest,
    /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
    /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
    /* [in] */ BYTE __RPC_FAR *lpbSrcUpper,
    /* [in] */ DWORD nFieldWidth,
    /* [in] */ DWORD nFieldHeight,
    /* [in] */ int iStrideDest,
    /* [in] */ int iStrideSrc,
    /* [in] */ DWORD Kmin,
    /* [in] */ DWORD Kmax);


void __RPC_STUB IDeinterlaceMaker_RestoreLowerFieldAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDeinterlaceMaker_RestoreUpperFieldAlpha_Proxy( 
    IDeinterlaceMaker __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *lpbDest,
    /* [in] */ BYTE __RPC_FAR *lpbSrcPrev,
    /* [in] */ BYTE __RPC_FAR *lpbSrcNext,
    /* [in] */ BYTE __RPC_FAR *lpbSrcLower,
    /* [in] */ DWORD nFieldWidth,
    /* [in] */ DWORD nFieldHeight,
    /* [in] */ int iStrideDest,
    /* [in] */ int iStrideSrc,
    /* [in] */ DWORD Kmin,
    /* [in] */ DWORD Kmax);


void __RPC_STUB IDeinterlaceMaker_RestoreUpperFieldAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDeinterlaceMaker_INTERFACE_DEFINED__ */



#ifndef __ICONVERTIMAGELib_LIBRARY_DEFINED__
#define __ICONVERTIMAGELib_LIBRARY_DEFINED__

/* library ICONVERTIMAGELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ICONVERTIMAGELib;

EXTERN_C const CLSID CLSID_ConvertImage;

#ifdef __cplusplus

class DECLSPEC_UUID("2ACC22E9-B881-4873-BC39-DE01DD49185E")
ConvertImage;
#endif

EXTERN_C const CLSID CLSID_StretchImage;

#ifdef __cplusplus

class DECLSPEC_UUID("31E38A3B-4457-4227-95B0-AC737DAC583E")
StretchImage;
#endif

EXTERN_C const CLSID CLSID_CopyMemory;

#ifdef __cplusplus

class DECLSPEC_UUID("8EAE9EC1-94D8-4BC4-AC19-CA65EEC825FE")
CopyMemory;
#endif

EXTERN_C const CLSID CLSID_TitleMixer;

#ifdef __cplusplus

class DECLSPEC_UUID("C98ABA7E-D4E3-4630-9601-C7323F6FCE7A")
TitleMixer;
#endif

EXTERN_C const CLSID CLSID_Y16ARLECompressor;

#ifdef __cplusplus

class DECLSPEC_UUID("0B5E501E-4513-4CA7-81BB-F08E129CA27A")
Y16ARLECompressor;
#endif

EXTERN_C const CLSID CLSID_DeinterlaceMaker;

#ifdef __cplusplus

class DECLSPEC_UUID("6105D26A-775A-47A6-9EB2-321639DD398E")
DeinterlaceMaker;
#endif
#endif /* __ICONVERTIMAGELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
