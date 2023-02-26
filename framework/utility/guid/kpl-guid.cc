#include <iostream>

#include "kpl-config.h"
#include "kpl-guid.h"

#ifdef KPL_WINDOWS
#include <objbase.h>
kplge::Guid kplge::generate_guid() {
  GUID win_guid;
  CoCreateGuid(&win_guid);
  std::array<unsigned char, 16> bytes = {
      (unsigned char)((win_guid.Data1 >> 24) & 0xFF),
      (unsigned char)((win_guid.Data1 >> 16) & 0xFF),
      (unsigned char)((win_guid.Data1 >> 8) & 0xFF),
      (unsigned char)((win_guid.Data1) & 0xff),
      (unsigned char)((win_guid.Data2 >> 8) & 0xFF),
      (unsigned char)((win_guid.Data2) & 0xff),
      (unsigned char)((win_guid.Data3 >> 8) & 0xFF),
      (unsigned char)((win_guid.Data3) & 0xFF),
      (unsigned char)win_guid.Data4[0],
      (unsigned char)win_guid.Data4[1],
      (unsigned char)win_guid.Data4[2],
      (unsigned char)win_guid.Data4[3],
      (unsigned char)win_guid.Data4[4],
      (unsigned char)win_guid.Data4[5],
      (unsigned char)win_guid.Data4[6],
      (unsigned char)win_guid.Data4[7]};
  return Guid{bytes};
}
#endif