#include <cstdio>
#include "TCHAR.h"
#include "CTh11Config.h"

const int CTh11Config::nDefaultNameBlt = CTh11Config::NAME_BLT_EN;
const int CTh11Config::nDefaultCommentBlt = CTh11Config::COMMENT_BLT_ALL;

CTh11Config::CTh11Config()
	: nNameBlt(nDefaultNameBlt), nCommentBlt(nDefaultCommentBlt)
{
}

CTh11Config::CTh11Config(int nNameBlt, int nCommentBlt)
	: nNameBlt(nDefaultNameBlt), nCommentBlt(nDefaultCommentBlt)
{
	this->SetNameBlt(nNameBlt);
	this->SetCommentBlt(nCommentBlt);
}

CTh11Config::~CTh11Config()
{
}

bool CTh11Config::Load(HINSTANCE hInstance)
{
	TCHAR szAppName[_MAX_FNAME];
	TCHAR szIniPath[_MAX_PATH];

	if (!IConfig::GetFilenames(hInstance, szAppName, szIniPath))
		return false;

	this->SetNameBlt(::GetPrivateProfileInt(szAppName, TEXT("NameBlt"), nDefaultNameBlt, szIniPath));
	this->SetCommentBlt(::GetPrivateProfileInt(szAppName, TEXT("CommentBlt"), nDefaultCommentBlt, szIniPath));

	return true;
}

bool CTh11Config::Save(HINSTANCE hInstance)
{
	TCHAR szAppName[_MAX_FNAME];
	TCHAR szIniPath[_MAX_PATH];

	if (!IConfig::GetFilenames(hInstance, szAppName, szIniPath))
		return false;

	TCHAR szValue[2];
	size_t nWroteChars;
	BOOL retval;

	nWroteChars = ::_stprintf_s(szValue, TEXT("%d"), this->nNameBlt);
	if (nWroteChars != 1)
		return false;
	retval = ::WritePrivateProfileString(szAppName, TEXT("NameBlt"), szValue, szIniPath);
	if (retval != TRUE)
		return false;

	nWroteChars = ::_stprintf_s(szValue, TEXT("%d"), this->nCommentBlt);
	if (nWroteChars != 1)
		return false;
	retval = ::WritePrivateProfileString(szAppName, TEXT("CommentBlt"), szValue, szIniPath);
	if (retval != TRUE)
		return false;

	return true;
}

int CTh11Config::GetNameBlt()
{
	return this->nNameBlt;
}

int CTh11Config::GetCommentBlt()
{
	return this->nCommentBlt;
}

bool CTh11Config::SetNameBlt(int nNameBlt)
{
	switch (nNameBlt)
	{
	case NAME_BLT_EN:
	case NAME_BLT_JA_FULL:
	case NAME_BLT_JA_REPLAY:
		this->nNameBlt = nNameBlt;
		return true;
	default:
		return false;
	}
}

bool CTh11Config::SetCommentBlt(int nCommentBlt)
{
	switch (nCommentBlt)
	{
	case COMMENT_BLT_ALL:
	case COMMENT_BLT_FIRST:
	case COMMENT_BLT_CONCAT:
		this->nCommentBlt = nCommentBlt;
		return true;
	default:
		return false;
	}
}
