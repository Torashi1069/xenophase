#include "CMerceDB.hpp"


hook_method<int (CMerceDB::*)(int GID, HOMUN_DBINFO* info)> CMerceDB::_InsertHomunInfo(SERVER, "CMerceDB::InsertHomunInfo");
int CMerceDB::InsertHomunInfo(int GID, HOMUN_DBINFO* info)
{
	return (this->*_InsertHomunInfo)(GID, info);

	//TODO
}


hook_method<int (CMerceDB::*)(int GID, HOMUN_DBINFO* info)> CMerceDB::_SaveHomunInfo(SERVER, "CMerceDB::SaveHomunInfo");
int CMerceDB::SaveHomunInfo(int GID, HOMUN_DBINFO* info)
{
	return (this->*_SaveHomunInfo)(GID, info);

	//TODO
}


hook_method<int (CMerceDB::*)(int GID, HOMUN_DBINFO* info)> CMerceDB::_GetHomunInfo(SERVER, "CMerceDB::GetHomunInfo");
int CMerceDB::GetHomunInfo(int GID, HOMUN_DBINFO* info)
{
	return (this->*_GetHomunInfo)(GID, info);

	//TODO
}


hook_method<void (CMerceDB::*)(int GID)> CMerceDB::_DeleteHomunInfo(SERVER, "CMerceDB::DeleteHomunInfo");
void CMerceDB::DeleteHomunInfo(int GID)
{
	return (this->*_DeleteHomunInfo)(GID);

	//TODO
}


hook_method<int (CMerceDB::*)(int GID)> CMerceDB::_InsertSkill_HO(SERVER, "CMerceDB::InsertSkill_HO");
int CMerceDB::InsertSkill_HO(int GID)
{
	return (this->*_InsertSkill_HO)(GID);

	//TODO
}


hook_method<void (CMerceDB::*)(int GID, unsigned char* buf, int bufSize)> CMerceDB::_UpdateSkill_HO(SERVER, "CMerceDB::UpdateSkill_HO");
void CMerceDB::UpdateSkill_HO(int GID, unsigned char* buf, int bufSize)
{
	return (this->*_UpdateSkill_HO)(GID, buf, bufSize);

	//TODO
}


hook_method<int (CMerceDB::*)(int GID, unsigned char* buf)> CMerceDB::_GetSkill_HO(SERVER, "CMerceDB::GetSkill_HO");
int CMerceDB::GetSkill_HO(int GID, unsigned char* buf)
{
	return (this->*_GetSkill_HO)(GID, buf);

	//TODO
}


hook_method<void (CMerceDB::*)(int GID)> CMerceDB::_DeleteSkill_HO(SERVER, "CMerceDB::DeleteSkill_HO");
void CMerceDB::DeleteSkill_HO(int GID)
{
	return (this->*_DeleteSkill_HO)(GID);

	//TODO
}
