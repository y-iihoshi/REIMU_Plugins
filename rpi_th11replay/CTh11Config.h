#pragma once

#include "..\rpi_threplay\IConfig.h"

class CTh11Config : public IConfig
{
public:
	enum NameBltType
	{
		NAME_BLT_EN = 0,
		NAME_BLT_JA_FULL,
		NAME_BLT_JA_REPLAY
	};

	enum CommentBltType
	{
		COMMENT_BLT_ALL = 0,
		COMMENT_BLT_FIRST,
		COMMENT_BLT_CONCAT
	};

private:
	int nNameBlt;
	int nCommentBlt;

public:
	static const int nDefaultNameBlt;
	static const int nDefaultCommentBlt;

public:
	CTh11Config();
	CTh11Config(int nNameBlt, int nCommentBlt);
	~CTh11Config();

	bool Load(HINSTANCE hInstance);
	bool Save(HINSTANCE hInstance);

	int GetNameBlt();
	int GetCommentBlt();
	bool SetNameBlt(int nNameBlt);
	bool SetCommentBlt(int nCommentBlt);
};
