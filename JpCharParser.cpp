// Copyright (C) 2016 SuperUnderDog
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"
#include <map>

#include "JpCharParser.h"


static inline bool IsTrailingJpChar( TCHAR const * const pctcsz )
{
	bool bResult = false;
	if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "��" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	return bResult;
}


struct _SJpCharConvertElm
{
	SJpChar jpc;
	TCHAR const * pctsz;
};

static _SJpCharConvertElm tjpcConvert[] =
{
	{ { cnsA, vwlA }, _T( "��" ) },
	{ { cnsA, vwlI }, _T( "��" ) },
	{ { cnsA, vwlU }, _T( "��" ) },
	{ { cnsA, vwlE }, _T( "��" ) },
	{ { cnsA, vwlO }, _T( "��" ) },

	{ { cnsK, vwlA }, _T( "��" ) },
	{ { cnsK, vwlI }, _T( "��" ) },
	{ { cnsK, vwlU }, _T( "��" ) },
	{ { cnsK, vwlE }, _T( "��" ) },
	{ { cnsK, vwlO }, _T( "��" ) },

	{ { cnsS, vwlA }, _T( "��" ) },
	{ { cnsS, vwlI }, _T( "��" ) },
	{ { cnsS, vwlU }, _T( "��" ) },
	{ { cnsS, vwlE }, _T( "��" ) },
	{ { cnsS, vwlO }, _T( "��" ) },

	{ { cnsT, vwlA }, _T( "��" ) },
	{ { cnsT, vwlI }, _T( "��" ) },
	{ { cnsT, vwlU }, _T( "��" ) },
	{ { cnsT, vwlE }, _T( "��" ) },
	{ { cnsT, vwlO }, _T( "��" ) },

	{ { cnsN, vwlA }, _T( "��" ) },
	{ { cnsN, vwlI }, _T( "��" ) },
	{ { cnsN, vwlU }, _T( "��" ) },
	{ { cnsN, vwlE }, _T( "��" ) },
	{ { cnsN, vwlO }, _T( "��" ) },

	{ { cnsH, vwlA }, _T( "��" ) },
	{ { cnsH, vwlI }, _T( "��" ) },
	{ { cnsH, vwlU }, _T( "��" ) },
	{ { cnsH, vwlE }, _T( "��" ) },
	{ { cnsH, vwlO }, _T( "��" ) },

	{ { cnsM, vwlA }, _T( "��" ) },
	{ { cnsM, vwlI }, _T( "��" ) },
	{ { cnsM, vwlU }, _T( "��" ) },
	{ { cnsM, vwlE }, _T( "��" ) },
	{ { cnsM, vwlO }, _T( "��" ) },

	{ { cnsY, vwlA }, _T( "��" ) },
	{ { cnsY, vwlU }, _T( "��" ) },
	{ { cnsY, vwlO }, _T( "��" ) },

	{ { cnsR, vwlA }, _T( "��" ) },
	{ { cnsR, vwlI }, _T( "��" ) },
	{ { cnsR, vwlU }, _T( "��" ) },
	{ { cnsR, vwlE }, _T( "��" ) },
	{ { cnsR, vwlO }, _T( "��" ) },

	{ { cnsW, vwlA }, _T( "��" ) },
	{ { cnsW, vwlI }, _T( "��" ) },
	{ { cnsW, vwlE }, _T( "��" ) },
	{ { cnsW, vwlO }, _T( "��" ) },

	{ { cns_NM, vwl_N }, _T( "��" ) },

	{ { cnsG, vwlA }, _T( "��" ) },
	{ { cnsG, vwlI }, _T( "��" ) },
	{ { cnsG, vwlU }, _T( "��" ) },
	{ { cnsG, vwlE }, _T( "��" ) },
	{ { cnsG, vwlO }, _T( "��" ) },

	{ { cnsZ, vwlA }, _T( "��" ) },
	{ { cnsZ, vwlI }, _T( "��" ) },
	{ { cnsZ, vwlU }, _T( "��" ) },
	{ { cnsZ, vwlE }, _T( "��" ) },
	{ { cnsZ, vwlO }, _T( "��" ) },

	{ { cnsD, vwlA }, _T( "��" ) },
	{ { cnsD, vwlI }, _T( "��" ) },
	{ { cnsD, vwlU }, _T( "��" ) },
	{ { cnsD, vwlE }, _T( "��" ) },
	{ { cnsD, vwlO }, _T( "��" ) },

	{ { cnsB, vwlA }, _T( "��" ) },
	{ { cnsB, vwlI }, _T( "��" ) },
	{ { cnsB, vwlU }, _T( "��" ) },
	{ { cnsB, vwlE }, _T( "��" ) },
	{ { cnsB, vwlO }, _T( "��" ) },

	{ { cnsP, vwlA }, _T( "��" ) },
	{ { cnsP, vwlI }, _T( "��" ) },
	{ { cnsP, vwlU }, _T( "��" ) },
	{ { cnsP, vwlE }, _T( "��" ) },
	{ { cnsP, vwlO }, _T( "��" ) },

	{ { cnsKy, vwlA }, _T( "����" ) },
	{ { cnsKy, vwlU }, _T( "����" ) },
	{ { cnsKy, vwlO }, _T( "����" ) },

	{ { cnsSh, vwlA }, _T( "����" ) },
	{ { cnsSh, vwlU }, _T( "����" ) },
	{ { cnsSh, vwlO }, _T( "����" ) },

	{ { cnsCh, vwlA }, _T( "����" ) },
	{ { cnsCh, vwlU }, _T( "����" ) },
	{ { cnsCh, vwlO }, _T( "����" ) },

	{ { cnsNy, vwlA }, _T( "�ɂ�" ) },
	{ { cnsNy, vwlU }, _T( "�ɂ�" ) },
	{ { cnsNy, vwlO }, _T( "�ɂ�" ) },

	{ { cnsHy, vwlA }, _T( "�Ђ�" ) },
	{ { cnsHy, vwlU }, _T( "�Ђ�" ) },
	{ { cnsHy, vwlO }, _T( "�Ђ�" ) },

	{ { cnsMy, vwlA }, _T( "�݂�" ) },
	{ { cnsMy, vwlU }, _T( "�݂�" ) },
	{ { cnsMy, vwlO }, _T( "�݂�" ) },

	{ { cnsRy, vwlA }, _T( "���" ) },
	{ { cnsRy, vwlU }, _T( "���" ) },
	{ { cnsRy, vwlO }, _T( "���" ) },

	{ { cnsGy, vwlA }, _T( "����" ) },
	{ { cnsGy, vwlU }, _T( "����" ) },
	{ { cnsGy, vwlO }, _T( "����" ) },

	{ { cnsJZy, vwlA }, _T( "����" ) },
	{ { cnsJZy, vwlU }, _T( "����" ) },
	{ { cnsJZy, vwlO }, _T( "����" ) },

	{ { cnsJDy, vwlA }, _T( "����" ) },
	{ { cnsJDy, vwlU }, _T( "����" ) },
	{ { cnsJDy, vwlO }, _T( "����" ) },

	{ { cnsBy, vwlA }, _T( "�т�" ) },
	{ { cnsBy, vwlU }, _T( "�т�" ) },
	{ { cnsBy, vwlO }, _T( "�т�" ) },

	{ { cnsPy, vwlA }, _T( "�҂�" ) },
	{ { cnsPy, vwlU }, _T( "�҂�" ) },
	{ { cnsPy, vwlO }, _T( "�҂�" ) },

	{ { cnsKw, vwlA }, _T( "����" ) },
	{ { cnsGw, vwlA }, _T( "����" ) },
	
	{ { cnsTei, vwlI }, _T( "�Ă�" ) }
};
#define CountOf_tjpcConvert ( sizeof( tjpcConvert ) / sizeof( tjpcConvert[ 0 ] ) )

