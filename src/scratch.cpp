// distance computation test
//   auto_array_ptr<t_float> mindist(N-1); // distances to the nearest neighbors
//  for (i=0; i<N-1; ++i) {
//     min = std::numeric_limits<t_float>::infinity();
//     t_index j, idx = i+1;
//     t_float tmp;
//     for (j=i+1; j<N; ++j) {
//       tmp = dist.ward2(i,j);
//       // tmp = distComputer.dist(i,j);
//       if (tmp<min) {
//         min = tmp;
//         idx = j;
//       }
//     }
//     mindist[i] = min;
//     }
// #ifdef TIMING
//   std::cout << "debug init: "<<t.next() << std::endl;;
//   std::cout << mindist[3]<< std::endl;
// #endif
t_float pointDistSq(t_float * const p, t_float * const q, std::ptrdiff_t dim) {
  float_t xx=0;
  for (t_index i=0; i<dim; ++i){t_float diff = (p[i]-q[i]); xx += diff * diff;}
  return xx;
} 


struct AvgComputer{
  t_float * vars;
  t_index * sizes;
  t_float * centers;
  int dim;
  int count = 0;

  AvgComputer(t_index * const _members, t_float * const Data, int _dim, t_index n):
   sizes(_members), dim(_dim){
    vars = (t_float *)malloc(n * sizeof(t_float));
    for(t_index i=0; i<n;++i){
      vars[i] = 0;
    }

    centers = (t_float *)malloc(n * dim * sizeof(t_float));
    for(t_index i=0; i<n*dim;++i){
      centers[i] = Data[i];
    }
    count = 0;
  }

  inline double dist(t_index idx1, t_index idx2){
    count++;
    // return sqrt(pointDistSq(centers + (idx1 * dim) , centers + (idx2 * dim), dim) + vars[idx1] + vars[idx2]);
    return pointDistSq(centers + (idx1 * dim) , centers + (idx2 * dim), dim) + vars[idx1] + vars[idx2];

  }
      inline double dist_init(t_index idx1, t_index idx2){
    count++;
    // return sqrt(2*(ni*nj)*pointDistSq(centers + (idx1 * dim) , centers + (idx2 * dim), dim)/(ni + nj));
    return pointDistSq(centers + (idx1 * dim) , centers + (idx2 * dim), dim);
  }

  void merge_inplace(const t_index i, const t_index j) const {
    t_float const * const Pi = centers+i*dim;
    t_float * const Pj = centers+j*dim;
    t_float newCenter[dim];
    for(t_index k=0; k<dim; ++k) {
      newCenter[k] = (Pi[k]*static_cast<t_float>(sizes[i]) +
               Pj[k]*static_cast<t_float>(sizes[j])) /
        static_cast<t_float>(sizes[i]+sizes[j]);
    }

    vars[j] = sizes[i] * pointDistSq(centers + (i * dim) , newCenter, dim) + \
          sizes[j] * pointDistSq(centers + (j * dim) , newCenter, dim) + \
          sizes[i] * vars[i] + sizes[j] * vars[j]; 
    vars[j] /= static_cast<t_float>(sizes[i]+sizes[j]);

    for(t_index k=0; k<dim; ++k) {
      Pj[k] = newCenter[k];
    }

    sizes[j] += sizes[i];
  }

  ~AvgComputer(){
    free(vars);
    free(centers);
  }
};

struct WardComputer{
  t_index * sizes;
  t_float * centers;
  int dim;
  std::ptrdiff_t dim2; 
  int count = 0;

  WardComputer(t_index * const _members, t_float * const Data, int _dim, t_index n):
  sizes(_members), dim(_dim){
    centers = (t_float *)malloc(n * dim * sizeof(t_float));
    for(t_index i=0; i<n*dim;++i){
      centers[i] = Data[i];
    }
    dim2 = dim;
    count = 0;
  }

  t_float pointDistSq2(const t_index i, const t_index j) const {
  float_t xx=0;
      t_float const * p = centers+i*dim2;
    t_float const * q = centers+j*dim2;
  for (t_index i=0; i<dim2; ++i){t_float diff = (p[i]-q[i]); xx += diff * diff;}
  return xx;
} 


  inline t_float dist(const t_index idx1, const t_index idx2){
    count++;
    t_float ni = static_cast<t_float>(sizes[idx1]); 
    t_float nj = static_cast<t_float>(sizes[idx2]);
    // return sqrt(2*(ni*nj)*pointDistSq(centers + (idx1 * dim) , centers + (idx2 * dim), dim)/(ni + nj));
    return 2*(ni*nj)*pointDistSq(centers + (idx1 * dim) , centers + (idx2 * dim), dim)/(ni + nj);
  }

    inline t_float dist_init(const t_index idx1, const t_index idx2){
    count++;
    // return sqrt(2*(ni*nj)*pointDistSq(centers + (idx1 * dim) , centers + (idx2 * dim), dim)/(ni + nj));
    return pointDistSq2(idx1 , idx2);
  }


  void merge_inplace(const t_index i, const t_index j) const {
    t_float const * const Pi = centers+i*dim;
    t_float * const Pj = centers+j*dim;
    for(t_index k=0; k<dim; ++k) {
      Pj[k] = (Pi[k]*static_cast<t_float>(sizes[i]) +
               Pj[k]*static_cast<t_float>(sizes[j])) /
        static_cast<t_float>(sizes[i]+sizes[j]);
    }
    sizes[j] += sizes[i];
  }

  ~WardComputer(){
    free(centers);
  }
};