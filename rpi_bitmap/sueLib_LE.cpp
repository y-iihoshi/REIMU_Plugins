#include "sueLib_LE.h"


//=============================================================================
//		�t�@�C���T�C�Y���擾����
//=============================================================================
// input
//		szFile	: �t�@�C����
//
// return
//		�t�@�C���T�C�Y(���݂��Ȃ��ꍇ��0��Ԃ�)
//
//=============================================================================
DWORD fsize(const char* szFile)
{
	HANDLE	hf;
	DWORD	filesize;

	DWORD	ret = GetFileAttributes(szFile);
	if(ret==0xFFFFFFFF)								return 0;	// �G���[(�p�X��������Ȃ�)
	else if((ret & FILE_ATTRIBUTE_DIRECTORY) != 0)	return 0;	// �f�B���N�g��

	hf = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hf == INVALID_HANDLE_VALUE) return 0;

	filesize = GetFileSize(hf,NULL);
	CloseHandle(hf);

	if(filesize==0xFFFFFFFF)		return 0;	// GetFileSize�̃G���[

	return filesize;
}

//=============================================================================
//		�t�@�C�����烁�����ւ̊ȈՓǂݍ���
//=============================================================================
// input
//		szFile	: �t�@�C����
//		saDest	: �o�͐�
//		dwSize	: �ǂݍ��ރT�C�Y�B�t�@�C���T�C�Y������ɖ����Ȃ���΃G���[
//				  0(�ȗ���)�̎��͂Ƃ肠�����S���ǂݍ���ł���
//		bError	: �t�@�C���T�C�Y��dwSize�ɑ���Ȃ����̋���
//				  true:�G���[��Ԃ�  false:���̕������ǂݍ���(�G���[�ɂ��Ȃ�)
//
// return
//		�ǂݍ��ݐ����������ǂ���
//
//=============================================================================
bool File2Memory(const char* szFile, smart_array< char >& saDest, DWORD dwSize, bool bError)
{
	DWORD filesize = fsize(szFile);
	if(filesize==0)								return false;	// �t�@�C���T�C�Y�擾���s
	else if(dwSize>0 && filesize<dwSize){
		if(bError)	return false;		// �t�@�C���T�C�Y����������
		else		dwSize = filesize;
	}
	else if(dwSize==0 || dwSize>filesize)	dwSize = filesize;	// �����ȗ����Ƃ��̓t�@�C����S���ǂݍ���

	FILE* fp = fopen(szFile, "rb");
	if(!fp)				return false;	// �t�@�C���J���Ȃ�

	saDest.Reset(new char[dwSize], dwSize);

	// �t�@�C���ǂݍ���
	fread(saDest.GetPtr(), saDest.GetSize(), 1, fp);

	fclose(fp);

	return true;
}
