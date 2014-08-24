// �v���O�C�����Ƃ̂��܂肫�������������镔��(Rev.2)
#include "reimu_plugin.h"
#include "..\rpi_threplay\sueLib_LE.h"
#include "rpi_th123replay.h"


// �G���g���|�C���g
BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		LoadPlugin(hModule);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

////////////////////////
//		�K�{�֐�
////////////////////////
// �v���O�C���̃��r�W����(�d�l�ԍ�)���擾����
int STDCALL GetPluginRevision()
{
	return 2;
}

// �v���O�C���̏����擾����
unsigned int STDCALL GetPluginInfo(int nInfoNo, char* szDst, unsigned int dwDstLength)
{
	return GetPluginInfoEx(nInfoNo, szDst, dwDstLength);
}

// �J�������̎擾
int STDCALL GetColumnInfo(ColumnInfo** lpInfo)
{
	return GetColumnInfoEx(lpInfo);
}

// �Ή����Ă��邩�ǂ���(�Ή����Ă���Δ�0��Ԃ�)
unsigned int STDCALL IsSupported(const char* pSrc, unsigned int dwSize)
{
	// ���ʗp�ɍŒ���K�v�ȃo�C�g����Ԃ�
	if(pSrc==NULL){
		return HEADER_SIZE;
	}
	// ����������
	else if(dwSize){
		return IsSupportedEx(pSrc, dwSize);
	}
	// �t�@�C������
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf, HEADER_SIZE)){
			return IsSupportedEx(buf.GetPtr(), buf.GetSize(), pSrc);
		}
		return 0;
	}
}

// ���X�g�r���[�ŕ\���������擾
int STDCALL GetFileInfoList(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo)
{
	// �T�C�Y�̑傫���t�@�C���𖳑ʂɓǂݍ��ނ͓̂��쑬�x���x���Ȃ�̂ŁA
	// ������IsSupported���Ă���
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// ����������
	if(dwSize){
		return GetFileInfoListEx(pSrc, dwSize, lpInfo);
	}
	// �t�@�C������
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoListEx(buf.GetPtr(), buf.GetSize(), lpInfo, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}

////////////////////////
//		�C�ӊ֐�
////////////////////////
#ifdef RPI_USE_GETFILEINFOTEXT1
// �����̃e�L�X�g���
int STDCALL GetFileInfoText1(const char* pSrc, unsigned int dwSize, char** pDst)
{
	// �T�C�Y�̑傫���t�@�C���𖳑ʂɓǂݍ��ނ͓̂��쑬�x���x���Ȃ�̂ŁA
	// ������IsSupported���Ă���
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// ����������
	if(dwSize){
		return GetFileInfoTextEx(1, pSrc, dwSize, pDst);
	}
	// �t�@�C������
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoTextEx(1, buf.GetPtr(), buf.GetSize(), pDst, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT1

#ifdef RPI_USE_GETFILEINFOTEXT2
// �E���̃e�L�X�g���
int STDCALL GetFileInfoText2(const char* pSrc, unsigned int dwSize, char** pDst)
{
	// �T�C�Y�̑傫���t�@�C���𖳑ʂɓǂݍ��ނ͓̂��쑬�x���x���Ȃ�̂ŁA
	// ������IsSupported���Ă���
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// ����������
	if(dwSize){
		return GetFileInfoTextEx(2, pSrc, dwSize, pDst);
	}
	// �t�@�C������
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoTextEx(2, buf.GetPtr(), buf.GetSize(), pDst, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT2


#ifdef RPI_USE_GETFILEINFOIMAGE1
// �����̉摜���
int STDCALL GetFileInfoImage1(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo)
{
	// �T�C�Y�̑傫���t�@�C���𖳑ʂɓǂݍ��ނ͓̂��쑬�x���x���Ȃ�̂ŁA
	// ������IsSupported���Ă���
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// ����������
	if(dwSize){
		return GetFileInfoImageEx(1, pSrc, dwSize, pDst, pInfo);
	}
	// �t�@�C������
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoImageEx(1, buf.GetPtr(), buf.GetSize(), pDst, pInfo, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT1

#ifdef RPI_USE_GETFILEINFOIMAGE2
// �E���̉摜���
int STDCALL GetFileInfoImage2(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo)
{
	// �T�C�Y�̑傫���t�@�C���𖳑ʂɓǂݍ��ނ͓̂��쑬�x���x���Ȃ�̂ŁA
	// ������IsSupported���Ă���
	if(IsSupported(pSrc, dwSize)==0)	return RPI_NOT_SUPPORT;

	// ����������
	if(dwSize){
		return GetFileInfoImageEx(2, pSrc, dwSize, pDst, pInfo);
	}
	// �t�@�C������
	else{
		smart_array< char > buf;
		if(File2Memory(pSrc, buf)){
			return GetFileInfoImageEx(2, buf.GetPtr(), buf.GetSize(), pDst, pInfo, pSrc);
		}
		return RPI_FILE_READ_ERROR;
	}
}
#endif		// #ifdef RPI_USE_GETFILEINFOTEXT2

#ifdef RPI_USE_EDITDIALOG
// �ҏW�_�C�A���O
int STDCALL EditDialog(HWND hWnd, const char* szFile)
{
	return EditDialogEx(hWnd, szFile);
}
#endif		// #ifdef RPI_USE_EDITDIALOG

#ifdef RPI_USE_CONFIGDIALOG
// �ݒ�_�C�A���O
int STDCALL ConfigDialog(HWND hWnd)
{
	return ConfigDialogEx(hWnd);
}
#endif		// #ifdef RPI_USE_CONFIGDIALOG
