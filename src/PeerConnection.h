/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_PEER_CONNECTION_H_
#define _D_PEER_CONNECTION_H_

#include "Option.h"
#include "Socket.h"
#include "Logger.h"
#include "common.h"

// we assume maximum length of incoming message is "piece" message with 16KB
// data. Messages beyond that size are dropped.
#define MAX_PAYLOAD_LEN (9+16*1024)

class PeerConnection {
private:
  int32_t cuid;
  SocketHandle socket;
  const Option* option;
  const Logger* logger;

  char resbuf[MAX_PAYLOAD_LEN];
  int32_t resbufLength;
  int32_t currentPayloadLength;
  char lenbuf[4];
  int32_t lenbufLength;

public:
  PeerConnection(int32_t cuid, const SocketHandle& socket, const Option* op);
  ~PeerConnection();
  
  // Returns the number of bytes written
  int32_t sendMessage(const unsigned char* data, int32_t dataLength);

  bool receiveMessage(unsigned char* data, int32_t& dataLength);

  /**
   * Returns true if a handshake message is fully received, otherwise returns
   * false.
   * In both cases, 'msg' is filled with received bytes and the filled length
   * is assigned to 'length'.
   */
  bool receiveHandshake(unsigned char* data, int32_t& dataLength, bool peek = false);
};

typedef SharedHandle<PeerConnection> PeerConnectionHandle;
typedef WeakHandle<PeerConnection> PeerConnectionWeakHandle;
#endif // _D_PEER_CONNECTION_H_
