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

#include "JpCharToRomaji.h"


static inline bool _ConvConsonantA( std::string & rstr,
	SDescJpCharElm const & rcjpcPrev, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & rcjpcNext, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( 'a' );	bResult = true;	break;
			case vwlI:	rstr += _T( 'i' );	bResult = true;	break;
			case vwlU:
				{
					if( vwlU == rcjpcPrev.jpc.vwl )
					{
						if( rcparam.bModUu ) rstr += _T( 'u' );
					}
					else if( vwlO == rcjpcPrev.jpc.vwl )
					{
						if( 0 == rcparam.iOu ) {/* nop */ }
						else if( 1 == rcparam.iOu )	rstr += _T( 'h' );
						else if( 2 == rcparam.iOu )	rstr += _T( 'u' );
						else	throw std::exception();
					}
					else
					{
						rstr += _T( 'u' );
					}
				}
				bResult = true;
				break;
			case vwlE:	rstr += _T( 'e' );	bResult = true;	break;
			case vwlO:
				{
					if( vwlO == rcjpcPrev.jpc.vwl )
					{
						if( 0 == rcparam.iOo )
						{
							if( ( cnsNone == rcjpcNext.jpc.cns ) &&
								( vwlNone == rcjpcNext.jpc.vwl ) )
							{
								rstr += _T( 'o' );
							}
						}
						else if( 1 == rcparam.iOo )
						{
							/* nop */
						}
						else if( 2 == rcparam.iOo )
						{
							rstr += _T( 'o' );
						}
						else
						{
							throw std::exception();
						}
					}
					else
					{
						rstr += _T( 'o' );
					}
				}
				bResult = true;
				break;
			default:
				break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantK( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ka" );		bResult = true;	break;
			case vwlI:	rstr += _T( "ki" );		bResult = true;	break;
			case vwlU:	rstr += _T( "ku" );		bResult = true;	break;
			case vwlE:	rstr += _T( "ke" );		bResult = true;	break;
			case vwlO:	rstr += _T( "ko" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "kka" );	bResult = true;	break;
			case vwlI:	rstr += _T( "kki" );	bResult = true;	break;
			case vwlU:	rstr += _T( "kku" );	bResult = true;	break;
			case vwlE:	rstr += _T( "kke" );	bResult = true;	break;
			case vwlO:	rstr += _T( "kko" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantS( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "sa" );		bResult = true;	break;
			case vwlI:
				rstr += ( ! rcparam.bModShi ) ? _T( "shi" ) : _T( "si" );
				bResult = true;
				break;
			case vwlU:	rstr += _T( "su" );		bResult = true;	break;
			case vwlE:	rstr += _T( "se" );		bResult = true;	break;
			case vwlO:	rstr += _T( "so" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ssa" );	bResult = true;	break;
			case vwlI:
				rstr += ( ! rcparam.bModShi ) ? _T( "sshi" ) : _T( "ssi" );
				bResult = true;
				break;
			case vwlU:	rstr += _T( "ssu" );	bResult = true;	break;
			case vwlE:	rstr += _T( "sse" );	bResult = true;	break;
			case vwlO:	rstr += _T( "sso" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantT( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ta" );		bResult = true;	break;
			case vwlI:
				rstr += ( ! rcparam.bModShi ) ? _T( "chi" ) : _T( "ti" );
				bResult = true;
				break;
			case vwlU:
				rstr += ( ! rcparam.bModTsu ) ? _T( "tsu" ) : _T( "tu" );
				bResult = true;
				break;
			case vwlE:	rstr += _T( "te" );		bResult = true;	break;
			case vwlO:	rstr += _T( "to" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "tta" );	bResult = true;	break;
			case vwlI:
				if( ! rcparam.bModShi )
				{
					rstr += ( ! rcparam.bModTch ) ? _T( "tchi" ) : _T( "cchi" );
				}
				else
				{
					rstr += _T( "tti" );
				}
				bResult = true;
				break;
			case vwlU:
				rstr += ( ! rcparam.bModTsu ) ? _T( "ttsu" ) : _T( "ttu" );
				bResult = true;
				break;
			case vwlE:	rstr += _T( "tte" );	bResult = true;	break;
			case vwlO:	rstr += _T( "tto" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantN( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "na" );		bResult = true;	break;
			case vwlI:	rstr += _T( "ni" );		bResult = true;	break;
			case vwlU:	rstr += _T( "nu" );		bResult = true;	break;
			case vwlE:	rstr += _T( "ne" );		bResult = true;	break;
			case vwlO:	rstr += _T( "no" );		bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantH( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ha" );		bResult = true;	break;
			case vwlI:	rstr += _T( "hi" );		bResult = true;	break;
			case vwlU:
				rstr += ( ! rcparam.bModFu ) ? _T( "fu" ) : _T( "hu" );
				bResult = true;	break;
			case vwlE:	rstr += _T( "he" );		bResult = true;	break;
			case vwlO:	rstr += _T( "ho" );		bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantM( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ma" );		bResult = true;	break;
			case vwlI:	rstr += _T( "mi" );		bResult = true;	break;
			case vwlU:	rstr += _T( "mu" );		bResult = true;	break;
			case vwlE:	rstr += _T( "me" );		bResult = true;	break;
			case vwlO:	rstr += _T( "mo" );		bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantY( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ya" );		bResult = true;	break;
			case vwlU:	rstr += _T( "yu" );		bResult = true;	break;
			case vwlO:	rstr += _T( "yo" );		bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantR( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ra" );		bResult = true;	break;
			case vwlI:	rstr += _T( "ri" );		bResult = true;	break;
			case vwlU:	rstr += _T( "ru" );		bResult = true;	break;
			case vwlE:	rstr += _T( "re" );		bResult = true;	break;
			case vwlO:	rstr += _T( "ro" );		bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantW( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "wa" );		bResult = true;	break;
			case vwlI:	rstr += _T( "wi" );		bResult = true;	break;
			case vwlE:	rstr += _T( "we" );		bResult = true;	break;
			case vwlO:	rstr += _T( "wo" );		bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonant_NM( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & rcjpcNext, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		if( vwl_N == rcjpcCurrent.jpc.vwl )
		{
			if( ! rcparam.bModMmbp )
			{
				if( ( cnsM == rcjpcNext.jpc.cns ) ||
					( cnsB == rcjpcNext.jpc.cns ) ||
					( cnsP == rcjpcNext.jpc.cns ) )
				{
					rstr += _T( "m" );
				}
				else
				{
					rstr += _T( "n" );
				}
			}
			else
			{
				rstr += _T( "n" );
			}
			bResult = true;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantG( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ga" );		bResult = true;	break;
			case vwlI:	rstr += _T( "gi" );		bResult = true;	break;
			case vwlU:	rstr += _T( "gu" );		bResult = true;	break;
			case vwlE:	rstr += _T( "ge" );		bResult = true;	break;
			case vwlO:	rstr += _T( "go" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "gga" );	bResult = true;	break;
			case vwlI:	rstr += _T( "ggi" );	bResult = true;	break;
			case vwlU:	rstr += _T( "ggu" );	bResult = true;	break;
			case vwlE:	rstr += _T( "gge" );	bResult = true;	break;
			case vwlO:	rstr += _T( "ggo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantZ( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "za" );		bResult = true;	break;
			case vwlI:
				rstr += ( ! rcparam.bModJi_Zi ) ? _T( "ji" ) : _T( "zi" );
				bResult = true;
				break;
			case vwlU:	rstr += _T( "zu" );		bResult = true;	break;
			case vwlE:	rstr += _T( "ze" );		bResult = true;	break;
			case vwlO:	rstr += _T( "zo" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "zza" );	bResult = true;	break;
			case vwlI:	rstr += _T( "zzi" );	bResult = true;	break;
			case vwlU:	rstr += _T( "zzu" );	bResult = true;	break;
			case vwlE:	rstr += _T( "zze" );	bResult = true;	break;
			case vwlO:	rstr += _T( "zzo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantD( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "da" );		bResult = true;	break;
			case vwlI:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "ji" ) : _T( "di" );
				bResult = true;
				break;
			case vwlU:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "zu" ) : _T( "du" );
				bResult = true;
				break;
			case vwlE:	rstr += _T( "de" );		bResult = true;	break;
			case vwlO:	rstr += _T( "do" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "dda" );	bResult = true;	break;
			case vwlI:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "jji" ) : _T( "ddi" );
				bResult = true;
				break;
			case vwlU:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "zzu" ) : _T( "ddu" );
				bResult = true;
				break;
			case vwlE:	rstr += _T( "dde" );	bResult = true;	break;
			case vwlO:	rstr += _T( "ddo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantB( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ba" );		bResult = true;	break;
			case vwlI:	rstr += _T( "bi" );		bResult = true;	break;
			case vwlU:	rstr += _T( "bu" );		bResult = true;	break;
			case vwlE:	rstr += _T( "be" );		bResult = true;	break;
			case vwlO:	rstr += _T( "bo" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "bba" );	bResult = true;	break;
			case vwlI:	rstr += _T( "bbi" );	bResult = true;	break;
			case vwlU:	rstr += _T( "bbu" );	bResult = true;	break;
			case vwlE:	rstr += _T( "bbe" );	bResult = true;	break;
			case vwlO:	rstr += _T( "bbo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantP( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "pa" );		bResult = true;	break;
			case vwlI:	rstr += _T( "pi" );		bResult = true;	break;
			case vwlU:	rstr += _T( "pu" );		bResult = true;	break;
			case vwlE:	rstr += _T( "pe" );		bResult = true;	break;
			case vwlO:	rstr += _T( "po" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ppa" );	bResult = true;	break;
			case vwlI:	rstr += _T( "ppi" );	bResult = true;	break;
			case vwlU:	rstr += _T( "ppu" );	bResult = true;	break;
			case vwlE:	rstr += _T( "ppe" );	bResult = true;	break;
			case vwlO:	rstr += _T( "ppo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantKy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "kya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "kyu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "kyo" );	bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "kkya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "kkyu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "kkyo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantSh( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:
				rstr += ( ! rcparam.bModSh ) ? _T( "sha" ) : _T( "sya" );
				bResult = true;
				break;
			case vwlU:
				rstr += ( ! rcparam.bModSh ) ? _T( "shu" ) : _T( "syu" );
				bResult = true;
				break;
			case vwlO:
				rstr += ( ! rcparam.bModSh ) ? _T( "sho" ) : _T( "syo" );
				bResult = true;
				break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:
				rstr += ( ! rcparam.bModSh ) ? _T( "ssha" ) : _T( "ssya" );
				bResult = true;
				break;
			case vwlU:
				rstr += ( ! rcparam.bModSh ) ? _T( "sshu" ) : _T( "ssyu" );
				bResult = true;
				break;
			case vwlO:
				rstr += ( ! rcparam.bModSh ) ? _T( "ssho" ) : _T( "ssyo" );
				bResult = true;
				break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantCh( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:
				if( 0 == rcparam.iModCh )		rstr += _T( "cha" );
				else if( 1 == rcparam.iModCh )	rstr += _T( "tya" );
				else if( 2 == rcparam.iModCh )	rstr += _T( "cya" );
				else	throw std::exception();
				bResult = true;
				break;
			case vwlU:
				if( 0 == rcparam.iModCh )		rstr += _T( "chu" );
				else if( 1 == rcparam.iModCh )	rstr += _T( "tyu" );
				else if( 2 == rcparam.iModCh )	rstr += _T( "cyu" );
				else	throw std::exception();
				bResult = true;
				break;
			case vwlO:
				if( 0 == rcparam.iModCh )		rstr += _T( "cho" );
				else if( 1 == rcparam.iModCh )	rstr += _T( "tyo" );
				else if( 2 == rcparam.iModCh )	rstr += _T( "cyo" );
				else	throw std::exception();
				bResult = true;
				break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:
				if( 0 == rcparam.iModCh )
				{
					rstr += ( ! rcparam.bModTch ) ? _T( "tcha" ) : _T( "ccha" );
				}
				else if( 1 == rcparam.iModCh )
				{
					rstr += _T( "tya" );
				}
				else if( 2 == rcparam.iModCh )
				{
					rstr += _T( "cya" );
				}
				else
				{
					throw std::exception();
				}
				bResult = true;
				break;
			case vwlU:
				if( 0 == rcparam.iModCh )
				{
					rstr += ( ! rcparam.bModTch ) ? _T( "tchu" ) : _T( "cchu" );
				}
				else if( 1 == rcparam.iModCh )
				{
					rstr += _T( "tyu" );
				}
				else if( 2 == rcparam.iModCh )
				{
					rstr += _T( "cyu" );
				}
				else
				{
					throw std::exception();
				}
				bResult = true;
				break;
			case vwlO:
				if( 0 == rcparam.iModCh )
				{
					rstr += ( ! rcparam.bModTch ) ? _T( "tcho" ) : _T( "ccho" );
				}
				else if( 1 == rcparam.iModCh )
				{
					rstr += _T( "tyo" );
				}
				else if( 2 == rcparam.iModCh )
				{
					rstr += _T( "cyo" );
				}
				else
				{
					throw std::exception();
				}
				bResult = true;
				break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantNy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "nya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "nyu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "nyo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantHy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "hya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "hyu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "hyo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantMy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "mya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "myu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "myo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantRy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "rya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "ryu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "ryo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantGy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "gya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "gyu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "gyo" );	bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ggya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "ggyu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "ggyo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantJZy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:
				if( 0 == rcparam.iJZy )		rstr += _T( "ja" );
				else if( 1 == rcparam.iJZy )	rstr += _T( "zya" );
				else if( 2 == rcparam.iJZy )	rstr += _T( "jya" );
				else	throw std::exception();
				bResult = true;
				break;
			case vwlU:
				if( 0 == rcparam.iJZy )		rstr += _T( "ju" );
				else if( 1 == rcparam.iJZy )	rstr += _T( "zyu" );
				else if( 2 == rcparam.iJZy )	rstr += _T( "jyu" );
				else	throw std::exception();
				bResult = true;
				break;
			case vwlO:
				if( 0 == rcparam.iJZy )		rstr += _T( "jo" );
				else if( 1 == rcparam.iJZy )	rstr += _T( "zyo" );
				else if( 2 == rcparam.iJZy )	rstr += _T( "jyo" );
				else	throw std::exception();
				bResult = true;
				break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:
				if( 0 == rcparam.iJZy )			rstr += _T( "jja" );
				else if( 1 == rcparam.iJZy )	rstr += _T( "zzya" );
				else if( 2 == rcparam.iJZy )	rstr += _T( "jjya" );
				else	throw std::exception();
				bResult = true;
				break;
			case vwlU:
				if( 0 == rcparam.iJZy )			rstr += _T( "jju" );
				else if( 1 == rcparam.iJZy )	rstr += _T( "zzyu" );
				else if( 2 == rcparam.iJZy )	rstr += _T( "jjyu" );
				else	throw std::exception();
				bResult = true;
				break;
			case vwlO:
				if( 0 == rcparam.iJZy )			rstr += _T( "jjo" );
				else if( 1 == rcparam.iJZy )	rstr += _T( "zzyo" );
				else if( 2 == rcparam.iJZy )	rstr += _T( "jjyo" );
				else	throw std::exception();
				bResult = true;
				break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantJDy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "ja" ) : _T( "dya" );
				bResult = true;
				break;
			case vwlU:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "ju" ) : _T( "dyu" );
				bResult = true;
				break;
			case vwlO:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "jo" ) : _T( "dyo" );
				bResult = true;
				break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "jja" ) : _T( "ddya" );
				bResult = true;
				break;
			case vwlU:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "jju" ) : _T( "ddyu" );
				bResult = true;
				break;
			case vwlO:
				rstr += ( ! rcparam.bModJiZuJ_DiDuDy ) ? _T( "jjo" ) : _T( "ddyo" );
				bResult = true;
				break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantBy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "bya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "byu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "byo" );	bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "bbya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "bbyu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "bbyo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantPy( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "pya" );		bResult = true;	break;
			case vwlU:	rstr += _T( "pyu" );		bResult = true;	break;
			case vwlO:	rstr += _T( "pyo" );		bResult = true;	break;
			default:	break;
		}
	}
	else
	{
		switch( rcjpcCurrent.jpc.vwl )
		{
			case vwlA:	rstr += _T( "ppya" );	bResult = true;	break;
			case vwlU:	rstr += _T( "ppyu" );	bResult = true;	break;
			case vwlO:	rstr += _T( "ppyo" );	bResult = true;	break;
			default:	break;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantKw( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		if( vwlA == rcjpcCurrent.jpc.vwl )
		{
			rstr += _T( "kwa" );
			bResult = true;
		}
	}
	else
	{
		if( vwlA == rcjpcCurrent.jpc.vwl )
		{
			rstr += _T( "kkwa" );
			bResult = true;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantGw( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & /* rcparam */ )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		if( vwlA == rcjpcCurrent.jpc.vwl )
		{
			rstr += _T( "gwa" );
			bResult = true;
		}
	}
	else
	{
		if( vwlA == rcjpcCurrent.jpc.vwl )
		{
			rstr += _T( "ggwa" );
			bResult = true;
		}
	}
	return bResult;
}
static inline bool _ConvConsonantTei( std::string & rstr,
	SDescJpCharElm const & /* rcjpcPrev */, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & /* rcjpcNext */, SRomajiParam const & rcparam )
{
	bool bResult = false;
	if( !( rcjpcCurrent.bAfterSokuon ) )
	{
		if( vwlI == rcjpcCurrent.jpc.vwl )
		{
			rstr += ( ! rcparam.bModTei ) ? _T( "tei" ) : _T( "ti" );
			bResult = true;
		}
	}
	return bResult;
}

static inline bool _ConvertToRomaji( std::string & rstr,
	SDescJpCharElm const & rcjpcPrev, SDescJpCharElm const & rcjpcCurrent,
	SDescJpCharElm const & rcjpcNext, SRomajiParam const & rcparam )
{
	bool bResult = false;
	switch( rcjpcCurrent.jpc.cns )
	{
		case cnsA:
			bResult = _ConvConsonantA(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsK:
			bResult = _ConvConsonantK(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsS:
			bResult = _ConvConsonantS(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsT:
			bResult = _ConvConsonantT(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsN:
			bResult = _ConvConsonantN(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsH:
			bResult = _ConvConsonantH(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsM:
			bResult = _ConvConsonantM(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsY:
			bResult = _ConvConsonantY(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsR:
			bResult = _ConvConsonantR(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsW:
			bResult = _ConvConsonantW(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cns_NM:
			bResult = _ConvConsonant_NM(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsG:
			bResult = _ConvConsonantG(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsZ:
			bResult = _ConvConsonantZ(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsD:
			bResult = _ConvConsonantD(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsB:
			bResult = _ConvConsonantB(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsP:
			bResult = _ConvConsonantP(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsKy:
			bResult = _ConvConsonantKy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsSh:
			bResult = _ConvConsonantSh(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsCh:
			bResult = _ConvConsonantCh(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsNy:
			bResult = _ConvConsonantNy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsHy:
			bResult = _ConvConsonantHy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsMy:
			bResult = _ConvConsonantMy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsRy:
			bResult = _ConvConsonantRy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsGy:
			bResult = _ConvConsonantGy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsJZy:
			bResult = _ConvConsonantJZy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsJDy:
			bResult = _ConvConsonantJDy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsBy:
			bResult = _ConvConsonantBy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsPy:
			bResult = _ConvConsonantPy(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsKw:
			bResult = _ConvConsonantKw(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsGw:
			bResult = _ConvConsonantGw(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		case cnsTei:
			bResult = _ConvConsonantTei(
				rstr, rcjpcPrev, rcjpcCurrent, rcjpcNext, rcparam );
			break;
		default:
			break;
	}
	return bResult;
}

bool ConvertToRomaji( std::string & rstr,
	std::list<SDescJpCharElm> const & rcdescjpclist, SRomajiParam const & rcparam )
{
	rstr.clear();
	bool bFail = false;
	std::list<SDescJpCharElm>::const_iterator cit = rcdescjpclist.begin();
	if( rcdescjpclist.end() != cit )
	{
		SDescJpCharElm const jpcNone;
		std::list<SDescJpCharElm>::const_iterator citCurrent = cit;
		cit++;
		if( rcdescjpclist.end() == cit )
		{
			// ÇPå¬ÇæÇØ
			if( !_ConvertToRomaji( rstr, jpcNone, *citCurrent, jpcNone, rcparam ) )
			{
				bFail = true;
			}
		}
		else
		{
			// ç≈èâÇÃóvëf
			if( !_ConvertToRomaji( rstr, jpcNone, *citCurrent, *cit, rcparam ) )
			{
				bFail = true;
			}
			else
			{
				std::list<SDescJpCharElm>::const_iterator citPrev = citCurrent;
				citCurrent = cit;
				cit++;
				// ÇQå¬ñ⁄à»ç~
				while( ( !bFail ) && ( rcdescjpclist.end() != cit ) )
				{
					if( !_ConvertToRomaji( rstr, *citPrev, *citCurrent, *cit, rcparam ) )
					{
						bFail = true;
					}
					else
					{
						citPrev = citCurrent;
						citCurrent = cit;
					}
					cit++;
				}
				if( !bFail )
				{
					// ç≈å„
					if( !_ConvertToRomaji( rstr, *citPrev, *citCurrent, jpcNone, rcparam ) )
					{
						bFail = true;
					}
				}
			}
		}
	}
	return ( !bFail );
}

