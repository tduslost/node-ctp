#ifndef N_MDUSER_H_
#define N_MDUSER_H_

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <node.h>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include <uv.h>
#include "uv_mduser.h"
#include <node_object_wrap.h>

using namespace v8;

extern bool islog;
extern void logger_cout(const char* content);
extern std::string to_string(int val);

class WrapMdUser :public node::ObjectWrap {
public:
	WrapMdUser(const FunctionCallbackInfo<Value>& args);
	~WrapMdUser(void);
	static void Connect(const FunctionCallbackInfo<Value>& args);
	static void On(const FunctionCallbackInfo<Value>& args);
	static void ReqUserLogin(const FunctionCallbackInfo<Value>& args);
	static void ReqUserLogout(const FunctionCallbackInfo<Value>& args);
	static void SubscribeMarketData(const FunctionCallbackInfo<Value>& args);
	static void UnSubscribeMarketData(const FunctionCallbackInfo<Value>& args);
	static void Disposed(const FunctionCallbackInfo<Value>& args);
	static void Init(Handle<Object> args);
	static Persistent<Function> constructor;
	void FunCallback(CbRtnField *data);
	void FunRtnCallback(int result, void* baton);
private:
	static void initEventMap();
	void pkg_cb_userlogin(Isolate*isolate,CbRtnField* data, Local<Value>cbArray[]);
	void pkg_cb_userlogout(Isolate*isolate, CbRtnField* data, Local<Value>cbArray[]);
	void pkg_cb_rspsubmarketdata(Isolate*isolate, CbRtnField* data, Local<Value>cbArray[]);
	void pkg_cb_unrspsubmarketdata(Isolate*isolate, CbRtnField* data, Local<Value>cbArray[]);
	void pkg_cb_rtndepthmarketdata(Isolate*isolate, CbRtnField* data, Local<Value>cbArray[]);
	void pkg_cb_rsperror(Isolate*isolate, CbRtnField* data, Local<Value>cbArray[]);
	Local<Value> pkg_rspinfo(Isolate*isolate, CThostFtdcRspInfoField *pRspInfo);
	uv_mduser* uvMdUser;
	int s_uuid=0;
	static std::map<const char*, int,ptrCmp> event_map;
	std::map<int, Persistent<Function, CopyablePersistentTraits<Function>> > callback_map;
	std::map<int, Persistent<Function, CopyablePersistentTraits<Function>> > fun_rtncb_map;
};

#endif
