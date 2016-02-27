// grappa
#include <Grappa.hpp>
#include <Collective.hpp>
#include <GlobalCompletionEvent.hpp>
#include <Metrics.hpp>

using namespace Grappa;

// stl
#include <vector>
#include <iomanip>
#include <cstring>
#include <limits>

// query library
#include "relation_io.hpp"
#include "MatchesDHT.hpp"
#include "DoubleDHT.hpp"
#include "MapReduce.hpp"
//#include "HashJoin.hpp"
#include "DHT_symmetric.hpp"
#include "Aggregates.hpp"
#include "Iterators.hpp"
#include "radish_utils.h"
#include "stats.h"
#include "strings.h"
#include "dates.h"
#include "relation.hpp"

DEFINE_uint64( nt, 30, "hack: number of tuples");
DEFINE_bool( jsonsplits, false, "interpret input file F as F/part-*,"
                             "and containing json records");

template <typename T>
struct counter {
  T count;
  static GlobalAddress<counter<T>> create(T init) {
    auto res = symmetric_global_alloc<counter<T>>();
    on_all_cores([res, init] {
        res->count = init;
        });           
    return res;
  }
} GRAPPA_BLOCK_ALIGNED;

template <typename T>
T get_count(GlobalAddress<counter<T>> p) {
  return p->count;                           
}

          // can be just the necessary schema
  class MaterializedTupleRef_V1_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V1_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V1_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V1_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V1_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V1_0_1_2));
    //}
    MaterializedTupleRef_V1_0_1_2 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V1_0_1_2(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V1_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V1_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V1_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V1_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V1_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V1_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V1_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } GRAPPA_BLOCK_ALIGNED;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V1_0_1_2& t) {
    return t.dump(o);
  }

Relation<MaterializedTupleRef_V1_0_1_2> V1;

GlobalCompletionEvent V2(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_1_gce_incomplete, [] {
  return V2.incomplete();
});
Relation<aligned_vector<MaterializedTupleRef_V1_0_1_2>> _temp_table_matA;

          // can be just the necessary schema
  class MaterializedTupleRef_V3_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V3_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V3_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V3_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V3_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V3_0));
    //}
    MaterializedTupleRef_V3_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V3_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V3_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V3_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V3_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V3_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V3_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V3_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V3_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V3_0& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V4_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V4_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V4_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V4_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V4_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V4_0));
    //}
    MaterializedTupleRef_V4_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V4_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V4_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V4_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V4_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V4_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V4_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V4_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V4_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V4_0& t) {
    return t.dump(o);
  }

MaterializedTupleRef_V4_0 t_002;
Relation<aligned_vector<MaterializedTupleRef_V3_0>> _temp_table_epsilon;

          // can be just the necessary schema
  class MaterializedTupleRef_V5_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V5_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V5_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V5_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V5_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V5_0));
    //}
    MaterializedTupleRef_V5_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V5_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V5_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V5_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V5_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V5_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V5_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V5_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V5_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V5_0& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V6_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V6_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V6_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V6_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V6_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V6_0));
    //}
    MaterializedTupleRef_V6_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V6_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V6_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V6_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V6_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V6_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V6_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V6_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V6_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V6_0& t) {
    return t.dump(o);
  }

MaterializedTupleRef_V6_0 t_004;
Relation<aligned_vector<MaterializedTupleRef_V5_0>> _temp_table_prunelimit;

          // can be just the necessary schema
  class MaterializedTupleRef_V7_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V7_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V7_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V7_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V7_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V7_0));
    //}
    MaterializedTupleRef_V7_0 (
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V7_0(const std::tuple<
        
        int64_t
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        int64_t
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V7_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V7_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V7_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V7_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V7_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V7_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V7_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V7_0& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V8_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V8_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V8_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V8_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V8_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V8_0));
    //}
    MaterializedTupleRef_V8_0 (
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V8_0(const std::tuple<
        
        int64_t
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        int64_t
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V8_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V8_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V8_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V8_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V8_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V8_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V8_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V8_0& t) {
    return t.dump(o);
  }

MaterializedTupleRef_V8_0 t_006;
Relation<aligned_vector<MaterializedTupleRef_V7_0>> _temp_table_newchaos;

GlobalCompletionEvent V9(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_5_gce_incomplete, [] {
  return V9.incomplete();
});
Relation<aligned_vector<MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0>> _temp_table_oldchaos;

          // can be just the necessary schema
  class MaterializedTupleRef_V10_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V10_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V10_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V10_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V10_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V10_0_1_2));
    //}
    MaterializedTupleRef_V10_0_1_2 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V10_0_1_2(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V10_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V10_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V10_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V10_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V10_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V10_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V10_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V10_0_1_2& t) {
    return t.dump(o);
  }

GlobalCompletionEvent V11(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_6_gce_incomplete, [] {
  return V11.incomplete();
});
MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0 t_010;
          // can be just the necessary schema
  class MaterializedTupleRef_V12_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V12_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V12_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V12_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V12_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V12_0_1_2));
    //}
    MaterializedTupleRef_V12_0_1_2 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V12_0_1_2(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V12_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V12_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V12_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V12_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V12_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V12_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V12_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V12_0_1_2& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V13_0_1_2_3 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    
        double f3;
    

    static constexpr int numFields() {
      return 4;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V13_0_1_2_3 _t;
        return

        
            ((char*)&_t.f3) + sizeof(_t.f3) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V13_0_1_2_3 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (((char*)&_t.f3) - ((char*)&_t.f2)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f2) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V13_0_1_2_3 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V13_0_1_2_3 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V13_0_1_2_3));
    //}
    MaterializedTupleRef_V13_0_1_2_3 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               ,
                       
                               const double& a3
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
            f3 = a3;
        
    }

    
    


    MaterializedTupleRef_V13_0_1_2_3(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
            f3 = std::get<3>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
            std::get<3>(r) = f3;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V13_0_1_2_3 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //        f3 = vals[3];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V13_0_1_2_3 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V13_0_1_2_3 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f3;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << " "
        
        << f3 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V13_0_1_2_3 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V13_0_1_2_3::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V13_0_1_2_3 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V13_0_1_2_3::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      
        o << f3 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V13_0_1_2_3& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V15_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V15_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V15_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V15_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V15_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V15_0_1));
    //}
    MaterializedTupleRef_V15_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V15_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V15_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V15_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V15_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V15_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V15_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V15_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V15_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V15_0_1& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V16_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V16_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V16_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V16_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V16_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V16_0));
    //}
    MaterializedTupleRef_V16_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V16_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V16_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V16_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V16_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V16_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V16_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V16_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V16_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V16_0& t) {
    return t.dump(o);
  }

decltype(DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V16_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( )) group_hash_000;

          // can be just the necessary schema
  class MaterializedTupleRef_V17_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V17_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V17_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V17_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V17_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V17_0));
    //}
    MaterializedTupleRef_V17_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V17_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V17_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V17_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V17_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V17_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V17_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V17_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V17_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V17_0& t) {
    return t.dump(o);
  }

decltype(DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V17_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( )) group_hash_001;

          // can be just the necessary schema
  class MaterializedTupleRef_V18_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V18_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V18_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V18_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V18_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V18_0_1));
    //}
    MaterializedTupleRef_V18_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V18_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V18_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V18_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V18_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V18_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V18_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V18_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V18_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V18_0_1& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V19_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V19_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V19_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V19_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V19_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V19_0));
    //}
    MaterializedTupleRef_V19_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V19_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V19_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V19_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V19_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V19_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V19_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V19_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V19_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V19_0& t) {
    return t.dump(o);
  }

decltype(DHT_symmetric<std::tuple<int64_t,int64_t>,MaterializedTupleRef_V19_0,hash_tuple::hash<std::tuple<int64_t,int64_t>>>::create_DHT_symmetric( )) group_hash_002;

          // can be just the necessary schema
  class MaterializedTupleRef_V20_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V20_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V20_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V20_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V20_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V20_0));
    //}
    MaterializedTupleRef_V20_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V20_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V20_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V20_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V20_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V20_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V20_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V20_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V20_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V20_0& t) {
    return t.dump(o);
  }

decltype(DHT_symmetric<std::tuple<int64_t,int64_t>,MaterializedTupleRef_V20_0,hash_tuple::hash<std::tuple<int64_t,int64_t>>>::create_DHT_symmetric( )) group_hash_003;

          // can be just the necessary schema
  class MaterializedTupleRef_V21_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V21_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V21_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V21_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V21_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V21_0_1_2));
    //}
    MaterializedTupleRef_V21_0_1_2 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V21_0_1_2(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V21_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V21_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V21_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V21_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V21_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V21_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V21_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V21_0_1_2& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V22_0_1_2_3 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    
        int64_t f2;
    
        double f3;
    

    static constexpr int numFields() {
      return 4;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V22_0_1_2_3 _t;
        return

        
            ((char*)&_t.f3) + sizeof(_t.f3) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V22_0_1_2_3 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (((char*)&_t.f3) - ((char*)&_t.f2)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f2) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V22_0_1_2_3 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V22_0_1_2_3 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V22_0_1_2_3));
    //}
    MaterializedTupleRef_V22_0_1_2_3 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               ,
                       
                               const int64_t& a2
                               ,
                       
                               const double& a3
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
            f3 = a3;
        
    }

    
    


    MaterializedTupleRef_V22_0_1_2_3(const std::tuple<
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
            f3 = std::get<3>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
            std::get<3>(r) = f3;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V22_0_1_2_3 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //        f3 = vals[3];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V22_0_1_2_3 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V22_0_1_2_3 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f3;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << " "
        
        << f3 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V22_0_1_2_3 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V22_0_1_2_3::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V22_0_1_2_3 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V22_0_1_2_3::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      
        o << f3 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V22_0_1_2_3& t) {
    return t.dump(o);
  }

