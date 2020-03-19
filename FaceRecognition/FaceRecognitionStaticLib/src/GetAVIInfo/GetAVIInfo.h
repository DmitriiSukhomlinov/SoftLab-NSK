

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Tue Sep 08 21:56:21 2015
 */
/* Compiler settings for .\GetAVIInfo.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __GetAVIInfo_h__
#define __GetAVIInfo_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGetAVIInfoOld_FWD_DEFINED__
#define __IGetAVIInfoOld_FWD_DEFINED__
typedef interface IGetAVIInfoOld IGetAVIInfoOld;
#endif 	/* __IGetAVIInfoOld_FWD_DEFINED__ */


#ifndef __IGetAVIInfo_FWD_DEFINED__
#define __IGetAVIInfo_FWD_DEFINED__
typedef interface IGetAVIInfo IGetAVIInfo;
#endif 	/* __IGetAVIInfo_FWD_DEFINED__ */


#ifndef __IGetAVIInfo2_FWD_DEFINED__
#define __IGetAVIInfo2_FWD_DEFINED__
typedef interface IGetAVIInfo2 IGetAVIInfo2;
#endif 	/* __IGetAVIInfo2_FWD_DEFINED__ */


#ifndef __IGetAVIInfoArray_FWD_DEFINED__
#define __IGetAVIInfoArray_FWD_DEFINED__
typedef interface IGetAVIInfoArray IGetAVIInfoArray;
#endif 	/* __IGetAVIInfoArray_FWD_DEFINED__ */


#ifndef __IGetAVIInfoEx_FWD_DEFINED__
#define __IGetAVIInfoEx_FWD_DEFINED__
typedef interface IGetAVIInfoEx IGetAVIInfoEx;
#endif 	/* __IGetAVIInfoEx_FWD_DEFINED__ */


#ifndef __IGetDVAudio_FWD_DEFINED__
#define __IGetDVAudio_FWD_DEFINED__
typedef interface IGetDVAudio IGetDVAudio;
#endif 	/* __IGetDVAudio_FWD_DEFINED__ */


#ifndef __IGetDVInfo_FWD_DEFINED__
#define __IGetDVInfo_FWD_DEFINED__
typedef interface IGetDVInfo IGetDVInfo;
#endif 	/* __IGetDVInfo_FWD_DEFINED__ */


#ifndef __GetAVIInfo_FWD_DEFINED__
#define __GetAVIInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class GetAVIInfo GetAVIInfo;
#else
typedef struct GetAVIInfo GetAVIInfo;
#endif /* __cplusplus */

#endif 	/* __GetAVIInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_GetAVIInfo_0000_0000 */
/* [local] */ 

#pragma pack(1)
typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_GetAVIInfo_0000_0000_0001
    {
    DWORD fccType;
    DWORD fr_flags;
    DWORD fr_pos;
    DWORD fr_size;
    } 	IndexFileEntry;

#pragma pack()


extern RPC_IF_HANDLE __MIDL_itf_GetAVIInfo_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GetAVIInfo_0000_0000_v0_0_s_ifspec;

#ifndef __IGetAVIInfoOld_INTERFACE_DEFINED__
#define __IGetAVIInfoOld_INTERFACE_DEFINED__

