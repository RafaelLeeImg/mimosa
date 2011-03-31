/* Copyleft(c)2010 HackerFellowship. All lefts reserved.
   
 * NalaGinrut <NalaGinrut@gmail.com>
 
 * May Lord Bless!Happy Hacking!
 
 * This program is free software;you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundataion;either version 2 of the License,or (at 
 * your option) any later version.
 
 * You should have read the GNU General Public License before start "RTFSC".
 
 * If not,see <http://www.gnu.org/licenses/>
 */

#include <types.h>
#include <retnum.h>
#include <libkern.h>
#include <generic/generic_stream.h>

gs_boj_t *generic_stream_create(char *name ,char *buffer,
				gs_type_t type ,u32_t status,
				void *custom ,
				gs_alloc_t alloc,
				gs_free_t free)
{
  gs_obj_t *gso = (gs_obj_t*)kmalloc(sizeof(gs_obj_t));

  assert(gso != NULL);
  assert(buffer != NULL);
  assert(name != NULL);

  gso->name = strndup(name ,GSO_MAX_NAME_LEN);
  gso->buffer = buffer;
  gso->position = 0;
  gso->count = 0;
  gso->type = type;
  gso->status = status;
  gso->custom = custom;

  if((custom != NULL) ^ (type == GST_CUSTOM))
    {
      panic("Only GST_CUSTOM could have custom!");
    }

  if(custom)
    {
      gso->alloc = alloc;
      gso->free = free;
    }
  else
    {
      gso->alloc = NULL;
      gso->free = NULL;
    }

  return gso;
}


retnum generic_stream_shoot(void const *data ,gs_obj_t *gso ,size_t size)
{
  void *buf = gso->buffer;
  size_t count = size;

  if(count < 0)
    return EINVSZ;
  
  count = (size <= GSO_MAX_BUF_LEN) ? size : GSO_MAX_BUF_LEN;
  memcpy(buf ,data ,count);

  return OK;
}

retnum generic_stream_imbibe(gs_obj_t *gso ,void *data ,size_t size)
{
  void const *buf = gso->buffer;
  size_t count = size;

  if(count < 0)
    return EINVSZ;

  count = (size <= GSO_MAX_BUF_LEN) ? size : GSO_MAX_BUF_LEN;
  memcpy(data ,buf ,count);
}

retnum generic_stream_dry(gs_obj_t *gso)
{
  kfree(gso->name);
  gso->name = NULL;

  if(gso->type != GST_DEVICE)
    {
      kfree(gso->buffer);
    }
  gso->buffer = NULL;

  if(gso->type == GST_CUSTOM)
    {
      gso->free((void*)gso);
    }
  gso->custom = NULL;
    
  gso->status |= GSOS_DRY;

  return OK;
}

  
