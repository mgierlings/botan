/**
 * XMSS WOTS Addressed Public Key
 * (C) 2016 Matthias Gierlings
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/


#ifndef BOTAN_XMSS_WOTS_ADDRESSED_PUBLICKEY_H__
#define BOTAN_XMSS_WOTS_ADDRESSED_PUBLICKEY_H__

#include <botan/xmss_address.h>
#include <botan/xmss_wots_publickey.h>

namespace Botan {

/**
 * Wrapper class to pair a XMSS_WOTS_PublicKey with an XMSS Address. Since
 * the PK_Ops::Verification interface does not allow an extra address
 * parameter to be passed to the sign(RandomNumberGenerator&), the address
 * needs to be stored together with the key and passed to the
 * XMSS_WOTS_Verification_Operation() on creation.
 **/
class XMSS_WOTS_Addressed_PublicKey : public virtual Public_Key
   {
   public:
      XMSS_WOTS_Addressed_PublicKey(const XMSS_WOTS_PublicKey& public_key)
         : m_pub_key(public_key), m_adrs() {}

      XMSS_WOTS_Addressed_PublicKey(const XMSS_WOTS_PublicKey& public_key,
                                    const XMSS_Address& adrs)
         : m_pub_key(public_key), m_adrs(adrs) {}

      XMSS_WOTS_Addressed_PublicKey(XMSS_WOTS_PublicKey&& public_key)
         : m_pub_key(std::move(public_key)), m_adrs() {}

      XMSS_WOTS_Addressed_PublicKey(XMSS_WOTS_PublicKey&& public_key,
                                    XMSS_Address&& adrs)
         : m_pub_key(std::move(public_key)), m_adrs(std::move(adrs)) {}

      const XMSS_WOTS_PublicKey& public_key() const { return m_pub_key; }
      XMSS_WOTS_PublicKey& public_key()  { return m_pub_key; }

      const XMSS_Address& address() const { return m_adrs; }
      XMSS_Address& address() { return m_adrs; }

      virtual std::string algo_name() const override
         {
         return m_pub_key.algo_name();
         }

      virtual AlgorithmIdentifier algorithm_identifier() const override
         {
         return m_pub_key.algorithm_identifier();
         }

      virtual bool check_key(RandomNumberGenerator& rng,
                             bool strong) const override
         {
         return m_pub_key.check_key(rng, strong);
         }

      virtual std::unique_ptr<PK_Ops::Verification>
         create_verification_op(const std::string& params,
                                const std::string& provider) const override
         {
         return m_pub_key.create_verification_op(params, provider);
         }

      virtual OID get_oid() const override
         {
         return m_pub_key.get_oid();
         }

      virtual size_t estimated_strength() const override
         {
         return m_pub_key.estimated_strength();
         }

      virtual size_t max_input_bits() const override
         {
         return m_pub_key.max_input_bits();
         }

      virtual size_t message_part_size() const override
         {
         return m_pub_key.message_part_size();
         }

      virtual size_t message_parts() const override
         {
         return m_pub_key.message_parts();
         }

      virtual std::vector<byte> x509_subject_public_key() const override
         {
         return m_pub_key.x509_subject_public_key();
         }

   protected:
      XMSS_WOTS_PublicKey m_pub_key;
      XMSS_Address m_adrs;
   };

}

#endif