#ifdef USE_LIB_MEMMOVE
/*	
 *  Copyright (C) 2010-2011,2016
 *	"Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libkern.h>
#include <types.h>

void *memmove(void *dest ,void const *src ,size_t n)
{
  char *d = dest;
  char const *s = src;

  if (s < d)
    {
      /* Moving from low mem to hi mem; start at end.  */
      for (s += n, d += n; n; --n)
	*--d = *--s;
    }
  else if (s != d)
    {
      /* Moving from hi mem to low mem; start at beginning.  */
      while(--n)
        *d++ = *s++;
    }

  return d;
}

#endif // End of USE_LIB_MEMMOVE;
