#pragma once
struct Request;


class CInventory
{
public:
	CInventory();
	virtual ~CInventory();

public:
	virtual void Delete(Request* request);
	virtual void Load(Request* request);
	virtual void Save(Request* request);
	virtual int OnRequest(Request* request);
};