GlobalCompletionEvent V24(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_7_gce_incomplete, [] {
  return V24.incomplete();
});
GlobalCompletionEvent V25(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_8_gce_incomplete, [] {
  return V25.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V27_0_1_2_3_4_5 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    
        int64_t f3;
    
        int64_t f4;
    
        double f5;
    

    static constexpr int numFields() {
      return 6;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V27_0_1_2_3_4_5 _t;
        return

        
            ((char*)&_t.f5) + sizeof(_t.f5) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V27_0_1_2_3_4_5 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (((char*)&_t.f3) - ((char*)&_t.f2)) << ",";
        
        std::cout << (((char*)&_t.f4) - ((char*)&_t.f3)) << ",";
        
        std::cout << (((char*)&_t.f5) - ((char*)&_t.f4)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f4) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V27_0_1_2_3_4_5 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V27_0_1_2_3_4_5 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V27_0_1_2_3_4_5));
    //}
    MaterializedTupleRef_V27_0_1_2_3_4_5 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               ,
                       
                               const int64_t& a3
                               ,
                       
                               const int64_t& a4
                               ,
                       
                               const double& a5
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
            f3 = a3;
        
            f4 = a4;
        
            f5 = a5;
        
    }

    
    


    MaterializedTupleRef_V27_0_1_2_3_4_5(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
            f3 = std::get<3>(o);
        
            f4 = std::get<4>(o);
        
            f5 = std::get<5>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
            std::get<3>(r) = f3;
        
            std::get<4>(r) = f4;
        
            std::get<5>(r) = f5;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V27_0_1_2_3_4_5 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //        f3 = vals[3];
    //    
    //        f4 = vals[4];
    //    
    //        f5 = vals[5];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V27_0_1_2_3_4_5 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V27_0_1_2_3_4_5 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f3;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f4;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f5;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << " "
        
        << f3 << " "
        
        << f4 << " "
        
        << f5 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V27_0_1_2_3_4_5 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V27_0_1_2_3_4_5::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V27_0_1_2_3_4_5 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V27_0_1_2_3_4_5::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      
        o << f3 << ",";
      
        o << f4 << ",";
      
        o << f5 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V27_0_1_2_3_4_5& t) {
    return t.dump(o);
  }

static MaterializedTupleRef_V27_0_1_2_3_4_5 create_V28(const MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2& t1, const MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2& t2) {
    MaterializedTupleRef_V27_0_1_2_3_4_5 t;
    
        t.f0 = t1.f0;
    
        t.f1 = t1.f1;
    
        t.f2 = t1.f2;
    

    
        t.f3 = t2.f0;
    
        t.f4 = t2.f1;
    
        t.f5 = t2.f2;
    

    return t;
}
MaterializedTupleRef_V20_0 __V20_update(const MaterializedTupleRef_V20_0& state, const MaterializedTupleRef_V21_0_1_2& t_019) {
    
    auto _v0 = Aggregates::SUM<double, double>(state.f0,t_019.f2);
    
    return MaterializedTupleRef_V20_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V20_0 __V20_init() {
    
    auto _v0 = Aggregates::Zero<double>();
    

    return MaterializedTupleRef_V20_0( std::make_tuple(_v0) );
}
GlobalCompletionEvent V30(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_9_gce_incomplete, [] {
  return V30.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V31_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V31_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V31_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V31_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V31_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V31_0_1_2));
    //}
    MaterializedTupleRef_V31_0_1_2 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V31_0_1_2(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V31_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V31_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V31_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V31_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V31_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V31_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V31_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V31_0_1_2& t) {
    return t.dump(o);
  }

MaterializedTupleRef_V19_0 __V19_update(const MaterializedTupleRef_V19_0& state, const MaterializedTupleRef_V31_0_1_2& t_024) {
    
    auto _v0 = Aggregates::SUM<double, double>(state.f0,t_024.f2);
    
    return MaterializedTupleRef_V19_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V19_0 __V19_init() {
    
    auto _v0 = Aggregates::Zero<double>();
    

    return MaterializedTupleRef_V19_0( std::make_tuple(_v0) );
}
GlobalCompletionEvent V33(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_10_gce_incomplete, [] {
  return V33.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V34_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V34_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V34_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V34_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V34_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V34_0_1_2));
    //}
    MaterializedTupleRef_V34_0_1_2 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V34_0_1_2(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V34_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V34_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V34_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V34_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V34_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V34_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V34_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V34_0_1_2& t) {
    return t.dump(o);
  }

MaterializedTupleRef_V17_0 __V17_update(const MaterializedTupleRef_V17_0& state, const MaterializedTupleRef_V18_0_1& t_016) {
    
    auto _v0 = Aggregates::SUM<double, double>(state.f0,t_016.f1);
    
    return MaterializedTupleRef_V17_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V17_0 __V17_init() {
    
    auto _v0 = Aggregates::Zero<double>();
    

    return MaterializedTupleRef_V17_0( std::make_tuple(_v0) );
}
GlobalCompletionEvent V36(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_11_gce_incomplete, [] {
  return V36.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V37_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V37_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V37_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V37_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V37_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V37_0_1));
    //}
    MaterializedTupleRef_V37_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V37_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V37_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V37_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V37_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V37_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V37_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V37_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V37_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V37_0_1& t) {
    return t.dump(o);
  }

MaterializedTupleRef_V16_0 __V16_update(const MaterializedTupleRef_V16_0& state, const MaterializedTupleRef_V37_0_1& t_026) {
    
    auto _v0 = Aggregates::SUM<double, double>(state.f0,t_026.f1);
    
    return MaterializedTupleRef_V16_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V16_0 __V16_init() {
    
    auto _v0 = Aggregates::Zero<double>();
    

    return MaterializedTupleRef_V16_0( std::make_tuple(_v0) );
}
GlobalCompletionEvent V39(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_12_gce_incomplete, [] {
  return V39.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V40_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V40_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V40_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V40_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V40_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V40_0_1));
    //}
    MaterializedTupleRef_V40_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V40_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V40_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V40_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V40_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V40_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V40_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V40_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V40_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V40_0_1& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V41_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V41_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V41_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V41_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V41_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V41_0_1_2));
    //}
    MaterializedTupleRef_V41_0_1_2 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V41_0_1_2(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V41_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V41_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V41_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V41_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V41_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V41_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V41_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V41_0_1_2& t) {
    return t.dump(o);
  }

GlobalCompletionEvent V43(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_13_gce_incomplete, [] {
  return V43.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V44_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V44_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V44_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V44_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V44_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V44_0_1_2));
    //}
    MaterializedTupleRef_V44_0_1_2 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V44_0_1_2(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V44_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V44_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V44_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V44_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V44_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V44_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V44_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V44_0_1_2& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V46_0_1_2_3_4 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    
        int64_t f3;
    
        double f4;
    

    static constexpr int numFields() {
      return 5;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V46_0_1_2_3_4 _t;
        return

        
            ((char*)&_t.f4) + sizeof(_t.f4) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V46_0_1_2_3_4 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (((char*)&_t.f3) - ((char*)&_t.f2)) << ",";
        
        std::cout << (((char*)&_t.f4) - ((char*)&_t.f3)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f3) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V46_0_1_2_3_4 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V46_0_1_2_3_4 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V46_0_1_2_3_4));
    //}
    MaterializedTupleRef_V46_0_1_2_3_4 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               ,
                       
                               const int64_t& a3
                               ,
                       
                               const double& a4
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
            f3 = a3;
        
            f4 = a4;
        
    }

    
    


    MaterializedTupleRef_V46_0_1_2_3_4(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
            f3 = std::get<3>(o);
        
            f4 = std::get<4>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
            std::get<3>(r) = f3;
        
            std::get<4>(r) = f4;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V46_0_1_2_3_4 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //        f3 = vals[3];
    //    
    //        f4 = vals[4];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V46_0_1_2_3_4 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V46_0_1_2_3_4 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f3;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f4;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << " "
        
        << f3 << " "
        
        << f4 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V46_0_1_2_3_4 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V46_0_1_2_3_4::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V46_0_1_2_3_4 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V46_0_1_2_3_4::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      
        o << f3 << ",";
      
        o << f4 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V46_0_1_2_3_4& t) {
    return t.dump(o);
  }

static MaterializedTupleRef_V46_0_1_2_3_4 create_V47(const MaterializedTupleRef_V41_0_1_2& t1, const MaterializedTupleRef_V15_0_1& t2) {
    MaterializedTupleRef_V46_0_1_2_3_4 t;
    
        t.f0 = t1.f0;
    
        t.f1 = t1.f1;
    
        t.f2 = t1.f2;
    

    
        t.f3 = t2.f0;
    
        t.f4 = t2.f1;
    

    return t;
}
          // can be just the necessary schema
  class MaterializedTupleRef_V48_0_1_2_3 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        int64_t f1;
    
        double f2;
    
        double f3;
    

    static constexpr int numFields() {
      return 4;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V48_0_1_2_3 _t;
        return

        
            ((char*)&_t.f3) + sizeof(_t.f3) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V48_0_1_2_3 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (((char*)&_t.f3) - ((char*)&_t.f2)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f2) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V48_0_1_2_3 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V48_0_1_2_3 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V48_0_1_2_3));
    //}
    MaterializedTupleRef_V48_0_1_2_3 (
                               const int64_t& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               ,
                       
                               const double& a3
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
            f3 = a3;
        
    }

    
    


    MaterializedTupleRef_V48_0_1_2_3(const std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
            f3 = std::get<3>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        int64_t
        ,
        
        double
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
            std::get<3>(r) = f3;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V48_0_1_2_3 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //        f3 = vals[3];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V48_0_1_2_3 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V48_0_1_2_3 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f3;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << " "
        
        << f3 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V48_0_1_2_3 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V48_0_1_2_3::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V48_0_1_2_3 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V48_0_1_2_3::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      
        o << f3 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V48_0_1_2_3& t) {
    return t.dump(o);
  }

