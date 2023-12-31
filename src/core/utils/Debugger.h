/****************************************************************************/
/*! @file
@brief �u���[�N�|�C���g�̂���t�@�C���ƍs�ԍ���ێ�����

-----------------------------------------------------------------------------
	Copyright (C) T.Imoto <http://www.kaede-software.com>
-----------------------------------------------------------------------------
@author		T.Imoto
@date		2010/04/18
@note
*****************************************************************************/

#ifndef __DEBUGGER_H__
#define __DEBUGGER_H__

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

#include <assert.h>

enum tTJSDBGHOOKType {
	DBGHOOK_PREV_EXE_LINE,	//!< ���C�����s��
	DBGHOOK_PREV_CALL,		//!< �֐��R�[��
	DBGHOOK_PREV_RETURN,	//!< ���^�[����
	DBGHOOK_PREV_EXCEPT,	//!< ��O�ˏo��
	DBGHOOK_PREV_BREAK,		//!< �X�N���v�g���̃u���[�N
};
// gee = debuggee
// ger = debugger
enum tTJSDBGEvent {
	DBGEV_GEE_LOG = 0x8000,		//!< gee -> ger ���O���o�� (���l�ɓ��ɈӖ��͂Ȃ�)
	DBGEV_GEE_BREAK,			//!< gee -> ger ��~�ʒm
	DBGEV_GEE_STACK_TRACE,		//!< gee -> ger �X�^�b�N�g���[�X���ʒm
	DBGEV_GEE_LOCAL_VALUE,		//!< gee -> ger ���[�J���ϐ����
	DBGEV_GEE_REQUEST_SETTINGS,	//!< gee -> ger ��O�ʒm�L���A�u���[�N�|�C���g��񓙂�v��
	DBGEV_GEE_CLASS_VALUE,		//!< gee -> ger �N���X�ϐ����

	DBGEV_GER_EXEC = 0x9000,	//!< ger -> gee ���s
	DBGEV_GER_BREAK,			//!< ger -> gee �ꎞ��~
	DBGEV_GER_STEP,				//!< ger -> gee �X�e�b�v
	DBGEV_GER_TRACE,			//!< ger -> gee �g���[�X
	DBGEV_GER_RETURN,			//!< ger -> gee ���^�[��
	DBGEV_GER_BREAKPOINT_START,	//!< ger -> gee �u���[�N�|�C���g��񑗐M�J�n
	DBGEV_GER_BREAKPOINT,		//!< ger -> gee �u���[�N�|�C���g���
	DBGEV_GER_BREAKPOINT_END,	//!< ger -> gee �u���[�N�|�C���g��񑗐M�I��
	DBGEV_GER_EXCEPTION_FLG,	//!< ger -> gee ��O�������ɒ�~���邩�ǂ���
};

struct BreakpointLine {
	typedef std::map<int,int>		lines;
	typedef lines::iterator			iterator;
	typedef lines::const_iterator	const_iterator;

	lines	Lines;

	bool IsBreakPoint( int lineno ) const {
		const_iterator j = Lines.find( lineno );
		if( j != Lines.end() ) {
			return true;
		}
		return false;
	}
	void SetBreakPoint( int lineno ) {
		iterator i = Lines.find( lineno );
		if( i == Lines.end() ) {
			std::pair<iterator, bool> ret = Lines.insert( BreakpointLine::lines::value_type( lineno, lineno ) );
			assert( ret.second );
		}
	}
	void ClearBreakPoint( int lineno ) {
		Lines.erase( lineno );
	}
};

struct Breakpoints {
	typedef std::map<std::wstring,BreakpointLine>	breakpoints;
	typedef breakpoints::iterator					iterator;
	typedef breakpoints::const_iterator				const_iterator;

	breakpoints BreakPoint;

	void SetBreakPoint( const std::wstring& filename, int lineno ) {
		iterator i = BreakPoint.find( filename );
		if( i == BreakPoint.end() ) {
			std::pair<iterator, bool> ret = BreakPoint.insert( breakpoints::value_type( filename, BreakpointLine() ) );
			assert( ret.second );
			i = ret.first;
		}
		i->second.SetBreakPoint(lineno);
	}
	void ClearBreakPoint( const std::wstring& filename, int lineno ) {
		iterator i = BreakPoint.find( filename );
		if( i == BreakPoint.end() ) {
			return;
		}
		i->second.ClearBreakPoint( lineno );
	}
	bool IsBreakPoint( const std::wstring& filename, int lineno ) const {
		const_iterator i = BreakPoint.find( filename );
		if( i != BreakPoint.end() ) {
			return i->second.IsBreakPoint(lineno);
		}
		return false;
	}
	const BreakpointLine* GetBreakPointLines( const std::wstring& filename ) const {
		const_iterator i = BreakPoint.find( filename );
		if( i != BreakPoint.end() ) {
			return &(i->second);
		}
		return NULL;
	}
	BreakpointLine* GetBreakPointLines( const std::wstring& filename ) {
		iterator i = BreakPoint.find( filename );
		if( i != BreakPoint.end() ) {
			return &(i->second);
		}
		return NULL;
	}
	bool HasBreakPoint( const std::wstring& filename ) {
		iterator i = BreakPoint.find( filename );
		if( i != BreakPoint.end() ) {
			return( i->second.Lines.size() > 0 );
		}
		return false;
	}
	void ClearAll() {
		BreakPoint.clear();
	}
};



#endif // __DEBUGGER_H__
