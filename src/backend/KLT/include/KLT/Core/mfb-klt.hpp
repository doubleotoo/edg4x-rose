
#ifndef __KLT_CORE_MFB_KLT_HPP__
#define __KLT_CORE_MFB_KLT_HPP__

#include "MFB/Sage/driver.hpp"

namespace MultiFileBuilder {

template <typename Object>
class KLT {};

template <>
class Driver<KLT> {
  public:
    template <typename Object>
    typename KLT<Object>::build_result_t build(const typename KLT<Object>::object_desc_t & desc);
};

class KLT_Driver : public Driver<Sage>, public Driver<KLT> {
  public:
    KLT_Driver(SgProject * project_ = NULL);
};

}

#endif /* __KLT_CORE_MFB_KLT_HPP__ */