static MaterializedTupleRef_V48_0_1_2_3 create_V49(const MaterializedTupleRef_V12_0_1_2& t1, const MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t2) {
    MaterializedTupleRef_V48_0_1_2_3 t;
    
        t.f0 = t1.f0;
    
        t.f1 = t1.f1;
    
        t.f2 = t1.f2;
    

    
        t.f3 = t2.f0;
    

    return t;
}
Relation<aligned_vector<MaterializedTupleRef_V10_0_1_2>> _temp_table_prunedA;

          // can be just the necessary schema
  class MaterializedTupleRef_V50_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V50_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V50_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V50_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V50_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V50_0));
    //}
    MaterializedTupleRef_V50_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V50_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V50_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V50_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V50_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V50_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V50_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V50_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V50_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } GRAPPA_BLOCK_ALIGNED;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V50_0& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V51_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V51_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V51_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V51_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V51_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V51_0));
    //}
    MaterializedTupleRef_V51_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V51_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V51_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V51_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V51_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V51_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V51_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V51_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V51_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V51_0& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V52_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V52_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V52_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V52_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V52_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V52_0_1));
    //}
    MaterializedTupleRef_V52_0_1 (
                               const double& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V52_0_1(const std::tuple<
        
        double
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        double
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V52_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V52_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V52_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V52_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V52_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V52_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V52_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V52_0_1& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V54_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V54_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V54_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V54_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V54_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V54_0_1));
    //}
    MaterializedTupleRef_V54_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V54_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V54_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V54_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V54_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V54_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V54_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V54_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V54_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V54_0_1& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V55_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V55_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V55_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V55_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V55_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V55_0));
    //}
    MaterializedTupleRef_V55_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V55_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V55_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V55_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V55_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V55_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V55_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V55_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V55_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V55_0& t) {
    return t.dump(o);
  }

decltype(DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V55_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( )) group_hash_004;

          // can be just the necessary schema
  class MaterializedTupleRef_V56_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V56_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V56_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V56_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V56_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V56_0));
    //}
    MaterializedTupleRef_V56_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V56_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V56_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V56_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V56_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V56_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V56_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V56_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V56_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V56_0& t) {
    return t.dump(o);
  }

decltype(DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V56_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( )) group_hash_005;

          // can be just the necessary schema
  class MaterializedTupleRef_V57_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V57_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V57_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V57_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V57_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V57_0_1));
    //}
    MaterializedTupleRef_V57_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V57_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V57_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V57_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V57_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V57_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V57_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V57_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V57_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V57_0_1& t) {
    return t.dump(o);
  }

GlobalCompletionEvent V58(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_14_gce_incomplete, [] {
  return V58.incomplete();
});
MaterializedTupleRef_V56_0 __V56_update(const MaterializedTupleRef_V56_0& state, const MaterializedTupleRef_V57_0_1& t_038) {
    
    auto _v0 = Aggregates::SUM<double, double>(state.f0,t_038.f1);
    
    return MaterializedTupleRef_V56_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V56_0 __V56_init() {
    
    auto _v0 = Aggregates::Zero<double>();
    

    return MaterializedTupleRef_V56_0( std::make_tuple(_v0) );
}
GlobalCompletionEvent V60(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_15_gce_incomplete, [] {
  return V60.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V61_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V61_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V61_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V61_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V61_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V61_0_1));
    //}
    MaterializedTupleRef_V61_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V61_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V61_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V61_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V61_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V61_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V61_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V61_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V61_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V61_0_1& t) {
    return t.dump(o);
  }

MaterializedTupleRef_V55_0 __V55_update(const MaterializedTupleRef_V55_0& state, const MaterializedTupleRef_V61_0_1& t_040) {
    
    auto _v0 = Aggregates::SUM<double, double>(state.f0,t_040.f1);
    
    return MaterializedTupleRef_V55_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V55_0 __V55_init() {
    
    auto _v0 = Aggregates::Zero<double>();
    

    return MaterializedTupleRef_V55_0( std::make_tuple(_v0) );
}
GlobalCompletionEvent V63(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_16_gce_incomplete, [] {
  return V63.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V64_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V64_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V64_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V64_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V64_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V64_0_1));
    //}
    MaterializedTupleRef_V64_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V64_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V64_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V64_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V64_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V64_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V64_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V64_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V64_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V64_0_1& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V65_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V65_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V65_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V65_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V65_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V65_0_1));
    //}
    MaterializedTupleRef_V65_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V65_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V65_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V65_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V65_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V65_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V65_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V65_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V65_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V65_0_1& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V66_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V66_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V66_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V66_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V66_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V66_0));
    //}
    MaterializedTupleRef_V66_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V66_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V66_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V66_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V66_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V66_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V66_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V66_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V66_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V66_0& t) {
    return t.dump(o);
  }

decltype(DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V66_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( )) group_hash_006;

          // can be just the necessary schema
  class MaterializedTupleRef_V67_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V67_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V67_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V67_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V67_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V67_0));
    //}
    MaterializedTupleRef_V67_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V67_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V67_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V67_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V67_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V67_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V67_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V67_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V67_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V67_0& t) {
    return t.dump(o);
  }

decltype(DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V67_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( )) group_hash_007;

          // can be just the necessary schema
  class MaterializedTupleRef_V68_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V68_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V68_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V68_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V68_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V68_0_1));
    //}
    MaterializedTupleRef_V68_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V68_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V68_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V68_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V68_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V68_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V68_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V68_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V68_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V68_0_1& t) {
    return t.dump(o);
  }

GlobalCompletionEvent V69(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_17_gce_incomplete, [] {
  return V69.incomplete();
});
MaterializedTupleRef_V67_0 __V67_update(const MaterializedTupleRef_V67_0& state, const MaterializedTupleRef_V68_0_1& t_045) {
    
    auto _v0 = Aggregates::MAX<double, double>(state.f0,t_045.f1);
    
    return MaterializedTupleRef_V67_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V67_0 __V67_init() {
    
    auto _v0 = std::numeric_limits<double>::lowest();
    

    return MaterializedTupleRef_V67_0( std::make_tuple(_v0) );
}
GlobalCompletionEvent V71(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_18_gce_incomplete, [] {
  return V71.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V72_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V72_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V72_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V72_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V72_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V72_0_1));
    //}
    MaterializedTupleRef_V72_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V72_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V72_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V72_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V72_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V72_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V72_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V72_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V72_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V72_0_1& t) {
    return t.dump(o);
  }

MaterializedTupleRef_V66_0 __V66_update(const MaterializedTupleRef_V66_0& state, const MaterializedTupleRef_V72_0_1& t_047) {
    
    auto _v0 = Aggregates::MAX<double, double>(state.f0,t_047.f1);
    
    return MaterializedTupleRef_V66_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V66_0 __V66_init() {
    
    auto _v0 = std::numeric_limits<double>::lowest();
    

    return MaterializedTupleRef_V66_0( std::make_tuple(_v0) );
}
GlobalCompletionEvent V74(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_19_gce_incomplete, [] {
  return V74.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V75_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V75_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V75_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V75_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V75_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V75_0_1));
    //}
    MaterializedTupleRef_V75_0_1 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V75_0_1(const std::tuple<
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V75_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V75_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V75_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V75_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V75_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V75_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V75_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V75_0_1& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V77_0_1_2_3 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    
        double f1;
    
        int64_t f2;
    
        double f3;
    

    static constexpr int numFields() {
      return 4;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V77_0_1_2_3 _t;
        return

        
            ((char*)&_t.f3) + sizeof(_t.f3) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V77_0_1_2_3 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (((char*)&_t.f3) - ((char*)&_t.f2)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f2) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V77_0_1_2_3 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V77_0_1_2_3 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V77_0_1_2_3));
    //}
    MaterializedTupleRef_V77_0_1_2_3 (
                               const int64_t& a0
                               ,
                       
                               const double& a1
                               ,
                       
                               const int64_t& a2
                               ,
                       
                               const double& a3
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
            f3 = a3;
        
    }

    
    


    MaterializedTupleRef_V77_0_1_2_3(const std::tuple<
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
            f3 = std::get<3>(o);
        
     }

     std::tuple<
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        ,
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
            std::get<3>(r) = f3;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V77_0_1_2_3 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //        f3 = vals[3];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V77_0_1_2_3 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V77_0_1_2_3 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f3;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << " "
        
        << f3 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V77_0_1_2_3 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V77_0_1_2_3::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V77_0_1_2_3 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V77_0_1_2_3::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      
        o << f3 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V77_0_1_2_3& t) {
    return t.dump(o);
  }

