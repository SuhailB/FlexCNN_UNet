#ifndef INTERVAL_H_
#define INTERVAL_H_

#include"vertex_attr.hpp"
#include<memory>
#include<string>
#include<cassert>
#include<cstring>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

// template <class T>
class Interval
{
public:

  /* 
   * nvid : number of total vertices to load
   * interval_id : save a unique identifier for the interval
   * base : load the interval from a immutable base interval with all vertices set to defaults
   */
  Interval(const VID_t offset, VID_t nvid, int interval_id, std::string base, bool mmap_=false) :
    in_mem_(false),inmem_ptr0_(nullptr),unmap_(false), active_(false), base_(base), fn_(base),
    nvid_(nvid), offset_(offset), interval_id_(interval_id), mmap_(mmap_)
  {
      assert(nvid <= MAX_INTERVAL_VERTICES);
      mmap_length_ = sizeof(VertexAttr) * nvid_;
  } 

  Interval(Interval&& m):
      in_mem_(m.in_mem_),
      inmem_ptr0_(m.inmem_ptr0_),
      mmap_ptr_(m.mmap_ptr_),
      mmap_length_(m.mmap_length_),
      unmap_(m.unmap_),
      offset_(m.offset_),
      nvid_(m.nvid_) //, heap_(nullptr)

  {
      m.unmap_ = false;
  }

  Interval& operator=(Interval&& m)
  {
      if(unmap_)  /// Should never be used
      {
          assert(munmap(mmap_ptr_,mmap_length_)==0);
      }
      in_mem_ = m.in_mem_;
      inmem_ptr0_ = m.inmem_ptr0_;
      mmap_ptr_ = m.mmap_ptr_;
      mmap_length_ = m.mmap_length_;
      unmap_ = m.unmap_;
      offset_ = m.offset_;
      nvid_ = m.nvid_;
       //heap_ = m.heap_;
      m.unmap_ = false;
      return *this;
  }

  ~Interval()
  {
    // if its mmap strategy and is currently needs to be unmapped
    if(unmap_ && mmap_) {
      assert(munmap(mmap_ptr_,mmap_length_)==0);
    } else { 
      if (in_mem_) {
        free(inmem_ptr0_);
      }
    }

#ifdef LOG_FULL
    cout << "~Interval base " << base_ << " fn " << fn_ << endl;
#endif

    // don't delete the original file protect if haven't written yet
    if (exists(fn_) && (base_ != fn_)) {
      remove(fn_); 
      assert(!exists(fn_));
#ifdef LOG_FULL
      cout << "~Interval deleted fn " << fn_ << endl;
#endif
    }
  }

  void LoadFromDisk()
  {
    assert(!in_mem_);
    in_mem_ = true; // count mmap and user-space buffer as in memory
    if (mmap_) {
      int fd;
#ifdef LOG_FULL
      cout << "mmap() fn: " << fn_ << endl;
#endif
      assert((fd = open(fn_.c_str(), O_RDWR)) != -1);
      assert((mmap_ptr_ = mmap(nullptr,mmap_length_,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0))!=MAP_FAILED);
      assert(close(fd) != 1); // mmap increments the files ref counter, munmap will decrement so we can safely close
      unmap_ = true;
    } else {
      inmem_ptr0_ = (VertexAttr*) malloc(mmap_length_);
#ifdef LOG_FULL
      cout << "LoadFromDisk() fn: " << fn_ << endl;
#endif
      assert(exists(fn_));
      std::ifstream ifile(fn_, ios::in | ios::binary); // ifstream is default read only mode
      // open input
      assert(ifile.is_open());
      assert(ifile.good());

      // read only needed Vertexes
      ifile.read((char*)inmem_ptr0_, mmap_length_);

      // close file 
      ifile.close();
    }
  }

  void Release()
  {
    assert(in_mem_);
    in_mem_ = false;
#ifdef LOG_FULL
    cout << "Release ";
#endif

    if (mmap_ && unmap_) {
      assert(munmap(mmap_ptr_,mmap_length_)==0);
#ifdef LOG_FULL
      cout << "unmapped fn: " << fn_ << endl;
#endif
    } else {
      free(inmem_ptr0_);
#ifdef LOG_FULL
      cout << "freed from user-space memory fn: " << fn_ << endl;
#endif
    }
  }

  /* changes the default fn_ (originally base_) to a unique
   * binary file in the binaries directory
   * This new binary file will be deleted upon ~Interval
   */
  void SaveToDisk()
  {
    assert(in_mem_);
    in_mem_ = false;
    // open output
    // output is now specific to the interval
    fn_ = get_curr() + "/interval" + std::to_string(interval_id_) + ".bin";
#ifdef LOG_FULL
    cout << "SaveToDisk() fn: " << fn_ << endl;
#endif
    std::ofstream ofile(fn_, ios::out | ios::binary); // read-mode
    assert(ofile.is_open());
    assert(ofile.good());

    // write struct array to file 
    if (mmap_) {
      ofile.write((char*)mmap_ptr_, mmap_length_); 
      assert(unmap_);
      assert(munmap(mmap_ptr_,mmap_length_)==0);
      unmap_ = false;
    } else {
      ofile.write((char*)inmem_ptr0_, mmap_length_); 
    }
    assert(ofile.good());

    // close file 
    ofile.close();

    free(inmem_ptr0_);
  }

  // treat mmap'd as in memory
  inline bool IsInMemory() const {return in_mem_;};
  inline VID_t GetNVertices() const {return nvid_;}

  inline VertexAttr* GetData() {
    assert(in_mem_);
    if (mmap_) {
      assert(unmap_);
      return (VertexAttr*) mmap_ptr_;
    } else {
      return inmem_ptr0_;
    }
  }

  // GetOffset not currently checked in recut
  inline VID_t GetOffset() const {return offset_;}
  // IsActive not currently checked in recut
  inline bool IsActive() const {return active_;}
  inline void SetActive(bool active) {active_ = active;}
  inline std::string GetFn() {return fn_;}

private:
  bool in_mem_;   /// Use mmap if in_mem_, use vector otherwise
  VertexAttr* inmem_ptr0_;
  void* mmap_ptr_;
  atomic<bool> active_;
  bool mmap_;
  size_t mmap_length_;
  bool unmap_;    /// Whether should call munmap on destructor
  VID_t offset_; // cont id of first element in interval
  VID_t nvid_;
  std::string fn_;
  std::string base_;
  int interval_id_;
};
#endif//INTERVAL_H_
