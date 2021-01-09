/*  Copyright (C) 2014-2021 FastoGT. All right reserved.
    This file is part of fastocloud.
    fastocloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    fastocloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with fastocloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>

#include <common/serializer/json_serializer.h>
#include <common/value.h>

namespace fastotv {

class SrtKey : public common::serializer::JsonSerializer<SrtKey> {
 public:
  typedef JsonSerializer<SrtKey> base_class;
  typedef std::string srt_passphrase_t;
  typedef int key_len_t;

  SrtKey();
  explicit SrtKey(const srt_passphrase_t& passphrase, key_len_t key_len);

  bool IsValid() const;

  srt_passphrase_t GetSrtPassPhrase() const;
  void SetSrtPassPhrase(const srt_passphrase_t& pass);

  void SetKeyLen(key_len_t key_len);
  key_len_t GetKeyLen() const;

  bool Equals(const SrtKey& key) const;

  static common::Optional<SrtKey> Make(common::HashValue* json);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  srt_passphrase_t passphrase_;
  key_len_t key_len_;
};

inline bool operator==(const SrtKey& left, const SrtKey& right) {
  return left.Equals(right);
}

inline bool operator!=(const SrtKey& x, const SrtKey& y) {
  return !(x == y);
}

}  // namespace fastotv
