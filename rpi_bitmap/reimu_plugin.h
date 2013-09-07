// �v���O�C�����Ƃ̂��܂肫�������������镔��(Rev.2)
#ifndef _INC_REIMU_PLUGIN
#define _INC_REIMU_PLUGIN

#include <windows.h>
#include <stdio.h>


// �C�ӊ֐����g�p���邩�ǂ������`
// �g�p���Ȃ��ꍇ�̓R�����g�A�E�g���Ă�������
// (exports.def�̃R�����g�A�E�g�����Y��Ȃ���)
//#define RPI_USE_GETFILEINFOTEXT1	// GetFileInfoText1
//#define RPI_USE_GETFILEINFOTEXT2	// GetFileInfoText2
#define RPI_USE_GETFILEINFOIMAGE1	// GetFileInfoImage1
//#define RPI_USE_GETFILEINFOIMAGE2	// GetFileInfoImage2
//#define RPI_USE_EDITDIALOG			// EditDialog
//#define RPI_USE_CONFIGDIALOG		// ConfigDialog


#ifndef DLLEXPORT
# define DLLEXPORT	__declspec(dllexport)
#endif
#ifndef STDCALL
# define STDCALL	__stdcall
#endif

// �G���[�R�[�h
#define RPI_NO_FUNCTION			-1	// �������̊֐�
#define RPI_ALL_RIGHT			0	// ����I��
#define RPI_NOT_SUPPORT			1	// ���Ή��̌`��
#define RPI_FILE_READ_ERROR		2	// �t�@�C���ǂݍ��݃G���[
#define	RPI_FILE_WRITE_ERROR	3	// �t�@�C�������o���G���[
#define RPI_NO_MEMORY			4	// �������[���m�ۏo���Ȃ�
#define RPI_UNKNOWN_ERROR		5	// ���m�̃G���[
#define RPI_DIALOG_CANCELED		6	// EditDialog��ConfigDialog�ŃL�����Z�����ꂽ


// ColumnInfo::nAlign�Ŏg�����
// ���ꂾ���̂��߂�commctrl.h���C���N���[�h�������Ȃ��̂�(��
#ifndef LVCFMT_LEFT
# define LVCFMT_LEFT	0x0000
# define LVCFMT_RIGHT	0x0001
# define LVCFMT_CENTER	0x0002
#endif

// ColumnInfo::nSortType�Ŏg�����
#ifndef SORT_STRING
# define SORT_STRING	0	//	0:������\�[�g(���ڂ̒��g�����̂܂܂̕�����Ƃ��Ď������Ƀ\�[�g����)
# define SORT_NUMBER	1	//	1:�����\�[�g(���ڂ̒��g�𐮐��Ƃ݂Ȃ��ă\�[�g����
							//    atoi���������A3����؂�̃J���}�͖��������)
# define SORT_FLOAT		2	//	2:�����\�[�g(���ڂ̒��g�������Ƃ݂Ȃ��ă\�[�g����(atof�ϊ�))
# define SORT_HEX		3	//  3:16�i���\�[�g(���ڂ̒��g��16�i���Ƃ݂Ȃ��ă\�[�g����)
#endif

// ColumnInfo::nSystem�Ŏg�����
#define CLSYS_STRING			0	//	0:����(GetFileInfoList�Ŏ擾��������������̂܂ܕ\��)
#define CLSYS_PATH				1	//	1:�t�@�C���p�X
#define CLSYS_DIRECTORY			2	//	2:�t�@�C���̂���ꏊ(�f�B���N�g��)
#define CLSYS_TITLE				3	//	3:�t�@�C���^�C�g��
#define CLSYS_EXT				4	//	4:�t�@�C���̊g���q
#define CLSYS_TIME_CREATE		5	//	5:�쐬����
#define CLSYS_TIME_LASTACCESS	6	//	6:�A�N�Z�X����
#define CLSYS_TIME_LASTWRITE	7	//	7:�X�V����
#define CLSYS_FILESIZE			8	//	8:�t�@�C���T�C�Y


#pragma pack(push)
#pragma pack(1) // �\���̂̃����o���E��1�o�C�g�ɂ���

