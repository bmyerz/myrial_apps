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
  class MaterializedTupleRef_V1_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V1_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V1_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V1_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V1_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V1_0));
    //}
    MaterializedTupleRef_V1_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V1_0(const std::tuple<
        
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
    //MaterializedTupleRef_V1_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V1_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V1_0 _ret;

        
            
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
    //MaterializedTupleRef_V1_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V1_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V1_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V1_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V1_0& t) {
    return t.dump(o);
  }

          // can be just the necessary schema
  class MaterializedTupleRef_V2_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        double f0;
    

    static constexpr int numFields() {
      return 1;
    }

    // size of all fields in struct removing only end padding
    static size_t fieldsSize() {
        const MaterializedTupleRef_V2_0 _t;
        return

        
            sizeof(_t.f0);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V2_0 _t;

        
        std::cout << _t.fieldsSize() << std::endl;
        


    }

    MaterializedTupleRef_V2_0 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V2_0 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V2_0));
    //}
    MaterializedTupleRef_V2_0 (
                               const double& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V2_0(const std::tuple<
        
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
    //MaterializedTupleRef_V2_0 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V2_0 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V2_0 _ret;

        
            
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
    //MaterializedTupleRef_V2_0 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V2_0::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V2_0 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V2_0::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //}

    std::ostream& dump(std::ostream& o) const {
      o << "Materialized(";

      
        o << f0 << ",";
      

      o << ")";
      return o;
    }

    
  } ;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V2_0& t) {
    return t.dump(o);
  }

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

