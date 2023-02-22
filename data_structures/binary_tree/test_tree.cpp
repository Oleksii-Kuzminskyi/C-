#include <iostream>
#include <utility>

#include "tree.h"

int main()
{
  using std::cout;
  using std::cin;
  using std::endl;

  // uninitialized tree
  tree ninit;
  cout <<"\nContainment of empty tree (size: " << ninit.size() << ")" << endl;
  ninit.print(); // wont't work if there's nothing to print

  // initializing tree with one element
  tree t(12);
  cout << "\nContainment of tree, initialized with one element (size: "
       << t.size() << ")" << endl;
  t.print();

  // inserting elements
  int ar[13] = {5, 15, 3, 7, 13, 17, 1, 9, 14, 20, 8, 11, 18};
  for (auto x : ar) t.insert(x);

  /**this is how t looks like after insertion*************

                          12
                      /       \
                    5          15
                 /   \        /  \
                3     7      13    17
              /        \       \     \
            1          9       14     20
                     /  \            /
                    8   11          18
  /************************************************************/

  cout << "\nContainment of tree, after multiple insertions (size: "
       << t.size() << ")" << endl;
  t.print();

  /*
   * let's see if deletion works correct, by removing the
   * prime root - 12, element with one child - e.g. 7,
   * element with two children - e.g. 15, and a leaf - e.g. 1
   */
  t.remove(12);
  t.remove(7);
  t.remove(15);
  t.remove(1);
  t.remove(999); // won't work with non-existing element

  cout << "\nContainment of tree, after tricky deletion (size: "
       << t.size() << ")" << endl;
  t.print();

  // checking search operations
  cout << "\n";
  cout << "Min: "      << t.min()    << endl;
  cout << "Max: "      << t.max()    << endl;
  cout << "Found 12: " << t.find(12) << endl;
  cout << "Found 20: " << t.find(20) << endl;

  // checking move assignment operator
  tree robber = std::move(t);
  cout << "\nContainment of new tree, created by move semantics (size: "
       << robber.size() << ")" << endl;
  robber.print();

  cout << "\nThe old tree, robbed by previous (size: "
       << t.size() << ")" << endl;
  t.print();

  /*
   * let's interact with another tree,
   * hope you belive me its order and size are correct :)
   */
  int ar1[7] = {25, 19, 10, -5, -10, 6, 16};
  tree t1;
  for (auto x : ar1) t1.insert(x);

  // checking addition operator
  tree sum = std::move(robber + t1);
  cout << "\nContainment of tree, created by adding two trees(size: "
       << sum.size() << ")" << endl;
  sum.print();

  // merging one tree with another
  robber.join(t1);
  cout << "\nContainment of tree, merged with another(size: "
       << robber.size() << ")" << endl;
  robber.print();

  // now flush the values from the tree out
  robber.clear();
  cout << "\nContainment of cleared tree(size: "
       << robber.size() << ")" << endl;
  robber.print();

  return 0;
}