static MaterializedTupleRef_V77_0_1_2_3 create_V78(const MaterializedTupleRef_V65_0_1& t1, const MaterializedTupleRef_V54_0_1& t2) {
    MaterializedTupleRef_V77_0_1_2_3 t;
    
        t.f0 = t1.f0;
    
        t.f1 = t1.f1;
    

    
        t.f2 = t2.f0;
    
        t.f3 = t2.f1;
    

    return t;
}
MaterializedTupleRef_V50_0 __V50_update(const MaterializedTupleRef_V50_0& state, const MaterializedTupleRef_V51_0& t_033) {
    
    auto _v0 = Aggregates::MAX<double, double>(state.f0,t_033.f0);
    
    return MaterializedTupleRef_V50_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V50_0 __V50_init() {
    
    auto _v0 = std::numeric_limits<double>::lowest();
    

    return MaterializedTupleRef_V50_0( std::make_tuple(_v0) );
}
MaterializedTupleRef_V50_0 __V50_combine(const MaterializedTupleRef_V50_0& state0, const MaterializedTupleRef_V50_0& state1) {
    
    auto _v0 = Aggregates::MAX<double, double>(state0.f0,state1.f0);
    
    return MaterializedTupleRef_V50_0(std::make_tuple(_v0));
}
GlobalCompletionEvent V79(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_20_gce_incomplete, [] {
  return V79.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V80_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V80_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V80_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V80_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V80_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V80_0));
    //}
    MaterializedTupleRef_V80_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V80_0(const std::tuple<
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V80_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V80_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V80_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V80_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V80_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V80_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V80_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V80_0& t) {
    return t.dump(o);
  }

Relation<aligned_vector<MaterializedTupleRef_V80_0>> _temp_table_newchaos;

GlobalCompletionEvent V81(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_21_gce_incomplete, [] {
  return V81.incomplete();
});
Relation<aligned_vector<MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2>> _temp_table_matA;

          // can be just the necessary schema
  class MaterializedTupleRef_V82_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V82_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V82_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V82_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V82_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V82_0));
    //}
    MaterializedTupleRef_V82_0 (
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V82_0(const std::tuple<
        
        int64_t
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        int64_t
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V82_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V82_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V82_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V82_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V82_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V82_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V82_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } GRAPPA_BLOCK_ALIGNED;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V82_0& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V83_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        bool f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V83_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V83_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V83_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V83_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V83_0));
    //}
    MaterializedTupleRef_V83_0 (
                               const bool& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V83_0(const std::tuple<
        
        bool
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        bool
        
        
     > to_tuple() {

        std::tuple<
        
        bool
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V83_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V83_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V83_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V83_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V83_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V83_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V83_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V83_0& t) {
    return t.dump(o);
  }

GlobalCompletionEvent V84(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_22_gce_incomplete, [] {
  return V84.incomplete();
});
MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0 t_055;
GlobalCompletionEvent V85(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_23_gce_incomplete, [] {
  return V85.incomplete();
});
MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0 t_057;
GlobalCompletionEvent V86(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_24_gce_incomplete, [] {
  return V86.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V87_0_1 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    
        int64_t f1;
    

    static constexpr int numFields() {
      return 2;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V87_0_1 _t;
        return

        
            ((char*)&_t.f1) + sizeof(_t.f1) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V87_0_1 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f0) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V87_0_1 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V87_0_1 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V87_0_1));
    //}
    MaterializedTupleRef_V87_0_1 (
                               const double& a0
                               ,
                       
                               const int64_t& a1
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
    }

    
    


    MaterializedTupleRef_V87_0_1(const std::tuple<
        
        double
        ,
        
        int64_t
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
     }

     std::tuple<
        
        double
        ,
        
        int64_t
        
        
     > to_tuple() {

        std::tuple<
        
        double
        ,
        
        int64_t
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V87_0_1 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V87_0_1 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V87_0_1 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V87_0_1 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V87_0_1::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V87_0_1 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V87_0_1::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V87_0_1& t) {
    return t.dump(o);
  }

static MaterializedTupleRef_V87_0_1 create_V88(const MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t1, const MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t2) {
    MaterializedTupleRef_V87_0_1 t;
    
        t.f0 = t1.f0;
    

    
        t.f1 = t2.f0;
    

    return t;
}
          // can be just the necessary schema
  class MaterializedTupleRef_V89_0_1_2 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    
        int64_t f1;
    
        double f2;
    

    static constexpr int numFields() {
      return 3;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V89_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V89_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V89_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V89_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V89_0_1_2));
    //}
    MaterializedTupleRef_V89_0_1_2 (
                               const double& a0
                               ,
                       
                               const int64_t& a1
                               ,
                       
                               const double& a2
                               
                       
                       ) {
        
            f0 = a0;
        
            f1 = a1;
        
            f2 = a2;
        
    }

    
    


    MaterializedTupleRef_V89_0_1_2(const std::tuple<
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
            f1 = std::get<1>(o);
        
            f2 = std::get<2>(o);
        
     }

     std::tuple<
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
     > to_tuple() {

        std::tuple<
        
        double
        ,
        
        int64_t
        ,
        
        double
        
        
        > r;
        
            std::get<0>(r) = f0;
        
            std::get<1>(r) = f1;
        
            std::get<2>(r) = f2;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V89_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V89_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V89_0_1_2 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f1;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f2;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << " "
        
        << f1 << " "
        
        << f2 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V89_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V89_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V89_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V89_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      
        o << f1 << ",";
      
        o << f2 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V89_0_1_2& t) {
    return t.dump(o);
  }

static MaterializedTupleRef_V89_0_1_2 create_V90(const MaterializedTupleRef_V87_0_1& t1, const MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t2) {
    MaterializedTupleRef_V89_0_1_2 t;
    
        t.f0 = t1.f0;
    
        t.f1 = t1.f1;
    

    
        t.f2 = t2.f0;
    

    return t;
}
MaterializedTupleRef_V82_0 __V82_update(const MaterializedTupleRef_V82_0& state, const MaterializedTupleRef_V83_0& t_053) {
    
    auto _v0 = Aggregates::COUNT<int64_t, bool>(state.f0,t_053.f0);
    
    return MaterializedTupleRef_V82_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V82_0 __V82_init() {
    
    auto _v0 = Aggregates::Zero<int64_t>();
    

    return MaterializedTupleRef_V82_0( std::make_tuple(_v0) );
}
MaterializedTupleRef_V82_0 __V82_combine(const MaterializedTupleRef_V82_0& state0, const MaterializedTupleRef_V82_0& state1) {
    
    auto _v0 = Aggregates::SUM<int64_t, int64_t>(state0.f0,state1.f0);
    
    return MaterializedTupleRef_V82_0(std::make_tuple(_v0));
}
GlobalCompletionEvent V91(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_25_gce_incomplete, [] {
  return V91.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V92_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V92_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V92_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V92_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V92_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V92_0));
    //}
    MaterializedTupleRef_V92_0 (
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V92_0(const std::tuple<
        
        int64_t
        
        
            >& o) {
        
            f0 = std::get<0>(o);
        
     }

     std::tuple<
        
        int64_t
        
        
     > to_tuple() {

        std::tuple<
        
        int64_t
        
        
        > r;
        
            std::get<0>(r) = f0;
        
        return r;
     }

    // shamelessly terrible disambiguation: one solution is named factory methods
    //MaterializedTupleRef_V92_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V92_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V92_0 _ret;

        
            
               {
               // use operator>> to parse into proper numeric type
               ss >> _ret.f0;
               //throw away the next delimiter
               std::string _temp;
               std::getline(ss, _temp, delim);
               }
            
        

        return _ret;
    }

    void toOStream(std::ostream& os) const {
        os.write((char*)this, this->fieldsSize());
    }

    void toOStreamAscii(std::ostream& os) const {
        os
        
        << f0 << std::endl;
    }

    //template <typename Tuple, typename T>
    //MaterializedTupleRef_V92_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V92_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V92_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V92_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V92_0& t) {
    return t.dump(o);
  }

GlobalCompletionEvent V93(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_26_gce_incomplete, [] {
  return V93.incomplete();
});
std::vector<MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0> result;
typedef MatchesDHT<std::tuple<int64_t>, MaterializedTupleRef_V15_0_1, hash_tuple::hash<std::tuple<int64_t>>> DHT_MaterializedTupleRef_V15_0_1;
DHT_MaterializedTupleRef_V15_0_1 hash_000;
typedef MatchesDHT<std::tuple<int64_t>, MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2, hash_tuple::hash<std::tuple<int64_t>>> DHT_MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2;
DHT_MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2 hash_001;
typedef MatchesDHT<std::tuple<int64_t>, MaterializedTupleRef_V54_0_1, hash_tuple::hash<std::tuple<int64_t>>> DHT_MaterializedTupleRef_V54_0_1;
DHT_MaterializedTupleRef_V54_0_1 hash_002;

StringIndex string_index;
void init( ) {
}

void query() {
    double start, end;
    double saved_scan_runtime = 0, saved_init_runtime = 0;
    start = walltime();

     {
    decltype(_temp_table_matA) l__temp_table_matA;
    l__temp_table_matA.data = Grappa::symmetric_global_alloc<aligned_vector<T>>();
    l__temp_table_matA.numtuples = 0; // starts empty, but it could get filled
                           // Often we may not want to bother counting, so this
                           // field may become incoherent.

    // make it available everywhere
    on_all_cores([=] {
        _temp_table_matA = l__temp_table_matA;
    });
}
{
    decltype(_temp_table_epsilon) l__temp_table_epsilon;
    l__temp_table_epsilon.data = Grappa::symmetric_global_alloc<aligned_vector<T>>();
    l__temp_table_epsilon.numtuples = 0; // starts empty, but it could get filled
                           // Often we may not want to bother counting, so this
                           // field may become incoherent.

    // make it available everywhere
    on_all_cores([=] {
        _temp_table_epsilon = l__temp_table_epsilon;
    });
}
{
    decltype(_temp_table_prunelimit) l__temp_table_prunelimit;
    l__temp_table_prunelimit.data = Grappa::symmetric_global_alloc<aligned_vector<T>>();
    l__temp_table_prunelimit.numtuples = 0; // starts empty, but it could get filled
                           // Often we may not want to bother counting, so this
                           // field may become incoherent.

    // make it available everywhere
    on_all_cores([=] {
        _temp_table_prunelimit = l__temp_table_prunelimit;
    });
}
{
    decltype(_temp_table_newchaos) l__temp_table_newchaos;
    l__temp_table_newchaos.data = Grappa::symmetric_global_alloc<aligned_vector<T>>();
    l__temp_table_newchaos.numtuples = 0; // starts empty, but it could get filled
                           // Often we may not want to bother counting, so this
                           // field may become incoherent.

    // make it available everywhere
    on_all_cores([=] {
        _temp_table_newchaos = l__temp_table_newchaos;
    });
}
{
    decltype(_temp_table_oldchaos) l__temp_table_oldchaos;
    l__temp_table_oldchaos.data = Grappa::symmetric_global_alloc<aligned_vector<T>>();
    l__temp_table_oldchaos.numtuples = 0; // starts empty, but it could get filled
                           // Often we may not want to bother counting, so this
                           // field may become incoherent.

    // make it available everywhere
    on_all_cores([=] {
        _temp_table_oldchaos = l__temp_table_oldchaos;
    });
}
hash_000.init_global_DHT( &hash_000, cores()*16*1024 );
auto l_group_hash_000 = DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V16_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( );
on_all_cores([=] {
  group_hash_000 = l_group_hash_000;
});
auto l_group_hash_001 = DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V17_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( );
on_all_cores([=] {
  group_hash_001 = l_group_hash_001;
});
auto l_group_hash_002 = DHT_symmetric<std::tuple<int64_t,int64_t>,MaterializedTupleRef_V19_0,hash_tuple::hash<std::tuple<int64_t,int64_t>>>::create_DHT_symmetric( );
on_all_cores([=] {
  group_hash_002 = l_group_hash_002;
});
auto l_group_hash_003 = DHT_symmetric<std::tuple<int64_t,int64_t>,MaterializedTupleRef_V20_0,hash_tuple::hash<std::tuple<int64_t,int64_t>>>::create_DHT_symmetric( );
on_all_cores([=] {
  group_hash_003 = l_group_hash_003;
});
hash_001.init_global_DHT( &hash_001, cores()*16*1024 );
{
    decltype(_temp_table_prunedA) l__temp_table_prunedA;
    l__temp_table_prunedA.data = Grappa::symmetric_global_alloc<aligned_vector<T>>();
    l__temp_table_prunedA.numtuples = 0; // starts empty, but it could get filled
                           // Often we may not want to bother counting, so this
                           // field may become incoherent.

    // make it available everywhere
    on_all_cores([=] {
        _temp_table_prunedA = l__temp_table_prunedA;
    });
}
auto group_hash_000 = symmetric_global_alloc<MaterializedTupleRef_V50_0>();
hash_002.init_global_DHT( &hash_002, cores()*16*1024 );
auto l_group_hash_004 = DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V55_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( );
on_all_cores([=] {
  group_hash_004 = l_group_hash_004;
});
auto l_group_hash_005 = DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V56_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( );
on_all_cores([=] {
  group_hash_005 = l_group_hash_005;
});
auto l_group_hash_006 = DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V66_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( );
on_all_cores([=] {
  group_hash_006 = l_group_hash_006;
});
auto l_group_hash_007 = DHT_symmetric<std::tuple<int64_t>,MaterializedTupleRef_V67_0,hash_tuple::hash<std::tuple<int64_t>>>::create_DHT_symmetric( );
on_all_cores([=] {
  group_hash_007 = l_group_hash_007;
});
auto group_hash_001 = symmetric_global_alloc<MaterializedTupleRef_V82_0>();

    end = walltime();
    init_runtime += (end-start);
    saved_init_runtime += (end-start);

    Grappa::Metrics::reset();
Grappa::Metrics::reset();

auto start_V94 = walltime();

        
        auto start_0 = walltime();
VLOG(1)  << "timestamp 0 start " << std::setprecision(15) << start_0;

{
    if (FLAGS_bin) {
        BinaryRelationFileReader<MaterializedTupleRef_V1_0_1_2> reader;
        V1 = reader.read( FLAGS_input_file_matrix + ".bin" );
    } else if (FLAGS_jsonsplits) {
        SplitsRelationFileReader<JSONRowParser<MaterializedTupleRef_V1_0_1_2,&schema_V1>, MaterializedTupleRef_V1_0_1_2> reader;
        V1 = reader.read( FLAGS_input_file_matrix );
    } else {
        V1.data = readTuples<MaterializedTupleRef_V1_0_1_2>( FLAGS_input_file_matrix, FLAGS_nt);
        V1.numtuples = FLAGS_nt;
        auto l_V1 = V1;
        on_all_cores([=]{ V1 = l_V1; });
    }
}
auto end_0 = walltime();
auto runtime_0 = end_0 - start_0;
VLOG(1)  << "pipeline 0: " << runtime_0 << " s";

VLOG(1)  << "timestamp 0 end " << std::setprecision(15) << end_0;

        
auto end_V94 = walltime();

auto runtime_V94 = end_V94 - start_V94;

saved_scan_runtime += runtime_V94;
VLOG(1) << "pipeline group V94: " << runtime_V94 << " s";
Grappa::Metrics::reset();
Grappa::Metrics::reset();
Grappa::Metrics::start_tracing();
auto start_V95 = walltime();
// Compiled subplan for GrappaSequence[GrappaStoreTemp(matA)[GrappaMemoryScan(global_array, None) [GrappaFileScan(public:adhoc:matrix)]],GrappaStoreTemp(epsilon)[GrappaApply(_COLUMN0_=0.001)[SingletonRelation]],GrappaStoreTemp(prunelimit)[GrappaApply(_COLUMN0_=1e-05)[SingletonRelation]],GrappaStoreTemp(newchaos)[GrappaApply(_COLUMN0_=1000)[SingletonRelation]],GrappaDoWhile[GrappaStoreTemp(oldchaos)[GrappaMemoryScan(symmetric_array, newchaos) [GrappaNullInput(newchaos)]],GrappaStoreTemp(prunedA)[GrappaApply(row=row,col=col,value=value)[GrappaSelect(($2 > $3))[GrappaBroadcastCrossProduct[GrappaApply(row=row,col=col,value=(value / colsum))[GrappaApply(row=$0,col=$1,value=$2,colsum=$4)[GrappaHashJoin(($1 = $3))[GrappaApply(row=$0,col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]],GrappaApply(col=$0,colsum=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM(value))[GrappaApply(col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]]]]]]]]],GrappaMemoryScan(symmetric_array, prunelimit) [GrappaNullInput(prunelimit)]]]]],GrappaStoreTemp(newchaos)[GrappaGroupBy(; MAX($0))[GrappaApply(_COLUMN0_=(maxVal - sumSquare))[GrappaApply(maxVal=$1,sumSquare=$3)[GrappaHashJoin(($0 = $2))[GrappaApply(col=$0,maxVal=$1)[GrappaPartitionGroupBy($0; MAX($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]],GrappaApply(col=$0,sumSquare=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]]]]]]],GrappaStoreTemp(matA)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]],GrappaTest[GrappaGroupBy(; COUNT($0))[GrappaApply(_COLUMN0_=(($1 - $0) > $2))[GrappaBroadcastCrossProduct[GrappaBroadcastCrossProduct[GrappaMemoryScan(symmetric_array, newchaos) [GrappaNullInput(newchaos)],GrappaMemoryScan(symmetric_array, oldchaos) [GrappaNullInput(oldchaos)]],GrappaMemoryScan(symmetric_array, epsilon) [GrappaNullInput(epsilon)]]]]]],GrappaStore(public:adhoc:OUTPUT)[GrappaMemoryScan(symmetric_array, newchaos) [GrappaNullInput(newchaos)]]]

// recycle result vectors _temp_table_matA
on_all_cores([=] {
    _temp_table_matA.data->clear();
});CompletionEvent p_task_1;
spawn(&p_task_1, [=] {

        
        auto start_1 = walltime();
VLOG(1)  << "timestamp 1 start " << std::setprecision(15) << start_1;

forall<&V2>( t_000.data, t_000.numtuples, [=](int64_t i, MaterializedTupleRef_V1_0_1_2& t_000) {
// GrappaStoreTemp(matA)[GrappaMemoryScan(global_array, None) [GrappaFileScan(public:adhoc:matrix)]]
_temp_table_matA.data->push_back(t_000);

});
auto end_1 = walltime();
auto runtime_1 = end_1 - start_1;
VLOG(1)  << "pipeline 1: " << runtime_1 << " s";

VLOG(1)  << "timestamp 1 end " << std::setprecision(15) << end_1;

        
});

p_task_1.wait();
// recycle result vectors _temp_table_epsilon
on_all_cores([=] {
    _temp_table_epsilon.data->clear();
});CompletionEvent p_task_2;
spawn(&p_task_2, [=] {

        
        auto start_2 = walltime();
VLOG(1)  << "timestamp 2 start " << std::setprecision(15) << start_2;

// GrappaApply(_COLUMN0_=0.001)
MaterializedTupleRef_V3_0 t_001;t_001.f0 = 0.001;
// GrappaStoreTemp(epsilon)[GrappaApply(_COLUMN0_=0.001)[SingletonRelation]]
_temp_table_epsilon.data->push_back(t_001);

auto end_2 = walltime();
auto runtime_2 = end_2 - start_2;
VLOG(1)  << "pipeline 2: " << runtime_2 << " s";

VLOG(1)  << "timestamp 2 end " << std::setprecision(15) << end_2;

        
});

p_task_2.wait();
// recycle result vectors _temp_table_prunelimit
on_all_cores([=] {
    _temp_table_prunelimit.data->clear();
});CompletionEvent p_task_3;
spawn(&p_task_3, [=] {

        
        auto start_3 = walltime();
VLOG(1)  << "timestamp 3 start " << std::setprecision(15) << start_3;

// GrappaApply(_COLUMN0_=1e-05)
MaterializedTupleRef_V5_0 t_003;t_003.f0 = 1e-05;
// GrappaStoreTemp(prunelimit)[GrappaApply(_COLUMN0_=1e-05)[SingletonRelation]]
_temp_table_prunelimit.data->push_back(t_003);

auto end_3 = walltime();
auto runtime_3 = end_3 - start_3;
VLOG(1)  << "pipeline 3: " << runtime_3 << " s";

VLOG(1)  << "timestamp 3 end " << std::setprecision(15) << end_3;

        
});

p_task_3.wait();
// recycle result vectors _temp_table_newchaos
on_all_cores([=] {
    _temp_table_newchaos.data->clear();
});CompletionEvent p_task_4;
spawn(&p_task_4, [=] {

        
        auto start_4 = walltime();
VLOG(1)  << "timestamp 4 start " << std::setprecision(15) << start_4;

// GrappaApply(_COLUMN0_=1000)
MaterializedTupleRef_V7_0 t_005;t_005.f0 = 1000;
// GrappaStoreTemp(newchaos)[GrappaApply(_COLUMN0_=1000)[SingletonRelation]]
_temp_table_newchaos.data->push_back(t_005);

auto end_4 = walltime();
auto runtime_4 = end_4 - start_4;
VLOG(1)  << "pipeline 4: " << runtime_4 << " s";

VLOG(1)  << "timestamp 4 end " << std::setprecision(15) << end_4;

        
});

p_task_4.wait();
do {
        found = false;
        
// recycle result vectors _temp_table_oldchaos
on_all_cores([=] {
    _temp_table_oldchaos.data->clear();
});CompletionEvent p_task_5;
spawn(&p_task_5, [=] {

        
        auto start_5 = walltime();
VLOG(1)  << "timestamp 5 start " << std::setprecision(15) << start_5;

forall<&V9>( t_007.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_007) {
// GrappaStoreTemp(oldchaos)[GrappaMemoryScan(symmetric_array, newchaos) [GrappaNullInput(newchaos)]]
_temp_table_oldchaos.data->push_back(t_007);

});
auto end_5 = walltime();
auto runtime_5 = end_5 - start_5;
VLOG(1)  << "pipeline 5: " << runtime_5 << " s";

VLOG(1)  << "timestamp 5 end " << std::setprecision(15) << end_5;

        
});

p_task_5.wait();
CompletionEvent p_task_6;
spawn(&p_task_6, [=] {

        
        auto start_6 = walltime();
VLOG(1)  << "timestamp 6 start " << std::setprecision(15) << start_6;

forall<&V11>( t_009.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_009) {
// GrappaBroadcastCrossProduct RIGHT
on_all_cores([=] {
                  t_010 = t_009;
                   });
                   
});
auto end_6 = walltime();
auto runtime_6 = end_6 - start_6;
VLOG(1)  << "pipeline 6: " << runtime_6 << " s";

VLOG(1)  << "timestamp 6 end " << std::setprecision(15) << end_6;

        
});

CompletionEvent p_task_7;
spawn(&p_task_7, [=] {

        
        auto start_7 = walltime();
VLOG(1)  << "timestamp 7 start " << std::setprecision(15) << start_7;

forall<&V24>( t_021.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2& t_021) {
// right side of GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]

hash_001.insert_async<&V24>(std::make_tuple(t_021.f0), t_021);
});
auto end_7 = walltime();
auto runtime_7 = end_7 - start_7;
VLOG(1)  << "pipeline 7: " << runtime_7 << " s";

VLOG(1)  << "timestamp 7 end " << std::setprecision(15) << end_7;

        
});