MaterializedTupleRef_V3_0 t_002;
MaterializedTupleRef_V2_0 t_003;
          // can be just the necessary schema
  class MaterializedTupleRef_V4_0_1_2 {
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
        const MaterializedTupleRef_V4_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V4_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V4_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V4_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V4_0_1_2));
    //}
    MaterializedTupleRef_V4_0_1_2 (
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

    
    


    MaterializedTupleRef_V4_0_1_2(const std::tuple<
        
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
    //MaterializedTupleRef_V4_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V4_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V4_0_1_2 _ret;

        
            
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
    //MaterializedTupleRef_V4_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V4_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V4_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V4_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
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

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V4_0_1_2& t) {
    return t.dump(o);
  }

Relation<MaterializedTupleRef_V4_0_1_2> V4;

GlobalCompletionEvent V5(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_2_gce_incomplete, [] {
  return V5.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V6_0_1_2_3 {
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
        const MaterializedTupleRef_V6_0_1_2_3 _t;
        return

        
            ((char*)&_t.f3) + sizeof(_t.f3) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V6_0_1_2_3 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (((char*)&_t.f3) - ((char*)&_t.f2)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f2) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V6_0_1_2_3 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V6_0_1_2_3 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V6_0_1_2_3));
    //}
    MaterializedTupleRef_V6_0_1_2_3 (
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

    
    


    MaterializedTupleRef_V6_0_1_2_3(const std::tuple<
        
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
    //MaterializedTupleRef_V6_0_1_2_3 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
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
    static MaterializedTupleRef_V6_0_1_2_3 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V6_0_1_2_3 _ret;

        
            
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
    //MaterializedTupleRef_V6_0_1_2_3 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V6_0_1_2_3::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V6_0_1_2_3 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V6_0_1_2_3::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
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

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V6_0_1_2_3& t) {
    return t.dump(o);
  }

static MaterializedTupleRef_V6_0_1_2_3 create_V7(const MaterializedTupleRef_V4_0_1_2& t1, const MaterializedTupleRef_V2_0& t2) {
    MaterializedTupleRef_V6_0_1_2_3 t;
    
        t.f0 = t1.f0;
    
        t.f1 = t1.f1;
    
        t.f2 = t1.f2;
    

    
        t.f3 = t2.f0;
    

    return t;
}
std::vector<MaterializedTupleRef_V1_0> result;


StringIndex string_index;
void init( ) {
}

void query() {
    double start, end;
    double saved_scan_runtime = 0, saved_init_runtime = 0;
    start = walltime();

     

    end = walltime();
    init_runtime += (end-start);
    saved_init_runtime += (end-start);

    Grappa::Metrics::reset();
Grappa::Metrics::reset();

auto start_V8 = walltime();

        
        auto start_1 = walltime();
VLOG(1)  << "timestamp 1 start " << std::setprecision(15) << start_1;

{
    if (FLAGS_bin) {
        BinaryRelationFileReader<MaterializedTupleRef_V4_0_1_2> reader;
        V4 = reader.read( FLAGS_input_file_matrix + ".bin" );
    } else if (FLAGS_jsonsplits) {
        SplitsRelationFileReader<JSONRowParser<MaterializedTupleRef_V4_0_1_2,&schema_V4>, MaterializedTupleRef_V4_0_1_2> reader;
        V4 = reader.read( FLAGS_input_file_matrix );
    } else {
        V4.data = readTuples<MaterializedTupleRef_V4_0_1_2>( FLAGS_input_file_matrix, FLAGS_nt);
        V4.numtuples = FLAGS_nt;
        auto l_V4 = V4;
        on_all_cores([=]{ V4 = l_V4; });
    }
}
auto end_1 = walltime();
auto runtime_1 = end_1 - start_1;
VLOG(1)  << "pipeline 1: " << runtime_1 << " s";

VLOG(1)  << "timestamp 1 end " << std::setprecision(15) << end_1;

        
auto end_V8 = walltime();

auto runtime_V8 = end_V8 - start_V8;

saved_scan_runtime += runtime_V8;
VLOG(1) << "pipeline group V8: " << runtime_V8 << " s";
Grappa::Metrics::reset();
Grappa::Metrics::reset();
Grappa::Metrics::start_tracing();
auto start_V9 = walltime();
// Compiled subplan for GrappaStore(public:adhoc:OUTPUT)[GrappaApply(_COLUMN0_=($3 * value))[GrappaBroadcastCrossProduct[GrappaMemoryScan(global_array, None) [GrappaFileScan(public:adhoc:matrix)],GrappaApply(_COLUMN0_=0.001)[SingletonRelation]]]]

CompletionEvent p_task_0;
spawn(&p_task_0, [=] {

        
        auto start_0 = walltime();
VLOG(1)  << "timestamp 0 start " << std::setprecision(15) << start_0;

// GrappaApply(_COLUMN0_=0.001)
MaterializedTupleRef_V2_0 t_001;t_001.f0 = 0.001;
// GrappaBroadcastCrossProduct RIGHT
on_all_cores([=] {
                  t_003 = t_001;
                   });
                   
auto end_0 = walltime();
auto runtime_0 = end_0 - start_0;
VLOG(1)  << "pipeline 0: " << runtime_0 << " s";

VLOG(1)  << "timestamp 0 end " << std::setprecision(15) << end_0;

        
});

CompletionEvent p_task_2;
spawn(&p_task_2, [=,&p_task_0] {

        p_task_0.wait();
        auto start_2 = walltime();
VLOG(1)  << "timestamp 2 start " << std::setprecision(15) << start_2;

forall<&V5>( t_004.data, t_004.numtuples, [=](int64_t i, MaterializedTupleRef_V4_0_1_2& t_004) {
// GrappaBroadcastCrossProduct LEFT

            MaterializedTupleRef_V6_0_1_2_3 t_005 =
              create_V7(t_004, t_003);
              // GrappaApply(_COLUMN0_=($3 * value))
MaterializedTupleRef_V1_0 t_000;t_000.f0 = ( (t_005.f3) * (t_005.f2) );
result.push_back(t_000);
VLOG(2) << t_000;

});
auto end_2 = walltime();
auto runtime_2 = end_2 - start_2;
VLOG(1)  << "pipeline 2: " << runtime_2 << " s";

VLOG(1)  << "timestamp 2 end " << std::setprecision(15) << end_2;

        
});

auto end_V9 = walltime();
Grappa::Metrics::stop_tracing();
auto runtime_V9 = end_V9 - start_V9;

in_memory_runtime += runtime_V9;
VLOG(1) << "pipeline group V9: " << runtime_V9 << " s";


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