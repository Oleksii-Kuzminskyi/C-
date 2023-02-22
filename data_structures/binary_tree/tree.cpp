#include "tree.h"

tree::tree()
{
  value = 0;
  empty = true;
  left = right = nullptr;
}

tree::tree(int val)
{
  value = val;
  empty = false;
  left = right = nullptr;
}

tree::tree(const tree & obj)
{
  if (obj.empty)
  {
    value = 0;
    empty = true;
    left = right = nullptr;
  }
  else
  {
    empty = false;

    if (obj.left != nullptr) left = new tree(*obj.left);

    value = obj.value;

    if (obj.right != nullptr) right = new tree(*obj.right);
  }

}

tree::tree(tree && obj)
{
  if (obj.empty)
  {
    empty = true;
    left = right = nullptr;
  }
  else
  {
    empty = false;

    if (obj.left != nullptr)
    {
      left = obj.left;
      obj.left = nullptr;
    }
    if (obj.right != nullptr)
    {
      right = obj.right;
      obj.right = nullptr;
    }

    value = obj.value;
    obj.empty = true;
  }
}

tree::~tree()
{
  if (left != nullptr) left->~tree();
  if (right != nullptr) right->~tree();
}

tree & tree::operator=(const tree & obj)
{
  if (obj.empty) return *this;
  else
  {
    if (empty)
    {
      empty = false;
      if (obj.left != nullptr) left = new tree(*obj.left);
      value = obj.value;
      if (obj.right != nullptr) right = new tree(*obj.right);
    }
    else
    {
      this->clear();
      empty = false;
      if (obj.left != nullptr) left = new tree(*obj.left);
      value = obj.value;
      if (obj.right != nullptr) right = new tree(*obj.right);
    }
  }
  return *this;
}

tree & tree::operator=(tree && obj)
{
  if (obj.empty) return *this;
  else
  {
    if (empty)
    {
      empty = false;
      if (obj.left != nullptr)
      {
        left = obj.left;
        obj.left = nullptr;
      }
      if (obj.right != nullptr)
      {
        right = obj.right;
        obj.right = nullptr;
      }
      value = obj.value;
      obj.empty = true;
    }
    else
    {
      this->clear();
      empty = false;
      if (obj.left != nullptr)
      {
        left = obj.left;
        obj.left = nullptr;
      }
      if (obj.right != nullptr)
      {
        right = obj.right;
        obj.right = nullptr;
      }
      value = obj.value;
      obj.empty = true;
    }
  }

  return *this;
}

tree operator+(const tree & t1, const tree & t2)
{
  tree result(t1);
  result.join(t2);

  return result;
}

void tree::insert(const int element)
{
  if (empty)
  {
    value = element;
    empty = false;
  }
  else
  {
    if (element > value)
    {
      if (right == nullptr) right = new tree(element);
      else right->insert(element);
    }
    else if (element < value)
    {
      if (left == nullptr) left = new tree(element);
      else left->insert(element);
    }
    else if (element == value) return;
  }

}

