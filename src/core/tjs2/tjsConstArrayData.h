//---------------------------------------------------------------------------
/*
	TJS2 Script Engine( Byte Code )
	Copyright (c), Takenori Imoto

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------

#ifndef tjsConstArrayDataH
#define tjsConstArrayDataH

#include "tjsTypes.h"
#include <vector>
#include "tjsVariant.h"
#include "tjsScriptBlock.h"
#include <map>
#include <string>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <dispatch/dispatch.h>
extern "C" {
    #import <UIKit/UIKit.h>
    #import <objc/message.h>
}


namespace TJS
{
/**
 * TJS2 �o�C�g�R�[�h�����o���� Variant �^�𕪗����A�ŗL�^�ŕێ����邽�߂̃N���X
 */
class tjsConstArrayData {
private:
	std::vector<tjs_int8> Byte;
	std::vector<tjs_int16> Short;
	std::vector<tjs_int32> Integer;
	std::vector<tjs_int64> Long;
	std::vector<double> Double;
	std::vector<std::basic_string<tjs_char> > String;
	std::vector<std::vector<tjs_uint8>* > ByteBuffer;

	// �ێ��������ǂ������肷�邽�߂̃n�b�V��
	std::map<tjs_int8,int> ByteHash;
	std::map<tjs_int16,int> ShortHash;
	std::map<tjs_int32,int> IntegerHash;
	std::map<tjs_int64,int> LongHash;
	std::map<double,int> DoubleHash;
	std::map<std::basic_string<tjs_char>,int> StringHash;
	// �I�N�e�b�g�^�̎��̓n�b�V�����g���Ă��Ȃ�

	static const tjs_uint8 TYPE_VOID = 0;
	static const tjs_uint8 TYPE_OBJECT = 1;
	static const tjs_uint8 TYPE_INTER_OBJECT = 2;
	static const tjs_uint8 TYPE_STRING = 3;
	static const tjs_uint8 TYPE_OCTET = 4;
	static const tjs_uint8 TYPE_REAL = 5;
	static const tjs_uint8 TYPE_BYTE = 6;
	static const tjs_uint8 TYPE_SHORT = 7;
	static const tjs_uint8 TYPE_INTEGER = 8;
	static const tjs_uint8 TYPE_LONG = 9;
	static const tjs_uint8 TYPE_UNKNOWN = -1;

	/**
	 * �I�N�e�b�g�^�̒l���i�[����
	 */
	int PutByteBuffer( tTJSVariantOctet* val );

	/**
	 * 1�o�C�g�̒l���i�[����
	 */
	int PutByte( tjs_int8 b );
	
	/**
	 * 2�o�C�g�̒l���i�[����
	 */
	int PutShort( tjs_int16 b );
	
	/**
	 * 4�o�C�g�̒l���i�[����
	 */
	int PutInteger( tjs_int32 b );
	
	/**
	 * 8�o�C�g�̒l���i�[����
	 */
	int PutLong( tjs_int64 b );
	
	/**
	 * ���������_�l���i�[����
	 */
	int PutDouble( double b );

	static inline void Add8ByteToVector( std::vector<tjs_uint8>* array, tjs_int64 value ) {
		array->push_back( (tjs_uint8)((value>>0)&0xff) );
		array->push_back( (tjs_uint8)((value>>8)&0xff) );
		array->push_back( (tjs_uint8)((value>>16)&0xff) );
		array->push_back( (tjs_uint8)((value>>24)&0xff) );
		array->push_back( (tjs_uint8)((value>>32)&0xff) );
		array->push_back( (tjs_uint8)((value>>40)&0xff) );
		array->push_back( (tjs_uint8)((value>>48)&0xff) );
		array->push_back( (tjs_uint8)((value>>56)&0xff) );
	}
	static inline void Add4ByteToVector( std::vector<tjs_uint8>* array, int value ) {
		array->push_back( (tjs_uint8)((value>>0)&0xff) );
		array->push_back( (tjs_uint8)((value>>8)&0xff) );
		array->push_back( (tjs_uint8)((value>>16)&0xff) );
		array->push_back( (tjs_uint8)((value>>24)&0xff) );
	}
	static inline void Add2ByteToVector( std::vector<tjs_uint8>* array, tjs_int16 value ) {
		array->push_back( (tjs_uint8)((value>>0)&0xff) );
		array->push_back( (tjs_uint8)((value>>8)&0xff) );
	}
public:
	tjsConstArrayData() {}
	~tjsConstArrayData();

	/**
	 * ��������i�[����
	 */
	int PutString( const tjs_char* val );

	/**
	 * �o�C�A���g�^���i�[���Ă���^�𓾂�
	 */
	int GetType( tTJSVariant& v, tTJSScriptBlock* block );

	/**
	 * �o�C�A���g�l���i�[����
	 */
	int PutVariant( tTJSVariant& v, tTJSScriptBlock* block );

	/**
	 * �ێ�����Ă���l���o�C�g��ɂ��Ď��o��
	 */
	std::vector<tjs_uint8>* ExportBuffer();
};

} // namespace
#endif // tjsConstArrayDataH