/* interface IGetAVIInfoOld */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGetAVIInfoOld;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F3B918F-FD8B-40f0-B1A7-0791EB6E5314")
    IGetAVIInfoOld : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BSTR file_name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [out] */ BSTR *file_name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoStreamNumber( 
            /* [out] */ long *num) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioStreamNumber( 
            /* [out] */ long *num) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoStreamInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info,
            /* [out] */ long *size_infoex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioStreamInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoFrameNumber( 
            /* [in] */ long index,
            /* [out] */ long *frame_count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioChunkNumber( 
            /* [in] */ long index,
            /* [out] */ long *chunk_count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoFrameInfo( 
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioChunkInfo( 
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoFormatInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioFormatInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoExtFormatInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioSampleInfo( 
            /* [in] */ long index,
            /* [in] */ UINT sample_number,
            /* [out] */ UINT *chunk_num,
            /* [out] */ UINT *offset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMainHeader( 
            /* [length_is][size_is][out] */ BYTE *buffer,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoFrameInfo2( 
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioChunkInfo2( 
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetAVIInfoOldVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetAVIInfoOld * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetAVIInfoOld * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetAVIInfoOld * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGetAVIInfoOld * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGetAVIInfoOld * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGetAVIInfoOld * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IGetAVIInfoOld * This,
            /* [in] */ BSTR file_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IGetAVIInfoOld * This,
            /* [out] */ BSTR *file_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoStreamNumber )( 
            IGetAVIInfoOld * This,
            /* [out] */ long *num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioStreamNumber )( 
            IGetAVIInfoOld * This,
            /* [out] */ long *num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoStreamInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info,
            /* [out] */ long *size_infoex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioStreamInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameNumber )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [out] */ long *frame_count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkNumber )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [out] */ long *chunk_count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFormatInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioFormatInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoExtFormatInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioSampleInfo )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [in] */ UINT sample_number,
            /* [out] */ UINT *chunk_num,
            /* [out] */ UINT *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMainHeader )( 
            IGetAVIInfoOld * This,
            /* [length_is][size_is][out] */ BYTE *buffer,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameInfo2 )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkInfo2 )( 
            IGetAVIInfoOld * This,
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags);
        
        END_INTERFACE
    } IGetAVIInfoOldVtbl;

    interface IGetAVIInfoOld
    {
        CONST_VTBL struct IGetAVIInfoOldVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetAVIInfoOld_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetAVIInfoOld_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetAVIInfoOld_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetAVIInfoOld_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGetAVIInfoOld_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGetAVIInfoOld_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGetAVIInfoOld_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGetAVIInfoOld_Load(This,file_name)	\
    ( (This)->lpVtbl -> Load(This,file_name) ) 

#define IGetAVIInfoOld_GetName(This,file_name)	\
    ( (This)->lpVtbl -> GetName(This,file_name) ) 

#define IGetAVIInfoOld_GetVideoStreamNumber(This,num)	\
    ( (This)->lpVtbl -> GetVideoStreamNumber(This,num) ) 

#define IGetAVIInfoOld_GetAudioStreamNumber(This,num)	\
    ( (This)->lpVtbl -> GetAudioStreamNumber(This,num) ) 

#define IGetAVIInfoOld_GetVideoStreamInfo(This,index,stream_header,size,ln,size_info,size_infoex)	\
    ( (This)->lpVtbl -> GetVideoStreamInfo(This,index,stream_header,size,ln,size_info,size_infoex) ) 

#define IGetAVIInfoOld_GetAudioStreamInfo(This,index,stream_header,size,ln,size_info)	\
    ( (This)->lpVtbl -> GetAudioStreamInfo(This,index,stream_header,size,ln,size_info) ) 

#define IGetAVIInfoOld_GetVideoFrameNumber(This,index,frame_count)	\
    ( (This)->lpVtbl -> GetVideoFrameNumber(This,index,frame_count) ) 

#define IGetAVIInfoOld_GetAudioChunkNumber(This,index,chunk_count)	\
    ( (This)->lpVtbl -> GetAudioChunkNumber(This,index,chunk_count) ) 

#define IGetAVIInfoOld_GetVideoFrameInfo(This,index,frame_number,hi_offset,low_offset,size)	\
    ( (This)->lpVtbl -> GetVideoFrameInfo(This,index,frame_number,hi_offset,low_offset,size) ) 

#define IGetAVIInfoOld_GetAudioChunkInfo(This,index,chunk_number,hi_offset,low_offset,size)	\
    ( (This)->lpVtbl -> GetAudioChunkInfo(This,index,chunk_number,hi_offset,low_offset,size) ) 

#define IGetAVIInfoOld_GetVideoFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetVideoFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfoOld_GetAudioFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetAudioFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfoOld_GetVideoExtFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetVideoExtFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfoOld_GetAudioSampleInfo(This,index,sample_number,chunk_num,offset)	\
    ( (This)->lpVtbl -> GetAudioSampleInfo(This,index,sample_number,chunk_num,offset) ) 

#define IGetAVIInfoOld_GetMainHeader(This,buffer,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetMainHeader(This,buffer,buf_size,copy_size) ) 

#define IGetAVIInfoOld_GetVideoFrameInfo2(This,index,frame_number,hi_offset,low_offset,size,flags)	\
    ( (This)->lpVtbl -> GetVideoFrameInfo2(This,index,frame_number,hi_offset,low_offset,size,flags) ) 

#define IGetAVIInfoOld_GetAudioChunkInfo2(This,index,chunk_number,hi_offset,low_offset,size,flags)	\
    ( (This)->lpVtbl -> GetAudioChunkInfo2(This,index,chunk_number,hi_offset,low_offset,size,flags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetAVIInfoOld_INTERFACE_DEFINED__ */


#ifndef __IGetAVIInfo_INTERFACE_DEFINED__
#define __IGetAVIInfo_INTERFACE_DEFINED__

/* interface IGetAVIInfo */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGetAVIInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3CB22126-3A53-4309-838D-1580A2339C8E")
    IGetAVIInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BSTR file_name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [out] */ BSTR *file_name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoStreamNumber( 
            /* [out] */ long *num) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioStreamNumber( 
            /* [out] */ long *num) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoStreamInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info,
            /* [out] */ long *size_infoex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioStreamInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoFrameNumber( 
            /* [in] */ long index,
            /* [out] */ long *frame_count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioChunkNumber( 
            /* [in] */ long index,
            /* [out] */ long *chunk_count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoFrameInfo( 
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioChunkInfo( 
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoFormatInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioFormatInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoExtFormatInfo( 
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioSampleInfo( 
            /* [in] */ long index,
            /* [in] */ UINT sample_number,
            /* [out] */ UINT *chunk_num,
            /* [out] */ UINT *offset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMainHeader( 
            /* [length_is][size_is][out] */ BYTE *buffer,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoFrameInfo2( 
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAudioChunkInfo2( 
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FastLoad( 
            /* [in] */ BSTR file_name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetAVIInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetAVIInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetAVIInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetAVIInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGetAVIInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGetAVIInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGetAVIInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGetAVIInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IGetAVIInfo * This,
            /* [in] */ BSTR file_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IGetAVIInfo * This,
            /* [out] */ BSTR *file_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoStreamNumber )( 
            IGetAVIInfo * This,
            /* [out] */ long *num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioStreamNumber )( 
            IGetAVIInfo * This,
            /* [out] */ long *num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoStreamInfo )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info,
            /* [out] */ long *size_infoex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioStreamInfo )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameNumber )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [out] */ long *frame_count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkNumber )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [out] */ long *chunk_count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameInfo )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkInfo )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFormatInfo )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioFormatInfo )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoExtFormatInfo )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioSampleInfo )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [in] */ UINT sample_number,
            /* [out] */ UINT *chunk_num,
            /* [out] */ UINT *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMainHeader )( 
            IGetAVIInfo * This,
            /* [length_is][size_is][out] */ BYTE *buffer,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameInfo2 )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkInfo2 )( 
            IGetAVIInfo * This,
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FastLoad )( 
            IGetAVIInfo * This,
            /* [in] */ BSTR file_name);
        
        END_INTERFACE
    } IGetAVIInfoVtbl;

    interface IGetAVIInfo
    {
        CONST_VTBL struct IGetAVIInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetAVIInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetAVIInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetAVIInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetAVIInfo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGetAVIInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGetAVIInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGetAVIInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGetAVIInfo_Load(This,file_name)	\
    ( (This)->lpVtbl -> Load(This,file_name) ) 

#define IGetAVIInfo_GetName(This,file_name)	\
    ( (This)->lpVtbl -> GetName(This,file_name) ) 

#define IGetAVIInfo_GetVideoStreamNumber(This,num)	\
    ( (This)->lpVtbl -> GetVideoStreamNumber(This,num) ) 

#define IGetAVIInfo_GetAudioStreamNumber(This,num)	\
    ( (This)->lpVtbl -> GetAudioStreamNumber(This,num) ) 

#define IGetAVIInfo_GetVideoStreamInfo(This,index,stream_header,size,ln,size_info,size_infoex)	\
    ( (This)->lpVtbl -> GetVideoStreamInfo(This,index,stream_header,size,ln,size_info,size_infoex) ) 

#define IGetAVIInfo_GetAudioStreamInfo(This,index,stream_header,size,ln,size_info)	\
    ( (This)->lpVtbl -> GetAudioStreamInfo(This,index,stream_header,size,ln,size_info) ) 

#define IGetAVIInfo_GetVideoFrameNumber(This,index,frame_count)	\
    ( (This)->lpVtbl -> GetVideoFrameNumber(This,index,frame_count) ) 

#define IGetAVIInfo_GetAudioChunkNumber(This,index,chunk_count)	\
    ( (This)->lpVtbl -> GetAudioChunkNumber(This,index,chunk_count) ) 

#define IGetAVIInfo_GetVideoFrameInfo(This,index,frame_number,hi_offset,low_offset,size)	\
    ( (This)->lpVtbl -> GetVideoFrameInfo(This,index,frame_number,hi_offset,low_offset,size) ) 

#define IGetAVIInfo_GetAudioChunkInfo(This,index,chunk_number,hi_offset,low_offset,size)	\
    ( (This)->lpVtbl -> GetAudioChunkInfo(This,index,chunk_number,hi_offset,low_offset,size) ) 

#define IGetAVIInfo_GetVideoFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetVideoFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfo_GetAudioFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetAudioFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfo_GetVideoExtFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetVideoExtFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfo_GetAudioSampleInfo(This,index,sample_number,chunk_num,offset)	\
    ( (This)->lpVtbl -> GetAudioSampleInfo(This,index,sample_number,chunk_num,offset) ) 

#define IGetAVIInfo_GetMainHeader(This,buffer,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetMainHeader(This,buffer,buf_size,copy_size) ) 

#define IGetAVIInfo_GetVideoFrameInfo2(This,index,frame_number,hi_offset,low_offset,size,flags)	\
    ( (This)->lpVtbl -> GetVideoFrameInfo2(This,index,frame_number,hi_offset,low_offset,size,flags) ) 

#define IGetAVIInfo_GetAudioChunkInfo2(This,index,chunk_number,hi_offset,low_offset,size,flags)	\
    ( (This)->lpVtbl -> GetAudioChunkInfo2(This,index,chunk_number,hi_offset,low_offset,size,flags) ) 

#define IGetAVIInfo_FastLoad(This,file_name)	\
    ( (This)->lpVtbl -> FastLoad(This,file_name) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetAVIInfo_INTERFACE_DEFINED__ */


#ifndef __IGetAVIInfo2_INTERFACE_DEFINED__
#define __IGetAVIInfo2_INTERFACE_DEFINED__

/* interface IGetAVIInfo2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGetAVIInfo2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0B2189C1-8738-4959-AF7A-B6B86AD0644D")
    IGetAVIInfo2 : public IGetAVIInfo
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FastLoadStream( 
            /* [in] */ BSTR file_name,
            /* [in] */ IUnknown *pIStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetAVIInfo2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetAVIInfo2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetAVIInfo2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetAVIInfo2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGetAVIInfo2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGetAVIInfo2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGetAVIInfo2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IGetAVIInfo2 * This,
            /* [in] */ BSTR file_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IGetAVIInfo2 * This,
            /* [out] */ BSTR *file_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoStreamNumber )( 
            IGetAVIInfo2 * This,
            /* [out] */ long *num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioStreamNumber )( 
            IGetAVIInfo2 * This,
            /* [out] */ long *num);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoStreamInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info,
            /* [out] */ long *size_infoex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioStreamInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *stream_header,
            /* [in] */ long size,
            /* [out] */ long *ln,
            /* [out] */ long *size_info);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameNumber )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [out] */ long *frame_count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkNumber )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [out] */ long *chunk_count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFormatInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioFormatInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoExtFormatInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [length_is][size_is][out] */ BYTE *format_info,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioSampleInfo )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [in] */ UINT sample_number,
            /* [out] */ UINT *chunk_num,
            /* [out] */ UINT *offset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMainHeader )( 
            IGetAVIInfo2 * This,
            /* [length_is][size_is][out] */ BYTE *buffer,
            /* [in] */ long buf_size,
            /* [out] */ long *copy_size);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFrameInfo2 )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [in] */ long frame_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunkInfo2 )( 
            IGetAVIInfo2 * This,
            /* [in] */ long index,
            /* [in] */ long chunk_number,
            /* [out] */ long *hi_offset,
            /* [out] */ ULONG *low_offset,
            /* [out] */ ULONG *size,
            /* [out] */ ULONG *flags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FastLoad )( 
            IGetAVIInfo2 * This,
            /* [in] */ BSTR file_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FastLoadStream )( 
            IGetAVIInfo2 * This,
            /* [in] */ BSTR file_name,
            /* [in] */ IUnknown *pIStream);
        
        END_INTERFACE
    } IGetAVIInfo2Vtbl;

    interface IGetAVIInfo2
    {
        CONST_VTBL struct IGetAVIInfo2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetAVIInfo2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetAVIInfo2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetAVIInfo2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetAVIInfo2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGetAVIInfo2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGetAVIInfo2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGetAVIInfo2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGetAVIInfo2_Load(This,file_name)	\
    ( (This)->lpVtbl -> Load(This,file_name) ) 

#define IGetAVIInfo2_GetName(This,file_name)	\
    ( (This)->lpVtbl -> GetName(This,file_name) ) 

#define IGetAVIInfo2_GetVideoStreamNumber(This,num)	\
    ( (This)->lpVtbl -> GetVideoStreamNumber(This,num) ) 

#define IGetAVIInfo2_GetAudioStreamNumber(This,num)	\
    ( (This)->lpVtbl -> GetAudioStreamNumber(This,num) ) 

#define IGetAVIInfo2_GetVideoStreamInfo(This,index,stream_header,size,ln,size_info,size_infoex)	\
    ( (This)->lpVtbl -> GetVideoStreamInfo(This,index,stream_header,size,ln,size_info,size_infoex) ) 

#define IGetAVIInfo2_GetAudioStreamInfo(This,index,stream_header,size,ln,size_info)	\
    ( (This)->lpVtbl -> GetAudioStreamInfo(This,index,stream_header,size,ln,size_info) ) 

#define IGetAVIInfo2_GetVideoFrameNumber(This,index,frame_count)	\
    ( (This)->lpVtbl -> GetVideoFrameNumber(This,index,frame_count) ) 

#define IGetAVIInfo2_GetAudioChunkNumber(This,index,chunk_count)	\
    ( (This)->lpVtbl -> GetAudioChunkNumber(This,index,chunk_count) ) 

#define IGetAVIInfo2_GetVideoFrameInfo(This,index,frame_number,hi_offset,low_offset,size)	\
    ( (This)->lpVtbl -> GetVideoFrameInfo(This,index,frame_number,hi_offset,low_offset,size) ) 

#define IGetAVIInfo2_GetAudioChunkInfo(This,index,chunk_number,hi_offset,low_offset,size)	\
    ( (This)->lpVtbl -> GetAudioChunkInfo(This,index,chunk_number,hi_offset,low_offset,size) ) 

#define IGetAVIInfo2_GetVideoFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetVideoFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfo2_GetAudioFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetAudioFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfo2_GetVideoExtFormatInfo(This,index,format_info,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetVideoExtFormatInfo(This,index,format_info,buf_size,copy_size) ) 

#define IGetAVIInfo2_GetAudioSampleInfo(This,index,sample_number,chunk_num,offset)	\
    ( (This)->lpVtbl -> GetAudioSampleInfo(This,index,sample_number,chunk_num,offset) ) 

#define IGetAVIInfo2_GetMainHeader(This,buffer,buf_size,copy_size)	\
    ( (This)->lpVtbl -> GetMainHeader(This,buffer,buf_size,copy_size) ) 

#define IGetAVIInfo2_GetVideoFrameInfo2(This,index,frame_number,hi_offset,low_offset,size,flags)	\
    ( (This)->lpVtbl -> GetVideoFrameInfo2(This,index,frame_number,hi_offset,low_offset,size,flags) ) 

#define IGetAVIInfo2_GetAudioChunkInfo2(This,index,chunk_number,hi_offset,low_offset,size,flags)	\
    ( (This)->lpVtbl -> GetAudioChunkInfo2(This,index,chunk_number,hi_offset,low_offset,size,flags) ) 

#define IGetAVIInfo2_FastLoad(This,file_name)	\
    ( (This)->lpVtbl -> FastLoad(This,file_name) ) 


#define IGetAVIInfo2_FastLoadStream(This,file_name,pIStream)	\
    ( (This)->lpVtbl -> FastLoadStream(This,file_name,pIStream) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetAVIInfo2_INTERFACE_DEFINED__ */


#ifndef __IGetAVIInfoArray_INTERFACE_DEFINED__
#define __IGetAVIInfoArray_INTERFACE_DEFINED__

/* interface IGetAVIInfoArray */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGetAVIInfoArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B663AC9-1532-4f32-8631-EDBF22440DF4")
    IGetAVIInfoArray : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVideoFramesInfo( 
            /* [in] */ long index,
            /* [in] */ long start_frame,
            /* [in] */ long frames_count,
            /* [size_is][out] */ IndexFileEntry *info,
            /* [size_is][out] */ long *hi_offset) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAudioChunksInfo( 
            /* [in] */ long index,
            /* [in] */ long start_chunk,
            /* [in] */ long chunks_count,
            /* [size_is][out] */ IndexFileEntry *info,
            /* [size_is][out] */ long *hi_offset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetAVIInfoArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetAVIInfoArray * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetAVIInfoArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetAVIInfoArray * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVideoFramesInfo )( 
            IGetAVIInfoArray * This,
            /* [in] */ long index,
            /* [in] */ long start_frame,
            /* [in] */ long frames_count,
            /* [size_is][out] */ IndexFileEntry *info,
            /* [size_is][out] */ long *hi_offset);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAudioChunksInfo )( 
            IGetAVIInfoArray * This,
            /* [in] */ long index,
            /* [in] */ long start_chunk,
            /* [in] */ long chunks_count,
            /* [size_is][out] */ IndexFileEntry *info,
            /* [size_is][out] */ long *hi_offset);
        
        END_INTERFACE
    } IGetAVIInfoArrayVtbl;

    interface IGetAVIInfoArray
    {
        CONST_VTBL struct IGetAVIInfoArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetAVIInfoArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetAVIInfoArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetAVIInfoArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetAVIInfoArray_GetVideoFramesInfo(This,index,start_frame,frames_count,info,hi_offset)	\
    ( (This)->lpVtbl -> GetVideoFramesInfo(This,index,start_frame,frames_count,info,hi_offset) ) 

#define IGetAVIInfoArray_GetAudioChunksInfo(This,index,start_chunk,chunks_count,info,hi_offset)	\
    ( (This)->lpVtbl -> GetAudioChunksInfo(This,index,start_chunk,chunks_count,info,hi_offset) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetAVIInfoArray_INTERFACE_DEFINED__ */


#ifndef __IGetAVIInfoEx_INTERFACE_DEFINED__
#define __IGetAVIInfoEx_INTERFACE_DEFINED__

/* interface IGetAVIInfoEx */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGetAVIInfoEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F8CA2B89-3B58-497e-A8FA-CAD6F67DD7AD")
    IGetAVIInfoEx : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadMBSTR( 
            /* [size_is][in] */ CHAR *file_name,
            /* [in] */ long size,
            /* [defaultvalue][in] */ long bFastLoad = 1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetAVIInfoExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetAVIInfoEx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetAVIInfoEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetAVIInfoEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadMBSTR )( 
            IGetAVIInfoEx * This,
            /* [size_is][in] */ CHAR *file_name,
            /* [in] */ long size,
            /* [defaultvalue][in] */ long bFastLoad);
        
        END_INTERFACE
    } IGetAVIInfoExVtbl;

    interface IGetAVIInfoEx
    {
        CONST_VTBL struct IGetAVIInfoExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetAVIInfoEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetAVIInfoEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetAVIInfoEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetAVIInfoEx_LoadMBSTR(This,file_name,size,bFastLoad)	\
    ( (This)->lpVtbl -> LoadMBSTR(This,file_name,size,bFastLoad) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetAVIInfoEx_INTERFACE_DEFINED__ */


#ifndef __IGetDVAudio_INTERFACE_DEFINED__
#define __IGetDVAudio_INTERFACE_DEFINED__

/* interface IGetDVAudio */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGetDVAudio;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6918976-06A3-4899-ACF7-4060DDE9569E")
    IGetDVAudio : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAudioFormat( 
            /* [size_is][out] */ BYTE *pWFX,
            /* [in] */ long nFmtSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAudioBufSize( 
            /* [out] */ long *pnAudioBufSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetChunkBufSize( 
            /* [out] */ long *pnFrameBufSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumChunkByTime( 
            /* [in] */ double dMarkInSec,
            /* [out] */ long *pnChunk,
            /* [out] */ long *nSkipOutBytes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumChunkBySample( 
            /* [in] */ long nSample,
            /* [out] */ long *pnChunk,
            /* [out] */ long *nSkipOutBytes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ExtractAudio( 
            /* [in] */ long nChunk,
            /* [size_is][in] */ BYTE *pDVData,
            /* [in] */ long nDVSize,
            /* [size_is][out] */ BYTE *pAudioData,
            /* [in] */ long nAudioBufSize,
            /* [out] */ long *pnAudioDataSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetDVAudioVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetDVAudio * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetDVAudio * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetDVAudio * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAudioFormat )( 
            IGetDVAudio * This,
            /* [size_is][out] */ BYTE *pWFX,
            /* [in] */ long nFmtSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAudioBufSize )( 
            IGetDVAudio * This,
            /* [out] */ long *pnAudioBufSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetChunkBufSize )( 
            IGetDVAudio * This,
            /* [out] */ long *pnFrameBufSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumChunkByTime )( 
            IGetDVAudio * This,
            /* [in] */ double dMarkInSec,
            /* [out] */ long *pnChunk,
            /* [out] */ long *nSkipOutBytes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumChunkBySample )( 
            IGetDVAudio * This,
            /* [in] */ long nSample,
            /* [out] */ long *pnChunk,
            /* [out] */ long *nSkipOutBytes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ExtractAudio )( 
            IGetDVAudio * This,
            /* [in] */ long nChunk,
            /* [size_is][in] */ BYTE *pDVData,
            /* [in] */ long nDVSize,
            /* [size_is][out] */ BYTE *pAudioData,
            /* [in] */ long nAudioBufSize,
            /* [out] */ long *pnAudioDataSize);
        
        END_INTERFACE
    } IGetDVAudioVtbl;

    interface IGetDVAudio
    {
        CONST_VTBL struct IGetDVAudioVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetDVAudio_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetDVAudio_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetDVAudio_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetDVAudio_GetAudioFormat(This,pWFX,nFmtSize)	\
    ( (This)->lpVtbl -> GetAudioFormat(This,pWFX,nFmtSize) ) 

#define IGetDVAudio_GetAudioBufSize(This,pnAudioBufSize)	\
    ( (This)->lpVtbl -> GetAudioBufSize(This,pnAudioBufSize) ) 

#define IGetDVAudio_GetChunkBufSize(This,pnFrameBufSize)	\
    ( (This)->lpVtbl -> GetChunkBufSize(This,pnFrameBufSize) ) 

#define IGetDVAudio_GetNumChunkByTime(This,dMarkInSec,pnChunk,nSkipOutBytes)	\
    ( (This)->lpVtbl -> GetNumChunkByTime(This,dMarkInSec,pnChunk,nSkipOutBytes) ) 

#define IGetDVAudio_GetNumChunkBySample(This,nSample,pnChunk,nSkipOutBytes)	\
    ( (This)->lpVtbl -> GetNumChunkBySample(This,nSample,pnChunk,nSkipOutBytes) ) 

#define IGetDVAudio_ExtractAudio(This,nChunk,pDVData,nDVSize,pAudioData,nAudioBufSize,pnAudioDataSize)	\
    ( (This)->lpVtbl -> ExtractAudio(This,nChunk,pDVData,nDVSize,pAudioData,nAudioBufSize,pnAudioDataSize) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetDVAudio_INTERFACE_DEFINED__ */


#ifndef __IGetDVInfo_INTERFACE_DEFINED__
#define __IGetDVInfo_INTERFACE_DEFINED__

/* interface IGetDVInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGetDVInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8CE4A353-53FB-448d-9FFC-8867140F4096")
    IGetDVInfo : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAspectRatio( 
            /* [in] */ long nFrameSize,
            /* [size_is][in] */ BYTE *pFrameData,
            /* [out] */ BOOL *pb16_9,
            /* [out] */ BYTE *pARFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFrameAspectRatio( 
            /* [in] */ long nFrame,
            /* [out] */ BOOL *pb16_9,
            /* [out] */ BYTE *pARFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTimeCode( 
            /* [in] */ long nFrameSize,
            /* [size_is][in] */ BYTE *pFrameData,
            /* [out] */ long *pnHour,
            /* [out] */ long *pnMin,
            /* [out] */ long *pnSec,
            /* [out] */ long *pnFr) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFrameTimeCode( 
            /* [in] */ long nFrame,
            /* [out] */ long *pnHour,
            /* [out] */ long *pnMin,
            /* [out] */ long *pnSec,
            /* [out] */ long *pnFr) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRecDateTime( 
            /* [in] */ long nFrameSize,
            /* [size_is][in] */ BYTE *pFrameData,
            /* [out] */ long *pnYear,
            /* [out] */ long *pnMonth,
            /* [out] */ long *pnDay,
            /* [out] */ long *pnHour,
            /* [out] */ long *pnMin,
            /* [out] */ long *pnSec) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFrameRecDateTime( 
            /* [in] */ long nFrame,
            /* [out] */ long *pnYear,
            /* [out] */ long *pnMonth,
            /* [out] */ long *pnDay,
            /* [out] */ long *pnHour,
            /* [out] */ long *pnMin,
            /* [out] */ long *pnSec) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetDVInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGetDVInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGetDVInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGetDVInfo * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAspectRatio )( 
            IGetDVInfo * This,
            /* [in] */ long nFrameSize,
            /* [size_is][in] */ BYTE *pFrameData,
            /* [out] */ BOOL *pb16_9,
            /* [out] */ BYTE *pARFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFrameAspectRatio )( 
            IGetDVInfo * This,
            /* [in] */ long nFrame,
            /* [out] */ BOOL *pb16_9,
            /* [out] */ BYTE *pARFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTimeCode )( 
            IGetDVInfo * This,
            /* [in] */ long nFrameSize,
            /* [size_is][in] */ BYTE *pFrameData,
            /* [out] */ long *pnHour,
            /* [out] */ long *pnMin,
            /* [out] */ long *pnSec,
            /* [out] */ long *pnFr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFrameTimeCode )( 
            IGetDVInfo * This,
            /* [in] */ long nFrame,
            /* [out] */ long *pnHour,
            /* [out] */ long *pnMin,
            /* [out] */ long *pnSec,
            /* [out] */ long *pnFr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRecDateTime )( 
            IGetDVInfo * This,
            /* [in] */ long nFrameSize,
            /* [size_is][in] */ BYTE *pFrameData,
            /* [out] */ long *pnYear,
            /* [out] */ long *pnMonth,
            /* [out] */ long *pnDay,
            /* [out] */ long *pnHour,
            /* [out] */ long *pnMin,
            /* [out] */ long *pnSec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFrameRecDateTime )( 
            IGetDVInfo * This,
            /* [in] */ long nFrame,
            /* [out] */ long *pnYear,
            /* [out] */ long *pnMonth,
            /* [out] */ long *pnDay,
            /* [out] */ long *pnHour,
            /* [out] */ long *pnMin,
            /* [out] */ long *pnSec);
        
        END_INTERFACE
    } IGetDVInfoVtbl;

    interface IGetDVInfo
    {
        CONST_VTBL struct IGetDVInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetDVInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGetDVInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGetDVInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGetDVInfo_GetAspectRatio(This,nFrameSize,pFrameData,pb16_9,pARFlags)	\
    ( (This)->lpVtbl -> GetAspectRatio(This,nFrameSize,pFrameData,pb16_9,pARFlags) ) 

#define IGetDVInfo_GetFrameAspectRatio(This,nFrame,pb16_9,pARFlags)	\
    ( (This)->lpVtbl -> GetFrameAspectRatio(This,nFrame,pb16_9,pARFlags) ) 

#define IGetDVInfo_GetTimeCode(This,nFrameSize,pFrameData,pnHour,pnMin,pnSec,pnFr)	\
    ( (This)->lpVtbl -> GetTimeCode(This,nFrameSize,pFrameData,pnHour,pnMin,pnSec,pnFr) ) 

#define IGetDVInfo_GetFrameTimeCode(This,nFrame,pnHour,pnMin,pnSec,pnFr)	\
    ( (This)->lpVtbl -> GetFrameTimeCode(This,nFrame,pnHour,pnMin,pnSec,pnFr) ) 

#define IGetDVInfo_GetRecDateTime(This,nFrameSize,pFrameData,pnYear,pnMonth,pnDay,pnHour,pnMin,pnSec)	\
    ( (This)->lpVtbl -> GetRecDateTime(This,nFrameSize,pFrameData,pnYear,pnMonth,pnDay,pnHour,pnMin,pnSec) ) 

#define IGetDVInfo_GetFrameRecDateTime(This,nFrame,pnYear,pnMonth,pnDay,pnHour,pnMin,pnSec)	\
    ( (This)->lpVtbl -> GetFrameRecDateTime(This,nFrame,pnYear,pnMonth,pnDay,pnHour,pnMin,pnSec) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGetDVInfo_INTERFACE_DEFINED__ */



#ifndef __GETAVIINFOLib_LIBRARY_DEFINED__
#define __GETAVIINFOLib_LIBRARY_DEFINED__

/* library GETAVIINFOLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_GETAVIINFOLib;

EXTERN_C const CLSID CLSID_GetAVIInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("568DF44F-DEAC-11D3-BBEE-0000B4908D28")
GetAVIInfo;
#endif
#endif /* __GETAVIINFOLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


