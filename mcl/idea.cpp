

struct aligned_bool {
  bool found;
} GRAPPA_BLOCK_ALIGNED;
aligned_bool combine_bools(aligned_bool& b1, aligned_bool& b2) {
  return aligned_bool(b1.found || b2.found);
}

template<typename T>
bool test(Relation<T> r) {
  auto found = symmetric_global_alloc<aligned_bool>();
  on_all_cores([=] {
    found->found = false;
  });


  forall(r.data, [=](T& tuple) {
    found->found = true; 
  });
   
  return reduce<aligned_bool, &combine_bools>(found).found;
} 
