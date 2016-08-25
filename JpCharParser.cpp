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
	if( 0 == _tcsncmp( _T( "ゃ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "ゅ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "ょ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "ゎ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "ぃ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "ぁ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "ぅ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "ぇ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
	{
		bResult = true;
	}
	else if( 0 == _tcsncmp( _T( "ぉ" ), pctcsz, 2 /* Multi byte hardcode */ ) )
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
	{ { cnsA, vwlA }, _T( "あ" ) },
	{ { cnsA, vwlI }, _T( "い" ) },
	{ { cnsA, vwlU }, _T( "う" ) },
	{ { cnsA, vwlE }, _T( "え" ) },
	{ { cnsA, vwlO }, _T( "お" ) },

	{ { cnsK, vwlA }, _T( "か" ) },
	{ { cnsK, vwlI }, _T( "き" ) },
	{ { cnsK, vwlU }, _T( "く" ) },
	{ { cnsK, vwlE }, _T( "け" ) },
	{ { cnsK, vwlO }, _T( "こ" ) },

	{ { cnsS, vwlA }, _T( "さ" ) },
	{ { cnsS, vwlI }, _T( "し" ) },
	{ { cnsS, vwlU }, _T( "す" ) },
	{ { cnsS, vwlE }, _T( "せ" ) },
	{ { cnsS, vwlO }, _T( "そ" ) },

	{ { cnsT, vwlA }, _T( "た" ) },
	{ { cnsT, vwlI }, _T( "ち" ) },
	{ { cnsT, vwlU }, _T( "つ" ) },
	{ { cnsT, vwlE }, _T( "て" ) },
	{ { cnsT, vwlO }, _T( "と" ) },

	{ { cnsN, vwlA }, _T( "な" ) },
	{ { cnsN, vwlI }, _T( "に" ) },
	{ { cnsN, vwlU }, _T( "ぬ" ) },
	{ { cnsN, vwlE }, _T( "ね" ) },
	{ { cnsN, vwlO }, _T( "の" ) },

	{ { cnsH, vwlA }, _T( "は" ) },
	{ { cnsH, vwlI }, _T( "ひ" ) },
	{ { cnsH, vwlU }, _T( "ふ" ) },
	{ { cnsH, vwlE }, _T( "へ" ) },
	{ { cnsH, vwlO }, _T( "ほ" ) },

	{ { cnsM, vwlA }, _T( "ま" ) },
	{ { cnsM, vwlI }, _T( "み" ) },
	{ { cnsM, vwlU }, _T( "む" ) },
	{ { cnsM, vwlE }, _T( "め" ) },
	{ { cnsM, vwlO }, _T( "も" ) },

	{ { cnsY, vwlA }, _T( "や" ) },
	{ { cnsY, vwlU }, _T( "ゆ" ) },
	{ { cnsY, vwlO }, _T( "よ" ) },

	{ { cnsR, vwlA }, _T( "ら" ) },
	{ { cnsR, vwlI }, _T( "り" ) },
	{ { cnsR, vwlU }, _T( "る" ) },
	{ { cnsR, vwlE }, _T( "れ" ) },
	{ { cnsR, vwlO }, _T( "ろ" ) },

	{ { cnsW, vwlA }, _T( "わ" ) },
	{ { cnsW, vwlI }, _T( "ゐ" ) },
	{ { cnsW, vwlE }, _T( "ゑ" ) },
	{ { cnsW, vwlO }, _T( "を" ) },

	{ { cns_NM, vwl_N }, _T( "ん" ) },

	{ { cnsG, vwlA }, _T( "が" ) },
	{ { cnsG, vwlI }, _T( "ぎ" ) },
	{ { cnsG, vwlU }, _T( "ぐ" ) },
	{ { cnsG, vwlE }, _T( "げ" ) },
	{ { cnsG, vwlO }, _T( "ご" ) },

	{ { cnsZ, vwlA }, _T( "ざ" ) },
	{ { cnsZ, vwlI }, _T( "じ" ) },
	{ { cnsZ, vwlU }, _T( "ず" ) },
	{ { cnsZ, vwlE }, _T( "ぜ" ) },
	{ { cnsZ, vwlO }, _T( "ぞ" ) },

	{ { cnsD, vwlA }, _T( "だ" ) },
	{ { cnsD, vwlI }, _T( "ぢ" ) },
	{ { cnsD, vwlU }, _T( "づ" ) },
	{ { cnsD, vwlE }, _T( "で" ) },
	{ { cnsD, vwlO }, _T( "ど" ) },

	{ { cnsB, vwlA }, _T( "ば" ) },
	{ { cnsB, vwlI }, _T( "び" ) },
	{ { cnsB, vwlU }, _T( "ぶ" ) },
	{ { cnsB, vwlE }, _T( "べ" ) },
	{ { cnsB, vwlO }, _T( "ぼ" ) },

	{ { cnsP, vwlA }, _T( "ぱ" ) },
	{ { cnsP, vwlI }, _T( "ぴ" ) },
	{ { cnsP, vwlU }, _T( "ぷ" ) },
	{ { cnsP, vwlE }, _T( "ぺ" ) },
	{ { cnsP, vwlO }, _T( "ぽ" ) },

	{ { cnsKy, vwlA }, _T( "きゃ" ) },
	{ { cnsKy, vwlU }, _T( "きゅ" ) },
	{ { cnsKy, vwlO }, _T( "きょ" ) },

	{ { cnsSh, vwlA }, _T( "しゃ" ) },
	{ { cnsSh, vwlU }, _T( "しゅ" ) },
	{ { cnsSh, vwlO }, _T( "しょ" ) },

	{ { cnsCh, vwlA }, _T( "ちゃ" ) },
	{ { cnsCh, vwlU }, _T( "ちゅ" ) },
	{ { cnsCh, vwlO }, _T( "ちょ" ) },

	{ { cnsNy, vwlA }, _T( "にゃ" ) },
	{ { cnsNy, vwlU }, _T( "にゅ" ) },
	{ { cnsNy, vwlO }, _T( "にょ" ) },

	{ { cnsHy, vwlA }, _T( "ひゃ" ) },
	{ { cnsHy, vwlU }, _T( "ひゅ" ) },
	{ { cnsHy, vwlO }, _T( "ひょ" ) },

	{ { cnsMy, vwlA }, _T( "みゃ" ) },
	{ { cnsMy, vwlU }, _T( "みゅ" ) },
	{ { cnsMy, vwlO }, _T( "みょ" ) },

	{ { cnsRy, vwlA }, _T( "りゃ" ) },
	{ { cnsRy, vwlU }, _T( "りゅ" ) },
	{ { cnsRy, vwlO }, _T( "りょ" ) },

	{ { cnsGy, vwlA }, _T( "ぎゃ" ) },
	{ { cnsGy, vwlU }, _T( "ぎゅ" ) },
	{ { cnsGy, vwlO }, _T( "ぎょ" ) },

	{ { cnsJZy, vwlA }, _T( "じゃ" ) },
	{ { cnsJZy, vwlU }, _T( "じゅ" ) },
	{ { cnsJZy, vwlO }, _T( "じょ" ) },

	{ { cnsJDy, vwlA }, _T( "ぢゃ" ) },
	{ { cnsJDy, vwlU }, _T( "ぢゅ" ) },
	{ { cnsJDy, vwlO }, _T( "ぢょ" ) },

	{ { cnsBy, vwlA }, _T( "びゃ" ) },
	{ { cnsBy, vwlU }, _T( "びゅ" ) },
	{ { cnsBy, vwlO }, _T( "びょ" ) },

	{ { cnsPy, vwlA }, _T( "ぴゃ" ) },
	{ { cnsPy, vwlU }, _T( "ぴゅ" ) },
	{ { cnsPy, vwlO }, _T( "ぴょ" ) },

	{ { cnsKw, vwlA }, _T( "くゎ" ) },
	{ { cnsGw, vwlA }, _T( "ぐゎ" ) },
	
	{ { cnsTei, vwlI }, _T( "てぃ" ) }
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


TCHAR const s_tccszSokuon[] = _T( "っ" );
#define _CountOf_SokuonLen	( ( sizeof( s_tccszSokuon ) / sizeof( s_tccszSokuon[ 0 ] ) ) - 1 )


bool ParseHiragana( std::list<SDescJpCharElm> & rdescjpclist, TCHAR const * const pctcsz )
{
	bool bFail = false;
	bool bFoundSokuon = false;
	// マルチバイト決め撃ちハードコーディング
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