tree::state tree::remove(const int element)
{
  /*
   * even if we find the desired element,
   * we need to peek what's going on beyond it;
   * this variable will sygnalize us besides
   * presence/absence of element, if the element
   * is leaf/has one child/has two children
   */
  state mode;

  /*
   * to check if removal element is prime root
   * (see further steps). We increse this variable
   * every time we recursively jump in 'remove()' method
   */
  static int transition = 0;


  if (empty)
  {
    mode = FAILURE;
    return mode;
  }

  if (element < value && left != nullptr)
  {
    ++transition;
    mode = left->remove(element);
    --transition;

    switch(mode)
    {
      case NO_CHILD :
        left->~tree();
        left = nullptr;
        break;
      case ONE_CHILD :
        if (left->left != nullptr)
        {
          tree * buf = left->left;
          left->left = nullptr;
          left->~tree();
          left = buf;
          buf = nullptr;
          mode = SUCCESS;
        }
        else
        {
          tree * buf = left->right;
          left->right = nullptr;
          left->~tree();
          left = buf;
          buf = nullptr;
          mode = SUCCESS;
        }
        break;
      case TWO_CHILD :
        int min = left->right->min();

        if (min == left->right->value)
        {
          tree * buf = left->right->right;
          left->right->right = nullptr;
          left->right->~tree();
          left->right = buf;
          buf = nullptr;
        }
        else
        {
          ++transition;
          left->right->remove(min);
          --transition;
        }

        left->value = min;
        mode = SUCCESS;
    }

  }

  if (element > value && right != nullptr)
  {
    ++transition;
    mode = right->remove(element);
    --transition;

    switch(mode)
    {
      case NO_CHILD :
        right->~tree();
        right = nullptr;
        break;
      case ONE_CHILD :
        if (right->left != nullptr)
        {
          tree * buf = right->left;
          right->left = nullptr;
          right->~tree();
          right = buf;
          buf = nullptr;
          mode = SUCCESS;
        }
        else
        {
          tree * buf = right->right;
          right->right = nullptr;
          right->~tree();
          right = buf;
          buf = nullptr;
          mode = SUCCESS;
        }
        break;
      case TWO_CHILD :
        int min = right->right->min();

        if (min == right->right->value)
        {
          tree * buf = right->right->right;
          right->right->right = nullptr;
          right->right->~tree();
          right->right = buf;
          buf = nullptr;
        }
        else
        {
          ++transition;
          right->right->remove(min);
          --transition;
        }

        right->value = min;
        mode = SUCCESS;
    }

  }

  if (element == value)
  {
    if (transition == 0)
    {
      if (is_leaf() && mode != SUCCESS)
      {
        value = 0;
        empty = true;
        mode = SUCCESS;
      }
      if (has_only_left_kid() && mode != SUCCESS)
      {
        value = left->value;
        tree * lbuf = left->left;
        tree * rbuf = left->right;
        left->left = left->right = nullptr;
        left->~tree();
        left = lbuf;
        right = rbuf;
        lbuf = rbuf = nullptr;
        mode = SUCCESS;
      }
      if (has_only_right_kid() && mode != SUCCESS)
      {
        value = right->value;
        tree * lbuf = right->left;
        tree * rbuf = right->right;
        right->left = right->right = nullptr;
        right->~tree();
        left = lbuf;
        right = rbuf;
        lbuf = rbuf = nullptr;
        mode = SUCCESS;
      }
      if (has_kids() && mode != SUCCESS)
      {
        int min = right->min();
        if (min == right->value)
        {
          tree * buf = right->right;
          right->right = nullptr;
          right->~tree();
          right = buf;
          buf = nullptr;
        }
        else
        {
          ++transition;
          right->remove(min);
          --transition;
        }

        value = min;
        mode = SUCCESS;
      }
    }
    else
    {
      if (is_leaf()) mode = NO_CHILD;
      if (has_only_left_kid() || has_only_right_kid()) mode = ONE_CHILD;
      if (has_kids()) mode = TWO_CHILD;
    }

  }

  if (element != value) mode = FAILURE;

  return mode;
}

void tree::join(const tree & obj)
{
  if (empty && !obj.empty)
  {
    empty = false;
    if (obj.left != nullptr) left = new tree(*obj.left);
    value = obj.value;
    if (obj.right != nullptr) right = new tree(*obj.right);
  }
  else if (!empty && !obj.empty)
  {
    if (obj.left != nullptr) join(*obj.left);
    if (obj.right != nullptr) join(*obj.right);

    insert(obj.value);
  }
}

void tree::clear()
{
  if (left != nullptr)
  {
    left->clear();
    left->~tree();
  }
  if (right != nullptr)
  {
    right->clear();
    right->~tree();
  }

  value = 0;
  empty = true;
}

unsigned int tree::size() const
{
  unsigned int sum = 0;

  if (!empty)
  {
    ++sum;

    if (left != nullptr) sum += left->size();

    if (right != nullptr) sum += right->size();
  }

  return sum;
}

bool tree::find(const int element) const
{
  bool found = false;

  if (!empty)
  {
    if (element < value && left != nullptr && !found)
    {
      found = left->find(element);
    }
    if (element > value && right != nullptr && !found)
    {
      found = right->find(element);
    }
  }


  return found = (element == value || found)? true : false;
}

int tree::min() const
{
  int min;

  if (left != nullptr) min = left->min();
  else min = value;

  min = (min < value)? min : value;

  return min;
}

int tree::max() const
{
  int max;

  if (right != nullptr) max = right->max();
  else max = value;

  max = (max > value)? max : value;

  return max;
}

void tree::print() const
{
  if (empty) return;

  else
  {
    if (left != nullptr) left->print();

    std::cout << value << std::endl;

    if (right != nullptr) right->print();
  }

}






























//
