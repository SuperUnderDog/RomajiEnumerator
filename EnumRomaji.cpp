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
#include <io.h>
#include <list>
#include <set>

#include "StreamContainer.h"
#include "JpCharParser.h"
#include "JpCharToRomaji.h"
#include "EnumRomaji.h"


static inline void WriteLine( CBaseOutStream * const pos, TCHAR const * const pctsz )
{
	pos->WriteLine( pctsz );
}


#define _ROMAJI_ALLPATTERN_COUNT	(	\
	2 *		/* bool bModUu;				// uu	false:u / true:uu						*/ \
	3 *		/* int iOu;					// ou	0:o / 1:ou->oh / 2:ou					*/ \
	3 *		/* int iOo;					// oo	0:o(last oo) / 1:o / 2:oo				*/ \
	2 *		/* bool bModShi;			// shi	false:shi / true:si						*/ \
	2 *		/* bool bModChi;			// chi	false:chi / true:ti						*/ \
	2 *		/* bool bModTch;			// tch	false:tch / true:tt						*/ \
	2 *		/* bool bModTsu;			// tsu	false:tsu / true:tu						*/ \
	2 *		/* bool bModFu;				// fu	false:fu / true:hu						*/ \
	2 *		/* bool bModMmbp;			// mb	false:mmambampa / true:nbanbanpa		*/ \
	2 *		/* bool bModJi_Zi;			// ji	false:ji / true:zi						*/ \
	2 *		/* bool bModJiZuJ_DiDuDy;	// zizu	false:zizujajujo / true:didudyadyudyo	*/ \
	2 *		/* bool bModSh;				// sha	false:shashusho / true:syasyusyo		*/ \
	3 *		/* int iModCh;				// cha	0:chachucho / 1:tyatyutyo / 2:cyacyucyo	*/ \
	3 *		/* int iJZy;				// ja	0:jajujo / 1:zyazyuzyo / 2:jyajyujyo	*/ \
	2	)	/* bool bModTei;			// tei	false:tei / true:ti						*/

static inline bool _EnumAllPatternRomaji(
	std::set<std::string> & rstrset, std::list<SDescJpCharElm> const & rcjpclist )
{
	rstrset.clear();
	bool bFail = false;
	for( int iPtrn = 0; ( !bFail ) && ( _ROMAJI_ALLPATTERN_COUNT > iPtrn ); iPtrn++ )
	{
		int iRemain = iPtrn;
		SRomajiParam param;
		// uu	false:u / true:uu
		param.bModUu = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// ou	0:o / 1:ou->oh / 2:ou
		param.iOu = iRemain % 3;
		iRemain /= 3;
		// oo	0:o(last oo) / 1:o / 2:oo
		param.iOo = iRemain % 3;
		iRemain /= 3;
		// shi	false:shi / true:si
		param.bModShi = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// chi	false:chi / true:ti
		param.bModChi = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// tch	false:tch / true:tt
		param.bModTch = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// tsu	false:tsu / true:tu
		param.bModTsu = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// fu	false:fu / true:hu
		param.bModFu = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// nb	false:mmambampa / true:nmanbanpa
		param.bModMmbp = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// ji	false:ji / true:zi
		param.bModJi_Zi = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// zizu	false:zizujajujo / true:didudyadyudyo
		param.bModJiZuJ_DiDuDy = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// sha	false:shashusho / true:syasyusyo
		param.bModSh = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;
		// cha	0:chachucho / 1:tyatyutyo / 2:cyacyucyo
		param.iModCh = iRemain % 3;
		iRemain /= 3;
		// ja	0:jajujo / 1:zyazyuzyo / 2:jyajyujyo
		param.iJZy = iRemain % 3;
		iRemain /= 3;
		// tei	false:tei / true:ti
		param.bModTei = ( 0 != ( 1 & iRemain ) );
		iRemain /= 2;

		if( 0 != iRemain ) throw std::exception();
		std::string str;
		if( !ConvertToRomaji( str, rcjpclist, param ) )
		{
			bFail = true;
		}
		else
		{
			if( rstrset.end() == rstrset.find( str ) )
			{
				rstrset.insert( str );
			}
		}
	}
	return ( !bFail );
}

