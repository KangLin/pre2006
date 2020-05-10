/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 19 20:11:17 2006
 */
/* Compiler settings for d:\Programe\VC\Macro\MicrosoftDevelopmentEnvironmentExtendTools\MicrosoftDevelopmentEnvironmentExtendTools.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __MicrosoftDevelopmentEnvironmentExtendToolsTypes_h__
#define __MicrosoftDevelopmentEnvironmentExtendToolsTypes_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICommands_FWD_DEFINED__
#define __ICommands_FWD_DEFINED__
typedef interface ICommands ICommands;
#endif 	/* __ICommands_FWD_DEFINED__ */


#ifndef __Commands_FWD_DEFINED__
#define __Commands_FWD_DEFINED__

#ifdef __cplusplus
typedef class Commands Commands;
#else
typedef struct Commands Commands;
#endif /* __cplusplus */

#endif 	/* __Commands_FWD_DEFINED__ */


#ifndef __ApplicationEvents_FWD_DEFINED__
#define __ApplicationEvents_FWD_DEFINED__

#ifdef __cplusplus
typedef class ApplicationEvents ApplicationEvents;
#else
typedef struct ApplicationEvents ApplicationEvents;
#endif /* __cplusplus */

#endif 	/* __ApplicationEvents_FWD_DEFINED__ */


#ifndef __DebuggerEvents_FWD_DEFINED__
#define __DebuggerEvents_FWD_DEFINED__

#ifdef __cplusplus
typedef class DebuggerEvents DebuggerEvents;
#else
typedef struct DebuggerEvents DebuggerEvents;
#endif /* __cplusplus */

#endif 	/* __DebuggerEvents_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __MicrosoftDevelopmentEnvironmentExtendTools_LIBRARY_DEFINED__
#define __MicrosoftDevelopmentEnvironmentExtendTools_LIBRARY_DEFINED__

/* library MicrosoftDevelopmentEnvironmentExtendTools */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_MicrosoftDevelopmentEnvironmentExtendTools,0x26EC7BA1,0x4949,0x4FF6,0x8A,0xC7,0x7A,0x6A,0xA0,0x99,0xD2,0x03);

#ifndef __ICommands_INTERFACE_DEFINED__
#define __ICommands_INTERFACE_DEFINED__

/* interface ICommands */
/* [object][dual][oleautomation][uuid] */ 


DEFINE_GUID(IID_ICommands,0xF5439B9A,0xA468,0x4137,0x88,0x8C,0x9D,0x3C,0xED,0xFE,0xF8,0x43);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5439B9A-A468-4137-888C-9D3CEDFEF843")
    ICommands : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AutoDispayMarcoOrConst( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SwitchHCpp( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OpenRCAsText( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IncludeFile( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AutoFormatCCode( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICommands __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICommands __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICommands __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICommands __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICommands __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutoDispayMarcoOrConst )( 
            ICommands __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SwitchHCpp )( 
            ICommands __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenRCAsText )( 
            ICommands __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IncludeFile )( 
            ICommands __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutoFormatCCode )( 
            ICommands __RPC_FAR * This);
        
        END_INTERFACE
    } ICommandsVtbl;

    interface ICommands
    {
        CONST_VTBL struct ICommandsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommands_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommands_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommands_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommands_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICommands_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICommands_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICommands_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICommands_AutoDispayMarcoOrConst(This)	\
    (This)->lpVtbl -> AutoDispayMarcoOrConst(This)

#define ICommands_SwitchHCpp(This)	\
    (This)->lpVtbl -> SwitchHCpp(This)

#define ICommands_OpenRCAsText(This)	\
    (This)->lpVtbl -> OpenRCAsText(This)

#define ICommands_IncludeFile(This)	\
    (This)->lpVtbl -> IncludeFile(This)

#define ICommands_AutoFormatCCode(This)	\
    (This)->lpVtbl -> AutoFormatCCode(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_AutoDispayMarcoOrConst_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_AutoDispayMarcoOrConst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_SwitchHCpp_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_SwitchHCpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_OpenRCAsText_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_OpenRCAsText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_IncludeFile_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_IncludeFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICommands_AutoFormatCCode_Proxy( 
    ICommands __RPC_FAR * This);


void __RPC_STUB ICommands_AutoFormatCCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommands_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Commands,0x6867FF16,0x93CC,0x454F,0xAC,0x3D,0x79,0x42,0x31,0x08,0x10,0x80);

#ifdef __cplusplus

class DECLSPEC_UUID("6867FF16-93CC-454F-AC3D-794231081080")
Commands;
#endif

DEFINE_GUID(CLSID_ApplicationEvents,0x369A7FCF,0xA911,0x4717,0x91,0x40,0x59,0x60,0x69,0xBB,0x24,0x28);

#ifdef __cplusplus

class DECLSPEC_UUID("369A7FCF-A911-4717-9140-596069BB2428")
ApplicationEvents;
#endif

DEFINE_GUID(CLSID_DebuggerEvents,0xE8FD6E23,0xC741,0x4365,0x91,0x40,0xD7,0x8F,0xA1,0x44,0xD1,0x7B);

#ifdef __cplusplus

class DECLSPEC_UUID("E8FD6E23-C741-4365-9140-D78FA144D17B")
DebuggerEvents;
#endif
#endif /* __MicrosoftDevelopmentEnvironmentExtendTools_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