CompletionEvent p_task_8;
spawn(&p_task_8, [=,&p_task_7] {

        p_task_7.wait();
        auto start_8 = walltime();
VLOG(1)  << "timestamp 8 start " << std::setprecision(15) << start_8;

forall<&V25>( t_022.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2& t_022) {
// left side of GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]

hash_001.lookup_iter<&V25>( std::make_tuple(t_022.f1), [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2& V26) {
  join_coarse_result_count++;
  MaterializedTupleRef_V27_0_1_2_3_4_5 t_023 = create_V28(t_022, V26);
  // GrappaApply(row=$0,value=$2,col1=$4,value1=$5)
MaterializedTupleRef_V22_0_1_2_3 t_020;t_020.f0 = t_023.f0;
t_020.f1 = t_023.f2;
t_020.f2 = t_023.f4;
t_020.f3 = t_023.f5;
// GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))
MaterializedTupleRef_V21_0_1_2 t_019;t_019.f0 = t_020.f0;
t_019.f1 = t_020.f2;
t_019.f2 = ( (t_020.f1) * (t_020.f3) );
// insert of GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]

group_hash_003->template update_partition<MaterializedTupleRef_V21_0_1_2, &__V20_update,&__V20_init>(std::make_tuple(t_019.f0,t_019.f1), t_019);
});
});
auto end_8 = walltime();
auto runtime_8 = end_8 - start_8;
VLOG(1)  << "pipeline 8: " << runtime_8 << " s";

VLOG(1)  << "timestamp 8 end " << std::setprecision(15) << end_8;

        
});

