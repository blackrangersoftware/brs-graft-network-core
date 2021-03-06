// Copyright (c) 2018, The Graft Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once


#include "wallet2.h"
#include "api/wallet2_api.h"
#include <memory>

class Serialization_portability_wallet_Test;

namespace tools
{

class GraftWallet : public wallet2
{
  friend class ::Serialization_portability_wallet_Test;
public:
  GraftWallet(cryptonote::network_type nettype, uint64_t kdf_rounds = 1, bool unattended = false);

  static std::unique_ptr<GraftWallet> createWallet(const std::string &daemon_address,
                                                   const std::string &daemon_host, int daemon_port,
                                                   const std::string &daemon_login,
                                                   cryptonote::network_type nettype);
  static std::unique_ptr<GraftWallet> createWallet(const std::string &account_data, const std::string &password,
                                                   const std::string &daemon_address, const std::string &daemon_host,
                                                   int daemon_port, const std::string &daemon_login,
                                                   cryptonote::network_type nettype, bool use_base64);


  static bool verify_message(const std::string &message, const std::string &address,
                             const std::string &signature, cryptonote::network_type nettype);

  /*!
   * \brief Generates a wallet or restores one.
   * \param  password       Password of wallet file
   * \param  recovery_param If it is a restore, the recovery key
   * \param  recover        Whether it is a restore
   * \param  two_random     Whether it is a non-deterministic wallet
   * \return                The secret key of the generated wallet
   */
  crypto::secret_key generateFromData(const std::string& password,
                                      const crypto::secret_key& recovery_param = crypto::secret_key(),
                                      bool recover = false, bool two_random = false);

  void loadFromData(const std::string& data, const std::string& password,
                    const std::string &cache_file = std::string(), bool use_base64 = true);

  void update_tx_cache(const pending_tx &ptx);

  std::string getAccountData(const std::string& password, bool use_base64 = true);

  std::string store_keys_to_data(const std::string& password, bool watch_only = false);
private:
  bool load_keys_from_data(const std::string& data, const std::string& password);
  void setup_cache_keys(const epee::wipeable_string &password);
};

}
