#pragma once
struct lua_State;


int LuaGlueFunc_Skill(lua_State* L);
int LuaGlueFunc_IsRechargeTime(lua_State* L);
int LuaGlueFunc_Attack(lua_State* L);
int LuaGlueFunc_Trace(lua_State* L);
int LuaGlueFunc_SummaryUpdate(lua_State* L);
int LuaGlueFunc_GetAttackRange(lua_State* L);
int LuaGlueFunc_Move(lua_State* L);
int LuaGlueFunc_GetCurPos(lua_State* L);
int LuaGlueFunc_Revival(lua_State* L);
int LuaGlueFunc_GetAsyncMsg(lua_State* L);
int LuaGlueFunc_GetNeighborNum(lua_State* L);
int LuaGlueFunc_timeGetTime(lua_State* L);
int LuaGlueFunc_PutMob(lua_State* L);
int LuaGlueFunc_DebugMsg(lua_State* L);
int LuaGlueFunc_GetObjects(lua_State* L);
int LuaGlueFunc_GetV(lua_State* L);
int LuaGlueFunc_Chat(lua_State* L);
int LuaGlueFunc_Emotion(lua_State* L);
int LuaGlueFunc_Teleport(lua_State* L);
int LuaGlueFunc_IsTarget(lua_State* L);
int LuaGlueFunc_GetOwnerAID(lua_State* L);
int LuaGlueFunc_IsServiceMap(lua_State* L);