CompletionEvent p_task_9;
spawn(&p_task_9, [=,&p_task_8] {

        p_task_8.wait();
        auto start_9 = walltime();
VLOG(1)  << "timestamp 9 start " << std::setprecision(15) << start_9;

// scan of GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]

group_hash_003->forall_entries<&V30>([=](std::pair<const std::tuple<int64_t,int64_t>,MaterializedTupleRef_V20_0>&V29) {
    MaterializedTupleRef_V31_0_1_2 t_024(std::tuple_cat(V29.first, V29.second.to_tuple()));
    // GrappaShuffle($0,$1)

auto target = hash_tuple::hash<std::tuple<int64_t,int64_t>>()(std::make_tuple(t_024.f0,t_024.f1)) % Grappa::cores();
// DEV NOTE: if something inside this call is not captured in the lambda,
// (probably a data structure) then we need to change its declaration to a global one.
// The alternative is just to capture [=] but this will mask unneeded communication.
Grappa::delegate::call<async, &V30>(target, [t_024] {
    // insert of GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]

group_hash_002->template update_partition<MaterializedTupleRef_V31_0_1_2, &__V19_update,&__V19_init>(std::make_tuple(t_024.f0,t_024.f1), t_024);
});
});

auto end_9 = walltime();
auto runtime_9 = end_9 - start_9;
VLOG(1)  << "pipeline 9: " << runtime_9 << " s";

VLOG(1)  << "timestamp 9 end " << std::setprecision(15) << end_9;

        
});

CompletionEvent p_task_10;
spawn(&p_task_10, [=,&p_task_9] {

        p_task_9.wait();
        auto start_10 = walltime();
VLOG(1)  << "timestamp 10 start " << std::setprecision(15) << start_10;

// scan of GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]

group_hash_002->forall_entries<&V33>([=](std::pair<const std::tuple<int64_t,int64_t>,MaterializedTupleRef_V19_0>&V32) {
    MaterializedTupleRef_V34_0_1_2 t_025(std::tuple_cat(V32.first, V32.second.to_tuple()));
    // GrappaApply(col=$1,value=($2 * $2))
MaterializedTupleRef_V18_0_1 t_016;t_016.f0 = t_025.f1;
t_016.f1 = ( (t_025.f2) * (t_025.f2) );
// insert of GrappaPartitionGroupBy(col; SUM(value))[GrappaApply(col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]]]

group_hash_001->template update_partition<MaterializedTupleRef_V18_0_1, &__V17_update,&__V17_init>(std::make_tuple(t_016.f0), t_016);
});

auto end_10 = walltime();
auto runtime_10 = end_10 - start_10;
VLOG(1)  << "pipeline 10: " << runtime_10 << " s";

VLOG(1)  << "timestamp 10 end " << std::setprecision(15) << end_10;

        
});

CompletionEvent p_task_11;
spawn(&p_task_11, [=,&p_task_10] {

        p_task_10.wait();
        auto start_11 = walltime();
VLOG(1)  << "timestamp 11 start " << std::setprecision(15) << start_11;

// scan of GrappaPartitionGroupBy(col; SUM(value))[GrappaApply(col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]]]

group_hash_001->forall_entries<&V36>([=](std::pair<const std::tuple<int64_t>,MaterializedTupleRef_V17_0>&V35) {
    MaterializedTupleRef_V37_0_1 t_026(std::tuple_cat(V35.first, V35.second.to_tuple()));
    // GrappaShuffle($0)

auto target = hash_tuple::hash<std::tuple<int64_t>>()(std::make_tuple(t_026.f0)) % Grappa::cores();
// DEV NOTE: if something inside this call is not captured in the lambda,
// (probably a data structure) then we need to change its declaration to a global one.
// The alternative is just to capture [=] but this will mask unneeded communication.
Grappa::delegate::call<async, &V36>(target, [t_026] {
    // insert of GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM(value))[GrappaApply(col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]]]]]

group_hash_000->template update_partition<MaterializedTupleRef_V37_0_1, &__V16_update,&__V16_init>(std::make_tuple(t_026.f0), t_026);
});
});

auto end_11 = walltime();
auto runtime_11 = end_11 - start_11;
VLOG(1)  << "pipeline 11: " << runtime_11 << " s";

VLOG(1)  << "timestamp 11 end " << std::setprecision(15) << end_11;

        
});

CompletionEvent p_task_12;
spawn(&p_task_12, [=,&p_task_11] {

        p_task_11.wait();
        auto start_12 = walltime();
VLOG(1)  << "timestamp 12 start " << std::setprecision(15) << start_12;

// scan of GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM(value))[GrappaApply(col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]]]]]

group_hash_000->forall_entries<&V39>([=](std::pair<const std::tuple<int64_t>,MaterializedTupleRef_V16_0>&V38) {
    MaterializedTupleRef_V40_0_1 t_027(std::tuple_cat(V38.first, V38.second.to_tuple()));
    // GrappaApply(col=$0,colsum=$1)
MaterializedTupleRef_V15_0_1 t_013;t_013.f0 = t_027.f0;
t_013.f1 = t_027.f1;
// right side of GrappaHashJoin(($1 = $3))[GrappaApply(row=$0,col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]],GrappaApply(col=$0,colsum=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM(value))[GrappaApply(col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]]]]]]]

hash_000.insert_async<&V39>(std::make_tuple(t_013.f0), t_013);
});

auto end_12 = walltime();
auto runtime_12 = end_12 - start_12;
VLOG(1)  << "pipeline 12: " << runtime_12 << " s";

VLOG(1)  << "timestamp 12 end " << std::setprecision(15) << end_12;

        
});

