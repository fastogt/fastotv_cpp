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

#include <fastotv/types/kvs_prop.h>

#define STREAM_NAME_FIELD "stream_name"
#define ACCESS_KEY_FIELD "access_key"
#define SECRET_KEY_FIELD "secret_key"
#define AWS_REGION_FIELD "aws_region"
#define STORAGE_SIZE_FIELD "storage_size"

namespace fastotv {

KVSProp::KVSProp() : KVSProp(std::string(), std::string(), std::string(), std::string()) {}

KVSProp::KVSProp(const stream_name_t& name,
                 const access_key_t& access_key,
                 const secret_key_t& secret_key,
                 const aws_region_t& aws_region,
                 storage_size_t storage)
    : stream_name_(name),
      access_key_(access_key),
      secret_key_(secret_key),
      aws_region_(aws_region),
      storage_size_(storage) {}

bool KVSProp::IsValid() const {
  return !stream_name_.empty() && !access_key_.empty() && !secret_key_.empty() && !aws_region_.empty();
}

KVSProp::stream_name_t KVSProp::GetStreamName() const {
  return stream_name_;
}

void KVSProp::SetStreamName(const stream_name_t& name) {
  stream_name_ = name;
}

KVSProp::access_key_t KVSProp::GetAccessKey() const {
  return access_key_;
}

void KVSProp::SetAccessKey(const access_key_t& key) {
  access_key_ = key;
}

KVSProp::secret_key_t KVSProp::GetSecretKey() const {
  return secret_key_;
}

void KVSProp::SetSecretKey(const secret_key_t& key) {
  secret_key_ = key;
}

KVSProp::aws_region_t KVSProp::GetAwsRegion() const {
  return aws_region_;
}

void KVSProp::SetAwsRegion(const aws_region_t& region) {
  aws_region_ = region;
}

KVSProp::storage_size_t KVSProp::GetStorageSize() const {
  return storage_size_;
}

void KVSProp::SetStorageSize(storage_size_t size) {
  storage_size_ = size;
}

bool KVSProp::Equals(const KVSProp& key) const {
  return stream_name_ == key.stream_name_ && access_key_ == key.access_key_ && secret_key_ == key.secret_key_ &&
         aws_region_ == key.aws_region_ && storage_size_ == key.storage_size_;
}

common::Optional<KVSProp> KVSProp::Make(common::HashValue* json) {
  if (!json) {
    return common::Optional<KVSProp>();
  }

  KVSProp res;
  common::Value* name_field = json->Find(STREAM_NAME_FIELD);
  std::string name;
  if (!name_field || !name_field->GetAsBasicString(&name)) {
    return common::Optional<KVSProp>();
  }
  res.stream_name_ = name;

  common::Value* acc_field = json->Find(ACCESS_KEY_FIELD);
  std::string acc;
  if (!acc_field || !acc_field->GetAsBasicString(&acc)) {
    return common::Optional<KVSProp>();
  }
  res.access_key_ = acc;

  common::Value* sec_field = json->Find(SECRET_KEY_FIELD);
  std::string sec;
  if (!sec_field || !sec_field->GetAsBasicString(&sec)) {
    return common::Optional<KVSProp>();
  }
  res.secret_key_ = sec;

  common::Value* aws_field = json->Find(AWS_REGION_FIELD);
  std::string aws;
  if (!aws_field || !aws_field->GetAsBasicString(&aws)) {
    return common::Optional<KVSProp>();
  }
  res.aws_region_ = aws;

  common::Value* stor_field = json->Find(STORAGE_SIZE_FIELD);
  int64_t stor;
  if (!stor_field || !stor_field->GetAsInteger64(&stor)) {
    return common::Optional<KVSProp>();
  }
  res.storage_size_ = stor;

  return res;
}

common::Error KVSProp::DoDeSerialize(json_object* serialized) {
  KVSProp res;
  std::string name;
  common::Error err = GetStringField(serialized, STREAM_NAME_FIELD, &name);
  if (err) {
    return err;
  }
  res.stream_name_ = name;

  std::string acc;
  err = GetStringField(serialized, ACCESS_KEY_FIELD, &acc);
  if (err) {
    return err;
  }
  res.access_key_ = acc;

  std::string sec;
  err = GetStringField(serialized, SECRET_KEY_FIELD, &sec);
  if (err) {
    return err;
  }
  res.secret_key_ = sec;

  std::string aws;
  err = GetStringField(serialized, AWS_REGION_FIELD, &aws);
  if (err) {
    return err;
  }
  res.aws_region_ = aws;

  int stor;
  err = GetIntField(serialized, STORAGE_SIZE_FIELD, &stor);
  if (err) {
    return err;
  }
  res.storage_size_ = stor;

  *this = res;
  return common::Error();
}

common::Error KVSProp::SerializeFields(json_object* out) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  ignore_result(SetStringField(out, STREAM_NAME_FIELD, stream_name_));
  ignore_result(SetStringField(out, ACCESS_KEY_FIELD, access_key_));
  ignore_result(SetStringField(out, SECRET_KEY_FIELD, secret_key_));
  ignore_result(SetStringField(out, AWS_REGION_FIELD, aws_region_));
  ignore_result(SetIntField(out, STORAGE_SIZE_FIELD, storage_size_));
  return common::Error();
}

}  // namespace fastotv