class CJpCharParser
{
public:
	CJpCharParser( void );
	virtual ~CJpCharParser() {};

private:
	std::map<std::string, SJpChar> m_jpcharconvmap;

public:
	bool Parse( SJpChar & rjpc, TCHAR const * const pctcsz );
};

CJpCharParser::CJpCharParser( void )
{
	for( int i = 0; CountOf_tjpcConvert > i; i++ )
	{
		if( m_jpcharconvmap.end() !=
			m_jpcharconvmap.find( tjpcConvert[ i ].pctsz ) )
		{
			throw std::exception();
		}
		m_jpcharconvmap.insert( std::make_pair(
			tjpcConvert[i].pctsz, tjpcConvert[ i ].jpc ) );

	}
}

bool CJpCharParser::Parse( SJpChar & rjpc, TCHAR const * const pctcsz )
{
	bool bResult = false;
	std::map<std::string, SJpChar>::const_iterator
		cit = m_jpcharconvmap.find( pctcsz );
	if( m_jpcharconvmap.end() != cit )
	{
		rjpc = (*cit).second;
		bResult = true;
	}
	return bResult;
}

static CJpCharParser jpcparset;


TCHAR const s_tccszSokuon[] = _T( "��" );
#define _CountOf_SokuonLen	( ( sizeof( s_tccszSokuon ) / sizeof( s_tccszSokuon[ 0 ] ) ) - 1 )


bool ParseHiragana( std::list<SDescJpCharElm> & rdescjpclist, TCHAR const * const pctcsz )
{
	bool bFail = false;
	bool bFoundSokuon = false;
	// �}���`�o�C�g���ߌ����n�[�h�R�[�f�B���O
	int i = 0;
	while( ( !bFail ) && ( _T( '\0' ) != pctcsz[ i ] ) &&
		( _T( '\0' ) != pctcsz[ i + 1 ] ) )
	{
		TCHAR const * const pctcszCurrent = &( pctcsz[ i ] );
		if( 0 == _tcsncmp( s_tccszSokuon, pctcszCurrent, _CountOf_SokuonLen ) )
		{
			if( bFoundSokuon )
			{
				bFail = true;
			}
			else
			{
				bFoundSokuon = true;
				i += _CountOf_SokuonLen;
			}
		}
		else
		{
			std::string str;
			if( ! IsTrailingJpChar( &( pctcszCurrent[ 2 /* Multi byte hardcode */ ] ) ) )
			{
				str.append( pctcszCurrent, 2 );
			}
			else
			{
				str.append( pctcszCurrent, 4 );
			}
			SJpChar jpc;
			if( !( jpcparset.Parse( jpc, str.c_str() ) ) )
			{
				bFail = true;
			}
			else
			{
				rdescjpclist.push_back( SDescJpCharElm( bFoundSokuon, jpc ) );
				i += str.size();
				bFoundSokuon = false;
			}
		}
	}
	if( _T( '\0' ) != pctcsz[ i ] || bFoundSokuon )
	{
		bFail = true;
	}
	return ( !bFail );
}