// recycle result vectors _temp_table_prunedA
on_all_cores([=] {
    _temp_table_prunedA.data->clear();
});CompletionEvent p_task_13;
spawn(&p_task_13, [=,&p_task_9
,&p_task_12
,&p_task_6] {

        p_task_9.wait();
p_task_12.wait();
p_task_6.wait();
        auto start_13 = walltime();
VLOG(1)  << "timestamp 13 start " << std::setprecision(15) << start_13;

// scan of GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]

group_hash_002->forall_entries<&V43>([=](std::pair<const std::tuple<int64_t,int64_t>,MaterializedTupleRef_V19_0>&V42) {
    MaterializedTupleRef_V44_0_1_2 t_029(std::tuple_cat(V42.first, V42.second.to_tuple()));
    // GrappaApply(row=$0,col=$1,value=($2 * $2))
MaterializedTupleRef_V41_0_1_2 t_028;t_028.f0 = t_029.f0;
t_028.f1 = t_029.f1;
t_028.f2 = ( (t_029.f2) * (t_029.f2) );
// left side of GrappaHashJoin(($1 = $3))[GrappaApply(row=$0,col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]],GrappaApply(col=$0,colsum=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM(value))[GrappaApply(col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]]]]]]]

hash_000.lookup_iter<&V43>( std::make_tuple(t_028.f1), [=](MaterializedTupleRef_V15_0_1& V45) {
  join_coarse_result_count++;
  MaterializedTupleRef_V46_0_1_2_3_4 t_030 = create_V47(t_028, V45);
  // GrappaApply(row=$0,col=$1,value=$2,colsum=$4)
MaterializedTupleRef_V13_0_1_2_3 t_012;t_012.f0 = t_030.f0;
t_012.f1 = t_030.f1;
t_012.f2 = t_030.f2;
t_012.f3 = t_030.f4;
// GrappaApply(row=row,col=col,value=(value / colsum))
MaterializedTupleRef_V12_0_1_2 t_011;t_011.f0 = t_012.f0;
t_011.f1 = t_012.f1;
t_011.f2 = ( (t_012.f2) / (t_012.f3) );
// GrappaBroadcastCrossProduct LEFT

            MaterializedTupleRef_V48_0_1_2_3 t_031 =
              create_V49(t_011, t_010);
              if (( (t_031.f2) > (t_031.f3) )) {
  // GrappaApply(row=row,col=col,value=value)
MaterializedTupleRef_V10_0_1_2 t_008;t_008.f0 = t_031.f0;
t_008.f1 = t_031.f1;
t_008.f2 = t_031.f2;
// GrappaStoreTemp(prunedA)[GrappaApply(row=row,col=col,value=value)[GrappaSelect(($2 > $3))[GrappaBroadcastCrossProduct[GrappaApply(row=row,col=col,value=(value / colsum))[GrappaApply(row=$0,col=$1,value=$2,colsum=$4)[GrappaHashJoin(($1 = $3))[GrappaApply(row=$0,col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]],GrappaApply(col=$0,colsum=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM(value))[GrappaApply(col=$1,value=($2 * $2))[GrappaPartitionGroupBy($0,$1; SUM($2))[GrappaShuffle($0,$1)[GrappaPartitionGroupBy(row,col; SUM($2))[GrappaApply(row=$0,col1=$2,_COLUMN2_=(value * value))[GrappaApply(row=$0,value=$2,col1=$4,value1=$5)[GrappaHashJoin(($1 = $3))[GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)],GrappaMemoryScan(symmetric_array, matA) [GrappaNullInput(matA)]]]]]]]]]]]]]]],GrappaMemoryScan(symmetric_array, prunelimit) [GrappaNullInput(prunelimit)]]]]]
_temp_table_prunedA.data->push_back(t_008);

}

});
});

auto end_13 = walltime();
auto runtime_13 = end_13 - start_13;
VLOG(1)  << "pipeline 13: " << runtime_13 << " s";

VLOG(1)  << "timestamp 13 end " << std::setprecision(15) << end_13;

        
});

p_task_6.wait();
p_task_9.wait();
p_task_13.wait();
p_task_11.wait();
p_task_7.wait();
p_task_8.wait();
p_task_12.wait();
p_task_10.wait();
CompletionEvent p_task_14;
spawn(&p_task_14, [=] {

        
        auto start_14 = walltime();
VLOG(1)  << "timestamp 14 start " << std::setprecision(15) << start_14;

forall<&V58>( t_039.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2& t_039) {
// GrappaApply(col=$1,_COLUMN1_=(value * value))
MaterializedTupleRef_V57_0_1 t_038;t_038.f0 = t_039.f1;
t_038.f1 = ( (t_039.f2) * (t_039.f2) );
// insert of GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]

group_hash_005->template update_partition<MaterializedTupleRef_V57_0_1, &__V56_update,&__V56_init>(std::make_tuple(t_038.f0), t_038);
});
auto end_14 = walltime();
auto runtime_14 = end_14 - start_14;
VLOG(1)  << "pipeline 14: " << runtime_14 << " s";

VLOG(1)  << "timestamp 14 end " << std::setprecision(15) << end_14;

        
});

CompletionEvent p_task_15;
spawn(&p_task_15, [=,&p_task_14] {

        p_task_14.wait();
        auto start_15 = walltime();
VLOG(1)  << "timestamp 15 start " << std::setprecision(15) << start_15;

// scan of GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]

group_hash_005->forall_entries<&V60>([=](std::pair<const std::tuple<int64_t>,MaterializedTupleRef_V56_0>&V59) {
    MaterializedTupleRef_V61_0_1 t_040(std::tuple_cat(V59.first, V59.second.to_tuple()));
    // GrappaShuffle($0)

auto target = hash_tuple::hash<std::tuple<int64_t>>()(std::make_tuple(t_040.f0)) % Grappa::cores();
// DEV NOTE: if something inside this call is not captured in the lambda,
// (probably a data structure) then we need to change its declaration to a global one.
// The alternative is just to capture [=] but this will mask unneeded communication.
Grappa::delegate::call<async, &V60>(target, [t_040] {
    // insert of GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]

group_hash_004->template update_partition<MaterializedTupleRef_V61_0_1, &__V55_update,&__V55_init>(std::make_tuple(t_040.f0), t_040);
});
});

auto end_15 = walltime();
auto runtime_15 = end_15 - start_15;
VLOG(1)  << "pipeline 15: " << runtime_15 << " s";

VLOG(1)  << "timestamp 15 end " << std::setprecision(15) << end_15;

        
});

CompletionEvent p_task_16;
spawn(&p_task_16, [=,&p_task_15] {

        p_task_15.wait();
        auto start_16 = walltime();
VLOG(1)  << "timestamp 16 start " << std::setprecision(15) << start_16;

// scan of GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]

group_hash_004->forall_entries<&V63>([=](std::pair<const std::tuple<int64_t>,MaterializedTupleRef_V55_0>&V62) {
    MaterializedTupleRef_V64_0_1 t_041(std::tuple_cat(V62.first, V62.second.to_tuple()));
    // GrappaApply(col=$0,sumSquare=$1)
MaterializedTupleRef_V54_0_1 t_035;t_035.f0 = t_041.f0;
t_035.f1 = t_041.f1;
// right side of GrappaHashJoin(($0 = $2))[GrappaApply(col=$0,maxVal=$1)[GrappaPartitionGroupBy($0; MAX($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]],GrappaApply(col=$0,sumSquare=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]]]

hash_002.insert_async<&V63>(std::make_tuple(t_035.f0), t_035);
});

auto end_16 = walltime();
auto runtime_16 = end_16 - start_16;
VLOG(1)  << "pipeline 16: " << runtime_16 << " s";

VLOG(1)  << "timestamp 16 end " << std::setprecision(15) << end_16;

        
});

CompletionEvent p_task_17;
spawn(&p_task_17, [=] {

        
        auto start_17 = walltime();
VLOG(1)  << "timestamp 17 start " << std::setprecision(15) << start_17;

forall<&V69>( t_046.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2& t_046) {
// GrappaApply(col=$1,value=$2)
MaterializedTupleRef_V68_0_1 t_045;t_045.f0 = t_046.f1;
t_045.f1 = t_046.f2;
// insert of GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]

group_hash_007->template update_partition<MaterializedTupleRef_V68_0_1, &__V67_update,&__V67_init>(std::make_tuple(t_045.f0), t_045);
});
auto end_17 = walltime();
auto runtime_17 = end_17 - start_17;
VLOG(1)  << "pipeline 17: " << runtime_17 << " s";

VLOG(1)  << "timestamp 17 end " << std::setprecision(15) << end_17;

        
});

CompletionEvent p_task_18;
spawn(&p_task_18, [=,&p_task_17] {

        p_task_17.wait();
        auto start_18 = walltime();
VLOG(1)  << "timestamp 18 start " << std::setprecision(15) << start_18;

// scan of GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]

group_hash_007->forall_entries<&V71>([=](std::pair<const std::tuple<int64_t>,MaterializedTupleRef_V67_0>&V70) {
    MaterializedTupleRef_V72_0_1 t_047(std::tuple_cat(V70.first, V70.second.to_tuple()));
    // GrappaShuffle($0)

auto target = hash_tuple::hash<std::tuple<int64_t>>()(std::make_tuple(t_047.f0)) % Grappa::cores();
// DEV NOTE: if something inside this call is not captured in the lambda,
// (probably a data structure) then we need to change its declaration to a global one.
// The alternative is just to capture [=] but this will mask unneeded communication.
Grappa::delegate::call<async, &V71>(target, [t_047] {
    // insert of GrappaPartitionGroupBy($0; MAX($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]

group_hash_006->template update_partition<MaterializedTupleRef_V72_0_1, &__V66_update,&__V66_init>(std::make_tuple(t_047.f0), t_047);
});
});

auto end_18 = walltime();
auto runtime_18 = end_18 - start_18;
VLOG(1)  << "pipeline 18: " << runtime_18 << " s";

VLOG(1)  << "timestamp 18 end " << std::setprecision(15) << end_18;

        
});

