#ifndef __SMART_ARRAY__
#define __SMART_ARRAY__


/*--------------------------------------------------------
参照カウンタつきスマートポインタ
・・・の配列版
--------------------------------------------------------*/



template< class P >
class smart_array
{
public:
	//デフォルトコンストラクタ。
	//・・・・からっぽである。
	smart_array():m_pnCounter( NULL ),m_aObject( NULL ),m_nSize( 0 ){}

	//コピーコンストラクタ。
	//アップキャストもOK
	template< class D >
	smart_array( const smart_array< D >& p ){
		if( p != NULL ){
			//ポインタコピー
			m_aObject = p.m_aObject;
			m_pnCounter = p.m_pnCounter;
			//参照カウンタ＋＋
			(*m_pnCounter)++;
			//サイズ
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

	//生ポインタコンストラクタ(何)
	//サイズを渡すといろいろ嬉しいことがあるかも。
	smart_array( P* p, unsigned int nSize = 0xFFFFFFFF ){
		//オブジェクト保管
		m_aObject = p;
		//制御パラ確保
		m_pnCounter = new unsigned int;
		//参照カウンタセット
		*m_pnCounter = 1;
		//サイズ
		m_nSize = nSize;
	}


	//代入演算子
	template< class D >
	smart_array< P >& operator =( const smart_array< D >& p ){
		//中身をやさしく削除
		Release();
		if( p != NULL ){
			//メンバコピー
			m_pnCounter = p.m_pnCounter;
			m_aObject = p.m_aObject;
			m_nSize = p.m_nSize;
			//参照カウンタUP!!
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
		//サイズがわからないので非推奨

		//中身をやんわり削除
		Release();
		//ぬるぽ！！
		if( p != NULL ){
			//制御パラ確保
			m_pnCounter = new unsigned int;
			//代入
			m_aObject = p;
			*m_pnCounter = 1;
			m_nSize = 0xFFFFFFFF;
		}

		return *this;
	}

	//再利用
	template< class D >
	smart_array< P >& Reset( D* p, unsigned int nSize ){
		Release();
		if( p != NULL ){
			//制御パラ確保
			m_pnCounter = new unsigned int;
			//代入
			m_aObject = p;
			*m_pnCounter = 1;
			m_nSize = nSize;
		}
		return *this;
	}


	//ディストラクタ。
	virtual ~smart_array(){
		Release();
	}

	//配列のふりをする。
#ifndef _DEBUG
	P& operator[]( unsigned int i ) const { return m_aObject[i]; }
#else
	//デバッグ用。配列を超えると例外を投げてくる。
	P& operator[]( unsigned int i ) const {
		if( i < m_nSize ){
			return  m_aObject[i];
		}else{
			throw "Buffer Overflow";
		}
	}
#endif

	//比較演算子
	//NULLチェックにも使えます。
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

	//コンテナ的なこと
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
		//ぬるぽ中
		if( m_aObject == NULL ){
			return;
		}
		//参照カウンタが０なら制御DATAも削除
		if( --(*m_pnCounter) == 0 ){
			delete m_pnCounter;
			delete[] m_aObject;
		}
		//初物のふりをする。
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