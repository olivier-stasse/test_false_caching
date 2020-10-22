
#include <iostream>
#include <omp.h>
#include <boost/timer/timer.hpp>

#define BUFFER_SIZE 1024

class TestFalseCaching {

 public:
  const unsigned int num_threads_=8;
  const unsigned int buffer_size_=BUFFER_SIZE;
  const unsigned int num_its_=100000;

  unsigned int nt_;
  
  double In_[BUFFER_SIZE];
  double Out_[BUFFER_SIZE];
    
  TestFalseCaching()
  {
  }
  
  void init_arrays()
  {
    for( int i = 0; i < num_threads_; i++ )
    {
      for( int j = 0; j < buffer_size_; j++ )
      {
        In_[j] = Out_[j] = j;
      }
    }
  }
  
  void one_array()
  {
    std::cout << "One MT" << std::endl;
    init_arrays();
    
    boost::timer::auto_cpu_timer t;
    
    for (unsigned int it_idx=0;
         it_idx<num_its_;
         it_idx++ )
    {
      for( int i = 0; i < num_threads_; i++ )
      {
        for( int j = 0; j < buffer_size_; j++ )
        {
          Out_[j]  =  In_[j] + Out_[j];
        }
      }
    }
  }

  void one_array_8mt()
  {

    std::cout << "8 MT - False caching" << std::endl;    
    init_arrays();
    
    boost::timer::auto_cpu_timer t;
    
    omp_set_num_threads(8);
    for (unsigned int it_idx=0;
         it_idx<num_its_;
         it_idx++ )
    {
#pragma omp parallel for
      for( int i = 0; i < num_threads_; i++ )
      {
        for( int j = 0; j < buffer_size_; j++ )
        {
          Out_[j]  =  In_[j] + Out_[j];
        }
      }
    }
  }

  void subdomain(int istart, int ipoints)
  {
    int i;
    for (i = 0; i < ipoints; i++)
      Out_[istart+i] = In_[istart+i] + Out_[istart+i];
  }
  
  void one_array_8mt_v2()
  {
    std::cout << "8 MT - Spreading of the memory" << std::endl;    
    init_arrays();
    
    boost::timer::auto_cpu_timer t;

    for (unsigned int it_idx=0;
         it_idx<num_its_;
         it_idx++ )
    {
      int iam, nt, ipoints, istart;
#pragma omp parallel default(shared) private(iam,nt,ipoints,istart)
      {
        iam = omp_get_thread_num();
        nt =  omp_get_num_threads();
        nt_ = nt;
        ipoints = buffer_size_ / nt;    /*size of partition*/
        istart = iam*ipoints;  /*starting array index*/
        if (iam == nt-1)     /*last thread may do more*/
          ipoints = buffer_size_ - istart;
        subdomain( istart, ipoints);
      }
    }
  }
  
};

int main()
{

  TestFalseCaching aTFC;
  
  aTFC.one_array();
  aTFC.one_array_8mt();
  aTFC.one_array_8mt_v2();
  std::cout << "Nb of threads: " << aTFC.nt_ << std::endl;
}
