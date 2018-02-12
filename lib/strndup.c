#ifdef USE_LIB_STRNDUP
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

#include <mm/mm.h>
#include <libkern.h>
#include <types.h>
// extern kmalloc;
extern void *kmalloc(size_t size);

char *strndup(char const *str ,size_t n)
{
  size_t len = strnlen (str, n);
  char *new = kmalloc(len + 1);

  if (new == NULL)
    return NULL;

  new[len] = '\0';
  return memcpy (new, str, len);
}

#endif // End of USE_LIB_STRNDUP;
