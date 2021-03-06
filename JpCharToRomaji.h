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

#include <string>

#include "JpCharParser.h"


struct SRomajiParam
{
	bool bModUu;			// うう	false:u / true:uu
	int iOu;				// おう	0:o / 1:ou->oh / 2:ou
	int iOo;				// おお	0:o(last oo) / 1:o / 2:oo
	bool bModShi;			// し	false:shi / true:si
	bool bModChi;			// ち	false:chi / true:ti
	bool bModTch;			// っch	false:tch / true:tt
	bool bModTsu;			// つ	false:tsu / true:tu
	bool bModFu;			// ふ	false:fu / true:hu
	bool bModMmbp;			// んｂ	false:mba / true:nba
	bool bModJi_Zi;			// じ	false:ji / true:zi
	bool bModJiZuJ_DiDuDy;	// ぢづ	false:zizujajujo / true:didudyadyudyo
	bool bModSh;			// しゃ	false:shashusho / true:syasyusyo
	int iModCh;				// ちゃ	0:chachucho / 1:tyatyutyo / 2:cyacyucyo
	int iJZy;				// じゃ	0:jajujo / 1:zyazyuzyo / 2:jyajyujyo
	bool bModTei;			// てぃ	false:tei / true:ti
};

extern bool ConvertToRomaji( std::string & rstr,
	std::list<SDescJpCharElm> const & rcdescjpclist, SRomajiParam const & rcparam );


