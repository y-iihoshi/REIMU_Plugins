#include "StringMaps.h"

using namespace std;
using namespace Th105;

namespace
{
	map<uint16_t, string> CreateVersionMap()
	{
		map<uint16_t, string> versions;

#if 0
		versions[100] = "1.00";
		versions[101] = "1.01";
		versions[102] = "1.02";
		versions[103] = "1.03";
		versions[104] = "1.04 or 1.05";
		versions[105] = "1.05?";
#endif
		versions[106] = "1.06";

		return versions;
	}

	map<Mode, string> CreateModeMap()
	{
		map<Mode, string> modes;

		modes[Mode::Story          ] = "Story";
#if 0
		modes[Mode::Arcade         ] = "Arcade";
#endif
		modes[Mode::VsCom          ] = "vs COM";
		modes[Mode::VsPlayer       ] = "vs PLAYER";
		modes[Mode::VsNetworkHost  ] = "vs NETWORK �i�z�X�g���j";
		modes[Mode::VsNetworkClient] = "vs NETWORK �i�N���C�A���g���j";
		modes[Mode::VsNetworkWatch ] = "vs NETWORK �i�ϐ�j";

		return modes;
	}

	map<Chara, string> CreateCharacterMap()
	{
		map<Chara, string> characters;

		characters[Chara::Reimu    ] = "���� �얲";
		characters[Chara::Marisa   ] = "���J ������";
		characters[Chara::Sakuya   ] = "�\�Z�� ���";
		characters[Chara::Alice    ] = "�A���X�E�}�[�K�g���C�h";
		characters[Chara::Patchouli] = "�p�`�����[�E�m�[���b�W";
		characters[Chara::Youmu    ] = "��� �d��";
		characters[Chara::Remilia  ] = "���~���A�E�X�J�[���b�g";
		characters[Chara::Yuyuko   ] = "���s�� �H�X�q";
		characters[Chara::Yukari   ] = "���_ ��";
		characters[Chara::Suika    ] = "�ɐ� ��";
		characters[Chara::Reisen   ] = "���E�D�܉؉@�E�C�i�o";
		characters[Chara::Aya      ] = "�˖��� ��";
		characters[Chara::Komachi  ] = "����� ����";
		characters[Chara::Iku      ] = "�i�] �ߋ�";
		characters[Chara::Tenshi   ] = "��ߖ��� �V�q";

		return characters;
	}

	map<uint16_t, string> CreateSystemCardMap()
	{
		map<uint16_t, string> cards;

		cards[0] = "�u�C�������v";
		cards[1] = "�u�쌂�v";
		cards[2] = "�u�K�[�h�����v";
		cards[3] = "�u�X�y�������v";
		cards[4] = "�u�̗͉񕜁v";
		cards[5] = "�u��͉񕜁v";

		return cards;
	}

