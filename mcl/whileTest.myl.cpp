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
    
        int64_t f0;
    

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
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V1_0(const std::tuple<
        
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
    
        int64_t f0;
    

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
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V2_0(const std::tuple<
        
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

MaterializedTupleRef_V2_0 t_001;
Relation<aligned_vector<MaterializedTupleRef_V1_0>> _temp_table_i;

bool found;
          // can be just the necessary schema
  class MaterializedTupleRef_V3_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    

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
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V3_0(const std::tuple<
        
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

GlobalCompletionEvent V4(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_1_gce_incomplete, [] {
  return V4.incomplete();
});
Relation<aligned_vector<MaterializedTupleRef_V3_0>> _temp_table_i;

          // can be just the necessary schema
  class MaterializedTupleRef_V5_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    

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
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V5_0(const std::tuple<
        
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

    
  } GRAPPA_BLOCK_ALIGNED;

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V5_0& t) {
    return t.dump(o);
  }

GlobalCompletionEvent V6(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_2_gce_incomplete, [] {
  return V6.incomplete();
});
MaterializedTupleRef_V5_0 __V5_update(const MaterializedTupleRef_V5_0& state, const MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_005) {
    
    auto _v0 = Aggregates::COUNT<int64_t, int64_t>(state.f0,t_005.f0);
    
    return MaterializedTupleRef_V5_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V5_0 __V5_init() {
    
    auto _v0 = Aggregates::Zero<int64_t>();
    

    return MaterializedTupleRef_V5_0( std::make_tuple(_v0) );
}
MaterializedTupleRef_V5_0 __V5_combine(const MaterializedTupleRef_V5_0& state0, const MaterializedTupleRef_V5_0& state1) {
    
    auto _v0 = Aggregates::SUM<int64_t, int64_t>(state0.f0,state1.f0);
    
    return MaterializedTupleRef_V5_0(std::make_tuple(_v0));
}
GlobalCompletionEvent V7(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_3_gce_incomplete, [] {
  return V7.incomplete();
});
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

GlobalCompletionEvent V9(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_4_gce_incomplete, [] {
  return V9.incomplete();
});
std::vector<MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0> result;


StringIndex string_index;
void init( ) {
}

void query() {
    double start, end;
    double saved_scan_runtime = 0, saved_init_runtime = 0;
    start = walltime();

     {
    decltype(_temp_table_i) l__temp_table_i;
    l__temp_table_i.data = Grappa::symmetric_global_alloc<aligned_vector<T>>();
    l__temp_table_i.numtuples = 0; // starts empty, but it could get filled
                           // Often we may not want to bother counting, so this
                           // field may become incoherent.

    // make it available everywhere
    on_all_cores([=] {
        _temp_table_i = l__temp_table_i;
    });
}
auto group_hash_000 = symmetric_global_alloc<MaterializedTupleRef_V5_0>();

    end = walltime();
    init_runtime += (end-start);
    saved_init_runtime += (end-start);

    Grappa::Metrics::reset();
Grappa::Metrics::reset();

auto start_V10 = walltime();

auto end_V10 = walltime();

auto runtime_V10 = end_V10 - start_V10;

saved_scan_runtime += runtime_V10;
VLOG(1) << "pipeline group V10: " << runtime_V10 << " s";
Grappa::Metrics::reset();
Grappa::Metrics::reset();
Grappa::Metrics::start_tracing();
auto start_V11 = walltime();
// Compiled subplan for GrappaSequence[GrappaStoreTemp(i)[GrappaApply(_COLUMN0_=4)[SingletonRelation]],GrappaDoWhile[GrappaStoreTemp(i)[GrappaApply(_COLUMN0_=($0 - 1))[GrappaMemoryScan(symmetric_array, i) [GrappaNullInput(i)]]],GrappaTest[GrappaGroupBy(; COUNT($0))[GrappaSelect(($0 > 0))[GrappaMemoryScan(symmetric_array, i) [GrappaNullInput(i)]]]]],GrappaStore(public:adhoc:OUTPUT)[GrappaMemoryScan(symmetric_array, i) [GrappaNullInput(i)]]]

// recycle result vectors _temp_table_i
on_all_cores([=] {
    _temp_table_i.data->clear();
});CompletionEvent p_task_0;
spawn(&p_task_0, [=] {

        
        auto start_0 = walltime();
VLOG(1)  << "timestamp 0 start " << std::setprecision(15) << start_0;

// GrappaApply(_COLUMN0_=4)
MaterializedTupleRef_V1_0 t_000;t_000.f0 = 4;
// GrappaStoreTemp(i)[GrappaApply(_COLUMN0_=4)[SingletonRelation]]
_temp_table_i.data->push_back(t_000);

auto end_0 = walltime();
auto runtime_0 = end_0 - start_0;
VLOG(1)  << "pipeline 0: " << runtime_0 << " s";

VLOG(1)  << "timestamp 0 end " << std::setprecision(15) << end_0;

        
});

p_task_0.wait();
do {
        found = false;
        
// recycle result vectors _temp_table_i
on_all_cores([=] {
    _temp_table_i.data->clear();
});CompletionEvent p_task_1;
spawn(&p_task_1, [=] {

        
        auto start_1 = walltime();
VLOG(1)  << "timestamp 1 start " << std::setprecision(15) << start_1;

forall<&V4>( t_003.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_003) {
// GrappaApply(_COLUMN0_=($0 - 1))
MaterializedTupleRef_V3_0 t_002;t_002.f0 = ( (t_003.f0) - (1) );
// GrappaStoreTemp(i)[GrappaApply(_COLUMN0_=($0 - 1))[GrappaMemoryScan(symmetric_array, i) [GrappaNullInput(i)]]]
_temp_table_i.data->push_back(t_002);

});
auto end_1 = walltime();
auto runtime_1 = end_1 - start_1;
VLOG(1)  << "pipeline 1: " << runtime_1 << " s";

VLOG(1)  << "timestamp 1 end " << std::setprecision(15) << end_1;

        
});

p_task_1.wait();
CompletionEvent p_task_2;
spawn(&p_task_2, [=] {

        
        auto start_2 = walltime();
VLOG(1)  << "timestamp 2 start " << std::setprecision(15) << start_2;

forall<&V6>( t_005.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_005) {
if (( (t_005.f0) > (0) )) {
  auto group_hash_000_local_ptr = group_hash_000.localize();
*group_hash_000_local_ptr = __V5_update(*group_hash_000_local_ptr, t_005);
}

});
auto end_2 = walltime();
auto runtime_2 = end_2 - start_2;
VLOG(1)  << "pipeline 2: " << runtime_2 << " s";

VLOG(1)  << "timestamp 2 end " << std::setprecision(15) << end_2;

        
});

CompletionEvent p_task_3;
spawn(&p_task_3, [=,&p_task_2] {

        p_task_2.wait();
        auto start_3 = walltime();
VLOG(1)  << "timestamp 3 start " << std::setprecision(15) << start_3;

// scan of GrappaGroupBy(; COUNT($0))[GrappaSelect(($0 > 0))[GrappaMemoryScan(symmetric_array, i) [GrappaNullInput(i)]]]

auto t_006_tmp = reduce<
MaterializedTupleRef_V5_0, &__V5_combine
>(group_hash_000);


MaterializedTupleRef_V8_0 t_006;
t_006.f0 = t_006_tmp.f0;



found = (t_006.f0 > 0);
        

// putting a wait here satisfies the invariant that inner code depends
// on global synchronization by the pipeline source
V7.wait();

auto end_3 = walltime();
auto runtime_3 = end_3 - start_3;
VLOG(1)  << "pipeline 3: " << runtime_3 << " s";

VLOG(1)  << "timestamp 3 end " << std::setprecision(15) << end_3;

        
});

p_task_2.wait();
p_task_3.wait();
} while (found);
CompletionEvent p_task_4;
spawn(&p_task_4, [=] {

        
        auto start_4 = walltime();
VLOG(1)  << "timestamp 4 start " << std::setprecision(15) << start_4;

forall<&V9>( t_007.data, [=](MaterializedTupleRef_FAKE_FROM_GRAPPA_NULL_0& t_007) {
result.push_back(t_007);
VLOG(2) << t_007;

});
auto end_4 = walltime();
auto runtime_4 = end_4 - start_4;
VLOG(1)  << "pipeline 4: " << runtime_4 << " s";

VLOG(1)  << "timestamp 4 end " << std::setprecision(15) << end_4;

        
});

p_task_4.wait();
auto end_V11 = walltime();
Grappa::Metrics::stop_tracing();
auto runtime_V11 = end_V11 - start_V11;

in_memory_runtime += runtime_V11;
VLOG(1) << "pipeline group V11: " << runtime_V11 << " s";


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