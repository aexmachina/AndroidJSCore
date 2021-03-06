//
// JSContext.cpp
// AndroidJSCore project
//
// https://github.com/ericwlange/AndroidJSCore/
//
// Created by Eric Lange
//
/*
 Copyright (c) 2014 Eric Lange. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 - Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "JSJNI.h"

NATIVE(JSContextGroup,jlong,create) (PARAMS) {
	return (long) JSContextGroupCreate();
}

NATIVE(JSContextGroup,jlong,retain) (PARAMS,jlong group) {
	return (long) JSContextGroupRetain((JSContextGroupRef)group);
}

NATIVE(JSContextGroup,void,release) (PARAMS,jlong group) {
	JSContextGroupRelease((JSContextGroupRef) group);
}

NATIVE(JSContext,jlong,create) (PARAMS) {
	return (long) JSGlobalContextCreate((JSClassRef) NULL);
}

NATIVE(JSContext,jlong,createInGroup) (PARAMS,jlong group) {
	return (long) JSGlobalContextCreateInGroup((JSContextGroupRef) group, (JSClassRef) NULL);
}

NATIVE(JSContext,jlong,retain) (PARAMS,jlong ctx) {
	return (long) JSGlobalContextRetain((JSGlobalContextRef) ctx);
}

NATIVE(JSContext,void,release) (PARAMS,jlong ctx) {
	JSGlobalContextRelease((JSGlobalContextRef) ctx);
}

NATIVE(JSContext,jlong,getGlobalObject) (PARAMS, jlong ctx) {
	return (long) JSContextGetGlobalObject((JSContextRef) ctx);
}

NATIVE(JSContext,jlong,getGroup) (PARAMS, jlong ctx) {
	return (long)JSContextGetGroup((JSContextRef) ctx);
}

NATIVE(JSContext,jobject,evaluateScript) (PARAMS, jlong ctx, jlong script, jlong thisObject,
		jlong sourceURL, int startingLineNumber) {

	JSValueRef exception = NULL;

	jclass ret = env->FindClass("org/liquidplayer/webkit/javascriptcore/JNIReturnObject");
	jmethodID cid = env->GetMethodID(ret,"<init>","()V");
	jobject out = env->NewObject(ret, cid);

	jfieldID fid = env->GetFieldID(ret , "reference", "J");
	env->SetLongField( out, fid, (long) JSEvaluateScript((JSContextRef) ctx, (JSStringRef) script,
			(JSObjectRef) thisObject, (JSStringRef) sourceURL, startingLineNumber, &exception));

	fid = env->GetFieldID(ret , "exception", "J");
	env->SetLongField( out, fid, (long) exception);

	return out;
}

NATIVE(JSContext,jobject,checkScriptSyntax) (PARAMS, jlong ctx, jlong script,
		jlong sourceURL, int startingLineNumber) {

	JSValueRef exception = NULL;

	jclass ret = env->FindClass("org/liquidplayer/webkit/javascriptcore/JNIReturnObject");
	jmethodID cid = env->GetMethodID(ret,"<init>","()V");
	jobject out = env->NewObject(ret, cid);

	jfieldID fid = env->GetFieldID(ret , "reference", "J");
	env->SetLongField( out, fid, (long) JSCheckScriptSyntax((JSContextRef) ctx, (JSStringRef) script,
			(JSStringRef) sourceURL, startingLineNumber, &exception));

	fid = env->GetFieldID(ret , "exception", "J");
	env->SetLongField( out, fid, (long) exception);

	return out;
}

NATIVE(JSContext,void,garbageCollect) (PARAMS, jlong ctx) {
	JSGarbageCollect((JSContextRef) ctx);
}

