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

    
  } GRAPPA_BLOCK_ALIGNED;

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

          // can be just the necessary schema
  class MaterializedTupleRef_V3_0_1_2 {
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
        const MaterializedTupleRef_V3_0_1_2 _t;
        return

        
            ((char*)&_t.f2) + sizeof(_t.f2) - ((char*)&_t);
         
    }

    // debugging function to get storage sizes
    static void print_representation() {
        const MaterializedTupleRef_V3_0_1_2 _t;

        
        
        std::cout << (((char*)&_t.f1) - ((char*)&_t.f0)) << ",";
        
        std::cout << (((char*)&_t.f2) - ((char*)&_t.f1)) << ",";
        
        std::cout << (_t.fieldsSize() - (((char*)&_t.f1) - ((char*)&_t)));
        std::cout << std::endl;
        


    }

    MaterializedTupleRef_V3_0_1_2 () {
      // no-op
    }

    //template <typename OT>
    //MaterializedTupleRef_V3_0_1_2 (const OT& other) {
    //  std::memcpy(this, &other, sizeof(MaterializedTupleRef_V3_0_1_2));
    //}
    MaterializedTupleRef_V3_0_1_2 (
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

    
    


    MaterializedTupleRef_V3_0_1_2(const std::tuple<
        
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
    //MaterializedTupleRef_V3_0_1_2 (std::vector<int64_t> vals, bool ignore1, bool ignore2) {
    //    
    //        f0 = vals[0];
    //    
    //        f1 = vals[1];
    //    
    //        f2 = vals[2];
    //    
    //}

    // use the tuple schema to interpret the input stream
    static MaterializedTupleRef_V3_0_1_2 fromIStream(std::istream& ss, char delim=' ') {
        MaterializedTupleRef_V3_0_1_2 _ret;

        
            
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
    //MaterializedTupleRef_V3_0_1_2 (const Tuple& v0, const T& from) {
    //    constexpr size_t v0_size = std::tuple_size<Tuple>::value;
    //    constexpr int from_size = T::numFields();
    //    static_assert(MaterializedTupleRef_V3_0_1_2::numFields() == (v0_size + from_size), "constructor only works on same number of total fields");
    //    TupleUtils::assign<0, decltype(_scheme)>(_fields, v0);
    //    std::memcpy(((char*)&_fields)+v0_size*sizeof(int64_t), &(from._fields), from_size*sizeof(int64_t));
    //}

    //template <typename Tuple>
    //MaterializedTupleRef_V3_0_1_2 (const Tuple& v0) {
    //    static_assert(MaterializedTupleRef_V3_0_1_2::numFields() == (std::tuple_size<Tuple>::value), "constructor only works on same number of total fields");
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

  std::ostream& operator<< (std::ostream& o, const MaterializedTupleRef_V3_0_1_2& t) {
    return t.dump(o);
  }

Relation<MaterializedTupleRef_V3_0_1_2> V3;

GlobalCompletionEvent V4(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_1_gce_incomplete, [] {
  return V4.incomplete();
});
MaterializedTupleRef_V1_0 __V1_update(const MaterializedTupleRef_V1_0& state, const MaterializedTupleRef_V2_0& t_001) {
    
    auto _v0 = Aggregates::COUNT<int64_t, int64_t>(state.f0,t_001.f0);
    
    return MaterializedTupleRef_V1_0(std::make_tuple(_v0));
}
MaterializedTupleRef_V1_0 __V1_init() {
    
    auto _v0 = Aggregates::Zero<int64_t>();
    

    return MaterializedTupleRef_V1_0( std::make_tuple(_v0) );
}
MaterializedTupleRef_V1_0 __V1_combine(const MaterializedTupleRef_V1_0& state0, const MaterializedTupleRef_V1_0& state1) {
    
    auto _v0 = Aggregates::SUM<int64_t, int64_t>(state0.f0,state1.f0);
    
    return MaterializedTupleRef_V1_0(std::make_tuple(_v0));
}
GlobalCompletionEvent V5(true);
GRAPPA_DEFINE_METRIC(CallbackMetric<int64_t>, app_2_gce_incomplete, [] {
  return V5.incomplete();
});
          // can be just the necessary schema
  class MaterializedTupleRef_V6_0 {
    // Invariant: data stored in _fields is always in the representation
    // specified by _scheme.

    public:
    
        int64_t f0;
    

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
                               const int64_t& a0
                               
                       
                       ) {
        
            f0 = a0;
        
    }

    
    


    MaterializedTupleRef_V6_0(const std::tuple<
        
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

std::vector<MaterializedTupleRef_V6_0> result;


StringIndex string_index;
void init( ) {
}

void query() {
    double start, end;
    double saved_scan_runtime = 0, saved_init_runtime = 0;
    start = walltime();

     auto group_hash_000 = symmetric_global_alloc<MaterializedTupleRef_V1_0>();

    end = walltime();
    init_runtime += (end-start);
    saved_init_runtime += (end-start);

    Grappa::Metrics::reset();
Grappa::Metrics::reset();

auto start_V7 = walltime();

        
        auto start_0 = walltime();
VLOG(1)  << "timestamp 0 start " << std::setprecision(15) << start_0;

{
    if (FLAGS_bin) {
        BinaryRelationFileReader<MaterializedTupleRef_V3_0_1_2> reader;
        V3 = reader.read( FLAGS_input_file_matrix + ".bin" );
    } else if (FLAGS_jsonsplits) {
        SplitsRelationFileReader<JSONRowParser<MaterializedTupleRef_V3_0_1_2,&schema_V3>, MaterializedTupleRef_V3_0_1_2> reader;
        V3 = reader.read( FLAGS_input_file_matrix );
    } else {
        V3.data = readTuples<MaterializedTupleRef_V3_0_1_2>( FLAGS_input_file_matrix, FLAGS_nt);
        V3.numtuples = FLAGS_nt;
        auto l_V3 = V3;
        on_all_cores([=]{ V3 = l_V3; });
    }
}
auto end_0 = walltime();
auto runtime_0 = end_0 - start_0;
VLOG(1)  << "pipeline 0: " << runtime_0 << " s";

VLOG(1)  << "timestamp 0 end " << std::setprecision(15) << end_0;

        
auto end_V7 = walltime();

auto runtime_V7 = end_V7 - start_V7;

saved_scan_runtime += runtime_V7;
VLOG(1) << "pipeline group V7: " << runtime_V7 << " s";
Grappa::Metrics::reset();
Grappa::Metrics::reset();
Grappa::Metrics::start_tracing();
auto start_V8 = walltime();
// Compiled subplan for GrappaStore(public:adhoc:out)[GrappaGroupBy(; COUNT($0))[GrappaApply(row=$0)[GrappaMemoryScan(global_array, None) [GrappaFileScan(public:adhoc:matrix)]]]]

CompletionEvent p_task_1;
spawn(&p_task_1, [=] {

        
        auto start_1 = walltime();
VLOG(1)  << "timestamp 1 start " << std::setprecision(15) << start_1;

forall<&V4>( t_002.data, t_002.numtuples, [=](int64_t i, MaterializedTupleRef_V3_0_1_2& t_002) {
// GrappaApply(row=$0)
MaterializedTupleRef_V2_0 t_001;t_001.f0 = t_002.f0;
auto group_hash_000_local_ptr = group_hash_000.localize();
*group_hash_000_local_ptr = __V1_update(*group_hash_000_local_ptr, t_001);
});
auto end_1 = walltime();
auto runtime_1 = end_1 - start_1;
VLOG(1)  << "pipeline 1: " << runtime_1 << " s";

VLOG(1)  << "timestamp 1 end " << std::setprecision(15) << end_1;

        
});

CompletionEvent p_task_2;
spawn(&p_task_2, [=,&p_task_1] {

        p_task_1.wait();
        auto start_2 = walltime();
VLOG(1)  << "timestamp 2 start " << std::setprecision(15) << start_2;

// scan of GrappaGroupBy(; COUNT($0))[GrappaApply(row=$0)[GrappaMemoryScan(global_array, None) [GrappaFileScan(public:adhoc:matrix)]]]

auto t_003_tmp = reduce<
MaterializedTupleRef_V1_0, &__V1_combine
>(group_hash_000);


MaterializedTupleRef_V6_0 t_003;
t_003.f0 = t_003_tmp.f0;



result.push_back(t_003);
VLOG(2) << t_003;


// putting a wait here satisfies the invariant that inner code depends
// on global synchronization by the pipeline source
V5.wait();

auto end_2 = walltime();
auto runtime_2 = end_2 - start_2;
VLOG(1)  << "pipeline 2: " << runtime_2 << " s";

VLOG(1)  << "timestamp 2 end " << std::setprecision(15) << end_2;

        
});
p_task_2.wait();
p_task_1.wait();
auto end_V8 = walltime();
Grappa::Metrics::stop_tracing();
auto runtime_V8 = end_V8 - start_V8;

in_memory_runtime += runtime_V8;
VLOG(1) << "pipeline group V8: " << runtime_V8 << " s";


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