static inline void _EnumRomaji_ProcLine(
	CBaseOutStream * poutstream, TCHAR const * const pctszLine )
{
	std::list<SDescJpCharElm> jpclist;
	if( !ParseHiragana( jpclist, pctszLine ) )
	{
		std::string str = _T( "Failed to parse \"" );
		str += pctszLine;
		str += _T( "\"." );
		throw std::exception( str.c_str() );
	}

	std::set<std::string> strset;
	if( !_EnumAllPatternRomaji( strset, jpclist ) )
	{
		std::string str = _T( "Failed to convert \"" );
		str += pctszLine;
		str += _T( "\"." );
		throw std::exception( str.c_str() );
	}

	for( std::set<std::string>::const_iterator cit = strset.begin();
		strset.end() != cit; cit++ )
	{
		poutstream->WriteLine( (*cit).c_str() );
	}
}

static inline void _EnumRomaji(
	CBaseOutStream * poutstream, CBaseInStream & rinstream )
{
	TCHAR * pctszLine = NULL;
	try
	{
		int const iLineBufSize = 0x80;
		pctszLine = new TCHAR[ iLineBufSize + 1 ];
		pctszLine[ iLineBufSize ] = 0;

		while( !( rinstream.eof() ) )
		{
			rinstream.getline( pctszLine, iLineBufSize );
			if( rinstream.fail() )
			{
				while( ( !( rinstream.eof() ) ) && rinstream.fail() )
				{
					rinstream.clear();
					rinstream.getline( pctszLine, iLineBufSize );
				}
			}
			else
			{
				_EnumRomaji_ProcLine( poutstream, pctszLine );
			}
		}

		delete[] pctszLine;
	}
	catch( ... )
	{
		if( NULL != pctszLine ) delete[] pctszLine;
		throw;
	}
}



void EnumRomaji( SApplicationParam const & rcparam )
{
	std::ofstream ofsDestDict;
	CBaseOutStream * poutstream = NULL;
	try
	{
		if( rcparam.strDestFile.empty() )
		{
			poutstream = new CCoutStream( std::cout );
		}
		else
		{
			ofsDestDict.open( rcparam.strDestFile,
				std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );
			if( ofsDestDict.fail() )
			{
				std::string str = _T( "Failed to open \"" );
				str += rcparam.strDestFile;
				str += _T( "\"." );
				throw std::exception( str.c_str() );
			}
			poutstream = new COfstream( ofsDestDict );
		}

		if( rcparam.strSrcFile.empty() )
		{
			CCinStream instream( std::cin );
			_EnumRomaji( poutstream, instream );
		}
		else
		{
			std::string strDir;
			size_t const sizetLastIdx = rcparam.strSrcFile.find_last_of( _T( "\\/" ) );
			if( std::string::npos != sizetLastIdx )
			{
				strDir = rcparam.strSrcFile.substr( 0, sizetLastIdx + 1 );
			}

			_finddata_t finddata;
			long lFind = -1L;
			try
			{
				if( -1L == ( lFind = _findfirst(
					rcparam.strSrcFile.c_str(), &finddata ) ) )
				{
					std::string str = _T( "Not exist file(s) match \"" );
					str += rcparam.strSrcFile.c_str();
					str += _T( "\"." );
					throw std::exception( str.c_str() );
				}
				do
				{
					std::ifstream ifsSrcDict;
					try
					{
						ifsSrcDict.open( strDir + finddata.name, std::ios_base::in );
						if( ifsSrcDict.fail() )
						{
							std::string str = _T( "Failed to open \"" );
							str += strDir + finddata.name;
							str += _T( "\"." );
							throw std::exception( str.c_str() );
						}
						CIfstream instream( ifsSrcDict );
						_EnumRomaji( poutstream, instream );
					}
					catch( ... )
					{
						ifsSrcDict.close();
						throw;
					}
				}
				while( _findnext( lFind, &finddata ) == 0 );
			}
			catch( ... )
			{
				if( -1 != lFind ) ::_findclose( lFind );
				throw;
			}
		}

		delete poutstream;
		ofsDestDict.close();
	}
	catch( ... )
	{
		if( NULL != poutstream ) delete poutstream;
		ofsDestDict.close();
		throw;
	}
}