// �J�������\����
struct ColumnInfo{	// sizeof(ColumnInfo) = 128
	char szTitle[116];	// �J�����ɕ\������^�C�g��
	int nAlign; 		// �e�L�X�g�̔z�u���@
						//	0:����
						//	1:�E��
						//	2:�Z���^�����O
						// (commctrl.h�Œ�`����Ă���LVCFMT_LEFT,LVCFMT_RIGHT,
						//	LVCFMT_CENTER�Ɠ���̂��̂ł�)
	int nSortType;		// �J�������N���b�N�������̂��̗�̃\�[�g���@
						//	0:������\�[�g(���ڂ̒��g�����̂܂܂̕�����Ƃ��Ď������Ƀ\�[�g����)
						//	1:�����\�[�g(���ڂ̒��g�𐮐��Ƃ݂Ȃ��ă\�[�g����
						//	  atoi���������A3����؂�̃J���}�͖��������)
						//	2:�����\�[�g(���ڂ̒��g�������Ƃ݂Ȃ��ă\�[�g����(atof�ϊ�))
						//	3:16�i���\�[�g(���ڂ̒��g��16�i���Ƃ݂Ȃ��ă\�[�g����)
	int nSystem;		// ���X�g�r���[�ɃV�X�e������\�����邩�ǂ���
						//	0:����(GetFileInfoList�Ŏ擾��������������̂܂ܕ\��)
						//	1:�t�@�C���p�X
						//	2:�t�@�C���̂���ꏊ(�f�B���N�g��)
						//	3:�t�@�C���^�C�g��
						//	4:�t�@�C���̊g���q
						//	5:�쐬����
						//	6:�A�N�Z�X����
						//	7:�X�V����
						//  8:�t�@�C���T�C�Y
};

// ���X�g���\����
struct FileInfo{  // sizeof(FileInfo) = 512
	char szText[512];	// ���X�g�ɕ\�����镶����(ColumnInfo��nSystem��0�̎��̂ݗL��)
};

#pragma pack(pop)

// RPI�֐�
extern "C" {
	// �K�{�֐�
	int DLLEXPORT STDCALL GetPluginRevision();
	unsigned int DLLEXPORT STDCALL GetPluginInfo(int nInfoNo, char* szDst, int nDstLength);
	int DLLEXPORT STDCALL GetColumnInfo(ColumnInfo** lpInfo);
	unsigned int DLLEXPORT STDCALL IsSupported(const char* pSrc, unsigned int dwSize);
	int DLLEXPORT STDCALL GetFileInfoList(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo);

	// �C�ӊ֐�
#ifdef RPI_USE_GETFILEINFOTEXT1
	int DLLEXPORT STDCALL GetFileInfoText1(const char* pSrc, unsigned int dwSize, char** pDst);
#endif
#ifdef RPI_USE_GETFILEINFOTEXT2
	int DLLEXPORT STDCALL GetFileInfoText2(const char* pSrc, unsigned int dwSize, char** pDst);
#endif
#ifdef RPI_USE_GETFILEINFOIMAGE1
	int DLLEXPORT STDCALL GetFileInfoImage1(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo);
#endif
#ifdef RPI_USE_GETFILEINFOIMAGE2
	int DLLEXPORT STDCALL GetFileInfoImage2(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo);
#endif
#ifdef RPI_USE_EDITDIALOG
	int DLLEXPORT STDCALL EditDialog(HWND hWnd, const char* szFile);
#endif
#ifdef RPI_USE_CONFIGDIALOG
	int DLLEXPORT STDCALL ConfigDialog(HWND hWnd);
#endif

}

// GetProcAddress���鎞�ɕ֗���typedef�錾
typedef int (WINAPI *LPGETPLUGINREVISION)();
typedef unsigned int (WINAPI *LPGETPLUGININFO)(int nInfoNo, char* szDst, unsigned int dwDstLength);
typedef int (WINAPI *LPGETCOLUMNINFO)(ColumnInfo** lpInfo);
typedef unsigned int (WINAPI *LPISSUPPORTED)(const char* pSrc, unsigned int dwSize);
typedef int (WINAPI *LPGETFILEINFOLIST)(const char* pSrc, unsigned int dwSize, FileInfo** lpInfo);
typedef int (WINAPI *LPGETFILEINFOTEXT1)(const char* pSrc, unsigned int dwSize, char** pDst);
typedef int (WINAPI *LPGETFILEINFOTEXT2)(const char* pSrc, unsigned int dwSize, char** pDst);
typedef int (WINAPI *LPGETFILEINFOIMAGE1)(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo);
typedef int (WINAPI *LPGETFILEINFOIMAGE2)(const char* pSrc, unsigned int dwSize, char** pDst, BITMAPINFO** pInfo);
typedef int (WINAPI *LPEDITDIALOG)(HWND hWnd, const char* szFile);
typedef int (WINAPI *LPCONFIGDIALOG)(HWND hWnd);

#endif