	map<Chara, map<uint16_t, string>> CreateCardMap()
	{
		map<Chara, map<uint16_t, string>> cards;

		cards[Chara::Reimu][100] = "����A�~�����b�g";
		cards[Chara::Reimu][101] = "�x���w";
		cards[Chara::Reimu][102] = "����";
		cards[Chara::Reimu][103] = "���V�r";
		cards[Chara::Reimu][104] = "�d���o�X�^�[";
		cards[Chara::Reimu][105] = "�q���w";
		cards[Chara::Reimu][106] = "��������";
		cards[Chara::Reimu][107] = "���n���V�r";
		cards[Chara::Reimu][108] = "�g�U�A�~�����b�g";
		cards[Chara::Reimu][109] = "��u�w";
		cards[Chara::Reimu][110] = "���߈���";
		cards[Chara::Reimu][200] = "�아�u���z����v";
		cards[Chara::Reimu][201] = "�_��u���z����v";
		cards[Chara::Reimu][206] = "�_�Z�u�����S���w�v";
		cards[Chara::Reimu][208] = "�아�u����Ó��v";
		cards[Chara::Reimu][209] = "�󕄁u�A�z��ʁv";
		cards[Chara::Reimu][210] = "���u�A�z�S�_�ʁv";
		cards[Chara::Reimu][214] = "�_�Z�u�V�e���_�r�v";
		cards[Chara::Reimu][219] = "�u���z�V���v";
		cards[Chara::Marisa][100] = "�E�B�b�`���C���C��";
		cards[Chara::Marisa][101] = "�~�A�Y�}�X�E�B�[�v";
		cards[Chara::Marisa][102] = "�O���E���h�X�^�[�_�X�g";
		cards[Chara::Marisa][103] = "���e�I�j�b�N�f�u��";
		cards[Chara::Marisa][104] = "���W�A���X�g���C�N";
		cards[Chara::Marisa][105] = "�o�X�L�[�X�E�B�[�p�[";
		cards[Chara::Marisa][106] = "�f�r���_���g�[�`";
		cards[Chara::Marisa][107] = "�i���[�X�p�[�N";
		cards[Chara::Marisa][108] = "�A�b�v�X�E�B�[�v";
		cards[Chara::Marisa][109] = "�X�e���~�T�C��";
		cards[Chara::Marisa][111] = "�O���[���X�v���b�h";
		cards[Chara::Marisa][200] = "�����u�}�X�^�[�X�p�[�N�v";
		cards[Chara::Marisa][202] = "���C�u�t�@�C�i���X�p�[�N�v";
		cards[Chara::Marisa][203] = "�����u�h���S�����e�I�v";
		cards[Chara::Marisa][205] = "�����u�X�^�[�_�X�g�����@���G�v";
		cards[Chara::Marisa][206] = "�����u�G�X�P�[�v�x���V�e�B�v";
		cards[Chara::Marisa][207] = "�a���u�u���C�W���O�X�^�[�v";
		cards[Chara::Marisa][208] = "�����u���e�I�j�b�N�V�����[�v";
		cards[Chara::Marisa][211] = "�����u���~�l�X�X�g���C�N�v";
		cards[Chara::Marisa][215] = "�V���u�I�[�����[�Y�T���v";
		cards[Chara::Marisa][219] = "�ח��u����₷���}�X�^�[�X�p�[�N�v";
		cards[Chara::Sakuya][100] = "�N���[�X�A�b�v�}�W�b�N";
		cards[Chara::Sakuya][101] = "�o�E���X�m�[�o�E���X";
		cards[Chara::Sakuya][102] = "�}�W�b�N�X�^�[�\�[�h";
		cards[Chara::Sakuya][103] = "�o�j�V���O�G�u���V���O";
		cards[Chara::Sakuya][104] = "�v���y�����O�V���o�[";
		cards[Chara::Sakuya][105] = "�X�N�E�F�A���R�V�F";
		cards[Chara::Sakuya][106] = "�����̌�";
		cards[Chara::Sakuya][107] = "�p�[�t�F�N�g���C�h";
		cards[Chara::Sakuya][200] = "�����u�E�l�h�[���v";
		cards[Chara::Sakuya][201] = "�����u�v���C�x�[�g�X�N�E�F�A�v";
		cards[Chara::Sakuya][202] = "�����u�C���X�N���C�u���b�h�\�E���v";
		cards[Chara::Sakuya][203] = "�����u�閶�̌��e�E�l�S�v";
		cards[Chara::Sakuya][204] = "�u���̐��E�v";
		cards[Chara::Sakuya][205] = "�����u�\�E���X�J���v�`���A�v";
		cards[Chara::Sakuya][206] = "�╄�u�V���o�[�o�E���h�v";
		cards[Chara::Sakuya][207] = "��p�u�G�^�[�i���~�[�N�v";
		cards[Chara::Sakuya][208] = "�����u���~�l�X���R�V�F�v";
		cards[Chara::Sakuya][209] = "�����u�������X�g�b�v�E�H�b�`�v";
		cards[Chara::Alice][100] = "�l�`���n";
		cards[Chara::Alice][101] = "�l�`����";
		cards[Chara::Alice][102] = "�l�`�u��";
		cards[Chara::Alice][103] = "�l�`�U�N";
		cards[Chara::Alice][104] = "�l�`�A��";
		cards[Chara::Alice][105] = "�l�`�Α�";
		cards[Chara::Alice][106] = "�l�`�瑄";
		cards[Chara::Alice][107] = "�l�`�r�o";
		cards[Chara::Alice][109] = "��]�˔��򂩂炭��l�`";
		cards[Chara::Alice][111] = "�V�[�J�[���C���[";
		cards[Chara::Alice][200] = "�����u�A�[�e�B�t���T�N���t�@�C�X�v";
		cards[Chara::Alice][201] = "�필�u���g�����M�I���v";
		cards[Chara::Alice][202] = "��u��C�l�`�v";
		cards[Chara::Alice][203] = "�����u���^�[���C�i�j���g�l�X�v";
		cards[Chara::Alice][204] = "�푀�u�h�[���Y�E�H�[�v";
		cards[Chara::Alice][205] = "���f�u�H���l�`�v";
		cards[Chara::Alice][206] = "�㕄�u�V�[�J�[�h�[���Y�v";
		cards[Chara::Alice][207] = "�g���u�a���l�`�v";
		cards[Chara::Alice][208] = "�l�`�u�������y�v";
		cards[Chara::Alice][209] = "���́u�g���b�v���C���[�v";
		cards[Chara::Patchouli][100] = "�T�}�[���b�h";
		cards[Chara::Patchouli][101] = "�E�B���^�[�G�������g";
		cards[Chara::Patchouli][102] = "�X�v�����O�E�B���h";
		cards[Chara::Patchouli][103] = "�I�[�^���G�b�W";
		cards[Chara::Patchouli][104] = "�h���[�X�s�A";
		cards[Chara::Patchouli][105] = "�T�}�[�t���C��";
		cards[Chara::Patchouli][106] = "�R���f���X�h�o�u��";
		cards[Chara::Patchouli][107] = "�t���b�V���I�u�X�v�����O";
		cards[Chara::Patchouli][108] = "�I�[�^���u���[�h";
		cards[Chara::Patchouli][109] = "�G�������h�V�e�B";
		cards[Chara::Patchouli][200] = "�΋����u�Z���g�G�����s���[�v";
		cards[Chara::Patchouli][201] = "�y�����u�m�G�L�A���f�����[�W���v";
		cards[Chara::Patchouli][202] = "���ؕ��u�G�������^���n�[�x�X�^�[�v";
		cards[Chara::Patchouli][203] = "�����u���C�����t���A�v";
		cards[Chara::Patchouli][204] = "�����u�T�C�����g�Z���i�v";
		cards[Chara::Patchouli][205] = "�ΐ��؋��y���u���҂̐΁v";
		cards[Chara::Patchouli][206] = "�����u�W�F���[�t�B�b�V���v�����Z�X�v";
		cards[Chara::Patchouli][207] = "���ؕ��u�T�e���C�g�q�}�����v";
		cards[Chara::Patchouli][210] = "���ؕ��u�t�H�g�V���Z�V�X�v";
		cards[Chara::Youmu][100] = "���ˉ��E�a";
		cards[Chara::Youmu][101] = "�����a";
		cards[Chara::Youmu][102] = "�������]�a";
		cards[Chara::Youmu][103] = "�ߍ��̔�";
		cards[Chara::Youmu][104] = "������a";
		cards[Chara::Youmu][105] = "�ܕ�����";
		cards[Chara::Youmu][106] = "�S���a";
		cards[Chara::Youmu][107] = "������";
		cards[Chara::Youmu][109] = "�v�ጕ";
		cards[Chara::Youmu][111] = "��є��g";
		cards[Chara::Youmu][200] = "�l���u�����a�v";
		cards[Chara::Youmu][201] = "�f�����u���z�a�v";
		cards[Chara::Youmu][202] = "�����u�H���̋�ցv";
		cards[Chara::Youmu][203] = "�l�S�u�����i���a�v";
		cards[Chara::Youmu][204] = "�f�����u���Î��q�a�v";
		cards[Chara::Youmu][205] = "��鮁u�H�������������̖@�v";
		cards[Chara::Youmu][206] = "����u���ԑM�X�v";
		cards[Chara::Youmu][207] = "�f�쌕�u�������E�a�v";
		cards[Chara::Remilia][100] = "�f�[�������[�h�E�H�[�N";
		cards[Chara::Remilia][101] = "�T�[���@���g�t���C���[";
		cards[Chara::Remilia][102] = "�f�[�������[�h�N���C�h��";
		cards[Chara::Remilia][103] = "�f�[�������[�h�A���[";
		cards[Chara::Remilia][104] = "���@���p�C�A�N���E";
		cards[Chara::Remilia][105] = "�`�F�[���M�����O";
		cards[Chara::Remilia][106] = "���P�b�g�L�b�N�A�b�v";
		cards[Chara::Remilia][107] = "�V�[�����O�t�B�A";
		cards[Chara::Remilia][109] = "�f�����Y�f�B�i�[�t�H�[�N";
		cards[Chara::Remilia][200] = "�g���u�s��郌�b�h�v";
		cards[Chara::Remilia][201] = "�K�E�u�n�[�g�u���C�N�v";
		cards[Chara::Remilia][202] = "�镄�u�f�[�����L���O�N���C�h���v";
		cards[Chara::Remilia][203] = "�g���u�X�J�[���b�g�f�r���v";
		cards[Chara::Remilia][204] = "�_���u�X�s�A�E�U�E�O���O�j���v";
		cards[Chara::Remilia][205] = "�鉤�u�h���L�����N���C�h���v";
		cards[Chara::Remilia][206] = "�镄�u�o�b�h���f�B�X�N�����u���v";
		cards[Chara::Remilia][207] = "�^���u�~�[���u���t�F�C�g�v";
		cards[Chara::Yuyuko][100] = "�H�Ӓ�";
		cards[Chara::Yuyuko][101] = "�����̌�";
		cards[Chara::Yuyuko][102] = "���F�f�r";
		cards[Chara::Yuyuko][103] = "�Ӓ����̕�";
		cards[Chara::Yuyuko][104] = "�D���̗�";
		cards[Chara::Yuyuko][105] = "�P����̑�";
		cards[Chara::Yuyuko][106] = "�U��̊Ö�";
		cards[Chara::Yuyuko][107] = "�t������";
		cards[Chara::Yuyuko][108] = "�X�t�B�A�u���[��";
		cards[Chara::Yuyuko][200] = "�����u�M���X�g���h���[���v";
		cards[Chara::Yuyuko][201] = "�����u���򕽍�s�H�v";
		cards[Chara::Yuyuko][202] = "�아�u�َ��̖��v";
		cards[Chara::Yuyuko][203] = "�����u����̉i���v";
		cards[Chara::Yuyuko][204] = "�Ė��u���z���̉���҂�v";
		cards[Chara::Yuyuko][205] = "�����u�َ����ւ̖񑩎�`�v";
		cards[Chara::Yuyuko][206] = "�쒱�u���̉H�����Ɏb���v";
		cards[Chara::Yuyuko][207] = "�����u�P����̎����v";
		cards[Chara::Yuyuko][208] = "�H��u���o�̗U�铔�v";
		cards[Chara::Yukari][100] = "�J���ĉ������ʎ蔠";
		cards[Chara::Yukari][101] = "�T���ɐ��ޗd��";
		cards[Chara::Yukari][102] = "���Ο���";
		cards[Chara::Yukari][103] = "���z���z��";
		cards[Chara::Yukari][104] = "���鏈�ɐR����";
		cards[Chara::Yukari][105] = "���z�P";
		cards[Chara::Yukari][106] = "�����Ɣ������̉F��";
		cards[Chara::Yukari][107] = "���̕����@";
		cards[Chara::Yukari][108] = "���f�̃G�T";
		cards[Chara::Yukari][200] = "�����u�l�d���E�v";
		cards[Chara::Yukari][201] = "���_�u���_���v";
		cards[Chara::Yukari][202] = "�����u�񎟌��ƎO�����̋��E�v";
		cards[Chara::Yukari][203] = "���E�u���͓I�Ȏl�d���E�v";
		cards[Chara::Yukari][204] = "���_�u��v";
		cards[Chara::Yukari][205] = "���E�u�q�ό��E�v";
		cards[Chara::Yukari][206] = "�����u������l�X�g�v";
		cards[Chara::Yukari][207] = "��a�u���Ő��̂���G�T�v";
		cards[Chara::Yukari][215] = "�p���u�Ԃ��p�w���Ԃ̗��v";
		cards[Chara::Suika][100] = "�d�S-��-";
		cards[Chara::Suika][101] = "�n��-��-";
		cards[Chara::Suika][102] = "�d�S-�a-";
		cards[Chara::Suika][103] = "�S";
		cards[Chara::Suika][104] = "���S��";
		cards[Chara::Suika][105] = "�n��-�a-";
		cards[Chara::Suika][106] = "�}��";
		cards[Chara::Suika][107] = "�a�S";
		cards[Chara::Suika][109] = "�΋S";
		cards[Chara::Suika][200] = "���u�ˉB�R�����v";
		cards[Chara::Suika][201] = "���_�u�S����̏p�v";
		cards[Chara::Suika][202] = "�S���u�~�b�V���O�p���[�v";
		cards[Chara::Suika][203] = "�S�u�V��͒j�����v";
		cards[Chara::Suika][204] = "�����u�{��S����̏p�v";
		cards[Chara::Suika][205] = "�S�_�u�~�b�V���O�p�[�v���p���[�v";
		cards[Chara::Suika][206] = "�����u�_�W���U�v";
		cards[Chara::Suika][207] = "�S�΁u�������x�ӉЏp�v";
		cards[Chara::Suika][208] = "�S���u��]�R���F�E���v";
		cards[Chara::Reisen][100] = "�}�C���h�G�N�X�v���[�W����";
		cards[Chara::Reisen][101] = "�C�����[�W���i���B�u���X�g";
		cards[Chara::Reisen][102] = "�t�B�[���h�E���g�����b�h";
		cards[Chara::Reisen][103] = "�f�B�X�r���[�t�A�X�y�N�g";
		cards[Chara::Reisen][104] = "�}�C���h�x���f�B���O";
		cards[Chara::Reisen][105] = "�A�C�T�C�g�N���[�j���O";
		cards[Chara::Reisen][106] = "�t�B�[���h�E���g���o�C�I���b�g";
		cards[Chara::Reisen][107] = "�f�B�X�I�[�_�[�A�C";
		cards[Chara::Reisen][108] = "�}�C���h�h���b�s���O";
		cards[Chara::Reisen][109] = "���b�v�����B�W����";
		cards[Chara::Reisen][110] = "�A���_�[�Z���X�u���C�N";
		cards[Chara::Reisen][200] = "�f���u���~�Ԋ�(�J���[�����B�W����)�v";
		cards[Chara::Reisen][202] = "�����u�ߊ�ԉ�(�}�C���h�X�^�[�}�C��)�v";
		cards[Chara::Reisen][203] = "���f�u�Ԋ�����(�N���E�����B�W����)�v";
		cards[Chara::Reisen][205] = "�u���O����(���i�e�B�b�N���b�h�A�C�Y)�v";
		cards[Chara::Reisen][206] = "��S�u�r�S�r��(�f�B���`���F�C�V����)�v";
		cards[Chara::Reisen][207] = "�r�S�u�r�S�n�w(�f�B�X�J�[�_�[)�v";
		cards[Chara::Reisen][208] = "�ŉ����u���z�D���̋ʁv";
		cards[Chara::Reisen][209] = "����u���m���o�̖�v";
		cards[Chara::Aya][100] = "������";
		cards[Chara::Aya][101] = "�������r";
		cards[Chara::Aya][102] = "�V��̗����I";
		cards[Chara::Aya][103] = "�Ö���I";
		cards[Chara::Aya][104] = "�󕗐�";
		cards[Chara::Aya][105] = "�����D��";
		cards[Chara::Aya][106] = "�V��̃_�E���o�[�X�g";
		cards[Chara::Aya][107] = "�����x�[�����O";
		cards[Chara::Aya][109] = "�V��i���V";
		cards[Chara::Aya][110] = "�V��̑���";
		cards[Chara::Aya][200] = "�����u�g�t��v";
		cards[Chara::Aya][201] = "�����u�V���~�Ղ̓�����ׁv";
		cards[Chara::Aya][202] = "�t���u�l�ԋ֐��̓��v";
		cards[Chara::Aya][203] = "�˕��u�V��̃}�N���o�[�X�g�v";
		cards[Chara::Aya][205] = "�����u�V�瓹�̊J���v";
		cards[Chara::Aya][206] = "�u���z���r�v";
		cards[Chara::Aya][211] = "���b�u��ꌃx�[�����O�v";
		cards[Chara::Aya][212] = "�˕��u���c�F�̐擱�v";
		cards[Chara::Komachi][100] = "���킸�������l��";
		cards[Chara::Komachi][101] = "�����΂�Ȃ��n����";
		cards[Chara::Komachi][102] = "�E���̋V";
		cards[Chara::Komachi][103] = "�ӑĂɐ��������V��";
		cards[Chara::Komachi][104] = "���_�̑劙";
		cards[Chara::Komachi][105] = "���o�̕�";
		cards[Chara::Komachi][106] = "���Ԃ̓�";
		cards[Chara::Komachi][107] = "�₵���艮�̋ٔ���";
		cards[Chara::Komachi][108] = "�ʂ肷����̐l��";
		cards[Chara::Komachi][110] = "���}���̌���";
		cards[Chara::Komachi][200] = "�M���u�̗͂���̂悤�Ɂv";
		cards[Chara::Komachi][201] = "�����u�]���􋖂������v";
		cards[Chara::Komachi][202] = "�아�u�����ɂł����镂�V��v";
		cards[Chara::Komachi][203] = "���́u���d���̓n���v";
		cards[Chara::Komachi][204] = "�����u�s�ɐg���A�ɐg���v";
		cards[Chara::Komachi][205] = "�����u�������܂����ٔ���v";
		cards[Chara::Komachi][206] = "�����u���ґI�ʂ̊��v";
		cards[Chara::Komachi][211] = "�n���u���Ԃ̋��ԁv";
		cards[Chara::Iku][100] = "�����̈ꌂ";
		cards[Chara::Iku][101] = "�H�߂͐��̔@��";
		cards[Chara::Iku][102] = "�����̓{��";
		cards[Chara::Iku][103] = "�Ód�U���e";
		cards[Chara::Iku][104] = "���_�̈ꌂ";
		cards[Chara::Iku][105] = "�H�߂͕��̔@��";
		cards[Chara::Iku][106] = "���_�̓{��";
		cards[Chara::Iku][107] = "���_�̈����";
		cards[Chara::Iku][111] = "���̊�";
		cards[Chara::Iku][200] = "�d���u���ےe�v";
		cards[Chara::Iku][201] = "�����u�����h�����v";
		cards[Chara::Iku][202] = "�����u�G���L�e���̗��{�v";
		cards[Chara::Iku][203] = "�����u�����̓f���v";
		cards[Chara::Iku][206] = "�����u���_���V�j�e�v";
		cards[Chara::Iku][207] = "�H�߁u�H�߂͋�̔@���v";
		cards[Chara::Iku][209] = "�����u���_�����v";
		cards[Chara::Iku][210] = "�����u���{�̎g���V�j�e�v";
		cards[Chara::Tenshi][100] = "���V�̌�";
		cards[Chara::Tenshi][101] = "�V���̐Β�";
		cards[Chara::Tenshi][102] = "��z�̈Ќ�";
		cards[Chara::Tenshi][103] = "��z�̌�";
		cards[Chara::Tenshi][104] = "�Z�k-��-";
		cards[Chara::Tenshi][105] = "���̗v";
		cards[Chara::Tenshi][106] = "�V�n�v���X";
		cards[Chara::Tenshi][107] = "��z�̌�";
		cards[Chara::Tenshi][200] = "�n���u�s���y��̌��v";
		cards[Chara::Tenshi][201] = "��z�u��z���z�̌��v";
		cards[Chara::Tenshi][202] = "�V���u�V������̌��v";
		cards[Chara::Tenshi][203] = "�n�k�u��J��y�̌��v";
		cards[Chara::Tenshi][204] = "�C���u�V�[�C�ۂ̌��v";
		cards[Chara::Tenshi][205] = "�v�΁u�V�n�J蓃v���X�v";
		cards[Chara::Tenshi][206] = "�C���u���O���z�̋��n�v";
		cards[Chara::Tenshi][207] = "�u�S�l�ނ̔�z�V�v";

		return cards;
	}

