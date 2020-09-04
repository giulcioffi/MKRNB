/*
  This file is part of the MKR NB library.
  Copyright (C) 2017  Arduino AG (http://www.arduino.cc/)
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _NB_HTTP_UTILS_H_
#define _NB_HTTP_UTILS_H_

#include "NBClient.h"
#include "utility/NBRootCerts.h"
class NBHttpUtils: public NBClient {

public:
  NBHttpUtils();
  virtual ~NBHttpUtils();

  virtual void setSignedCertificate(const uint8_t* cert, const char* name, size_t size);
  virtual void setRootCertificate();
  virtual void setPrivateKey(const uint8_t* key, const char* name, size_t size);
  virtual void useSignedCertificate(const char* name);
  virtual void usePrivateKey(const char* name);
  virtual void setTrustedRoot(const char* name);
  virtual void setUserRoots(const NBRootCert * userRoots, size_t size);
  virtual void eraseTrustedRoot();
  virtual void eraseAllCertificates();
  virtual void eraseCert(const char* name, int type);
  virtual void handleUrc(const String& urc);
  virtual void enableSSL();
  virtual void disableSSL();
  virtual void configServer(const char* url, int httpport);
  virtual void head(const char* path, const char* filename);
  virtual void get(const char* path, const char* filename);
  virtual void read(const char* filename);
  virtual void del(const char* path, const char* filename);
  virtual void put(const char* path, const char* filename);
  virtual void post(const char* path, const char* filename);
  virtual bool responseStatus();
private:
  void removeCertForType(String certname, int type);

private:
  static bool _rootCertsLoaded;
  int _certIndex;
  const NBRootCert * _nbRoots;
  int _sizeRoot;
  bool _httpresp;
  bool _ssl;

};

#endif