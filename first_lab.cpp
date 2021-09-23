#include <iostream>
#include <set>
#include <random>
#include <bits/stdc++.h>
#include <fstream>


class States{
  public:
   virtual bool contains(int s) const = 0;

};
class DiscreteState: public States {
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    virtual bool contains(int s) const override{
        return s == state;
    }
};


class SegmentState: public States {
private:
    int const beg, end;
  
public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }
    
    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class SetState: public States {
private:
    std::set<int> const states;
    
public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }
    
    bool contains(int s) const {
        return states.count(s) > 0;
    }
};


class SegmentPlsDiscrState: public States{
  private: 
    const SegmentState &ss; 
    const DiscreteState &ds;
  public:
    SegmentPlsDiscrState(const SegmentState &ss,
     const DiscreteState &ds): ss(ss), ds(ds){};

    bool contains(int s) const{
      return ss.contains(s) && ds.contains(s);
    }
};
class SegmentMnsDiscrState: public States{
  private:
    const SegmentState &ss;
    const DiscreteState & ds;
   public:
    SegmentMnsDiscrState(const SegmentState &ss,
     const DiscreteState &ds): ss(ss), ds(ds){};

    bool contains(int s) const{
      return ss.contains(s) && !ds.contains(s);
    }
};
class SegmentPlMnDiscrState: public States{
  private:
    const SegmentState &ss;
    const DiscreteState & ds1;
    const DiscreteState & ds2;
   public:
    SegmentPlMnDiscrState(const SegmentState &ss,
     const DiscreteState &ds1, const DiscreteState &ds2): ss(ss), ds1(ds1), ds2(ds2){};

    bool contains(int s) const{
      return ss.contains(s) && ds1.contains(s) && !ds2.contains(s);
    }
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;
    
public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(States const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        
        return static_cast<float>(good)/static_cast<float>(test_count);
    }

    
    /*float operator()(DiscreteState const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        
        return static_cast<float>(good)/static_cast<float>(test_count);
    }

    float operator()(SegmentState const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        
        return static_cast<float>(good)/static_cast<float>(test_count);
    }
    
    float operator()(SetState const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        
        return static_cast<float>(good)/static_cast<float>(test_count);
    }*/
};

int main(int argc, const char * argv[]) {
    std::ofstream out("output.txt");
    std::ofstream out2("output2.txt");
    const int seed = 10;
    int num_of_tests, test_min, test_max;
    DiscreteState d(1);
    SegmentState st(0,5);
    SetState ss({1, 3, 5, 7, 9, 11});
    out<< "y = [";
    /*for(long long i = 10; i < 1e7; i *= 2){
      ProbabilityTest pt(seed, 0, 11, i);
      out << pt(ss) << ", "; 
      out2 << i << ", ";
    }*/
    /*for(long long i = 1; i < 100; i += 10){
      ProbabilityTest pt(seed, 0, 100, 1e6);
      SegmentState s(0, i);
      out << pt(s) << ", "; 
      out2 << i << ", ";
    }*/
    /*for(int i = 1; i < 90; i += 10){
      ProbabilityTest pt(seed, 1, 100, 1e7);
      SegmentState s(i, i+10);
      out << pt(s) << ", "; 
      out2 << i << ", ";
    }*/
    for(int i = 0; i < 89; i += 10)
    {
      SetState sk({1 + i, 3 + i, 5 + i, 7 + i, 9 + i, 11 + i});
      ProbabilityTest pt(seed, 1, 100, 1e7);
      out << pt(sk) << ", ";
      out2 << i << ", ";
    }
    out << "]" << std::endl;
    out2 << "]" << std::endl;
    
    ProbabilityTest pt(seed, 0, 100, 100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(st) << std::endl;
    std::cout << pt(ss) << std::endl;
    return 0;
}

//Как зависит вероятность от количества тестов?
//Как зависит вероятность от размера промежутка?
//Зависит ли вероятность от расположения промежутка или же только от его размера?
 
