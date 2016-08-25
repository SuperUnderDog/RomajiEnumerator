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

#pragma once
#include <list>


enum EConsonant
{
	cnsNone,
	cnsA,
	cnsK,
	cnsS,
	cnsT,
	cnsN,
	cnsH,
	cnsM,
	cnsY,
	cnsR,
	cnsW,
	cns_NM,
	cnsG,
	cnsZ,
	cnsD,
	cnsB,
	cnsP,
	cnsKy,
	cnsSh,
	cnsCh,
	cnsNy,
	cnsHy,
	cnsMy,
	cnsRy,
	cnsGy,
	cnsJZy,
	cnsJDy,
	cnsBy,
	cnsPy,
	cnsKw,
	cnsGw,
	cnsTei
};

enum EVowel
{
	vwlNone,
	vwlA,
	vwlI,
	vwlU,
	vwlE,
	vwlO,
	vwl_N
};

struct SJpChar
{
	EConsonant cns;
	EVowel vwl;

	SJpChar( void ) : cns( cnsNone ), vwl( vwlNone ) {}
	SJpChar( EConsonant const cnsArg, EVowel const vwlArg ) :
		cns( cnsArg ), vwl( vwlArg ) {}
};

struct SDescJpCharElm
{
	bool bAfterSokuon;
	SJpChar jpc;

	SDescJpCharElm( void ) : bAfterSokuon( false ), jpc( cnsNone, vwlNone )
	{}
	SDescJpCharElm( bool const bArgAfterSokuon, SJpChar const & rcjpcArg ) :
		bAfterSokuon( bArgAfterSokuon ), jpc( rcjpcArg )
	{}
};


extern bool ParseHiragana( std::list<SDescJpCharElm> & rdescjpclist, TCHAR const * const pctcsz );