CompletionEvent p_task_19;
spawn(&p_task_19, [=,&p_task_18
,&p_task_16] {

        p_task_18.wait();
p_task_16.wait();
        auto start_19 = walltime();
VLOG(1)  << "timestamp 19 start " << std::setprecision(15) << start_19;

// scan of GrappaPartitionGroupBy($0; MAX($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]

group_hash_006->forall_entries<&V74>([=](std::pair<const std::tuple<int64_t>,MaterializedTupleRef_V66_0>&V73) {
    MaterializedTupleRef_V75_0_1 t_048(std::tuple_cat(V73.first, V73.second.to_tuple()));
    // GrappaApply(col=$0,maxVal=$1)
MaterializedTupleRef_V65_0_1 t_042;t_042.f0 = t_048.f0;
t_042.f1 = t_048.f1;
// left side of GrappaHashJoin(($0 = $2))[GrappaApply(col=$0,maxVal=$1)[GrappaPartitionGroupBy($0; MAX($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]],GrappaApply(col=$0,sumSquare=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]]]

hash_002.lookup_iter<&V74>( std::make_tuple(t_042.f0), [=](MaterializedTupleRef_V54_0_1& V76) {
  join_coarse_result_count++;
  MaterializedTupleRef_V77_0_1_2_3 t_049 = create_V78(t_042, V76);
  // GrappaApply(maxVal=$1,sumSquare=$3)
MaterializedTupleRef_V52_0_1 t_034;t_034.f0 = t_049.f1;
t_034.f1 = t_049.f3;
// GrappaApply(_COLUMN0_=(maxVal - sumSquare))
MaterializedTupleRef_V51_0 t_033;t_033.f0 = ( (t_034.f0) - (t_034.f1) );
auto group_hash_000_local_ptr = group_hash_000.localize();
*group_hash_000_local_ptr = __V50_update(*group_hash_000_local_ptr, t_033);
});
});

auto end_19 = walltime();
auto runtime_19 = end_19 - start_19;
VLOG(1)  << "pipeline 19: " << runtime_19 << " s";

VLOG(1)  << "timestamp 19 end " << std::setprecision(15) << end_19;

        
});

// recycle result vectors _temp_table_newchaos
on_all_cores([=] {
    _temp_table_newchaos.data->clear();
});CompletionEvent p_task_20;
spawn(&p_task_20, [=,&p_task_19] {

        p_task_19.wait();
        auto start_20 = walltime();
VLOG(1)  << "timestamp 20 start " << std::setprecision(15) << start_20;

// scan of GrappaGroupBy(; MAX($0))[GrappaApply(_COLUMN0_=(maxVal - sumSquare))[GrappaApply(maxVal=$1,sumSquare=$3)[GrappaHashJoin(($0 = $2))[GrappaApply(col=$0,maxVal=$1)[GrappaPartitionGroupBy($0; MAX($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]],GrappaApply(col=$0,sumSquare=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]]]]]]

auto t_050_tmp = reduce<
MaterializedTupleRef_V50_0, &__V50_combine
>(group_hash_000);


MaterializedTupleRef_V80_0 t_050;
t_050.f0 = t_050_tmp.f0;



// GrappaStoreTemp(newchaos)[GrappaGroupBy(; MAX($0))[GrappaApply(_COLUMN0_=(maxVal - sumSquare))[GrappaApply(maxVal=$1,sumSquare=$3)[GrappaHashJoin(($0 = $2))[GrappaApply(col=$0,maxVal=$1)[GrappaPartitionGroupBy($0; MAX($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; MAX(value))[GrappaApply(col=$1,value=$2)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]],GrappaApply(col=$0,sumSquare=$1)[GrappaPartitionGroupBy($0; SUM($1))[GrappaShuffle($0)[GrappaPartitionGroupBy(col; SUM($1))[GrappaApply(col=$1,_COLUMN1_=(value * value))[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]]]]]]]]]]
_temp_table_newchaos.data->push_back(t_050);


// putting a wait here satisfies the invariant that inner code depends
// on global synchronization by the pipeline source
V79.wait();

auto end_20 = walltime();
auto runtime_20 = end_20 - start_20;
VLOG(1)  << "pipeline 20: " << runtime_20 << " s";

VLOG(1)  << "timestamp 20 end " << std::setprecision(15) << end_20;

        
});

p_task_16.wait();
p_task_19.wait();
p_task_14.wait();
p_task_20.wait();
p_task_17.wait();
p_task_18.wait();
p_task_15.wait();
// recycle result vectors _temp_table_matA
on_all_cores([=] {
    _temp_table_matA.data->clear();
});CompletionEvent p_task_21;
spawn(&p_task_21, [=] {

        
        auto start_21 = walltime();
VLOG(1)  << "timestamp 21 start " << std::setprecision(15) << start_21;

forall<&V81>( t_051.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0_1_2& t_051) {
// GrappaStoreTemp(matA)[GrappaMemoryScan(symmetric_array, prunedA) [GrappaNullInput(prunedA)]]
_temp_table_matA.data->push_back(t_051);

});
auto end_21 = walltime();
auto runtime_21 = end_21 - start_21;
VLOG(1)  << "pipeline 21: " << runtime_21 << " s";

VLOG(1)  << "timestamp 21 end " << std::setprecision(15) << end_21;

        
});

p_task_21.wait();
CompletionEvent p_task_22;
spawn(&p_task_22, [=] {

        
        auto start_22 = walltime();
VLOG(1)  << "timestamp 22 start " << std::setprecision(15) << start_22;

forall<&V84>( t_054.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_054) {
// GrappaBroadcastCrossProduct RIGHT
on_all_cores([=] {
                  t_055 = t_054;
                   });
                   
});
auto end_22 = walltime();
auto runtime_22 = end_22 - start_22;
VLOG(1)  << "pipeline 22: " << runtime_22 << " s";

VLOG(1)  << "timestamp 22 end " << std::setprecision(15) << end_22;

        
});

CompletionEvent p_task_23;
spawn(&p_task_23, [=] {

        
        auto start_23 = walltime();
VLOG(1)  << "timestamp 23 start " << std::setprecision(15) << start_23;

forall<&V85>( t_056.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_056) {
// GrappaBroadcastCrossProduct RIGHT
on_all_cores([=] {
                  t_057 = t_056;
                   });
                   
});
auto end_23 = walltime();
auto runtime_23 = end_23 - start_23;
VLOG(1)  << "pipeline 23: " << runtime_23 << " s";

VLOG(1)  << "timestamp 23 end " << std::setprecision(15) << end_23;

        
});

CompletionEvent p_task_24;
spawn(&p_task_24, [=,&p_task_22
,&p_task_23] {

        p_task_22.wait();
p_task_23.wait();
        auto start_24 = walltime();
VLOG(1)  << "timestamp 24 start " << std::setprecision(15) << start_24;

forall<&V86>( t_058.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_058) {
// GrappaBroadcastCrossProduct LEFT

            MaterializedTupleRef_V87_0_1 t_059 =
              create_V88(t_058, t_057);
              // GrappaBroadcastCrossProduct LEFT

            MaterializedTupleRef_V89_0_1_2 t_060 =
              create_V90(t_059, t_055);
              // GrappaApply(_COLUMN0_=(($1 - $0) > $2))
MaterializedTupleRef_V83_0 t_053;t_053.f0 = ( (( (t_060.f1) - (t_060.f0) )) > (t_060.f2) );
auto group_hash_001_local_ptr = group_hash_001.localize();
*group_hash_001_local_ptr = __V82_update(*group_hash_001_local_ptr, t_053);
});
auto end_24 = walltime();
auto runtime_24 = end_24 - start_24;
VLOG(1)  << "pipeline 24: " << runtime_24 << " s";

VLOG(1)  << "timestamp 24 end " << std::setprecision(15) << end_24;

        
});

CompletionEvent p_task_25;
spawn(&p_task_25, [=,&p_task_24] {

        p_task_24.wait();
        auto start_25 = walltime();
VLOG(1)  << "timestamp 25 start " << std::setprecision(15) << start_25;

// scan of GrappaGroupBy(; COUNT($0))[GrappaApply(_COLUMN0_=(($1 - $0) > $2))[GrappaBroadcastCrossProduct[GrappaBroadcastCrossProduct[GrappaMemoryScan(symmetric_array, newchaos) [GrappaNullInput(newchaos)],GrappaMemoryScan(symmetric_array, oldchaos) [GrappaNullInput(oldchaos)]],GrappaMemoryScan(symmetric_array, epsilon) [GrappaNullInput(epsilon)]]]]

auto t_061_tmp = reduce<
MaterializedTupleRef_V82_0, &__V82_combine
>(group_hash_001);


MaterializedTupleRef_V92_0 t_061;
t_061.f0 = t_061_tmp.f0;



found = (t_061.f0 > 0);
        

// putting a wait here satisfies the invariant that inner code depends
// on global synchronization by the pipeline source
V91.wait();

auto end_25 = walltime();
auto runtime_25 = end_25 - start_25;
VLOG(1)  << "pipeline 25: " << runtime_25 << " s";

VLOG(1)  << "timestamp 25 end " << std::setprecision(15) << end_25;

        
});

p_task_22.wait();
p_task_25.wait();
p_task_23.wait();
p_task_24.wait();
} while (found);
CompletionEvent p_task_26;
spawn(&p_task_26, [=] {

        
        auto start_26 = walltime();
VLOG(1)  << "timestamp 26 start " << std::setprecision(15) << start_26;

forall<&V93>( t_062.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_062) {
result.push_back(t_062);
VLOG(2) << t_062;

});
auto end_26 = walltime();
auto runtime_26 = end_26 - start_26;
VLOG(1)  << "pipeline 26: " << runtime_26 << " s";

VLOG(1)  << "timestamp 26 end " << std::setprecision(15) << end_26;

        
});

p_task_26.wait();
auto end_V95 = walltime();
Grappa::Metrics::stop_tracing();
auto runtime_V95 = end_V95 - start_V95;

in_memory_runtime += runtime_V95;
VLOG(1) << "pipeline group V95: " << runtime_V95 << " s";


    // since reset the stats after scan, need to set these again
    scan_runtime = saved_scan_runtime;
    init_runtime = saved_init_runtime;
}


int main(int argc, char** argv) {
    init(&argc, &argv);

    run([] {

    init();
double start = Grappa::walltime();
    	query();
      double end = Grappa::walltime();
      query_runtime = end - start;
      on_all_cores([] { emit_count = result.size(); });
      Metrics::merge_and_print();
    });

    finalize();
    return 0;
}