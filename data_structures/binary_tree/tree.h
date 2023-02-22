#ifndef TREE_H_
#define TREE_H_

#include <iostream>

class tree;

class tree
{
private:
  int    value;
  tree * left;
  tree * right;
private:
  bool empty;
  enum state
  {
    FAILURE  ,
    NO_CHILD ,
    ONE_CHILD,
    TWO_CHILD,
    SUCCESS  ,
  };
private:
  bool is_leaf() const;
  bool has_only_left_kid() const;
  bool has_only_right_kid() const;
  bool has_kids() const;
public:
  tree();
  explicit tree(int val);
  tree(const tree & obj);
  tree(tree && obj);
  ~tree();
public:
  tree &      operator=(const tree & obj);
  tree &      operator=(tree && obj);
  friend tree operator+(const tree & t1, const tree & t2);
public:
  void        insert(const int element);
  tree::state remove(const int element);
  void        join(const tree & obj);
  void        clear();
public:
  unsigned int size() const;
  bool         find(const int element) const;
  int          min() const;
  int          max() const;
  void         print() const;
};


inline bool tree::is_leaf() const
{
  return (left == nullptr && right == nullptr);
}
inline bool tree::has_only_left_kid() const
{
  return (left != nullptr && right == nullptr);
}
inline bool tree::has_only_right_kid() const
{
  return (left == nullptr && right != nullptr);
}
inline bool tree::has_kids() const
{
  return (left != nullptr && right != nullptr);
}


#endif
