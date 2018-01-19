#ifndef INCLUDED_PICK_GIFTS_H
#define INCLUDED_PICK_GIFTS_H

#include "gift.h"
#include <vector>

void pickGifts( unsigned long long balance,
		int number,
		const vector< Gift >& gifts,
		int startIndex,
		vector< Gift >& selected );

#endif