	map<uint8_t, string> CreateStageMap()
	{
		map<uint8_t, string> stages;

		stages[ 0] = "����_��(�|��)";
		stages[ 1] = "���@�̐X";
		stages[ 2] = "�����̑�";
		stages[ 3] = "�d���̎R";
		stages[ 4] = "���_�C";
		stages[ 5] = "�L���V";
		stages[ 6] = "��z�V";
		stages[10] = "����_��";
		stages[11] = "���J���@�X";
		stages[12] = "�g���َ��v��";
		stages[13] = "�l�`�̐X";
		stages[14] = "�g���ّ�}����";
		stages[15] = "���E";
		stages[16] = "�g���ك��r�[";
		stages[17] = "���ʘO�̐��";
		stages[18] = "�����̒|��";

		return stages;
	}

	map<uint8_t, string> CreateBgmMap()
	{
		map<uint8_t, string> bgms;

		bgms[ 0] = "�n�̐F�͉��F";
		bgms[ 1] = "������t��";
		bgms[ 2] = "�x�鐅��";
		bgms[ 3] = "�}��̗V�Y";
		bgms[ 4] = "�����C�ɍg���@�` Legendary Fish";
		bgms[ 5] = "�L���V�ρ@�` Wonderful Heaven";
		bgms[ 6] = "�c�S�n�̗L���V";
		bgms[10] = "�����d���k";
		bgms[11] = "���̊�@�` Casket of Star";
		bgms[12] = "�t���������O�i�C�g";
		bgms[13] = "�u�N���V���e�B�̐l�`�t";
		bgms[14] = "�L�L�ˉ������@�` Till When�H";
		bgms[15] = "���N�g�K�[���@�` ��������";
		bgms[16] = "�H��ɍ炩���A�n���̍��@�` Border of Life";
		bgms[17] = "�S�������ׂ̈̃Z�v�e�b�g";
		bgms[18] = "�邪�~��Ă���";
		bgms[19] = "�ӌ�";
		bgms[20] = "���C�̓��@�` Invisible Full Moon";
		bgms[21] = "���_����";
		bgms[22] = "�ފ݋A�q�@�` Riverside View";

		return bgms;
	}
}

const map<uint16_t, string> Th105::Versions(::CreateVersionMap());
const map<Mode, string> Th105::Modes(::CreateModeMap());
const map<Chara, string> Th105::Characters(::CreateCharacterMap());
const map<uint16_t, string> Th105::SystemCards(::CreateSystemCardMap());
const map<Chara, map<uint16_t, string>> Th105::Cards(::CreateCardMap());
const map<uint8_t, string> Th105::Stages(::CreateStageMap());
const map<uint8_t, string> Th105::Bgms(::CreateBgmMap());
