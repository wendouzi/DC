/* Copyright (C) 1991,1992,1994-2001,2003,2004,2007
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/*
 *	ISO C99 Standard: 7.2 Diagnostics	<assert.h>
 */
#pragma once
#include <iostream>
#include <stdlib.h>
#define assert(exp) { if (!(exp)) { std::cout << "Assertion failed: " << #exp << "\n" << "line: " << __LINE__ << "\n" << "file: " << __FILE__ << "\n";exit(EXIT_FAILURE); } }

