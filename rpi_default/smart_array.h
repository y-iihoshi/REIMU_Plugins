#ifndef __SMART_ARRAY__
#define __SMART_ARRAY__


/*--------------------------------------------------------
�Q�ƃJ�E���^���X�}�[�g�|�C���^
�E�E�E�̔z���
--------------------------------------------------------*/



template< class P >
class smart_array
{
public:
	//�f�t�H���g�R���X�g���N�^�B
	//�E�E�E�E������ۂł���B
	smart_array():m_pnCounter( NULL ),m_aObject( NULL ),m_nSize( 0 ){}

	//�R�s�[�R���X�g���N�^�B
	//�A�b�v�L���X�g��OK
	template< class D >
	smart_array( const smart_array< D >& p ){
		if( p != NULL ){
			//�|�C���^�R�s�[
			m_aObject = p.m_aObject;
			m_pnCounter = p.m_pnCounter;
			//�Q�ƃJ�E���^�{�{
			(*m_pnCounter)++;
			//�T�C�Y
			m_nSize = p.m_nSize;
		}else{
			m_aObject = NULL;
			m_pnCounter = NULL;
			m_nSize = 0;
		}
	}
	smart_array( const smart_array& p ){
		if( p != NULL ){
			m_aObject = p.m_aObject;
			m_pnCounter = p.m_pnCounter;
			(*m_pnCounter)++;
			m_nSize = p.m_nSize;
		}else{
			m_aObject = NULL;
			m_pnCounter = NULL;
			m_nSize = 0;
		}
	}

	//���|�C���^�R���X�g���N�^(��)
	//�T�C�Y��n���Ƃ��낢����������Ƃ����邩���B
	smart_array( P* p, unsigned int nSize = 0xFFFFFFFF ){
		//�I�u�W�F�N�g�ۊ�
		m_aObject = p;
		//����p���m��
		m_pnCounter = new unsigned int;
		//�Q�ƃJ�E���^�Z�b�g
		*m_pnCounter = 1;
		//�T�C�Y
		m_nSize = nSize;
	}


	//������Z�q
	template< class D >
	smart_array< P >& operator =( const smart_array< D >& p ){
		//���g���₳�����폜
		Release();
		if( p != NULL ){
			//�����o�R�s�[
			m_pnCounter = p.m_pnCounter;
			m_aObject = p.m_aObject;
			m_nSize = p.m_nSize;
			//�Q�ƃJ�E���^UP!!
			(*m_pnCounter)++;
		}
		return *this;
	}
	smart_array& operator =( const smart_array& p ){
		Release();
		if( p != NULL ){
			m_pnCounter = p.m_pnCounter;
			m_aObject = p.m_aObject;
			m_nSize = p.m_nSize;
			(*m_pnCounter)++;
		}
		return *this;
	}

	template< class D >
	smart_array< P >& operator =( D* p ){
		//�T�C�Y���킩��Ȃ��̂Ŕ񐄏�

		//���g�������폜
		Release();
		//�ʂ�ہI�I
		if( p != NULL ){
			//����p���m��
			m_pnCounter = new unsigned int;
			//���
			m_aObject = p;
			*m_pnCounter = 1;
			m_nSize = 0xFFFFFFFF;
		}

		return *this;
	}

	//�ė��p
	template< class D >
	smart_array< P >& Reset( D* p, unsigned int nSize ){
		Release();
		if( p != NULL ){
			//����p���m��
			m_pnCounter = new unsigned int;
			//���
			m_aObject = p;
			*m_pnCounter = 1;
			m_nSize = nSize;
		}
		return *this;
	}


	//�f�B�X�g���N�^�B
	virtual ~smart_array(){
		Release();
	}

	//�z��̂ӂ������B
#ifndef _DEBUG
	P& operator[]( unsigned int i ) const { return m_aObject[i]; }
#else
	//�f�o�b�O�p�B�z��𒴂���Ɨ�O�𓊂��Ă���B
	P& operator[]( unsigned int i ) const {
		if( i < m_nSize ){
			return  m_aObject[i];
		}else{
			throw "Buffer Overflow";
		}
	}
#endif

	//��r���Z�q
	//NULL�`�F�b�N�ɂ��g���܂��B
	bool operator==( const P* p ) const{
		return m_aObject == p;
	}
	bool operator==( const smart_array< P >& p ) const{
		return m_aObject == p.m_aObject;
	}
	bool operator!=( const P* p ) const{
		return m_aObject != p;
	}
	bool operator!=( const smart_array< P >& p ) const{
		return m_aObject != p.m_aObject;
	}

	//�R���e�i�I�Ȃ���
#ifndef _DEBUG
	unsigned int GetSize(){ return m_nSize; }
#endif
#ifdef _DEBUG
	unsigned int GetSize(){
		if( m_nSize == 0xFFFFFFFF ){
			throw "undefined size";
		}else{
			return m_nSize;
		}
	}
#endif
	P* GetPtr(){ return m_aObject; }
	P* GetEndPtr(){ return m_aObject + m_nSize; }


#if (_MSC_VER==1200)	// VC++6.0
	friend class smart_array;
#else					// VC++.NET
	template< class Y > friend class smart_array;
#endif

protected:
	void Release(){
		//�ʂ�ے�
		if( m_aObject == NULL ){
			return;
		}
		//�Q�ƃJ�E���^���O�Ȃ琧��DATA���폜
		if( --(*m_pnCounter) == 0 ){
			delete m_pnCounter;
			delete[] m_aObject;
		}
		//�����̂ӂ������B
		m_pnCounter = NULL;
		m_aObject = NULL;
		m_nSize = 0;
		return;
	}


private:
	unsigned int* m_pnCounter;
	P* m_aObject;

	unsigned int m_nSize;


};


#endif