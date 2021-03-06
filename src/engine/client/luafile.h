#ifndef ENGINE_CLIENT_LUAFILE_H
#define ENGINE_CLIENT_LUAFILE_H

#if defined(FEATURE_LUA)
#include <lua.hpp>
#include <engine/external/luabridge/LuaBridge.h>
#include <engine/external/luabridge/RefCountedPtr.h>
#else
#define lua_State int
#endif

#include "base/system.h"

#if defined(FEATURE_LUA)
#define LUA_CALL_FUNC(LUA_STATE, FUNC_NAME, TYPE, RETURN, ...) { try { \
	LuaRef func = getGlobal(LUA_STATE, FUNC_NAME); \
	if(func) \
		RETURN = func(__VA_ARGS__).cast<TYPE>(); }\
	catch (std::exception& e) \
	{ printf("LUA EXCEPTION: %s\n", e.what()); } }
#else
#define LUA_CALL_FUNC(LUA_STATE, FUNC_NAME, TYPE, RETURN, ...) ;;
#endif

class IClient;
class IStorageTW;
class CLua;

class CLuaFile
{
	MACRO_ALLOC_HEAP()

	friend class CLuaBinding;
public:
	enum
	{
		STATE_ERROR=-1,
		STATE_IDLE,
		STATE_LOADED
	};

	enum
	{
		PERMISSION_IO		= 1 << 0,
		PERMISSION_DEBUG	= 1 << 1,
		PERMISSION_FFI		= 1 << 2,
		PERMISSION_OS		= 1 << 3,
		PERMISSION_PACKAGE	= 1 << 4,
		NUM_PERMISSIONS
	};

	const char *m_pErrorStr;

private:
	CLua *m_pLua;
	lua_State *m_pLuaState;
	int m_State;
	const std::string m_Filename;

	int m_PermissionFlags;

	char m_aScriptTitle[64];
	char m_aScriptInfo[128];
	bool m_ScriptHasSettings;
	bool m_ScriptAutoload;

public:
	CLuaFile(CLua *pLua, std::string Filename, bool Autoload);
	~CLuaFile();
	void Init();
	void Reset(bool error = false);
	void LoadPermissionFlags(const char *pFilename);
	void Unload(bool error = false);
#if defined(FEATURE_LUA)
	luabridge::LuaRef GetFunc(const char *pFuncName);
#endif
	template<class T> T CallFunc(const char *pFuncName);

	int State() const { return m_State; }
	int GetPermissionFlags() const { return m_PermissionFlags; }
	const char* GetFilename() const { return m_Filename.c_str(); }
	const char* GetScriptTitle() const { return m_aScriptTitle; }
	const char* GetScriptInfo() const { return m_aScriptInfo; }
	bool GetScriptHasSettings() const { return m_ScriptHasSettings; }
	bool GetScriptIsAutoload() const { return m_ScriptAutoload; }
	bool SetScriptIsAutoload(bool NewVal) { bool ret = m_ScriptAutoload; m_ScriptAutoload = NewVal; return ret; }
	lua_State *L() const { return m_pLuaState; }

	CLua *Lua() const { return m_pLua; }
	
	static void RegisterLuaCallbacks(lua_State * L);

	void LuaPrintOverride(std::string str);

private:
	void OpenLua();
	bool LoadFile(const char *pFilename);
	bool CheckCertificate(const char *pFilename);

	bool ScriptHasSettings();
};

#endif
