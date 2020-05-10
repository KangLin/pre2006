

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Feb 09 11:16:55 2007
 */
/* Compiler settings for .\CAD.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __CADidl_h__
#define __CADidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DCAD_FWD_DEFINED__
#define ___DCAD_FWD_DEFINED__
typedef interface _DCAD _DCAD;
#endif 	/* ___DCAD_FWD_DEFINED__ */


#ifndef ___DCADEvents_FWD_DEFINED__
#define ___DCADEvents_FWD_DEFINED__
typedef interface _DCADEvents _DCADEvents;
#endif 	/* ___DCADEvents_FWD_DEFINED__ */


#ifndef __CAD_FWD_DEFINED__
#define __CAD_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAD CAD;
#else
typedef struct CAD CAD;
#endif /* __cplusplus */

#endif 	/* __CAD_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __CADLib_LIBRARY_DEFINED__
#define __CADLib_LIBRARY_DEFINED__

/* library CADLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_CADLib;

#ifndef ___DCAD_DISPINTERFACE_DEFINED__
#define ___DCAD_DISPINTERFACE_DEFINED__

/* dispinterface _DCAD */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DCAD;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8BE7099A-B453-41F2-B525-4F8D073A0177")
    _DCAD : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DCADVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DCAD * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DCAD * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DCAD * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DCAD * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DCAD * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DCAD * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DCAD * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DCADVtbl;

    interface _DCAD
    {
        CONST_VTBL struct _DCADVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DCAD_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DCAD_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DCAD_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DCAD_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DCAD_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DCAD_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DCAD_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DCAD_DISPINTERFACE_DEFINED__ */


#ifndef ___DCADEvents_DISPINTERFACE_DEFINED__
#define ___DCADEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DCADEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DCADEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("240C81B7-FFBC-4FC6-A62E-AF83A17A4A5C")
    _DCADEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DCADEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DCADEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DCADEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DCADEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DCADEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DCADEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DCADEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DCADEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DCADEventsVtbl;

    interface _DCADEvents
    {
        CONST_VTBL struct _DCADEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DCADEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DCADEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DCADEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DCADEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DCADEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DCADEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DCADEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DCADEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CAD;

#ifdef __cplusplus

class DECLSPEC_UUID("7958C036-FFCF-4D83-9955-283EEAB9ADE3")
CAD;
#endif
#endif /* __CADLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


