#include <iostream>
#include <ratio>

#include "kpl-config.h"
#include "kpl-guid.h"

#ifdef KPL_WINDOWS
#include <objbase.h>
#endif

namespace kplge {
std::string Guid::to_str() const {
  char guid_cstr[39];
  snprintf(
      guid_cstr, sizeof(guid_cstr),
      "{"
      "%02x%02x%02x%02x"
      "-"
      "%02x%02x"
      "-"
      "%02x%02x"
      "-"
      "%02x%02x"
      "-"
      "%02x%02x%02x%02x%02x%02x"
      "}",
      bytes_[0], bytes_[1], bytes_[2], bytes_[3], bytes_[4], bytes_[5],
      bytes_[6], bytes_[7], bytes_[8], bytes_[9], bytes_[10], bytes_[11],
      bytes_[12], bytes_[13], bytes_[14], bytes_[15]);
  return std::string{guid_cstr};
}

std::ostream& operator<<(std::ostream& out, const Guid& guid) {
  out << guid.to_str();
  return out;
}

#ifdef KPL_WINDOWS
Guid generate_guid() {
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
#endif  // KPL_WINDOWS
}  // namespace kplge